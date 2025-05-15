#include <stdio.h>
#include <omp.h>

int main() {
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();
    #pragma omp critical
        {
            printf("Hello, World! from thread %d of %d\n", thread_id, total_threads);
        }
        if (thread_id == 0) {
            printf("Number of threads: %d\n", total_threads);
        }
    }
    return 0;
}
