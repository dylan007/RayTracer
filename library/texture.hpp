#ifndef TEXTUREH
#define TEXTUREH

#include "vec3.hpp"
#include "perlin.hpp"

class texture{
public: 
    virtual vec value(float u,float v,const vec& p) const=0;
};

class constant_texture: public texture{
public:
    constant_texture(){}
    constant_texture(vec c): color(c){}
    virtual vec value(float u,float v,const vec& p) const {
        return color;
    }
    vec color;
};

class checker_texture: public texture{
public:
    checker_texture(){}
    checker_texture(texture *t0,texture *t1): even(t0),odd(t1){}
    virtual vec value(float u,float v,const vec& p) const {
        float sines = sin(10*p.x) * sin(10 * p.y) * sin(10 * p.z);
        if(sines < 0)
            return odd->value(u,v,p);
        else
            return even->value(u,v,p);
    }
    texture *odd;
    texture *even;
};

class noise_texture: public texture{
public:
    noise_texture(){}
    noise_texture(float sc):scale(sc){}
    virtual vec value(float u,float v,const vec& p) const {
        // return vec(1,1,1) * noise.noise(scale*p);
        // return vec(1,1,1) * noise.turb(scale*p);
        return vec(1,1,1)*0.5*(1+sin(scale*p.z) + 10*noise.turb(p));
    }
    float scale;
    perlin noise;
};

#endif