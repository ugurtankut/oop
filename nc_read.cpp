#include<iostream>
#include<netcdfcpp.h>
using namespace std;

// function definitions
float** allocate(int nx, int ny, float init);

int main(){
  // open file
  NcFile ifile("output.nc", NcFile::ReadOnly);
  if (!ifile.is_valid()) {
    cout << "can not open netcdf file! exiting ...";
    return -1;
  }
  cout << "Number of dimensions = " << ifile.num_dims() << endl;
  cout << "Number of variables  = " << ifile.num_vars() << endl;

  //NcDim *dim_x = ifile.get_dim('x');
  //long nx = dim_x->size();
  //cout << "Size of x dimension = " << dim_x->size() << endl;

  // define 2d array
  float **var = NULL;
  var = allocate(52, 52, 0.0);

  // read netcdf variable
  NcVar *zeta = ifile.get_var("zeta");
  long rec = 5;
  NcValues *val = zeta->get_rec(rec);
  //for (int i = 0; i < val->num(); i++)
  //  cout << i << " " << val->as_float(i) << endl;  
  
  int k = 0;
  for (int i = 0; i < 52; i++)
    for (int j = 0; j < 52; j++)
       var[i][j] = val->as_float(k);
       k++;

  //close file
  ifile.close();

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
