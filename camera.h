#ifndef CAMERA_H
#define CAMERA_H

class camera{
public:
    int nx = PIXELS_X;
    int ny = PIXELS_Y;
    double viewport_height = 2;
    double focal_length = 4;
    int samples_per_pixel = 10;
    int max_depth = 10;
    float reflectance = 0.5;

    void render(const hittable& world);
    void renderNreflectances(const hittable& world, int n);

private:
    double aspect_ratio, H;
    vec3 horizontal, vertical, origin, top_left, delta_u, delta_v, top_left_pixel;
    colour background_colour;
    double &viewport_width = H;
    double &V = viewport_height;
    double &F = focal_length;

    void initialise();
    void compute_background_colour(ray const &lightray);
    colour image4shader(ray const &lightray, const hittable& obj);
    colour general_shader(ray const& lightray, hittable const & obj, int depth);
};

/*---------------------------------------------
Definitions of member functions//
---------------------------------------------*/

void camera::initialise(){
    aspect_ratio = double (nx) / ny;
    horizontal = vec3(viewport_height * aspect_ratio, 0, 0);
    vertical = vec3(0, viewport_height, 0);
    origin = vec3(0, 0, 0);
    H = horizontal.length();
    top_left = vec3(-H / 2, V / 2, -sqrt(F*F - (V/2)*(V/2) - (H/2)*(H/2)));

    delta_u = vec3(viewport_width / nx, 0, 0);
    delta_v = vec3(0, viewport_height / ny, 0);
    top_left_pixel = top_left + 0.5 * delta_u + 0.5 * -delta_v;
}

void camera::compute_background_colour(ray const &lightray) {
    double scaled_y = map(lightray.direction().unit_vector().y(), -1, 1, 0, 1);
    colour background_colour1(1, 1, 1);
    colour background_colour2(0.3, 0.5, 1);
    background_colour = mix_colour(background_colour1, background_colour2, scaled_y);
}

void camera::render(const hittable& world){
    initialise();
    cout << "P3\n" << nx << " " << ny << "\n255\n";

    for (int j = 0; j < ny; j++){
        for (int i = 0; i < nx; i++){
            colour pixel_colour(0, 0, 0);
            for (int n = 0; n < samples_per_pixel; n++){
                vec3 offset = randomdouble(-0.5, +0.5) * delta_u + randomdouble(-0.5, +0.5) * delta_v;
                ray cameraray(origin, top_left_pixel + i * delta_u + j * -delta_v - origin + offset);
                pixel_colour += general_shader(cameraray, world, max_depth);
            }
            pixel_colour /= samples_per_pixel;
            write_colour(pixel_colour);
        }
    }
}

void camera::renderNreflectances(const hittable& world, int n){
    initialise();
    cout << "P3\n" << nx << " " << ny << "\n255\n";

    for (int j = 0; j < ny; j++){
        for (int i = 0; i < nx; i++){
            colour pixel_colour(0, 0, 0);
            reflectance = 0.1 + int(n * double(i) / nx) / double(n);
            for (int n = 0; n < samples_per_pixel; n++){
                vec3 offset = randomdouble(-0.5, +0.5) * delta_u + randomdouble(-0.5, +0.5) * delta_v;
                ray cameraray(origin, top_left_pixel + i * delta_u + j * -delta_v - origin + offset);
                pixel_colour += general_shader(cameraray, world, max_depth);
            }
            pixel_colour /= samples_per_pixel;
            write_colour(pixel_colour);
        }
    }
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


#endif