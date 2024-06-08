#include <iostream>
#include <math.h>
using namespace std;

class vec3 {
    float v[3];

public:

    vec3(float x = 0, float y = 0, float z = 0) {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }

    inline float x() const{return v[0];}
    inline float y() const{return v[1];}
    inline float z() const{return v[2];}
    inline float r() const{return v[0];}
    inline float g() const{return v[1];}
    inline float b() const{return v[2];}


    inline vec3 operator-() const{
        return *this * -1;
    }
    inline vec3 operator+(vec3 const &vector) const{
        return vec3(v[0] + vector.x(), v[1] + vector.y(), v[2] + vector.z());
    }
    inline vec3& operator+=(vec3 const &vector) {
        v[0] += vector.x();
        v[1] += vector.y();
        v[2] += vector.z();
        return *this;
    }
    inline vec3 operator-(vec3 const &vector) const{
        return vec3(v[0] - vector.x(), v[1] - vector.y(), v[2] - vector.z());
    }
    inline vec3& operator-=(vec3 const &vector) {
        v[0] -= vector.x();
        v[1] -= vector.y();
        v[2] -= vector.z();
        return *this;
    }
    inline vec3 operator*(float const &t) const{
        return vec3(v[0] * t, v[1] * t, v[2] * t);
    }
    inline vec3& operator*=(float const &t){
        v[0] *= t;
        v[1] *= t;
        v[2] *= t;
        return *this;
    }
    inline vec3 operator*(vec3 const vector) const{
        return vec3(v[0] * vector.x(), v[1] * vector.y(), v[2] * vector.z());
    }
    inline vec3& operator*=(vec3 const vector){
        v[0] *= vector.x();
        v[1] *= vector.y();
        v[2] *= vector.z();
        return *this;
    }
    inline vec3 operator/(vec3 const vector) const{
        return vec3(v[0] / vector.x(), v[1] / vector.y(), v[2] / vector.z());
    }
    inline vec3& operator/=(vec3 const vector){
        v[0] /= vector.x();
        v[1] /= vector.y();
        v[2] /= vector.z();
        return *this;
    }
    inline vec3 operator/(float const &t) const{
        return vec3(v[0] / t, v[1] / t, v[2] / t);
    }
    inline vec3& operator/=(float const &t){
        v[0] /= t;
        v[1] /= t;
        v[2] /= t;
        return *this;
    }
    inline float operator[](int i) const{
        if (i == 0) return v[0];
        else if (i == 1) return v[1];
        else if (i == 2) return v[2];
        else return 0;
    }
    inline vec3 unit_vector() {
        return *this/length();
    }
    inline vec3& normalise(){
        *this /= length();
        return *this;
    }
    float length(){
        return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    }

    friend inline ostream &operator<<(ostream&, vec3 const &);
    friend inline istream &operator>>(istream&, vec3 &);
    friend inline float dot(vec3 const &v1, vec3 const &v2);
    friend inline vec3 cross(vec3 const &v1, vec3 const &v2);
};

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

int main(){
    vec3 vector1;
    cin >> vector1;
    cout << "Vector A is: " << vector1 << endl;
    vec3 vector2;
    cin >> vector2;
    cout << "Vector B is: " << vector2 << endl;
    cout << "Dot product " << dot(vector1, vector2) << endl;
    cout << "Cross product " << cross(vector1, vector2) << endl;
    cout << dot(cross(vector1, vector2), vector1) << endl << dot(cross(vector1, vector2), vector2) << endl;
    cout << vector1 * vector2 << endl;
    cout << vector1.unit_vector() << endl;
    cout << vector1 << endl;
    vector1.normalise();
    cout << vector1 << endl;
    cout << vector2.r() << " " << vector2.y() << " " << vector2.b() << endl;
}