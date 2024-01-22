#include <iostream>
#include <mpi.h>
int main(int argc, char *argv[])
{
  int major, minor;

  //MPI_Comm_size(MPI_COMM)	
  MPI_Get_version(&major, &minor);
  std::cout << "Run-time MPI version is " << major << "." << minor << std::endl;
  return 0;
}
