#include <stdio.h>
#include <omp.h>

void task1(){printf("Task 1 is running on thread %d\n", omp_get_thread_num());}
void task2(){printf("Task 2 is running on thread %d\n", omp_get_thread_num());}
void task3(){printf("Task 3 is running on thread %d\n", omp_get_thread_num());}
void task4(){printf("Task 4 is running on thread %d\n", omp_get_thread_num());}
void task5(){printf("Task 5 is running on thread %d\n", omp_get_thread_num());}

int main(){
    printf("Starting multitasking with OpenMP...\n");

#pragma omp parallel
    {
    #pragma omp single
        {
        #pragma omp task
            task1();

        #pragma omp task
            task2();

        #pragma omp task
            task3();

        #pragma omp task
            task4();

        #pragma omp task
            task5();
        }
    }
    printf("All tasks completed.\n");
    return 0;
}

