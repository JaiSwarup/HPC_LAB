#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4

void initializeMatrix(int matrix[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
}

void printMatrix(int matrix[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    int rank, size;
    int A[N][N], B[N][N], C[N][N];
    int local_A[N][N], local_C[N][N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Matrix A:\n");
        initializeMatrix(A);
        printMatrix(A);

        printf("\nMatrix B:\n");
        initializeMatrix(B);
        printMatrix(B);
    }

    MPI_Bcast(B, N * N, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(A, N * N / size, MPI_INT, local_A, N * N / size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < N / size; i++)
    {
        for (int j = 0; j < N; j++)
        {
            local_C[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                local_C[i][j] += local_A[i][k] * B[k][j];
            }
        }
    }

    MPI_Gather(local_C, N * N / size, MPI_INT, C, N * N / size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("\nResultant Matrix C (A x B):\n");
        printMatrix(C);
    }

    MPI_Finalize();
    return 0;
}
