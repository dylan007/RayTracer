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
        unit_dir.normalize();
        float t = 0.5 * (unit_dir.y + 1);
        return (1.0 - t) * vec(1.0,1.0,1.0) + t * vec(0.5,0.7,1.0);
    }
}

hitable *random_scene() {
    int n = 500;
    hitable **list = new hitable*[n+1];
    list[0] =  new sphere(vec(0,-1000,0), 1000, new lambertian(vec(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = rn();
            vec center(a+0.9*rn(),0.2,b+0.9*rn()); 
            if ((center-vec(4,0.2,0)).length() > 0.9) { 
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new sphere(center, 0.2, new lambertian(vec(rn()*rn(), rn()*rn(), rn()*rn())));
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(center, 0.2,
                            new metal(vec(0.5*(1 + rn()), 0.5*(1 + rn()), 0.5*(1 + rn())),  0.5*rn()));
                }
                else {  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec(-4, 1, 0), 1.0, new lambertian(vec(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec(4, 1, 0), 1.0, new metal(vec(0.7, 0.6, 0.5), 0.0));
    return new hitable_list(list,i);
}


void run(int nx,int ny,int ns,int startx,int starty,int lenx,int leny,vector<vector<vector<int>>> &res){
    // cout << "P3\n" << nx << " " << ny << "\n255\n";
    srand(10);
    // hitable *list[5];
    // list[0] = new sphere(vec(0,0,-1),0.5,new lambertian(vec(0.1,0.2,0.5)));
    // list[1] = new sphere(vec(0,-100.5,-1),100.0,new lambertian(vec(1.0,0.3,0.0)));
    // list[2] = new sphere(vec(1,0,-1),0.5,new metal(vec(0.8,0.6,0.2),0.3));
    // // list[3] = new sphere(vec(-1,0,-1),0.5,new metal(vec(0.8,0.8,0.8),1.0));
    // list[3] = new sphere(vec(-1,0,-1),0.5,new dielectric(1.5));
    // list[4] = new sphere(vec(-1,0,-1),-0.45,new dielectric(1.5));
    // hitable *world = new hitable_list(list,5);
    hitable *world = random_scene();
    vec lookfrom(13,2,3);
    vec lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;

    camera cam(lookfrom,lookat,vec(0,1,0),20, float(nx)/float(ny),aperture,dist_to_focus);

    // float R = cos(M_PI/4);
    // hitable *list[2];
    // // list[0] = new sphere(vec(0,0,-1),0.5,new lambertian(vec(0.1,0.2,0.5)));
    // // list[1] = new sphere(vec(0,-100.5,-1),100.0,new lambertian(vec(1.0,0.3,0.0)));
    // list[0] = new sphere(vec(-R,0,-1),R,new lambertian(vec(0,1.0,0)));
    // list[1] = new sphere(vec(R,0,-1),R,new lambertian(vec(1.0,0,0)));
    // hitable *world = new hitable_list(list,2);
    for(int j=starty+leny-1;j>=starty;j--){
        for(int i=startx;i<startx+lenx;i++){
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
            // col.normalize();
            res[i-startx][j-starty][0] = int(255.99 * col.x);
            res[i-startx][j-starty][1] = int(255.99 * col.y);
            res[i-startx][j-starty][2] = int(255.99 * col.z);
            // cout << ir << " " << ig << " " << ib << endl;
        }
    }
}