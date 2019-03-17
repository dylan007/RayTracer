#ifndef HITABLELIST
#define HITABLELIST
#include "hitable.hpp"
#include "aabb.hpp"

class hitable_list: public hitable{
public:
    hitable **list;
    int list_size;
    hitable_list() {;}
    hitable_list(hitable **l, int n){list = l;list_size = n;}
    virtual bool hit(ray& r,float tmin,float tmax,hit_record& rec) const;
    virtual bool bounding_box(float t0,float t1,aabb& box) const;
};

bool hitable_list::bounding_box(float t0,float t1,aabb& box) const {
    if(list_size < 1) return false;
    aabb temp_box;
    bool first_true = list[0]->bounding_box(t0,t1,temp_box);
    if(!first_true)
        return false;
    else
        box = temp_box;
    for(int i=1;i<list_size;i++){
        if(list[0]->bounding_box(t0,t1,temp_box))
            box = surrounding_box(box,temp_box);
    }
}

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