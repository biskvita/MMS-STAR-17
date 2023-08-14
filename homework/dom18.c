#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 7
#define INIT_BALANCE 1000

typedef struct Account
{
    int balance; 
} Account; 

Account account;
pthread_mutex_t mutex; 

void* deposit(void* arg)
{
    pthread_mutex_lock(&mutex);
    int amount = *((int*)arg);
    account.balance = account.balance + amount; 
    pthread_mutex_unlock(&mutex);
}

void* withdraw(void* arg)
{
    pthread_mutex_lock(&mutex);
    int amount = *((int*)arg);
    account.balance = account.balance - amount; 
    pthread_mutex_unlock(&mutex);
}

int main()
{
    account.balance = INIT_BALANCE;
    pthread_t theads[NUM_THREADS];
    int deposit_amount = 200;
    int deposit_withdraw = 100; 
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (i % 2 == 0)
        {
            pthread_create(&theads[i], NULL, &deposit, &deposit_amount);
        }
        else
        {
            pthread_create(&theads[i], NULL, &withdraw, &deposit_withdraw);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(theads[i], NULL);
    }

    printf("MONEY: %d\n", account.balance);
    pthread_mutex_destroy(&mutex);

    return 0; 
}