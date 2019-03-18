#ifndef DIFFUSE_HPP_INCLUDED
#define DIFFUSE_HPP_INCLUDED
#include "material.hpp"

class diffuse_light : public material {
public:
    diffuse_light(texture *a) : emit(a) {}
    virtual bool scatter(ray& r,hit_record& rec,vec& attenuation,ray& scattered)const{return false;}
    virtual vec emitted(float u,float v,const vec& p) const {
        return emit->value(u,v,p);
    }
    texture *emit;
};

#endif // DIFFUSE_HPP_INCLUDED
