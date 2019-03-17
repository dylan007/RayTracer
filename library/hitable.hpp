#ifndef HITABLEH
#define HITABLEH

#include "ray.hpp"
#include "aabb.hpp"

class material;

void get_sphere_uv(const vec& p, float& u, float& v) {
    float phi = atan2(p.z, p.x);
    float theta = asin(p.y);
    u = 1-(phi + M_PI) / (2*M_PI);
    v = (theta + M_PI/2) / M_PI;
}


struct hit_record{
    float t;
    float u;
    float v;
    vec p;
    vec normal;
    material *mat_ptr;
};

class hitable {
    public:
        virtual bool hit(ray& r, float t_min,float t_max,hit_record& rec) const = 0;
        virtual bool bounding_box(float t0,float t1,aabb& box) const = 0;
};

class flip_normals : public hitable{
public:
    flip_normals(hitable* p) : ptr(p) {}
    virtual bool hit(ray& r,float t_min,float t_max,hit_record& rec)const{
        if(ptr->hit(r,t_min,t_max,rec)){
            rec.normal =scalar_mul(rec.normal,-1);
            return true;
        }
        else
            return false;
    }
    virtual bool bounding_box(float t0,float t1,aabb& box)const{
        return ptr->bounding_box(t0,t1,box);
    }
    hitable *ptr;
} ;
#endif
