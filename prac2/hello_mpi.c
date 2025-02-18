#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank (ID) of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the total number of processes
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Each process prints its own message
    printf("Hello World from process %d out of %d\n", rank, size);

    // Finalize MPI environment
    MPI_Finalize();
    return 0;
}
