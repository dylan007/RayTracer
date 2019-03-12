#ifndef SPHEREH
#define SPHEREH

#include "hitable.hpp"

class sphere: public hitable{
    public:
        sphere() {}
        sphere(vec cen,float r,material *m):center(cen),radius(r),mat_ptr(m) {}
        virtual bool hit(ray &r,float tmin,float tmax,hit_record& rec) const;
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
#endif