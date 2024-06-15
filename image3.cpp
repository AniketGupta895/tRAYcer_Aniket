// //This program will create a  gradient background as in image2. It will add a sphere at and the pixels at which the sphere should appear will be turned red. Very simple shading function, it does not take into account surface normals or anything other than simple a boolean of whether the sphere exists at that point or not.

#include "ray.h"
#include "colour.h"
#include <iostream>
#include <math.h>
using namespace std;
#define PIXELS_X 600
#define PIXELS_Y 400

bool sphere_is_hit(ray const &p, vec3 const &centre, double const &r){
    //Ray is of form A + t * B
    const vec3 A = p.origin();
    const vec3 B = p.direction();
    const vec3 C = centre;
    bool is_hit = ((pow(dot(B, A - C), 2) - dot(B, B) * (dot(A - C, A - C) - r * r) >= 0)) ? true : false;
    return is_hit;
}

vec3 image3shader(ray const &lightray, vec3 const &centre, double const &radius){
    double y_component = lightray.direction().unit_vector().y();
    double scaled_y = 0.5f * (y_component + 1);
    colour gradientcolour1(1, 1, 1);
    colour gradientcolour2(0.3, 0.5, 1);
    colour gradientcolour = mix_colour(gradientcolour1, gradientcolour2, scaled_y);
    colour spherecolour(1, 0.4, 0.4);
    return mix_colour(gradientcolour, spherecolour, sphere_is_hit(lightray, centre, radius));
}

int main(){
    int nx = PIXELS_X;
    int ny = PIXELS_Y;
    double aspect_ratio = double (nx) / ny;
    
    cout << "P3\n" << nx << " " << ny << "\n255\n";

    double radius;
    vec3 centre;
    cin >> centre >> radius;

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
            write_colour(image3shader(cameraray, centre, radius));
        }
    }
    
    // double alpha = 2 * asin((H/2) / F);
    // double beta = 2 * asin((V/2) / F);
    // vec3 startingray = left_bottom + vertical;
    // for (int j = 0; j < ny; j++){
    //     for (int i = 0; i < nx; i++){
    //         double u = double(i) / nx * alpha;
    //         double v = double(j) / ny * beta;
    //         vec3 polarray = cartesian_to_polar(startingray) + vec3(0, -u, -v);
    //         ray cameraray(origin, polar_to_cartesian(polarray).normalise()); 
    //         cout << (image3shader(cameraray, centre, radius) * 255.99).make_int() << endl;

    //         //This line was added for trying to visualise the area that the camerarays sweep
    //         //cout << "v " << cameraray.direction().unit_vector() << endl;
    //     }
    // }

    ////These lines add faces to the above added vertices. The output is saved in a .obj file that can be in      
    // for (int i = 1; i < nx * (ny - 1); i++){
    //     if (i % nx == 0) continue;
    //     cout << "f " << i << " " << i + 1 << " " << i + nx << endl;
    // }
    // for (int i = 1; i < nx * (ny - 1); i++){
    //     if ((i - 1) % nx == 0) continue;
    //     cout << "f " << i << " " << i + nx - 1 << " " << i + nx << endl;
    // }
    // cout << alpha << endl << beta << endl;

}
 
