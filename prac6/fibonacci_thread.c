#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10  // Number of Fibonacci numbers

int fibonacci[N];  // Shared array to store Fibonacci series

// Function to generate Fibonacci number for each thread
void* generate_fibonacci(void* arg) {
    int index = *(int*)arg;
    
    // Compute Fibonacci number
    if (index == 0) {
        fibonacci[index] = 0;
    }
    else if (index == 1) {
        fibonacci[index] = 1;
    }
    else {
        fibonacci[index] = fibonacci[index-1] + fibonacci[index-2];
    }

    printf("Thread %d computed Fibonacci[%d] = %d\n", index, index, fibonacci[index]);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[N];
    int indexes[N];

    // Create N threads
    for (int i = 0; i < N; i++) {
        indexes[i] = i;
        pthread_create(&threads[i], NULL, generate_fibonacci, (void*)&indexes[i]);
    }

    // Join all threads
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the complete Fibonacci series
    printf("\nFibonacci Series of %d terms:\n", N);
    for (int i = 0; i < N; i++) {
        printf("%d ", fibonacci[i]);
    }
    printf("\n");

    return 0;
}
