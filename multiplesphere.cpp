#include "inclusions.h"

vec3 multisphereshader(ray const &lightray, hittable_list hittables){
    double scaled_y = map(lightray.direction().unit_vector().y(), -1, 1, 0, 1);
    colour gradientcolour1(1, 1, 1);
    colour gradientcolour2(0.3, 0.5, 1);
    colour gradientcolour = mix_colour(gradientcolour1, gradientcolour2, scaled_y);

    colour spherecolour(0, 0, 0);
    hit_record hitrec;
    bool hit = false;
    if (hittables.hit(lightray, 0, INFINITY, hitrec)) {
        hit = true;
        spherecolour = map(hitrec.normal, -1, 1, 0, 1);
    }

    return mix_colour(gradientcolour, spherecolour, hit);
}

int main(){
    int nx = PIXELS_X;
    int ny = PIXELS_Y;
    double aspect_ratio = double (nx) / ny;
    
    cout << "P3\n" << nx << " " << ny << "\n255\n";

    int number_of_spheres; cin >> number_of_spheres;
    hittable_list listofspheres;
    for (int i = 0; i < number_of_spheres; i++){
        vec3 centre;
        double radius;
        cin >> centre >> radius;
        listofspheres.add(shared_ptr<sphere>(new sphere(centre, radius)));
    }

    double viewport_height = 2;
    vec3 horizontal(viewport_height * aspect_ratio, 0, 0);
    vec3 vertical(0, viewport_height, 0);
    vec3 origin(0, 0, 0);
    double H = horizontal.length();
    double &viewport_width = H;
    double &V = viewport_height;
    double focal_length = 4;
    double &F = focal_length;
    vec3 left_bottom(-H / 2, -V / 2, -sqrt(F*F - (V/2)*(V/2) - (H/2)*(H/2)));

    //Use same gradient as in image2, if sphere is hit, make that area red
    vec3 delta_u(viewport_width / nx, 0, 0);
    vec3 delta_v(0, viewport_height / ny, 0);
    vec3 left_bottom_pixel = left_bottom + vec3(0.5 * delta_u.x(), -0.5 * delta_v.y(), 0);
    for (int j = ny - 1; j >=0; j--){
        for (int i = 0; i < nx; i++){
            ray cameraray(origin, left_bottom + i * delta_u + j * delta_v - origin);
            write_colour(multisphereshader(cameraray, listofspheres));
        }
    }
}