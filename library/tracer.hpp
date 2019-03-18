#include<iostream>
#include "sphere.hpp"
#include "hitable_list.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "bvh.hpp"
#include "texture.hpp"
#include "box.hpp"
#include "aarect.hpp"
#include "constant_medium.hpp"
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
        vec emitted = rec.mat_ptr->emitted(rec.u,rec.v,rec.p);
        if(depth<50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered))
            return emitted + attenuation * color(scattered,world,depth+1);
        else
            return emitted;
        // vec target = rec.p + rec.normal + random_in_unit_sphere();
        // ray tmp = ray(rec.p,target-rec.p);
        // return 0.5 * color(tmp, world);
        // return 0.5 * vec(rec.normal.x + 1,rec.normal.y + 1 , rec.normal.z + 1);
    }
    else{
//        vec unit_dir = r.direction();
//        unit_dir.normalize();
//        float t = 0.5 * (unit_dir.y + 1);
//        return (1.0 - t) * vec(1.0,1.0,1.0) + t * vec(0.5,0.7,1.0);
            return vec(0,0,0);
    }
}


hitable *two_spheres(){
    texture *checker = new checker_texture(new constant_texture(vec(0.2,0.3,0.1)),new constant_texture(vec(0.9,0.9,0.9)));
    int n = 50;
    hitable **list = new hitable*[n+1];
    list[0] = new sphere(vec(0,-10,0),10,new lambertian(checker));
    list[1] = new sphere(vec(0,10,0),10,new lambertian(checker));
    return new hitable_list(list,2);
}

hitable *two_perlin_spheres(){
    texture *pertext = new noise_texture(4);
    hitable **list = new hitable*[2];
    list[0] = new sphere(vec(0,-1000,0),1000,new lambertian(pertext));
    list[1] = new sphere(vec(0,2,0),2,new lambertian(pertext));
    return new hitable_list(list,2);
}

hitable *simple_light()
{
    texture *pertext = new noise_texture(4);
    hitable **list = new hitable*[4];
    list[0] = new sphere(vec(0,-1000,0),1000,new lambertian(pertext));
    list[1] = new sphere(vec(0,2,0),2,new lambertian(pertext));
    list[2] = new sphere(vec(0,7,0),2,new diffuse_light(new constant_texture(vec(4,4,4))));
    list[3] = new xy_rect(3,5,1,3,-2,new diffuse_light(new constant_texture(vec(4,4,4))));
    return new hitable_list(list,4);
}


hitable* cornell_smoke()
{
    hitable **list = new hitable*[10];
    int i=0;
    material *red= new lambertian(new constant_texture(vec(0.65,0.05,0.05)));
    material *white= new lambertian(new constant_texture(vec(0.73,0.73,0.73)));
    material *green= new lambertian(new constant_texture(vec(0.12,0.45,0.15)));
    material *light= new diffuse_light(new constant_texture(vec(7,7,7)));
    list[i++] = new flip_normals(new yz_rect(0,555,0,555,555,green));
    list[i++] = new yz_rect(0,555,0,555,0,red);
    list[i++] = new xz_rect(113,443,127,432,554,light);
    list[i++] = new flip_normals(new xz_rect(0,555,0,555,555,white));
    list[i++] = new xz_rect(0,555,0,555,0,white);
    list[i++] = new flip_normals(new xy_rect(0,555,0,555,555,white));
    // list[i++] = new box(vec(130,0,65),vec(295,165,230),white);
    // list[i++] = new box(vec(265,0,295),vec(430,330,460),white);
    hitable *b1 = new translate(new rotate_y(new box(vec(0,0,0),vec(165,165,165),white),-18),vec(130,0,65));
    hitable *b2 = new translate(new rotate_y(new box(vec(0,0,0),vec(165,330,165),white),15),vec(265,0,295));
    list[i++] = new constant_medium(b1,0.01,new constant_texture(vec(1,1,1)));
    list[i++] = new constant_medium(b2,0.01,new constant_texture(vec(0,0,0)));
    return new hitable_list(list,i);
}


hitable *cornell_box() {
    hitable **list = new hitable*[8];
    int i = 0;
    material *red = new lambertian( new constant_texture(vec(0.65, 0.05, 0.05)) );
    material *white = new lambertian( new constant_texture(vec(0.73, 0.73, 0.73)) );
    material *green = new lambertian( new constant_texture(vec(0.12, 0.45, 0.15)) );
    material *light = new diffuse_light( new constant_texture(vec(15, 15, 15)) );
    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new xz_rect(213, 343, 227, 332, 554, light);
    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));
    list[i++] = new translate(new rotate_y(new box(vec(0, 0, 0), vec(165, 165, 165), white), -18), vec(130,0,65));
    list[i++] = new translate(new rotate_y(new box(vec(0, 0, 0), vec(165, 330, 165), white),  15), vec(265,0,295));
    return new hitable_list(list,i);
}

hitable *final() {
    int nb = 20;
    hitable **list = new hitable*[30];
    hitable **boxlist = new hitable*[10000];
    hitable **boxlist2 = new hitable*[10000];
    material *white = new lambertian( new constant_texture(vec(0.73, 0.73, 0.73)) );
    material *ground = new lambertian( new constant_texture(vec(0.48, 0.83, 0.53)) );
    int b = 0;
    for (int i = 0; i < nb; i++) {
        for (int j = 0; j < nb; j++) {
            float w = 100;
            float x0 = -1000 + i*w;
            float z0 = -1000 + j*w;
            float y0 = 0;
            float x1 = x0 + w;
            float y1 = 100*(rn()+0.01);
            float z1 = z0 + w;
            boxlist[b++] = new box(vec(x0,y0,z0), vec(x1,y1,z1), ground);
        }
    }
    int l = 0;
    list[l++] = new bvh_node(boxlist, b, 0, 1);
    material *light = new diffuse_light( new constant_texture(vec(7, 7, 7)) );
    list[l++] = new xz_rect(123, 423, 147, 412, 554, light);
    vec center(400, 400, 200);
    list[l++] = new moving_sphere(center, center+vec(30, 0, 0), 0, 1, 50, new lambertian(new constant_texture(vec(0.7, 0.3, 0.1))));
    list[l++] = new sphere(vec(260, 150, 45), 50, new dielectric(1.5));
    list[l++] = new sphere(vec(0, 150, 145), 50, new metal(vec(0.8, 0.8, 0.9), 10.0));
    hitable *boundary = new sphere(vec(360, 150, 145), 70, new dielectric(1.5));
    list[l++] = boundary;
    list[l++] = new constant_medium(boundary, 0.2, new constant_texture(vec(0.2, 0.4, 0.9)));
    boundary = new sphere(vec(0, 0, 0), 5000, new dielectric(1.5));
    list[l++] = new constant_medium(boundary, 0.0001, new constant_texture(vec(1.0, 1.0, 1.0)));
    // int nx, ny, nn;
    // unsigned char *tex_data = stbi_load("earthmap.jpg", &nx, &ny, &nn, 0);
    // material *emat =  new lambertian(new image_texture(tex_data, nx, ny));
    texture *pertext = new noise_texture(4);
    list[l++] = new sphere(vec(400,200, 400), 100, new lambertian(pertext));
    list[l++] =  new sphere(vec(220,280, 300), 80, new lambertian(pertext));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxlist2[j] = new sphere(vec(165*rn(), 165*rn(), 165*rn()), 10, white);
    }
    list[l++] =   new translate(new rotate_y(new bvh_node(boxlist2,ns, 0.0, 1.0), 15), vec(-100,270,395));
    return new hitable_list(list,l);
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

void run(int nx,int ny,int ns,int startx,int starty,int lenx,int leny,vector<vector<vector<int>>> &res){
    // cout << "P3\n" << nx << " " << xy_recty << "\n255\n";
    srand(10);
    // hitable *list[5];
    // list[0] = new sphere(vec(0,0,-1xy_rect,0.5,new lambertian(vec(0.1,0.2,0.5)));
    // list[1] = new sphere(vec(0,-100xy_rect5,-1),100.0,new lambertian(vec(1.0,0.3,0.0)));
    // list[2] = new sphere(vec(1,0,-1xy_rect,0.5,new metal(vec(0.8,0.6,0.2),0.3));
    // // list[3] = new sphere(vec(-1,xy_rect,-1),0.5,new metal(vec(0.8,0.8,0.8),1.0));
    // list[3] = new sphere(vec(-1,0,-xy_rect),0.5,new dielectric(1.5));
    // list[4] = new sphere(vec(-1,0,-xy_rect),-0.45,new dielectric(1.5));
    // hitable *world = new hitable_lixy_rectt(list,5);
    // hitable *world = two_spheres();
    // hitable *world = two_perlin_spheres();
    // hitable *world = simple_light();
    // hitable *world = cornell_box();
    hitable *world = final();
    // vec lookfrom(13,2,3);
    // vec lookat(0,0,0);
    // float dist_to_focus = 10.0;
    // float aperture = 0.1;
    vec lookfrom(278,278,-800);
    vec lookat(278,278,0);
    float dist_to_focus = 10.0;//(lookfrom-lookat).length();
    float aperture =  0.0;

    camera cam(lookfrom,lookat,vec(0,1,0),30, float(nx)/float(ny),aperture,dist_to_focus,0.0,1.0);

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
