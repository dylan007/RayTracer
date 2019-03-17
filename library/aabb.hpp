#ifndef AABBH
#define AABBH


#include "vec3.hpp"
#include "ray.hpp"

inline float ffmin(float a,float b){return a<b?a:b;}
inline float ffmax(float a,float b){return a>b?a:b;}

class aabb{
public:
    vec _min;
    vec _max;
    aabb(){}
    aabb(const vec& a,const vec& b){_min = a;_max=b;}

    vec min() const {return _min;}
    vec max() const {return _max;}

    // bool hit(ray& r, float tmin, float tmax) {
    //     for(int a=0;a<3;a++){
    //         float t0 = ffmin((_min[a]-r.origin()[a])/r.direction()[a],(_max[a] - r.origin()[a])/r.direction()[a]);
    //         float t1 = ffmax((_min[a]-r.origin()[a])/r.direction()[a],(_max[a] - r.origin()[a])/r.direction()[a]);
    //         tmin = ffmax(t0,tmin);
    //         tmax = ffmin(t1,tmax);
    //         if(tmax<=tmin)
    //             return false;
    //     }
    //     return true;
    // }

    bool hit(ray& r,float tmin,float tmax) const {
        for(int a=0;a<3;a++){
            float invD = 1.0f/r.direction()[a];
            float t0 = (min()[a] - r.origin()[a]) * invD;
            float t1 = (max()[a] - r.origin()[a]) * invD;
            if(invD < 0.0f)
                std::swap(t0,t1);
            tmin = t0 > tmin ? t0 : tmin;
            tmax = t1 < tmax ? t1 : tmax;
            if(tmax <= tmin)
                return false;
        }
        return true;
    }
};

aabb surrounding_box(aabb box0,aabb box1){
    vec small(ffmin(box0.min().x, box1.min().x),ffmin(box0.min().y,box1.min().y),ffmin(box0.min().z,box1.min().z));
    vec big(ffmax(box0.max().x, box1.max().x),ffmax(box0.max().y,box1.max().y),ffmax(box0.max().z,box1.max().z));
    return aabb(small,big);
}

#endif