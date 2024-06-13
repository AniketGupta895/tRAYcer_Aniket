#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <iostream>
using namespace std;

class vec3 {
    float v[3];
public:
    vec3(float x, float y, float z);
    vec3();

    float x() const;
    float y() const;
    float z() const;
    float r() const;
    float g() const;
    float b() const;

    vec3 operator-() const;
    vec3 operator+(vec3 const &vector) const;
    vec3& operator+=(vec3 const &vector);
    vec3 operator-(vec3 const &vector) const;
    vec3& operator-=(vec3 const &vector);
    vec3 operator*(float const &t) const;
    vec3& operator*=(float const &t);
    vec3 operator*(vec3 const &vector) const;
    vec3& operator*=(vec3 const vector);
    vec3 operator/(vec3 const vector) const;
    vec3& operator/=(vec3 const vector);
    vec3 operator/(float const &t) const;
    vec3& operator/=(float const &t);
    float operator[](int i) const;
    vec3 unit_vector();
    vec3& normalise();
    vec3& make_int();
    float length();

    friend inline ostream &operator<<(ostream&, vec3 const &);
    friend inline istream &operator>> (istream &ist, vec3 &vector);

};

vec3::vec3(float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

vec3::vec3(){
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
}

inline float vec3::x() const{return v[0];}
inline float vec3::y() const{return v[1];}
inline float vec3::z() const{return v[2];}
inline float vec3::r() const{return v[0];}
inline float vec3::g() const{return v[1];}
inline float vec3::b() const{return v[2];}

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
inline vec3 vec3::operator*(float const &t) const{
    return vec3(v[0] * t, v[1] * t, v[2] * t);
}
inline vec3& vec3::operator*=(float const &t){
    v[0] *= t;
    v[1] *= t;
    v[2] *= t;
    return *this;
}
inline vec3 vec3::operator*(vec3 const &vector) const{
    return vec3(v[0] * vector.x(), v[1] * vector.y(), v[2] * vector.z());
}

inline vec3 operator*(float t, vec3 const &vector){
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
inline vec3 vec3::operator/(float const &t) const{
    return vec3(v[0] / t, v[1] / t, v[2] / t);
}
inline vec3& vec3::operator/=(float const &t){
    v[0] /= t;
    v[1] /= t;
    v[2] /= t;
    return *this;
}
inline float vec3::operator[](int i) const{
    if (i == 0) return v[0];
    else if (i == 1) return v[1];
    else if (i == 2) return v[2];
    else return 0;
}
inline vec3 vec3::unit_vector() {
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
inline float vec3::length(){
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

inline ostream &operator<< (ostream &ost, vec3 const &vector){
    ost << vector.x() << " " << vector.y() << " " << vector.z();
    return ost;
}
inline istream &operator>> (istream &ist, vec3 &vector){
    ist >> vector.v[0] >> vector.v[1] >> vector.v[2];
    return ist;
}
inline float dot(vec3 const &v1, vec3 const &v2){
    return (v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z());
}
inline vec3 cross(vec3 const &v1, vec3 const &v2){
    return vec3(v1.y() * v2.z() - v1.z() * v2.y(), v1.z() * v2.x() - v1.x() * v2.z(), v1.x() * v2.y() - v1.y() * v2.x());
}

#endif // VEC3_H