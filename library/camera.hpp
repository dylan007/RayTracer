#ifndef CAMERAH
#define CAMERAH

#include "ray.hpp"

class camera {
public:
    camera(){
        lower_left_corner = vec(-2.0,-1.0,-1.0);
        horizontal = vec(4.0,0.0,0.0);
        vertical = vec(0.0,2.0,0.0);
        origin = vec(0.0,0.0,0.0);
    }
    ray get_ray(float u,float v){return ray(origin,lower_left_corner+ u * horizontal + v * vertical);}

    vec origin;
    vec lower_left_corner;
    vec horizontal;
    vec vertical;
};

#endif