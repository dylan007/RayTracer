#ifndef SPHEREH
#define SPHEREH
#include "hitable.hpp"
#include "aabb.hpp"
#include "material.hpp"
class sphere: public hitable{
    public:
        sphere() {}
        sphere(vec cen,float r,material *m):center(cen),radius(r),mat_ptr(m) {}
        virtual bool hit(ray &r,float tmin,float tmax,hit_record& rec) const;
        virtual bool bounding_box(float t0,float t1,aabb& box) const;
        vec center;
        float radius;
        material* mat_ptr;
};

bool sphere::hit(ray& r,float t_min,float t_max,hit_record& rec) const {
    vec oc = r.origin() - center;
    float a = dot(r.direction(),r.direction());
    float b = dot(oc,r.direction());
    float c = dot(oc,oc)- radius*radius;
    float disc = b*b - a*c;
    if(disc > 0){
        float temp = (-b - sqrt(disc))/a;
        if(temp<t_max && temp>t_min){
            rec.t = temp;
            rec.p = r.get_point(rec.t);
            get_sphere_uv((rec.p-center)/radius,rec.u,rec.v);
            rec.normal = (rec.p - center)/radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(disc))/a;
        if(temp<t_max && temp>t_min){
            rec.t = temp;
            rec.p = r.get_point(rec.t);
            rec.normal = (rec.p - center)/radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;

}

bool sphere::bounding_box(float t0,float t1,aabb& box) const{
    box = aabb(center - vec(radius,radius,radius),center + vec(radius,radius,radius));
    return true;
}


class moving_sphere: public hitable{
public:
    moving_sphere();
    moving_sphere(vec cen0,vec cen1,float t0,float t1,float r,material *m): center0(cen0),center1(cen1),time0(t0),time1(t1),radius(r),mat_ptr(m) {};
    virtual bool hit(ray& r,float tmin,float tmax,hit_record& rec) const;
    virtual bool bounding_box(float t0,float t1,aabb& box) const;
    vec center(float time) const;
    vec center0,center1;
    float time0,time1;
    float radius;
    material *mat_ptr;
};

vec moving_sphere::center(float time) const{
    return center0 + ((time-time0)/(time1-time0)) * (center1-center0);
}

bool moving_sphere::hit(ray& r,float t_min,float t_max,hit_record& rec) const {
    vec oc = r.origin() - center(r.time());
    float a = dot(r.direction(),r.direction());
    float b = dot(oc,r.direction());
    float c = dot(oc,oc)- radius*radius;
    float disc = b*b - a*c;
    if(disc > 0){
        float temp = (-b - sqrt(disc))/a;
        if(temp<t_max && temp>t_min){
            rec.t = temp;
            rec.p = r.get_point(rec.t);
            rec.normal = (rec.p - center(r.time()))/radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(disc))/a;
        if(temp<t_max && temp>t_min){
            rec.t = temp;
            rec.p = r.get_point(rec.t);
            rec.normal = (rec.p - center(r.time()))/radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;

}

bool moving_sphere::bounding_box(float t0,float t1,aabb& box) const{
    aabb box0(center(t0)-vec(radius,radius,radius),center(t0)+vec(radius,radius,radius));
    aabb box1(center(t1)-vec(radius,radius,radius),center(t1)+vec(radius,radius,radius));
    box = surrounding_box(box0,box1);
    return true;
}

#endif
