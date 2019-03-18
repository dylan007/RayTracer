#ifndef AARECTH
#define AARECTH

#include "hitable.hpp"
#include "aabb.hpp"
#include "material.hpp"

class xy_rect : public hitable{
public:
    xy_rect(){}
    xy_rect(float _x0,float _x1,float _y0,float _y1, float _k,material *mat) : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) {};
    virtual bool hit(ray& r,float t0,float t1,hit_record& rec)const;
    virtual bool bounding_box(float t0,float t1,aabb& box)const{
    box = aabb(vec(x0,y0,k-0.0001),vec(x1,y1,k+0.0001));
    return true;
    }
    material *mp;
    float x0,y0,x1,y1,k;
};

bool xy_rect::hit(ray& r, float t0,float t1,hit_record& rec)const{
    float t = (k-r.origin().z)/r.direction().z;
    if ( t < t0 || t>t1)
        return false;
    float x = r.origin().x + t*r.direction().x;
    float y = r.origin().y + t*r.direction().y;
    if(x<x0 || x>x1 || y<y0 || y>y1)
        return false;
    rec.u = (x-x0)/(x1-x0);
    rec.v = (y-y0)/(y1-y0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.get_point(t);
    rec.normal=vec(0,0,1);
    return true;
}

class xz_rect : public hitable{
public:
    xz_rect(){}
    xz_rect(float _x0,float _x1,float _z0,float _z1, float _k,material *mat) : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat) {};
    virtual bool hit(ray& r,float t0,float t1,hit_record& rec)const;
    virtual bool bounding_box(float t0,float t1,aabb& box)const{
    box = aabb(vec(x0,z0,k-0.0001),vec(x1,z1,k+0.0001));
    return true;
    }
    material *mp;
    float x0,z0,x1,z1,k;
};

class yz_rect : public hitable{
public:
    yz_rect(){}
    yz_rect(float _y0,float _y1,float _z0,float _z1, float _k,material *mat) : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat) {};
    virtual bool hit(ray& r,float t0,float t1,hit_record& rec)const;
    virtual bool bounding_box(float t0,float t1,aabb& box)const{
    box = aabb(vec(y0,z0,k-0.0001),vec(y1,z1,k+0.0001));
    return true;
    }
    material *mp;
    float y0,z0,y1,z1,k;
};

bool xz_rect::hit(ray& r, float t0,float t1,hit_record& rec)const{
    float t = (k-r.origin().y)/r.direction().y;
    if ( t < t0 || t>t1)
        return false;
    float x = r.origin().x + t*r.direction().x;
    float z = r.origin().z + t*r.direction().z;
    if(x<x0 || x>x1 || z<z0 || z>z1)
        return false;
    rec.u = (x-x0)/(x1-x0);
    rec.v = (z-z0)/(z1-z0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.get_point(t);
    rec.normal=vec(0,1,0);
    return true;
}

bool yz_rect::hit(ray& r, float t0,float t1,hit_record& rec)const{
    float t = (k-r.origin().x)/r.direction().x;
    if ( t < t0 || t>t1)
        return false;
    float y = r.origin().y + t*r.direction().y;
    float z = r.origin().z + t*r.direction().z;
    if(z<z0 || z>z1 || y<y0 || y>y1)
        return false;
    rec.u = (y-y0)/(y1-y0);
    rec.v = (z-z0)/(z1-z0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.get_point(t);
    rec.normal=vec(1,0,0);
    return true;
}


#endif // RECT_HPP_INCLUDED
