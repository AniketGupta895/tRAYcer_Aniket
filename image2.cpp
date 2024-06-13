#include "ray.h"
#include <iostream>
using namespace std;
#define PIXELS_X 1080
#define PIXELS_Y 720

inline vec3 mix(vec3 const &colour1, vec3 const &colour2, float const t){
    return (1.0f - t) * colour1 + t * colour2;
}

vec3 image2shade(ray const &lightray){
    vec3 direction = lightray.direction().unit_vector();
    float y_component = direction.y();
    float scaled_y = 0.5f * (y_component + 1);
    vec3 colour1(1, 1, 1);
    vec3 colour2(0, 0, 1);
    return mix(colour1, colour2, scaled_y);
}

int main(){
    float focal_length = 1;
    int nx = PIXELS_X;
    int ny = PIXELS_Y;
    float res_ratio = float(nx) / ny;
    vec3 left_bottom(-res_ratio, -1,  -focal_length);
    vec3 horizontal(2 * res_ratio, 0, 0);
    vec3 vertical(0, 2, 0);
    vec3 origin(0, 0, 0);

    cout << "P3\n" << nx << " " << ny << "\n255\n";

    for (int j = ny - 1; j >= 0; j--){
        for (int i = 0; i < nx; i++){
            float u = float(i)/nx;
            float v = float(j)/ny;
            ray cameraray(origin, left_bottom + u * horizontal + v * vertical);
            vec3 colour = (image2shade(cameraray) * 255.99).make_int();
            cout << colour << endl;
        }
    }

}