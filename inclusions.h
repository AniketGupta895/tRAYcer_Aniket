#include <iostream>
using namespace std;

#include "vec3.h"
#include "ray.h"
#include "colour.h"
#include "hittable.h"
#include <vector>
#include <memory>

using std::shared_ptr;
using std::make_shared;

#include "hittable_list.h"
#include "sphere.h"

#define PIXELS_X 800
#define PIXELS_Y 600


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



