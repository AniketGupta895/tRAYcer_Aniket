#ifndef RAY_H
#define RAY_H

//inclusion of dependencies
#include "vec3.h"

class ray{
    vec3 A, B;
public: 
    ray(vec3 const &a, vec3 const &b): A(a), B(b) {}
    vec3 origin() const;
    vec3 direction() const;
    vec3 point_at_parameter(float const &t) const;
};

/*---------------------------------------------
Definitions of member functions//
---------------------------------------------*/

inline vec3 ray::origin() const{
    return A;
}
inline vec3 ray::direction() const{
    return B;
}
inline vec3 ray::point_at_parameter(float const &t) const{
    return A + B * t;
}

vec3 vector_in_unit_sphere(){
    vec3 newvector = random_vector(-1, 1);
    bool vector_ok = false;
    while (!vector_ok){
        if (newvector.length() > 1){
            newvector = random_vector(-1, 1);
            continue;
        }
        vector_ok = true;
    }
    return newvector.unit_vector();
}

void make_ray_on_hemisphere(vec3 &vector, const vec3& normal){
    if (dot(vector, normal) < 0) vector = -vector;
}


#endif
