#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ARRAY_SIZE 10

void parent_process(int pipe1[2], int pipe2[2], int pipe3[2]) 
{
    close(pipe2[0]);
    close(pipe2[1]);
    close(pipe1[0]);
    close(pipe3[0]);

    //printf("------PROCESS PARENT------\n");
    int arr[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        arr[i] = rand() % 100; 
    }

    if (write(pipe1[1], &arr, sizeof(arr)) == -1)
    {
        return; 
    }

    printf("PARENT: Array sent to PIPE1: ");

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
    int received;
    
    if (write(pipe3[1], &received, sizeof(received)) == -1)
    {
        return ; 
    }

    printf("PARENT: New Sum received from PIPE3 : %d\n", received);
    printf("RECEIVED: %d\n", received);

    close(pipe3[1]);
    close(pipe1[1]);
}

void process_A(int pipe1[2], int pipe2[2]) 
{
    close(pipe1[1]);
    close(pipe2[0]);

    //printf("------PROCESS A------\n");
    int arr2[ARRAY_SIZE];

    if (read(pipe1[0], &arr2, sizeof(arr2)) == -1)
    {
        return; 
    }

    printf("Array received from PIPE1\n");

    int sum = 0;

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        sum += arr2[i];
    }

    if (write(pipe2[1], &sum, sizeof(sum)) == -1)
    {
        return; 
    }

    printf("Sum sent to PIPE2: %d\n", sum);
    close(pipe2[1]);
    close(pipe1[0]);
}

void process_B(int pipe2[2], int pipe3[2]) 
{
    close(pipe2[1]);
    close(pipe3[0]);
    
    //printf("------PROCESS B------\n");
    int sum; 

    if (read(pipe2[0], &sum, sizeof(sum)) == -1)
    {
        return; 
    }

    printf("Sum received from PIPE2: %d\n", sum);
    sum = sum * sum; 

    if (write(pipe3[1], &sum, sizeof(sum)) == -1)
    {
        return; 
    }

    printf("New Sum sent to PIPE3: %d\n", sum);
    close(pipe3[1]);
    close(pipe2[0]);
}

int main() 
{
    int pipe1[2], pipe2[2], pipe3[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1) 
    {
        perror("Pipe creation failed.");
        exit(1);
    }

    pid_t pid_A = fork();

    if (pid_A == 0) 
    {
        process_A(pipe1, pipe2);
    } 
    else if (pid_A > 0) 
    {
        pid_t pid_B = fork();

        if (pid_B == 0) 
        {
            process_B(pipe2, pipe3);
        } 
        else if (pid_B > 0) 
        {
            parent_process(pipe1, pipe2, pipe3);
            wait(NULL);
            wait(NULL);
        } 
        else 
        {
            exit(1);
        }
    }
    else 
    {
        exit(1);
    }
  
    return 0; 
}