// //This program will create a  gradient background as in image2. It will add a sphere at and the pixels at which the sphere should appear will be turned red. Very simple shading function, it does not take into account surface normals or anything other than simple a boolean of whether the sphere exists at that point or not.

#include "ray.h"
#include "colour.h"
#include <iostream>
#include <math.h>
#include <assert.h>
using namespace std;
#define PIXELS_X 1920
#define PIXELS_Y 1080

double map(double const &value, double old_left, double old_right, double new_left, double new_right){
    double new_value = value - old_left;
    new_value *= (new_right - new_left) / (old_right - old_left);
    new_value += new_left;
    return new_value;
}

inline vec3 map(vec3 const &vector, double old_left, double old_right, double new_left, double new_right){
    return vec3(
    map(vector.x(), old_left, old_right, new_left, new_right), 
    map(vector.y(), old_left, old_right, new_left, new_right),
    map(vector.z(), old_left, old_right, new_left, new_right)
    );
}

double sphere_is_hit(ray const &p, vec3 const &centre, double const &r){
    //Ray is of form A + t * B
    const vec3 A = p.origin();
    const vec3 B = p.direction();
    const vec3 C = centre;
    const double a = dot(B, B);
    const double b = -2 * dot(B, C - A);
    const double c = dot(C - A, C - A) - r * r;
    double discriminant = (b * b - 4 * a * c);
    if (discriminant > 0){
        return (-b - sqrt(discriminant)) / (2 * a);
    }
    else{
        return 0;
    }
}

vec3 image4shader(ray const &lightray, vec3 const &centre, double const &radius){
    double scaled_y = map(lightray.direction().unit_vector().y(), -1, 1, 0, 1);
    colour gradientcolour1(1, 1, 1);
    colour gradientcolour2(0.3, 0.5, 1);
    colour gradientcolour = mix_colour(gradientcolour1, gradientcolour2, scaled_y);

    colour spherecolour(0, 0, 0);
    bool hit = false;
    double t = sphere_is_hit(lightray, centre, radius);
    if (t) {
        hit = true;
        spherecolour = (lightray.point_at_parameter(t) - centre).unit_vector();
        spherecolour = map(spherecolour, -1, 1, 0, 1);
    }

    return mix_colour(gradientcolour, spherecolour, hit);
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
            write_colour(image4shader(cameraray, centre, radius));
        }
    }
}
 
