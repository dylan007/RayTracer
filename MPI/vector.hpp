#include<bits/stdc++.h>
using namespace std;

class vec{
public: 
    float x,y,z;
    vec() {}
    vec(float a,float b,float c){x=a;y=b;z=c;}
    inline float length() {return sqrt(x*x + y*y + z*z);}
    inline float sq_length() {return x*x + y*y + z*z;}
    inline void normalize(){float l = sqrt(x*x + y*y + z*z);x/=l;y/=l;z/=l;}
    inline std::istream& operator>>(std::istream &is){is >> x >> y >> z;return is;}
    inline std::ostream& operator<<(std::ostream &os){os << x << " " << y << " " << z;return os;}
    inline vec& operator+=(const vec &a){x += a.x;y += a.y;z += a.z;return *this;}
    inline vec& operator-=(const vec &a){x -= a.x;y -= a.y;z -= a.z;return *this;}
    inline vec& operator*=(const float t){x *= t;y *= t;z *= t;return *this;}
    inline vec& operator*=(const vec &a){x *= a.x;y *= a.y; z *= a.z;return *this;}
    inline vec& operator/=(const float t){x /= t;y /= t;z /= t;return *this;}
};

inline vec operator+(const vec& a,const vec& b){return vec(a.x + b.x,a.y + b.y,a.z + b.z);}
inline vec operator-(const vec& a,const vec& b){return vec(a.x - b.x,a.y - b.y,a.z - b.z);}
inline vec operator*(const vec& a,const vec& b){return vec(a.x * b.x,a.y * b.y, a.z * b.z);}
inline vec operator/(const vec& a,const float t){return vec(a.x/t,a.y/t,a.z/t);}
inline vec operator*(const vec& a,const float t){return vec(a.x*t,a.y*t,a.z*t);}
inline vec operator*(const float t,const vec &a){return vec(a.x*t,a.y*t,a.z*t);}
inline float dot(const vec &a,const vec &b){return a.x * b.x + a.y * b.y + a.z * b.z;}
inline vec cross(const vec &a,const vec&b){return vec(a.y * b.z - b.y * a.z,-(a.x * b.z - b.x * a.y),(a.x * b.y - a.y * b.x));}