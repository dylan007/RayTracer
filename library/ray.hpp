#ifndef RAYH
#define RAYH
#include"vec3.hpp"

class ray{
public:
	vec A,B;
	int hitcount;
	ray(){;}
	ray(const vec& a,const vec &b){A=a;B=b;hitcount=0;}
	vec origin(){return A;}
	vec direction(){return B;}
	vec get_point(float t){return A + t*B;}
};
#endif