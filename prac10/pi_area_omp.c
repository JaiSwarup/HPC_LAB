#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_POINTS 1000000

int main() {
    int count = 0;
    double x, y;
    int i;
    int radius = 5; 

    double start_time = omp_get_wtime();

    #pragma omp parallel for private(x, y) reduction(+:count)
    for (i = 0; i < NUM_POINTS; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) {
            count++;
        }
    }

    double pi = 4.0 * (double)count / NUM_POINTS;
    double area = pi * radius * radius;

    double end_time = omp_get_wtime();

    printf("Estimated Pi = %f\n", pi);
    printf("Radius = %d\n", radius);
    printf("Area of Circle = %f\n", area);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}
