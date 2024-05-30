// #include <iostream>
// #include <fstream>
// using namespace std;

// int main() {
//     int nx = 1080, ny = 720;
    
//     ofstream file("image.ppm");
//     if (!file){
//         cout << "Unable to open file" << endl;
//         return 1;
//     }

//     file << "P3\n" << nx << " " << ny << "\n1023\n";

//     for (int i = ny; i > 0; i--){
//         for (int j = 0; j < nx; j++) {
//             float r = float(i)/float(ny);
//             float g = float(j)/float(nx);
//             float b = 0.2;
//             int ir = int(r * 1023.99);
//             int ib = int(b * 1023.99);
//             int ig = int(g * 1023.99);
//             file << ir << " " << ig << " " << ib << "\n";
//         }
//     }
//     file << endl;
//     file.close();
//     cout << "Done :)" << endl; 
//     return 0;
// }

#include <iostream>
#include <fstream>
#include <cstdlib>

int main() {
    int nx = 100;
    int ny = 100;
    int maxColorValue = 1023;

    std::ofstream file("image.ppm");
    if (!file) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    // Write the PPM header
    file << "P3\n" << nx << " " << ny << "\n" << maxColorValue << "\n";

    // Generate and write pixel data
    for (int y = 0; y < ny; ++y) {
        for (int x = 0; x < nx; ++x) {
            int r = std::rand() % (maxColorValue + 1);
            int g = std::rand() % (maxColorValue + 1);
            int b = std::rand() % (maxColorValue + 1);
            file << r << " " << g << " " << b << " ";
        }
        file << "\n";
    }

    file.close();
    return 0;
}

