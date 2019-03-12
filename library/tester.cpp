/*=======================
Author    : Shounak Dey
=======================	*/

#include<bits/stdc++.h>
#include"ray.hpp"
using namespace std;

int main(){
	vec a,b;
	a = vec(0,0,0);
	b = vec(1,2,3);
	ray r = ray(a,b);
	vec p = r.get_point(2.3);
	cout << p.x << " " << p.y << " " << p.z << endl;
	return 0;
}
