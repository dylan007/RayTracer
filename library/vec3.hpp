#ifndef VECH
#define VECH

#include<bits/stdc++.h>
using namespace std;


float rn(){
    return (float)rand() / (float)RAND_MAX;
}


class vec{
public:
    float x,y,z;
    vec() {}
    vec(float a,float b,float c){x=a;y=b;z=c;}
    // inline float x() const {return x;}
    // inline float y() const {return y;}
    // inline float z() const {return z;}
    inline float& operator[](int i){if(i==0)return x;else if(i==1)return y;else return z;}
    inline void normalize(){
        float l = sqrt(x*x + y*y + z*z);
        if(l==0)
            return;
        x/=l;y/=l;z/=l;
    }
    inline float length() {return sqrt(x*x + y*y + z*z);}
    inline float sq_length() {return x*x + y*y + z*z;}
	friend istream& operator>>(istream& is, vec& t){is >> t.x >> t.y >> t.z;return is;}
    friend ostream& operator<<(ostream& os, vec& t){os << t.x << " " << t.y << " " << t.z;return os;}
    inline vec& operator+=(const vec &a){x += a.x;y += a.y;z += a.z;return *this;}
    inline vec& operator-=(const vec &a){x -= a.x;y -= a.y;z -= a.z;return *this;}
    inline vec& operator*=(const float t){x *= t;y *= t;z *= t;return *this;}
    inline vec& operator*=(const vec &a){x *= a.x;y *= a.y; z *= a.z;return *this;}
    inline vec& operator/=(const float t){x /= t;y /= t;z /= t;return *this;}
    inline bool operator!=(const vec &t){return (x!=t.x)||(y!=t.y)||(z!=t.z);}
};

inline vec operator+(const vec& a,const vec& b){return vec(a.x + b.x,a.y + b.y,a.z + b.z);}
inline vec operator-(const vec& a,const vec& b){return vec(a.x - b.x,a.y - b.y,a.z - b.z);}
inline vec operator*(const vec& a,const vec& b){return vec(a.x * b.x,a.y * b.y, a.z * b.z);}
inline vec operator/(const vec& a,const float t){return vec(a.x/t,a.y/t,a.z/t);}
inline vec operator*(const vec& a,const float t){return vec(a.x*t,a.y*t,a.z*t);}
inline vec operator*(const float t,const vec &a){return vec(a.x*t,a.y*t,a.z*t);}
// inline float operator[](const vec& a,int i){if(i==0)return a.x;else if(i==1)return a.y;else return a.z;}
inline float dot(const vec &a,const vec &b){return a.x * b.x + a.y * b.y + a.z * b.z;}
inline vec cross(const vec &a,const vec&b){return vec(a.y * b.z - b.y * a.z,-(a.x * b.z - b.x * a.z),(a.x * b.y - a.y * b.x));}
vec scalar_mul(vec a,float f)
{
    int i;
    a.x=a.x*f;
    a.y=a.y*f;
    a.z=a.z*f;
    return a;
}
#endif
