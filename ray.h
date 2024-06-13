#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class ray{
    vec3 A, B;
public: 
    ray(vec3 const &a, vec3 const &b);
    vec3 origin() const;
    vec3 direction() const;
    vec3 point_at_parameter(float const &t) const;
};

ray::ray(vec3 const &a, vec3 const &b){
    A = a;
    B = b;
}

inline vec3 ray::origin() const{
    return A;
}

inline vec3 ray::direction() const{
    return B;
}

inline vec3 ray::point_at_parameter(float const &t) const{
    return A + B * t;
}

#endif
