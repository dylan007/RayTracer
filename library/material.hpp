#ifndef MATERIALH
#define MATERIALH
#include "ray.hpp"
#include "hitable.hpp"

class material{
public:
    virtual bool scatter(ray &r,hit_record& rec,vec& attenuation,ray& scattered) const = 0;
};

float rn(){
    return (float)rand() / (float)RAND_MAX;
}

vec random_in_unit_sphere(){
    vec p;
    do{
        p = 2.0 * vec(rn(),rn(),rn()) - vec(1,1,1);
    }while(p.sq_length() >= 1.0);
    return p;
}

vec reflect(vec& v,vec& n){
    return v - 2*dot(v,n)*n;
}


class lambertian : public material {
public: 
    lambertian(const vec& a): albedo(a){}
    virtual bool scatter(ray& r_in, hit_record& rec, vec& attenuation, ray& scattered) const{
        vec target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target-rec.p);
        attenuation = albedo;
        return true;
    }
    vec albedo;
};

class metal : public material {
public:
    metal(const vec& a) : albedo(a){}
    virtual bool scatter(ray& r_in, hit_record& rec, vec& attenuation, ray& scattered) const {
        vec unit_vec = r_in.direction();
        unit_vec.normalize();
        vec reflected = reflect(unit_vec,rec.normal);
        scattered = ray(rec.p,reflected);
        attenuation = albedo;
        return (dot(scattered.direction(),rec.normal)>0);    
    }
    vec albedo;
};

#endif