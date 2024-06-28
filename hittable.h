#ifndef HITTABLE_H
#define HITTABLE_H

class material;

class hit_record{
public:
    vec3 p;
    double t;
    vec3 normal;
    bool front_face;
    shared_ptr<material> mat;

    void set_face_normal(const ray& lightray, const vec3& outnormal);
};

class hittable{
public:
    virtual bool hit(ray const& lightray, interval ray_interval, hit_record& rec) const = 0;
    virtual ~hittable() = default;
};

//inclusion of dependencies
#include "material.h"

void hit_record::set_face_normal(const ray& lightray, const vec3& outnormal){
    if (dot(lightray.direction(), outnormal) < 0) front_face = true;
    else front_face = false;
}

#endif