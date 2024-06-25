#ifndef SPHERE_H
#define SPHERE_H

class sphere : public hittable{
    vec3 centre;
    double radius;
public: 
    sphere(vec3 Centre, double Radius): radius(Radius), centre(Centre) {};
    bool hit(ray const& lightray, interval ray_interval, hit_record& rec) const override{
        //Ray is of form A + t * B
        const vec3 A = lightray.origin();
        const vec3 B = lightray.direction();
        const vec3 C = centre;
        const double a = dot(B, B);
        const double b = -2 * dot(B, C - A);
        const double c = dot(C - A, C - A) - radius * radius;
        double discriminant = (b * b - 4 * a * c);

        if (discriminant < 0) return false;

        double t_striked = (-b - sqrt(discriminant)) / (2 * a);
        if (!ray_interval.surrounds(t_striked)) {
            t_striked = (-b + sqrt(discriminant)) / (2 * a);
            if (!ray_interval.surrounds(t_striked)) return false;
        }

        rec.t = t_striked;
        rec.p = lightray.point_at_parameter(t_striked);
        vec3 outnormal = (rec.p - centre) / radius;
        rec.set_face_normal(lightray, outnormal);
        rec.normal = rec.front_face ? outnormal : -outnormal;
        return true;
    }
};

#endif