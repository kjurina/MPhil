#include <iostream>
#include <mpi.h>

#define SIZE 102400

int main(){
  int rank;
  int size;
  void *ptr;
	
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Status st;

	
  ptr=malloc(SIZE);
	
  if (rank == 0){
    //MPI_Send(ptr, SIZE, MPI_CHAR, (rank + 1), 1, MPI_COMM_WORLD);
    //MPI_Recv(ptr, SIZE, MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Sendrecv(ptr, SIZE, MPI_CHAR, (rank + 1), 0, ptr, SIZE, MPI_CHAR, \
    1, MPI_ANY_TAG, MPI_COMM_WORLD, &st); 
  }
  if (rank == 1){
    //MPI_Recv(ptr, SIZE, MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //MPI_Send(ptr, SIZE, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    MPI_Sendrecv(ptr, SIZE, MPI_CHAR, (rank - 1), 1, ptr, SIZE, MPI_CHAR, \
    0, MPI_ANY_TAG, MPI_COMM_WORLD, &st); 
  }

  //MPI_Sendrecv_replace(); 
	
  std::cout << "Rank " << rank << "finished" << std::endl;

  MPI_Finalize();
  return 0;
}
