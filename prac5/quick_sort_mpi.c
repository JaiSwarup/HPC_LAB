#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 16

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    int rank, size;
    int arr[N];
    int local_size;
    int *local_array;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_size = N / size;
    local_array = (int *)malloc(local_size * sizeof(int));

    if (rank == 0)
    {
        srand(time(0));
        printf("Unsorted Array:\n");
        for (int i = 0; i < N; i++)
        {
            arr[i] = rand() % 100;
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    MPI_Scatter(arr, local_size, MPI_INT, local_array, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    quickSort(local_array, 0, local_size - 1);

    MPI_Gather(local_array, local_size, MPI_INT, arr, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        printf("\nPartially Sorted Array (Before Final Merge):\n");
        printArray(arr, N);

        quickSort(arr, 0, N - 1);

        printf("\nFully Sorted Array:\n");
        printArray(arr, N);
    }

    free(local_array);
    MPI_Finalize();
    return 0;
}
