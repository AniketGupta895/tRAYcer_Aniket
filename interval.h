#ifndef INTERVAL_H
#define INTERVAL_H

class vec3;

class interval{
public:
    double min, max;
    interval(): min(+infinity), max(-infinity){}
    interval(double tmin, double tmax): min(tmin), max(tmax){}

    inline bool contains(double t){return (min <= t && t <= max);}
    inline bool surrounds(double t){return (min < t && t < max);}
    inline double clamp(double x) const;
    inline vec3 clamp(vec3 const& vector) const;

    static const interval empty, universe;
};

/*---------------------------------------------
Definitions of member functions//
---------------------------------------------*/

//inclusion of dependencies:
#include "vec3.h"

//empty is from + to - infinity because of we it is impossible for tmin to be +infinity and tmax to be -infinity. Ig we can make empty interval even something like 1, -1 because of the way contains and surrounds functions are written but ok I'll write it like this for now.
const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

inline double interval::clamp(double x) const {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
inline vec3 interval::clamp(vec3 const& vector) const{
    return vec3(
        clamp(vector.x()),
        clamp(vector.y()),
        clamp(vector.z())
    );
}

#endif