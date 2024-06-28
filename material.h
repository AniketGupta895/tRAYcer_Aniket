#ifndef MATERIAL_H
#define MATERIAL_H

class hit_record;

class material{
public:
    virtual bool scatter(const ray& lightray, ray& scattered_ray, hit_record &hit_rec, colour &attenuation){
        return false;
    }
    virtual ~material() = default;
};


class lambertian: public material{
    colour albedo;
public:
    lambertian(colour const &albedo): albedo(albedo) {}
    bool scatter(const ray& lightray, ray& scattered_ray, hit_record &hit_rec, colour &attenuation) override;
};


class metal: public material{
    colour albedo;
    double fuzz;
public:
    metal(colour const& albedo, double fuzz = 0): albedo(albedo), fuzz(fuzz){}
    bool scatter(const ray& lightray, ray& scattered_ray, hit_record &hitrec, colour &attenuation) override;
};


class dielectric: public material{
    colour albedo;
    double refractive_index;
    double reflectance(double refractive_index, double costheta);
public:
    dielectric(colour const& albedo, double refractive_index): albedo(albedo), refractive_index(refractive_index){}
    bool scatter(const ray& lightray, ray& scattered_ray, hit_record &hitrec, colour &attenuation) override;
};

/*---------------------------------------------
Definitions of member functions//
---------------------------------------------*/

//inclusion of dependencies
#include "hittable.h"

bool lambertian::scatter(const ray& lightray, ray& scattered_ray, hit_record &hit_rec, colour &attenuation) {
    attenuation = albedo;
    vec3 childray_direction = vector_in_unit_sphere() + hit_rec.normal;
    if (childray_direction.near_zero()) childray_direction = hit_rec.normal;
    scattered_ray = ray(hit_rec.p, childray_direction);
    return true;
}

bool metal::scatter(const ray& lightray, ray& scattered_ray, hit_record &hitrec, colour &attenuation){
    attenuation = albedo;
    vec3 scattered_ray_direction = reflect_vector(lightray.direction(), hitrec.normal);
    double fuzzyradius = dot(scattered_ray_direction, hitrec.normal);
    scattered_ray_direction += fuzz * fuzzyradius * vector_in_unit_sphere();
    scattered_ray = ray(hitrec.p, scattered_ray_direction);
    return true;
}

bool dielectric::scatter(const ray& lightray, ray& scattered_ray, hit_record &hitrec, colour &attenuation){
    attenuation = albedo;
    double ri = hitrec.front_face ? refractive_index : 1.0 / refractive_index;

    vec3 incident_ray = lightray.direction();
    double incident_vector_length = incident_ray.length();
    double costheta = std::fmin(dot(-incident_ray, hitrec.normal) / incident_vector_length, 1.0);
    double sintheta = sqrt(1 - pow(costheta, 2));

    vec3 scattered_ray_direction;

    if (sintheta > ri || reflectance(refractive_index, costheta) >= randomdouble()) {
        scattered_ray_direction = reflect_vector(incident_ray, hitrec.normal);
    }
    else{
        scattered_ray_direction = refract_vector(incident_ray, hitrec.normal, ri);
    }
    scattered_ray = ray(hitrec.p, scattered_ray_direction);
    return true;
}

inline double dielectric::reflectance(double refractive_index, double costheta){
    double R = pow(((1 - refractive_index) / (1 + refractive_index)), 2);
    return R + (1 - R) * pow(1 - costheta, 5);
}

#endif