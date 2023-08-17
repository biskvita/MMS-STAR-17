#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int K ; 

void a(int argc, char* argv[])
{
    if (argc > 3)
    {
        perror(":(\n");
        return;
    }

    unsigned long long N = atoll(argv[2]);
    char* fileName = argv[1];

    FILE* f1 = fopen(fileName, "wb");

    if (!f1)
    {
        perror("File problem...\n");
        exit(1);
    }

    for (unsigned long long i = 1; i <= N; i++)
    {
        fwrite(&i, sizeof(i), 1, f1);
    }

    fclose(f1);
}

int sumDigits(unsigned long long num)
{
    unsigned long long temp = num;
    int sum = 0, remainder;

    while (temp != 0)
    {
        remainder = temp % 10;
        sum = sum + remainder;
        temp = temp / 10;
    }

    return sum; 
}

void childFunc(const char* argvNum, int index, int pipes_fd_list[K][2])
{
    unsigned long long sum = 0;
    unsigned long long curNum = 0; 
    
    FILE* f1 = fopen(argvNum, "rb");

    if (!f1)
    {
        perror("File problem: ");
        return; 
    }

    while(!feof(f1))
    {
        fread(&curNum, sizeof(curNum), 1, f1);
        //printf("cur: %llu\n", curNum);
        sum += sumDigits(curNum); 
    }
    
    write(pipes_fd_list[index][1], &sum, sizeof(sum));
    fclose(f1);
}

void b(int argc, char* argv[])
{
    int pid; 
    int K = argc;
    int pipes_fd_list[K][2]; 

    for (int i = 1; i < argc; i++)
    {
        pipe(pipes_fd_list[i-1]);
        pid = fork();

        if (pid < 0)
        {
            exit(-1);
        }
        else if (pid == 0)
        {
            childFunc(argv[i], i-1, pipes_fd_list);
            break;  
        }
    }
    
    if (pid > 0)
    {
        for (int i = 1; i < argc; i++)
        {
            wait(NULL);
        }
        
        unsigned long long sum_total = 0;
        unsigned long long cur_partial_sum;

        for(int i = 1; i < argc; i++) 
        {
            read(pipes_fd_list[i-1][0], &cur_partial_sum, sizeof(cur_partial_sum));
            printf("%s - %lld\n", argv[i], cur_partial_sum);
            sum_total += cur_partial_sum;
        }

        printf("Total sum of digits: %lld\n", sum_total);
    }

}

int main(int argc, char* argv[])
{
    //a(argc, argv);
    b(argc, argv);

    return 0; 
}