#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    int fd[3][2]; 

    for (int i = 0; i < 3; i++)
    {
        if (pipe(fd[i]) < 0)
        { 
            return 1; 
        }
    }

    int myValue = 7;
    int pid1 = fork();

    if (pid1 < 0) 
    { 
        return 2;
    }
    else if (pid1 == 0)
    {
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);

        int received; 
        read(fd[0][0], &received, sizeof(received));
        printf("RECEIVED IN CHILD1 FROM PARENT: %d\n", received);
        received *= 3; 

        write(fd[1][1], &received, sizeof(received));
        printf("SEND FROM CHILD1: %d\n", received);

        close(fd[0][0]);
        close(fd[1][1]);
    }

    int pid2 = fork();

    if (pid2 < 0) 
    { 
        return 2;
    }
    else if (pid2 == 0 && pid1 > 0)
    {
        close(fd[0][1]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);

        int received; 
        read(fd[1][0], &received, sizeof(received));
        printf("RECEIVED IN CHILD2 FROM CHILD1: %d\n", received);
        
        if (received % 2 == 0)
        {
            received = received * received;
        }
        else
        {
            received = received / 2; 
        }

        write(fd[2][1], &received, sizeof(received));
        printf("SEND FROM CHILD2: %d\n", received);

        close(fd[1][0]);
        close(fd[2][1]);
    }

    if (pid1 > 0 && pid2 > 0)
    {
        close(fd[0][0]);
        close(fd[1][0]);
        close(fd[1][1]);
        close(fd[2][1]);

        write(fd[0][1], &myValue, sizeof(myValue));
        printf("SEND FROM PARENT: %d\n", myValue);

        read(fd[2][0], &myValue, sizeof(myValue));
        printf("RECEIVED IN PARENT FROM CHILD2: %d\n", myValue);

        close(fd[0][1]);
        close(fd[2][0]);
    }

    return 0;
}