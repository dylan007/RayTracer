#include<iostream>
#include "sphere.hpp"
#include "hitable_list.hpp"
#include "camera.hpp"
#include "material.hpp"
#include<math.h>
using namespace std;

// float hit_sphere(vec center,float radius,ray r){
//     vec oc = r.origin() - center;
//     float a = dot(r.B,r.B);
//     float b = 2.0*dot(r.B,oc);
//     float c = dot(oc,oc) - radius * radius;
//     float disc = b*b - 4.0*a*c;  
//     if(disc>=0)
//         return (-b - sqrt(disc))/(2.0*a);
//     else
//         return -1.0;
// }

// vec color(ray r){
//     float ret = hit_sphere(vec(0,0,-1),0.5,r);
//     // cout << ret << endl;
//     if(ret>0.0){
//         vec N = r.get_point(ret) - vec(0,0,-1);
//         if(N.length()!=0)
//             N.normalize();
//         return 0.5 * vec(N.x + 1,N.y + 1,N.z + 1);
//     }
//     vec unit_dir = r.direction();
//     unit_dir.normalize();
//     float t = 0.5 * (unit_dir.y + 1.0);
//     return (1-t) * vec(1.0,1.0,1.0) + t * vec(1,0,0);
// }


vec color(ray &r, hitable *world,int depth){
    hit_record rec;
    if(world->hit(r,0.001,MAXFLOAT,rec)){
        ray scattered;
        vec attenuation;
        if(depth<50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered))
            return attenuation * color(scattered,world,depth+1);
        else
            return vec(0,0,0);
        // vec target = rec.p + rec.normal + random_in_unit_sphere();
        // ray tmp = ray(rec.p,target-rec.p);
        // return 0.5 * color(tmp, world);
        // return 0.5 * vec(rec.normal.x + 1,rec.normal.y + 1 , rec.normal.z + 1);
    }
    else{
        vec unit_dir = r.direction();
        float t = 0.5 * (unit_dir.y + 1);
        return (1.0 - t) * vec(1,1,1) + t * vec(0.5,0.7,1.0);
    }
}

int main(){
    int nx = 2140;
    int ny = 1080;
    int ns = 10;
    cout << "P3\n" << nx << " " << ny << "\n255\n";
    hitable *list[4];
    list[0] = new sphere(vec(0,0,-1),0.5,new lambertian(vec(0.8,0.3,0.3)));
    list[1] = new sphere(vec(0,-100.5,-1),100.0,new lambertian(vec(0.8,0.8,0.0)));
    list[2] = new sphere(vec(1,0,-1),0.5,new metal(vec(0.8,0.6,0.2)));
    list[3] = new sphere(vec(-1,0,-1),0.5,new metal(vec(0.8,0.8,0.8)));
    hitable *world = new hitable_list(list,4);
    camera cam;
    for(int j=ny-1;j>=0;j--){
        for(int i=0;i<nx;i++){
            vec col(0,0,0);
            for(int s=0;s < ns;s++){
                float u = float(i + rn())/float(nx);
                float v = float(j + rn())/float(ny);
                ray r = cam.get_ray(u,v);
                vec p = r.get_point(2.0);
                col += color(r,world,0);
            }
            col /= ns;
            col = vec(sqrt(col.x),sqrt(col.y),sqrt(col.y));
            int ir = int(255.99 * col.x);
            int ig = int(255.99 * col.y);
            int ib = int(255.99 * col.z);
            cout << ir << " " << ig << " " << ib << endl;
        }
    }
}