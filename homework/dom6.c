#include <stdio.h>
#include <stdint.h>

#define TINT 1
#define TCHAR 2
#define TDOUBLE 3
#define TFLOAT 4
#define TUINT8 5
#define TUINT16 6
#define TUINT32 7
#define TUINT64 8

float binarySearch(float left, float right, float seekedNumber)
{
    float mid = (left + right) / 2;

    if (left <= right)
    {
        if (mid * mid * mid > seekedNumber)
        {
            return binarySearch(left, mid - 0.001, seekedNumber);
        }
        else if (mid * mid * mid < seekedNumber)
        {
            return binarySearch(mid + 0.001, right, seekedNumber); 
        }
    }

    return mid;
}

float sqrt3(float number)
{
    return binarySearch(0.001, number-0.001, number); 
}

void printValue(const void* valuePtr, uint8_t flag)
{
    switch (flag)
    {
    case TINT:
        printf("Value: %d\n", *(int*)valuePtr);
        break;
    case TCHAR:
        printf("Value: %c\n", *(char*)valuePtr);
        break;
    case TDOUBLE:
        printf("Value: %f\n", *(double*)valuePtr);
        break;
    case TFLOAT:
        printf("Value: %f\n", *(float*)valuePtr);
        break;
    case TUINT8:
        printf("Value: %u\n", *(uint8_t*)valuePtr);
        break;
    case TUINT16:
        printf("Value: %u\n", *(uint16_t*)valuePtr);
        break;
    case TUINT32:
        printf("Value: %u\n", *(uint32_t*)valuePtr);
        break;
    case TUINT64:
        printf("Value: %lu\n", *(uint64_t*)valuePtr);
        break;
    }
}

int isPositive(int a)
{
    return a >= 0 ? 1 : 0; 
}

int addOne(int a)
{
    return a + 1; 
}

int isEven(int a)
{
    return a % 2 == 0 ? 1 : 0;
}

int printElement(int a)
{
    printf("%d ", a);
    return a; 
}

int square(int a)
{
    return a*a; 
}

int isPrime(int a)
{
    for (int i = 2; i <= a / 2; i++)
    {
        if (a % i == 0)
        {
            return 0; 
        }
    }
    
    return 1; 
}

int sumOneBits(int a)
{
    int count = 0;

    while (a)
    {
        count += a & 1; 
        a >>= 1; 
    }
    
    return count; 
}

void filter_and_map(const int arr[], size_t n, int (*filter_f)(int), int (*map_f)(int), int dest[], size_t* dest_cnt)
{
    size_t j = 0; 

    for (size_t i = 0; i < n; i++)
    {
        if (filter_f(arr[i]) == 1)
        {
            dest[j++] = map_f(arr[i]);
        }
    }

    *dest_cnt = j;
}

void printArray(int arr[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    
    printf("\n");
}

void task3(int arr[], size_t n, int dest[], size_t new_size, int (*filter_f)(int), int (*map_f)(int))
{
    filter_and_map(arr, n, filter_f, map_f, dest, &new_size);
    printf("New Size: %d\nArray: ", new_size);
    printArray(dest, new_size);   
}

int main()
{
    float n = 6;
    printf("Sqrt3 of %lf: %lf\n", n, sqrt3(n));

    //#################################################
    int num = 23; 
    printValue(&num, TINT);

    char symbol = 'A';
    printValue(&symbol, TCHAR);

    uint32_t unum = 333;
    printValue(&unum, TUINT32);

    //##################################################
    int arr[8] = {1, 2, 3, 4, -1, -2, 11, -100};
    int dest[10];
    size_t new_size = 0;

    task3(arr, 8, dest, new_size, isPositive, addOne);
    task3(arr, 8, dest, new_size, isEven, printElement);
    task3(arr, 8, dest, new_size, isPrime, square);
    task3(arr, 8, dest, new_size, isPositive, sumOneBits);

    return 0; 
}