#include <stdio.h>
#include <omp.h>

#define N 6

void loop_schedule_demo(char *schedule_type){
    int i, tid;
    printf("\nSchedule Type: %s\n", schedule_type);

#pragma omp parallel for private(i, tid) schedule(runtime)
    for (i = 0; i < N; i++){
        tid = omp_get_thread_num();
        printf("Iteration %2d is executed by thread %d\n", i, tid);
    }
}

int main(){
    int i, tid;

    omp_set_num_threads(3);

    printf("=== Default Scheduling ===\n");
#pragma omp parallel for private(i, tid)
    for (i = 0; i < N; i++){
        tid = omp_get_thread_num();
        printf("Iteration %2d is executed by thread %d\n", i, tid);
    }

    omp_set_schedule(omp_sched_static, 2);
    loop_schedule_demo("Static, chunk=2");

    omp_set_schedule(omp_sched_dynamic, 2);
    loop_schedule_demo("Dynamic, chunk=2");
    return 0;
}
