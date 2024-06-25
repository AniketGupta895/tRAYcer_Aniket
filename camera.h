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

    void render(const hittable& world){
        initialise();
        cout << "P3\n" << nx << " " << ny << "\n255\n";

        for (int j = 0; j < ny; j++){
            for (int i = 0; i < nx; i++){
                colour pixel_colour(0, 0, 0);
                for (int n = 0; n < samples_per_pixel; n++){
                    vec3 offset = randomdouble(-0.5, +0.5) * delta_u + randomdouble(-0.5, +0.5) * delta_v;
                    ray cameraray(origin, top_left_pixel + i * delta_u + j * -delta_v - origin + offset);
                    pixel_colour += diffuseshader(cameraray, world, max_depth, reflectance);
                }
                pixel_colour /= samples_per_pixel;
                write_colour(pixel_colour);
            }
        }
    }

    void renderNreflectances(const hittable& world, int n){
        initialise();
        cout << "P3\n" << nx << " " << ny << "\n255\n";

        for (int j = 0; j < ny; j++){
            for (int i = 0; i < nx; i++){
                colour pixel_colour(0, 0, 0);
                reflectance = 0.1 + int(n * double(i) / nx) / double(n);
                for (int n = 0; n < samples_per_pixel; n++){
                    vec3 offset = randomdouble(-0.5, +0.5) * delta_u + randomdouble(-0.5, +0.5) * delta_v;
                    ray cameraray(origin, top_left_pixel + i * delta_u + j * -delta_v - origin + offset);
                    pixel_colour += diffuseshader(cameraray, world, max_depth, reflectance);
                }
                pixel_colour /= samples_per_pixel;
                write_colour(pixel_colour);
            }
        }
    }

private:
    double aspect_ratio, H;
    vec3 horizontal, vertical, origin, top_left, delta_u, delta_v, top_left_pixel;
    colour background_colour;
    double &viewport_width = H;
    double &V = viewport_height;
    double &F = focal_length;

    void initialise(){
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

    void compute_background_colour(ray const &lightray) {
        double scaled_y = map(lightray.direction().unit_vector().y(), -1, 1, 0, 1);
        colour background_colour1(1, 1, 1);
        colour background_colour2(0.3, 0.5, 1);
        background_colour = mix_colour(background_colour1, background_colour2, scaled_y);
    }

    colour shader(ray const &lightray, const hittable& obj) {
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

    vec3 vector_in_unit_sphere() const{
        vec3 newvector = random_vector(-1, 1);
        bool vector_ok = false;
        while (!vector_ok){
            if (newvector.length() > 1){
                newvector = random_vector(-1, 1);
                continue;
            }
            vector_ok = true;
        }
        return newvector.unit_vector();
    }

    void make_ray_on_hemisphere(vec3 &vector, const vec3& normal) const{
        if (dot(vector, normal) < 0) vector = -vector;
    }

    colour diffuseshader(ray const &lightray, const hittable& obj, int depth, float reflectance){
        bool hit = false;
        hit_record hitrec;

        colour objectcolour(0, 0, 0);
        if (depth > 0){
            if (obj.hit(lightray, interval(0.001, infinity), hitrec)){
                hit = true;
                vec3 childray_direction = vector_in_unit_sphere() + hitrec.normal;
                // vec3 childray_direction = vector_in_unit_sphere();
                // make_ray_on_hemisphere(childray_direction, hitrec.normal);
                
                ray childray(hitrec.p, childray_direction);
                objectcolour = reflectance * diffuseshader(childray, obj, depth - 1, reflectance);
            }
        }
        else return colour(0, 0, 0);

        compute_background_colour(lightray);
        return mix_colour(background_colour, objectcolour, hit);
    }
};

#endif