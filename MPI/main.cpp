#include<bits/stdc++.h>
#include<math.h>
#include<mpi.h>

using namespace std;

//Define hyperparameters
#define NX 20
#define NY 10
#define NS 10

int main(int argc,char *argv[]){
    //Initializing the MPI Context
    int rank,size;
    string out;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    const int root=0;


    //Initializing common variables for each process.
    int image[NX][NY][3];
    int area = NX * NY;
    int work_area = area / size;
    int wx = (int)sqrt(size);       //Assuming that the number of procs is a perfect square.
    int wy = (int)sqrt(size);       //Number of workers in each row/column.
    int sx = NX/wx;                 //Size of each row.
    int sy = NY/wy;                 //Size of each column.
    int startx = (rank / wy) * sx;
    int starty = (rank % wx) * sy;
    int lenx = sx;
    int leny = sy;
    int pimage[lenx][leny][3];
    out = to_string(rank) + " " + to_string(startx) + " " + to_string(starty) + " " + to_string(lenx) + " " + to_string(leny) + "\n";
    cout << out;


    //Define Custom Datatypes
    // MPI_Datatype block,rblock;
    // int sizes[3] = {NX,NY,3};
    // int subsizes[3] = {wx,wy,3};
    // int starts[3] = {0,0,0};
    // MPI_Type_create_subarray(3,sizes,subsizes,starts,MPI_ORDER_C,MPI_INT,&block);
    // MPI_Type_create_resized(block,0,sy*3,&rblock);
    // MPI_Type_commit(&rblock);    


    // Calculate the pixel values.
    for(int i=startx;i<=startx+lenx-1;i++){
        for(int j=starty;j<=starty+leny-1;j++){
            pimage[i][j][0] = rank;
            pimage[i][j][1] = rank;
            pimage[i][j][2] = rank;
            out = to_string(image[i][j][0]) + " " + to_string(image[i][j][1]) + " " + to_string(image[i][j][2]) + "\n";
            cout << out;
        }
    }
    // MPI_Barrier(MPI_COMM_WORLD);
    // int sendcounts[wx*wy];
    // for(int i=0;i<wx*wy;i++) sendcounts[i] = 1;
    // int displs[wx*wy];
    // int curr=0;
    // for(int i=0;i<wx;i++){
    //     for(int j=0;j<wy;j++){
    //         displs[i*wx + j] = curr;
    //         curr++;
    //     }
    //     curr = wx*sx*sy*i;
    // }
    // //Gather from all the other processes.
    // MPI_Gatherv(&pimage,sx*sy*3,MPI_INT,&image,sendcounts,displs,rblock,0,MPI_COMM_WORLD);


    //Generate the image in process with rank 0.
    // if(rank==root){
    //     out = "P3\n" + to_string(NX) + " " + to_string(NY) + "\n255\n";
    //     cout << out; 
    //     for(int i=0;i<NX;i++){
    //         for(int j=0;j<NY;j++){
    //             out = to_string(i) + " " + to_string(j) + "\n";
    //             cout << out;
                // out = to_string(image[i][j][0]) + " " + to_string(image[i][j][1]) + " " + to_string(image[i][j][2]) + "\n";
    //             // cout << image[i][j][0] << " " << image[i][j][1] << " " << image[i][j][2] << endl;
    //             cout << out;
    //         }
    //     }
    // }
    MPI_Finalize();
    return 0;
}