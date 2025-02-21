#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int *fib, n;
void *compute_fibonacci(void *arg)
{
    int index = *(int *)arg;
    if (index == 0)
        fib[index] = 0;
    else if (index == 1)
        fib[index] = 1;
    else
        fib[index] = fib[index - 1] + fib[index - 2];
    pthread_exit(NULL);
}
int main()
{
    printf("Enter the number of Fibonacci numbers to generate: ");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    fib = (int *)malloc(n * sizeof(int));
    pthread_t threads[n];
    int indices[n];
    for (int i = 0; i < n; i++)
    {
        indices[i] = i;
        pthread_create(&threads[i], NULL, compute_fibonacci, &indices[i]);
        pthread_join(threads[i], NULL);
    }
    printf("Fibonacci Series: ");
    for (int i = 0; i < n; i++)
        printf("%d ", fib[i]);
    printf("\n");

    free(fib);
    return 0;
}