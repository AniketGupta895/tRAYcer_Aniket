#ifndef COLOUR_H
#define COLOUR_H

using namespace std;
using colour = vec3;

inline vec3 mix_colour(vec3 const &colour1, vec3 const &colour2, double const t){
    return (1.0f - t) * colour1 + t * colour2;
}

void gamma_correct(colour &col, double gamma){
    col = colour(
        pow(col.x(), 1 / gamma),
        pow(col.y(), 1 / gamma),
        pow(col.z(), 1 / gamma)        
    );
}

void write_colour(colour const &pixelcolour, double gamma = 2){
    static const interval intensity(0.000, 0.999);
    colour to_write = pixelcolour;
    gamma_correct(to_write, gamma);
    to_write = intensity.clamp(to_write);
    cout << (to_write * 256).make_int() << endl;
}

#endif