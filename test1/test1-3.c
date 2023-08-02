#include <stdio.h>

const int MAX = 100; 

void subseq(int arr[], int n, int dest[], int *new_n)
{
    int max = 1;
    int count = 1;
    int index = 0; 

    for (int i = 1; i < n; i++)
    {
        if (arr[i] < arr[i-1])
        {
            ++count;
        }
        else
        {
            if (count > max)
            {
                max = count;
                index = i - count; 
            }

            count = 1;
               
        }
    }

    for (int i = 0; i < max; i++)
    {
        dest[i] = arr[index];
        ++index; 
    }

    *new_n = max;

    for (int i = 0; i < max; i++)
    {
        printf("%d ", dest[i]);
    }

    printf("\n");
}

int main()
{
    int N;

    printf("N for array: ");
    scanf("%d", &N);

    int array[100];
    int dest[100]; 
    int new_n = 0; 

    for (size_t i = 0; i < N; i++)
    {
       scanf("%d", &array[i]);
    }
    
    subseq(array, N, dest, &new_n);

    return 0;
}