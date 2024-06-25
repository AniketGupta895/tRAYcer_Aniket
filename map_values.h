#ifndef MAP_VALUES_H
#define MAP_VALUES_H

double map(double const &value, double old_left, double old_right, double new_left, double new_right){
    double new_value = value - old_left;
    new_value *= (new_right - new_left) / (old_right - old_left);
    new_value += new_left;
    return new_value;
}

inline vec3 map(vec3 const &vector, double old_left, double old_right, double new_left, double new_right){
    return vec3(
    map(vector.x(), old_left, old_right, new_left, new_right), 
    map(vector.y(), old_left, old_right, new_left, new_right),
    map(vector.z(), old_left, old_right, new_left, new_right)
    );
}

inline double map(double const &t, interval old_interval, interval new_interval){
    return map(t, old_interval.min, old_interval.max, new_interval.min, new_interval.max);
}

inline vec3 map(vec3 const &vector, interval old_interval, interval new_interval){
    return map(vector, old_interval.min, old_interval.max, new_interval.min, new_interval.max);
}

#endif