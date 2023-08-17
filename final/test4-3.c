#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/stat.h>

typedef struct Row 
{
    int rowNum;
    int* numbersArr;
    int sizeArr; 
    double res;

} Row;

void* threadFunc(void* arg) 
{
    Row* current = (Row*)arg;
    double sum = 0;

    for (int i = 0; i < current->sizeArr; i++) 
    {
        sum += current->numbersArr[i];
    }

    current->res = sum / current->sizeArr;

    return NULL;
}

int checkIfExists(const char* fileName)
{
    struct stat buffer;
    return stat(fileName, &buffer) == 0 ? 1 : 0;
}

int main() 
{
    int n, m;
    printf("N and M: ");
    scanf("%d %d", &n, &m);

    Row rows[n];

    for(int i = 0; i < n; i++) 
    {
        char rowStr[4];
        scanf("%s %d", rowStr, &(rows[i].rowNum));

        if (strcmp(rowStr, "ROW") != 0)
        {
            printf("wrong\n");
            return -1; 
        }

        rows[i].sizeArr = m;
        rows[i].numbersArr = (int*)malloc(m * sizeof(int));

        if (!rows[i].numbersArr)
        {
            perror(":(\n");
            exit(-1);
        }

        for(int j = 0; j < m; j++) 
        {
            scanf("%d", &(rows[i].numbersArr[j]));
        }
    }

    char fileName[100];
    printf("File: ");
    scanf("%s", fileName);

    if (checkIfExists(fileName) == 1)
    {
        printf("File exists...\n");
        return -1; 
    }

    pthread_t threads[n];

    for (int i = 0; i < n; i++) 
    {
        pthread_create(&threads[i], NULL, threadFunc, &rows[i]);
    }

    for (int i = 0; i < n; i++) 
    {
        pthread_join(threads[i], NULL);
    }

    FILE* f2 = fopen(fileName, "w");

    if(!f2)
    {
        perror(":(");
        exit(1);
    }

    for (int i = 0; i < n; i++) 
    {
        fprintf(f2, "ROW %d %.3lf\n", rows[i].rowNum, rows[i].res);
    }

    fclose(f2);

    for (int i = 0; i < n; i++) 
    {
        free(rows[i].numbersArr);
    }

    return 0;
}

/*
    5 6
    ROW 1 21 14 31 -51 33 1
    ROW 2 41 56 74 -21 42 -52
    ROW 3 51 61 17 37 97 39
    ROW 4 19 -1 85 -9 51 2
    ROW 5 71 26 43 36 22 99
    file1
*/
