#ifndef VEC3_H
#define VEC3_H

class interval;

class vec3 {
    double v[3];
public:
    vec3(double x = 0, double y = 0, double z = 0);
    vec3(vec3 const& other);
    vec3& operator=(vec3 const& other);

    double x() const;
    double y() const;
    double z() const;
    double r() const;
    double g() const;
    double b() const;

    vec3 operator-() const;
    vec3 operator+(vec3 const &vector) const;
    vec3& operator+=(vec3 const &vector);
    vec3 operator-(vec3 const &vector) const;
    vec3& operator-=(vec3 const &vector);
    vec3 operator*(double const &t) const;
    vec3& operator*=(double const &t);
    vec3 operator*(vec3 const &vector) const;
    vec3& operator*=(vec3 const vector);
    vec3 operator/(vec3 const vector) const;
    vec3& operator/=(vec3 const vector);
    vec3 operator/(double const &t) const;
    vec3& operator/=(double const &t);
    double operator[](int i) const;
    vec3 unit_vector() const;
    vec3& normalise();
    vec3& make_int();
    double length() const;
    bool near_zero() const;

    friend inline ostream &operator<<(ostream&, vec3 const &);
    friend inline istream &operator>> (istream &ist, vec3 &vector);

};

/*---------------------------------------------
Definitions of member functions//
---------------------------------------------*/

//inclusion of dependencies
#include "interval.h"

vec3::vec3(double x, double y, double z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}
vec3::vec3(vec3 const& other){
    v[0] = other.x();
    v[1] = other.y();
    v[2] = other.z();
}
vec3& vec3::operator=(vec3 const& other){
    v[0] = other.x();
    v[1] = other.y();
    v[2] = other.z();
    return *this;
}

inline double vec3::x() const{return v[0];}
inline double vec3::y() const{return v[1];}
inline double vec3::z() const{return v[2];}
inline double vec3::r() const{return v[0];}
inline double vec3::g() const{return v[1];}
inline double vec3::b() const{return v[2];}

inline vec3 vec3::operator-() const{
    return *this * -1;
}
inline vec3 vec3::operator+(vec3 const &vector) const{
    return vec3(v[0] + vector.x(), v[1] + vector.y(), v[2] + vector.z());
}
inline vec3& vec3::operator+=(vec3 const &vector) {
    v[0] += vector.x();
    v[1] += vector.y();
    v[2] += vector.z();
    return *this;
}
inline vec3 vec3::operator-(vec3 const &vector) const{
    return vec3(v[0] - vector.x(), v[1] - vector.y(), v[2] - vector.z());
}
inline vec3& vec3::operator-=(vec3 const &vector) {
    v[0] -= vector.x();
    v[1] -= vector.y();
    v[2] -= vector.z();
    return *this;
}
inline vec3 vec3::operator*(double const &t) const{
    return vec3(v[0] * t, v[1] * t, v[2] * t);
}
inline vec3& vec3::operator*=(double const &t){
    v[0] *= t;
    v[1] *= t;
    v[2] *= t;
    return *this;
}
inline vec3 vec3::operator*(vec3 const &vector) const{
    return vec3(v[0] * vector.x(), v[1] * vector.y(), v[2] * vector.z());
}
inline vec3 operator*(double t, vec3 const &vector){
    return vector * t;
}
inline vec3& vec3::operator*=(vec3 const vector){
    v[0] *= vector.x();
    v[1] *= vector.y();
    v[2] *= vector.z();
    return *this;
}
inline vec3 vec3::operator/(vec3 const vector) const{
    return vec3(v[0] / vector.x(), v[1] / vector.y(), v[2] / vector.z());
}
inline vec3& vec3::operator/=(vec3 const vector){
    v[0] /= vector.x();
    v[1] /= vector.y();
    v[2] /= vector.z();
    return *this;
}
inline vec3 vec3::operator/(double const &t) const{
    return vec3(v[0] / t, v[1] / t, v[2] / t);
}
inline vec3& vec3::operator/=(double const &t){
    v[0] /= t;
    v[1] /= t;
    v[2] /= t;
    return *this;
}
inline double vec3::operator[](int i) const{
    if (i == 0) return v[0];
    else if (i == 1) return v[1];
    else if (i == 2) return v[2];
    else return 0;
}
inline vec3 vec3::unit_vector() const{
    return *this/length();
}
inline vec3& vec3::normalise(){
    *this /= length();
    return *this;
}
inline vec3& vec3::make_int(){
    v[0] = floor(v[0]);
    v[1] = floor(v[1]);
    v[2] = floor(v[2]);
    return *this;
}
inline double vec3::length() const{
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}
inline bool vec3::near_zero() const{
    double epsilon = 1e-8;
    if (abs(v[0]) <= epsilon && abs(v[1]) <= epsilon && abs(v[2]) <= epsilon){
        return true;
    }
    return false;
}

inline ostream &operator<< (ostream &ost, vec3 const &vector){
    ost << vector.x() << " " << vector.y() << " " << vector.z();
    return ost;
}
inline istream &operator>> (istream &ist, vec3 &vector){
    ist >> vector.v[0] >> vector.v[1] >> vector.v[2];
    return ist;
}
inline double dot(vec3 const &v1, vec3 const &v2){
    return (v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z());
}
inline vec3 cross(vec3 const &v1, vec3 const &v2){
    return vec3(v1.y() * v2.z() - v1.z() * v2.y(), v1.z() * v2.x() - v1.x() * v2.z(), v1.x() * v2.y() - v1.y() * v2.x());
}

inline vec3 polar_to_cartesian(vec3 const& polarvector){
    double r = polarvector[0];
    double theta = polarvector[1];
    double phi = polarvector[2];
    return vec3(r * cos(phi) * cos(theta), r * sin(phi), -r * cos(phi) * sin(theta));
}
inline vec3 cartesian_to_polar(vec3 const& cartesianvector){
    double x = cartesianvector[0];
    double y = cartesianvector[1];
    double z = cartesianvector[2];
    return vec3(sqrt(x * x + y * y + z * z), atan2(-z, x), atan2(y, sqrt(x * x + z * z)));
}

inline vec3 random_vector(double min, double max){
    return vec3(
        randomdouble(min, max),
        randomdouble(min, max),
        randomdouble(min, max)
        );
}

inline vec3 reflect_vector(vec3 const& incident_vector, vec3 const& normal){
    return incident_vector + 2 * dot(incident_vector, normal) * -normal;
}
inline vec3 refract_vector(vec3 const& incident_vector, vec3 const& normal, double relative_refractive_index){
    double incident_vector_length = incident_vector.length();
    double costheta = std::fmin(dot(-incident_vector, normal) / incident_vector_length, 1.0);
    double sintheta = sqrt(1 - pow(costheta, 2));

    vec3 r_perpendicular = incident_vector + costheta * incident_vector_length * normal;
    vec3 r_parallel = incident_vector_length * sqrt(pow(relative_refractive_index, 2) - pow(sintheta, 2)) * -normal;
    return r_perpendicular + r_parallel;
}

#endif // VEC3_H