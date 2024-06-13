#include "vec3.h"
#define PIXElS_X 1080
#define PIXELS_Y 720

int main(){
    int nx = PIXElS_X;
    int ny = PIXELS_Y;
    cout << "P3\n" << nx << " " << ny << "\n255\n";

    for (int i = 0; i < ny; i++){
        for (int j = 0; j < nx; j++){
            vec3 colour(1.0f - 1.0f * i / ny, 1.0f * j / nx, 0.2f);
            cout << (colour *= 255.99).make_int() << endl;
        }
    }

}