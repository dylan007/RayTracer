#include<stdio.h>

int main(){
    int nx=2400,ny=1240;
    printf("P3\n%d %d\n255\n",nx,ny);
    int i,j;
    for(j=ny-1;j>=0;j--){
        for(i=0;i<nx;i++){
            float r = (float)(i)/(float)(nx);
            float g = (float)(j)/(float)(ny);
            float b = 0.2;
            int ir = (int)(255.99 * r);
            int ig = (int)(255.99 * g);
            int ib = (int)(255.99 * b);
            printf("%d %d %d\n",ir,ig,ib);
        }
    }
    return 0;
}