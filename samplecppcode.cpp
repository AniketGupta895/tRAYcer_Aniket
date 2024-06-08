#include <iostream>
using namespace std;

int main() {
    int nx = 1080, ny = 720;
    
    // ofstream file("image.ppm");
    // if (!file){
    //     cout << "Unable to open file" << endl;
    //     return 1;
    // }

    cout << "P3\n" << nx << " " << ny << "\n255\n";

    for (int i = ny; i > 0; i--){
        for (int j = 0; j < nx; j++) {
            float r = float(i)/float(ny);
            float g = float(j)/float(nx);
            float b = 0.2;
            int ir = int(r * 255.99);
            int ib = int(b * 255.99);
            int ig = int(g * 255.99);
            cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    cout << endl;
    return 0;
}
