#include<iostream>
#include "sphere.hpp"
#include "hitable_list.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "perlin.hpp"
#include "rect.hpp"
#include "bvh.hpp"
#include "diffuse.hpp"
#include<math.h>
#define MAXFLOAT 3.402823e+38
using namespace std;

///***********///
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
vec color(ray &r, hitable *world,int depth){
    hit_record rec;
    if(world->hit(r,0.001,MAXFLOAT,rec)){
        ray scattered;
        vec attenuation;
        vec emitted = rec.mat_ptr->emitted(rec.u,rec.v,rec.p);
        if(depth<50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered))
            return emitted + attenuation * color(scattered,world,depth+1);
        else
            return emitted;
    }
    else{
        return vec(0,0,0);
    }
}


//vec color(ray &r, hitable *world,int depth){
//    hit_record rec;
//    if(world->hit(r,0.001,MAXFLOAT,rec)){
//        ray scattered;
//        vec attenuation;
//        vec emitted = rec.mat_ptr->emitted(rec.u,rec.v,rec.p);
//        if(depth<50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered))
//            return emitted + attenuation * color(scattered,world,depth+1);
//        else
//            return emitted;
//        // vec target = rec.p + rec.normal + random_in_unit_sphere();
//        // ray tmp = ray(rec.p,target-rec.p);
//        // return 0.5 * color(tmp, world);
//        // return 0.5 * vec(rec.normal.x + 1,rec.normal.y + 1 , rec.normal.z + 1);
//    }
//    else{
////        vec unit_dir = r.direction();
////        unit_dir.normalize();
////        float t = 0.5 * (unit_dir.y + 1);
////        return (1.0 - t) * vec(1.0,1.0,1.0) + t * vec(0.5,0.7,1.0);
//            return vec(0,0,0);
//    }
//}
hitable *two_perlin_spheres(){
    texture *pertext = new noise_texture();
    hitable **list = new hitable*[2];
    list[0] = new sphere(vec(0,-1000,0),1000,new lambertian(pertext));
    list[1] = new sphere(vec(0,2,0),2,new lambertian(pertext));
    return new hitable_list(list,2);
}

hitable *simple_list()
{
    texture *pertext = new noise_texture(4);
    hitable **list = new hitable*[4];
    list[0] = new sphere(vec(0,-1000,0),1000,new lambertian(pertext));
    list[1] = new sphere(vec(0,2,0),2,new lambertian(pertext));
    list[2] = new sphere(vec(0,7,0),2,new diffuse_light(new constant_texture(vec(4,4,4))));
    list[3] = new xy_rect(3,5,1,3,-2,new diffuse_light(new constant_texture(vec(4,4,4))));
    return new hitable_list(list,4);
}

hitable* cornell_box()
{
    hitable **list = new hitable*[6];
    int i=0;
    material *red= new lambertian(new constant_texture(vec(0.65,0.05,0.05)));
    material *white= new lambertian(new constant_texture(vec(0.73,0.73,0.73)));
    material *green= new lambertian(new constant_texture(vec(0.12,0.45,0.15)));
    material *light= new diffuse_light(new constant_texture(vec(15,15,15)));
    list[i++]= new flip_normals(new yz_rect(0,555,0,555,555,green));
    list[i++]= new yz_rect(0,555,0,555,0,red);
    list[i++]= new xz_rect(213,343,227,332,554,light);
    list[i++]= new flip_normals(new xz_rect(0,555,0,555,555,white));
    list[i++]= new xz_rect(0,555,0,555,0,white);
    list[i++]= new flip_normals(new xy_rect(0,555,0,555,555,white));
    return new hitable_list(list,i);
}
hitable *random_scene() {
    int n = 500;
    hitable **list = new hitable*[n+1];
    texture *checker = new checker_texture(new constant_texture(vec(0.2,0.3,0.1)),new constant_texture(vec(0.9,0.9,0.9)));
    list[0] =  new sphere(vec(0,-1000,0), 1000, new lambertian(checker));
    int i = 1;
    for (int a = -10; a < 10; a++) {
        for (int b = -10; b < 10; b++) {
            float choose_mat = rn();
            vec center(a+0.9*rn(),0.2,b+0.9*rn());
            if ((center-vec(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new moving_sphere(center, center+vec(0,0.5*rn(),0),0.0,1.0,0.2, new lambertian(new constant_texture(vec(rn()*rn(), rn()*rn(), rn()*rn()))));
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
    list[i++] = new sphere(vec(-4, 1, 0), 1.0, new lambertian(new constant_texture(vec(0.4, 0.2, 0.1))));
    list[i++] = new sphere(vec(4, 1, 0), 1.0, new metal(vec(0.7, 0.6, 0.5), 0.0));
    return new bvh_node(list,i,0.0,1.0);
}

int main(){
    int nx = 600;
    int ny = 300;
    int ns = 200;
    FILE* fim=fopen("image.ppm","w");
    vec lookfrom(278,278,-800);
    vec lookat(278,278,0);
    float focus_dist = 10.0;//(lookfrom-lookat).length();
    float aperture =  0.0;
    //cout << "P3\n" << nx << " " << ny << "\n255\n";
    fprintf(fim,"P3\n%d %d\n255\n",nx,ny);
    hitable *world = cornell_box()  ;
    camera cam(lookfrom,lookat,vec(0,1,0),40,float(nx)/float(ny),aperture,focus_dist,0.0,1.0);
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
            fprintf(fim,"%d %d %d\n",ir,ig,ib);
        }
    }
}
