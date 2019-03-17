#ifndef CAMERAH
#define CAMERAH

#include "ray.hpp"

vec random_in_unit_disk(){
    vec p;
    do{
        p = 2.0 * vec(rn(),rn(),0) - vec(1,1,0);
    }while(dot(p,p) >= 1.0);
    return p;
}

class camera {
public:
    camera(vec lookfrom,vec lookat, vec vup, float vfov, float aspect,float aperture,float focus_dist,float t0,float t1){
        time0 = t0;
        time1 = t1;
        lens_radius = aperture/2;
        float theta = vfov * M_PI/180.0;
        float half_height = tan(theta/2);
        float half_width = aspect * half_height;
        origin = lookfrom;
        w = (lookfrom-lookat);
        w.normalize();
        u = cross(vup,w);
        u.normalize();
        v = cross(w,u);
        lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;
        horizontal = 2*half_width*focus_dist*u;
        vertical = 2*half_height*focus_dist*v;
    }
    ray get_ray(float s,float t){
        vec rd = lens_radius * random_in_unit_disk();
        vec offset = u * rd.x + v * rd.y;
        float time = time0 + rn()*(time1-time0);
        return ray(origin + offset,lower_left_corner + s*horizontal + t*vertical-origin-offset,time);
    }

    vec origin;
    vec lower_left_corner;
    vec horizontal;
    vec vertical;
    vec u,v,w;
    float time0,time1;
    float lens_radius;
};

#endif