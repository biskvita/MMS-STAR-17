#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 16

sem_t semaphore;

int getRandom()
{
    return (rand() % (5 - 1 + 1)) + 1;
}

void* routinee(void* args)
{
    printf("Thread %d is waiting...\n", *(int*)args);
    sem_wait(&semaphore);

    int num = getRandom();
    sleep(num);
    printf("Thread %d is executing after %d seconds of sleep\n", *(int*)args, num);

    free(args);
    sem_post(&semaphore);
}

int main()
{
    pthread_t threads[THREAD_NUM];
    sem_init(&semaphore, 0, 32);

    for (int i = 0; i < THREAD_NUM; i++)
    {
        int* a = malloc(sizeof(int));
        *a = i; 

        if(pthread_create(&threads[i], NULL, &routinee, a) != 0)
        {
            return 1; 
        }
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        if(pthread_join(threads[i], NULL) != 0)
        {
            return 2; 
        }
    }
    
    sem_destroy(&semaphore);

    return 0; 
}