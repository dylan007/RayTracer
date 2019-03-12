#ifndef HITABLELIST
#define HITABLELIST
#include "hitable.hpp"


class hitable_list: public hitable{
public:
    hitable **list;
    int list_size;
    hitable_list() {;}
    hitable_list(hitable **l, int n){list = l;list_size = n;}
    virtual bool hit(ray& r,float tmin,float tmax,hit_record& rec) const;
};

bool hitable_list::hit(ray& r, float tmin,float tmax, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;    
    double closest_so_far = tmax;
    for(int i=0;i<list_size;i++){
        if(list[i]->hit(r,tmin,closest_so_far,temp_rec)){
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif