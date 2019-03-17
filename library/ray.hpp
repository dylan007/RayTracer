#ifndef RAYH
#define RAYH
#include"vec3.hpp"

class ray{
public:
	vec A,B;
	float _time;
	int hitcount;
	ray(){;}
	ray(const vec& a,const vec &b,float ti=0.0){A=a;B=b;hitcount=0;_time=ti;}
	vec origin(){return A;}
	vec direction(){return B;}
	float time(){return _time;}
	vec get_point(float t){return A + t*B;}
};
#endif