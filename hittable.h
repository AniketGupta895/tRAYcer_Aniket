#ifndef HITTABLE_H
#define HITTABLE_H

class hit_record{
public:
    vec3 p;
    double t;
    vec3 normal;
    bool front_face;

    void set_face_normal(const ray& lightray, const vec3& outnormal){
        if (dot(lightray.direction(), outnormal) < 0) front_face = true;
        else front_face = false;
    }
};

class hittable{
public:
    virtual bool hit(ray const& lightray, double tmin, double tmax, hit_record& rec) const = 0;
    virtual ~hittable() = default;
};

#endif