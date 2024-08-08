#ifndef CAMERA_H
#define CAMERA_H

class camera{
public:
    int nx = PIXELS_X;
    int ny = PIXELS_Y;
    double viewport_height;
    double vfov = 27;
    double focal_length = 1;
    int samples_per_pixel = 10;
    int max_depth = 10;
    vec3 v_up= vec3(0, 1, 0);
    vec3 camera_origin = vec3(-3, 3, 1);
    vec3 lookat = vec3(0, 0, -6);
    double roll = 0;
    double defocus_angle = 0;
    double focus_dist = 10;

    void render(const hittable& world, int portion_n);
    // void renderNreflectances(const hittable& world, int n);

private:
    double aspect_ratio, H;
    vec3 camera_u, camera_v, origin, top_left, delta_u, delta_v, top_left_pixel, view_direction;
    colour background_colour;
    double &viewport_width = H;
    double &V = viewport_height;
    vec3 defocus_disk_u, defocus_disk_v;

    void initialise();
    void compute_background_colour(ray const &lightray);
    colour image4shader(ray const &lightray, const hittable& obj);
    colour general_shader(ray const& lightray, hittable const & obj, int depth);
    vec3 defocus_disk_sample() const;
};

/*---------------------------------------------
Definitions of member functions//
---------------------------------------------*/

void camera::initialise(){
    aspect_ratio = double (nx) / ny;
    view_direction = (lookat - camera_origin).unit_vector();
    // focal_length = (lookat - camera_origin).length();

    viewport_height = 2 * tan(degrees_to_radians(vfov) / 2) * focus_dist;
    
    camera_u = viewport_height * aspect_ratio * cross(view_direction, v_up).unit_vector();
    camera_v = viewport_height * cross(camera_u, view_direction).unit_vector();
    origin = vec3(0, 0, 0);
    H = camera_u.length();
    top_left = camera_origin + (-camera_u / 2 + camera_v / 2 + focus_dist * view_direction);

    delta_u = camera_u / nx;
    delta_v = camera_v / ny;
    top_left_pixel = top_left + 0.5 * delta_u + 0.5 * -delta_v;

    double defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = cross(view_direction, v_up).unit_vector() * defocus_radius;
    defocus_disk_v = cross(camera_u, view_direction).unit_vector() * defocus_radius;
}

void camera::compute_background_colour(ray const &lightray) {
    double scaled_y = map(lightray.direction().unit_vector().y(), -1, 1, 0, 1);
    colour background_colour1(1, 1, 1);
    colour background_colour2(0.3, 0.5, 1);
    background_colour = mix_colour(background_colour1, background_colour2, scaled_y);
}

void camera::render(const hittable& world, int portion_n){
    initialise();
    //cout << "P3\n" << nx << " " << ny << "\n255\n";

    ofstream time_data_file;
    time_data_file.open("timedatafile.txt");
    chrono::steady_clock::time_point start_time = chrono::high_resolution_clock::now();

    for (int j = (portion_n - 1) * ny / 10; j < (portion_n) * ny / 10; j++){
        auto time_elapsed = chrono::high_resolution_clock::now() - start_time;
        double double_time_elapsed = time_elapsed.count();
        std::clog << (j + 1) * 100 / ny  << "% Time elapsed: " << double_time_elapsed / 1000000000.0 << "s. Lines completed: " << j + 1 << "/" << ny << endl;

        for (int i = 0; i < nx; i++){
            chrono::steady_clock::time_point begin_pixel_time = chrono::high_resolution_clock::now();

            colour pixel_colour(0, 0, 0);
            for (int n = 0; n < samples_per_pixel; n++){
                vec3 offset = randomdouble(-0.5, +0.5) * delta_u + randomdouble(-0.5, +0.5) * delta_v;
                vec3 ray_origin = (defocus_angle <= 0) ? camera_origin : defocus_disk_sample();
                ray cameraray(ray_origin, top_left_pixel + i * delta_u + j * -delta_v - ray_origin + offset);
                pixel_colour += general_shader(cameraray, world, max_depth);
            }
            pixel_colour /= samples_per_pixel;
            write_colour(pixel_colour);

            time_data_file << (chrono::high_resolution_clock::now() - begin_pixel_time).count() << endl;
        }
    }
    time_data_file.close();
    clog << "Done" << endl;
}

colour camera::general_shader(ray const& lightray, hittable const & obj, int depth){
    bool hit = false;
    hit_record hitrec;

    colour objectcolour(0, 0, 0);
    if (depth > 0){
        if (obj.hit(lightray, interval(0.0001, infinity), hitrec)){
            hit = true;
            ray scattered_ray(vec3(0, 0, 0), vec3(0, 0, 0));
            colour attenuation;
            if (hitrec.mat->scatter(lightray, scattered_ray, hitrec, attenuation)){ 
                return attenuation * general_shader(scattered_ray, obj, depth - 1);
            }
            else {
                //cout << "S" << endl;
                return colour(0, 0, 0);
            }
        }
    }
    else {
        //cout << "M" << endl;
        return colour(0, 0, 0);
    }

    compute_background_colour(lightray);
    return mix_colour(background_colour, objectcolour, hit);
}

colour camera::image4shader(ray const &lightray, const hittable& obj) {
    compute_background_colour(lightray);

    colour objectcolour(0, 0, 0);
    hit_record hitrec;  
    bool hit = false;
    if (obj.hit(lightray, interval(0, infinity), hitrec)) {
        hit = true;
        objectcolour = map(hitrec.normal, interval(-1, 1), interval(0, 1));
    }

    return mix_colour(background_colour, objectcolour, hit);
}

vec3 camera::defocus_disk_sample() const {
    // Returns a random point in the camera defocus disk.
    vec3 p = vector_in_unit_disk();
    return camera_origin + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}


#endif