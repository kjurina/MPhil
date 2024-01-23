#include <iostream>
#include <mpi.h>

int main(void)
{
  int rank, size;
  MPI_Status st;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int v = 0;

  if(rank == 0)
  {
    MPI_Send(&v, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD);
    MPI_Recv(&v, 1, MPI_INT, size - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
  }
  else
  {
    MPI_Recv(&v, 1, MPI_INT, (rank - 1), MPI_ANY_TAG, MPI_COMM_WORLD, &st);

    v += rank;
      std::cout << "Hit rank " << rank << " v = " << v << std::endl;

    MPI_Send(&v, 1, MPI_INT, (rank + 1) % size, 1, MPI_COMM_WORLD);
  }

  if( rank == 0 )
  {
    std::cout << v << " and it should be " << (size*(size-1))/2 << std::endl;
  }
  
  MPI_Finalize();
}