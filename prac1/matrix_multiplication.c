#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 2000

int main()
{
    int **A = (int **)malloc(SIZE * sizeof(int *));
    int **B = (int **)malloc(SIZE * sizeof(int *));
    int **C = (int **)malloc(SIZE * sizeof(int *));

    for (int i = 0; i < SIZE; i++)
    {
        A[i] = (int *)malloc(SIZE * sizeof(int));
        B[i] = (int *)malloc(SIZE * sizeof(int));
        C[i] = (int *)malloc(SIZE * sizeof(int));
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            A[i][j] = (int)(rand() % 10);
            B[i][j] = (int)(rand() % 10);
            C[i][j] = 0.0;
        }
    }

    clock_t start = clock();

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < SIZE; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // End time measurement
    clock_t end = clock();

    // Calculate time taken in seconds
    int time_spent = (int)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %d seconds\n", time_spent);

    // Free memory
    for (int i = 0; i < SIZE; i++)
    {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
