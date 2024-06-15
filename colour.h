#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"
#include <iostream>
using namespace std;
using colour = vec3;

inline vec3 mix_colour(vec3 const &colour1, vec3 const &colour2, double const t){
    return (1.0f - t) * colour1 + t * colour2;
}

void write_colour(colour const &pixelcolour){
    cout << (vec3(pixelcolour.r(), pixelcolour.g(), pixelcolour.b()) * 255.99).make_int() << endl;
}

#endif