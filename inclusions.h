#ifndef INCLUSIONS_H
#define INCLUSIONS_H

#include <iostream>
using namespace std;

// #define NS_PRIVATE_IMPLEMENTATION
// #define CA_PRIVATE_IMPLEMENTATION
// #define MTL_PRIVATE_IMPLEMENTATION

#include <math.h>
#include <vector>
#include <memory>
#include <limits>
#include <stdlib.h>
#include <time.h>
// #include <Metal/Metal.hpp>
// #include <QuartzCore/QuartzCore.hpp>
// #include <Foundation/Foundation.hpp>


using std::shared_ptr;
using std::make_shared;

#define PIXELS_X 1920
#define PIXELS_Y 1080
#define PI M_PI
#define infinity numeric_limits<double>::infinity()

inline double radians_to_degrees(double radians){
    return radians * PI / 180;
}

inline double degrees_to_radians(double degrees){
    return degrees * 180 / PI;
}

inline void initrand(){
    srand(time(0));
    int* i = new int;
    *i = rand();
    delete i;
}

inline double randomdouble(double left = 0, double right = 1){
    double normalised_rand = rand() / (RAND_MAX + 1.0);
    return left + normalised_rand * (right - left);
}


#include "vec3.h"
#include "interval.h"
#include "ray.h"
#include "colour.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "map_values.h"
#include "camera.h"

#endif

