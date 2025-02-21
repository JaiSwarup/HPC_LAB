#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_THREADS 5
pthread_mutex_t lock;
int shared_resource = 0;
void *thread_function(void *arg)
{
    int thread_id = *(int *)arg;
    pthread_mutex_lock(&lock);
    printf("Thread %d: Entering critical section.\n", thread_id);
    shared_resource++;
    printf("Shared resource value: %d\n", shared_resource);
    sleep(1);
    printf("Thread %d: Leaving critical section.\n", thread_id);
    pthread_mutex_unlock(&lock);
    return NULL;
}
int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    printf("Final shared resource value: %d\n", shared_resource);

    return 0;
}