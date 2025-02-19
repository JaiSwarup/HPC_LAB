#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int size, rank;
    int n = 100000;
    int *array = NULL;
    int local_sum = 0, total_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        array = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++)
        {
            array[i] = rand() % 10;
        }
    }

    int chunk_size = n / size;
    int *sub_array = (int *)malloc(chunk_size * sizeof(int));

    MPI_Scatter(array, chunk_size, MPI_INT, sub_array, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk_size; i++)
    {
        local_sum += sub_array[i];
    }

    printf("Process %d contributed: %d\n", rank, local_sum);

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("Total sum of array elements = %d\n", total_sum);
        free(array);
    }

    free(sub_array);
    MPI_Finalize();

    return 0;
}
