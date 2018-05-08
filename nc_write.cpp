#include<iostream>
#include<netcdfcpp.h>
using namespace std;

// function definitions
float** allocate(int nx, int ny, float init);

int main(){
  // open file
  NcFile ofile("output_new.nc", NcFile::Replace);
  if (!ofile.is_valid()) {
    cout << "can not open netcdf file! exiting ...";
    return -1;
  }

  // add dimensions
  NcDim *dim_x = ofile.add_dim("x", 52);
  NcDim *dim_y = ofile.add_dim("y", 52);
  NcDim *dim_t = ofile.add_dim("time");

  // create variables
  NcVar *var_z = ofile.add_var("zeta", ncFloat, dim_t, dim_y, dim_x);
  var_z->add_att("units", "meter");
  var_z->add_att("long_name", "free surface height");

  // fill with data
  float **var = NULL;
  var = allocate(52, 52, 0.0);

  for (int k = 0; k < 5; k++) {
    for (int i = 0; i < 52; i++)
      for (int j = 0; j < 52; j++)
        var[i][j] = (float) ((i*52+j)*k);
    var_z->put_rec(&var[0][0], k);
  } 

  //close file
  ofile.close();

  return 0;
}

// allocate 2d contiguous array (ny: row, nx: column)
float** allocate(int nx, int ny, float init) {
  // allocate 2d contiguous array 
  float** A = new float*[ny];
  float*  B = new float[nx*ny];
  for (int j = 0; j < ny; j++) {
     A[j] = &(B[j*nx]); 
  }
 
  // init
  for (int j = 0; j < ny; j++) {
     for (int k = 0; k < nx; k++) {
       A[j][k] = init;
     }
  }  
  return(A);
}
