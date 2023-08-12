#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

int printf_time(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    time_t t;
    struct tm* tm = gmtime(&t);
    char* str = asctime(tm);
    size_t len = strlen(str);

    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }

    printf("[%s]: ", str);
    vprintf(format, args);
    va_end(args);

    return 0;
}

char* convert(int number)
{
    int copy = number;
    int count = 0;
    char arr2[100] ;
    int i;
    int index = 0;

    while (copy) 
    {
        count++;
        copy /= 10;
    }

    char* arr = (char*)malloc(count);
 
    while (number > 0) 
    {
        arr2[index++] = number % 10 + '0';
        number /= 10;
    }

    for (i = 0; i < count; i++) 
    {
        arr[i] = arr2[index - i - 1];
    }
 
    arr[i] = '\0';

    return arr;
}

int printIntGetCount(int num)
{
    if (num == 0)
    {
        putc('0', stdout);
        return 1;
    }

    int count = 0;

    if (num < 0)
    {
        putc('-', stdout);
        count++;
        num = -num;
    }

    char* buffer = convert(num);

    while (*buffer)
    {
        putc(*buffer, stdout);
        count++;
        *buffer++; 
    }
    
    return count; 
}

double printDoubleGetCount(double num)
{
    if (num == 0)
    {
        putc('0', stdout);
        return 1;
    }

    int count = 0;

    if (num < 0)
    {
        putc('-', stdout);
        count++;
        num = -num;
    }

    count += printIntGetCount((int)num) + 1;
    putc('.', stdout);

    double leftOver = num - (int)num; 

    for (size_t i = 0; i < 6; i++)
    {
        leftOver *= 10;
        putc((int)leftOver + '0', stdout);
        count += 1;
        leftOver -= (int)leftOver; 
    }
    
    return count; 
}

int my_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int countPrinted = 0;
    int num = 0; double numDouble = 0; char c; 

    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;

            switch (*fmt)
            {
            case 'c':
                c = (char)va_arg(args, int);
                putc(c, stdout);
                countPrinted += 1;
                break;
            case 'd':
                num = va_arg(args, int);
                countPrinted += printIntGetCount(num);
                break;
            case 'f':
                numDouble = va_arg(args, double);
                countPrinted += printDoubleGetCount(num);
                break;
            default:
                putc(*fmt, stdout);
                countPrinted += 1;
                break;
            }
        }
        else
        {
            putc(*fmt, stdout);
            countPrinted += 1; 
        }

        fmt++;
    }

    va_end(args);
    return countPrinted;
}

double* initArray(size_t size)
{
    double* arr = (double*) malloc(size * sizeof(double));

    if (!arr)
    {
        perror(":(\n");
        exit(-1);
    }

    for (size_t i = 0; i < size; i++)
    {
        arr[i] = (rand() % 100) / 100.;
    }
    
    return arr; 
}

void reallocArray(double* arr, int* size, int newSize, int start, int end)
{
    int old = *size; 
    *size += newSize;
    arr = (double*)realloc(arr, sizeof(double)*(*size));

    if (!arr)
    {
        perror(":(\n");
        exit(-1);
    }

    while (old < *size)
    {
        *(arr + old) = (start + rand() % end - 100) / 100.;
        ++old; 
    }
}

void printArray(double* arr, int size)
{
    for (int i = 0; i < size; i++)
    {   
        printf("%.2lf ", arr[i]);
    }

    printf("\n");
}

void task2()
{
    srand(time(0));
    int n, m, p;
    printf("N: ");
    scanf("%d", &n);

    double* arr = initArray(n);
    printArray(arr, n);

    printf("M: ");
    scanf("%d", &m);
    reallocArray(arr, &n, m, 1*100, 2*100);
    printArray(arr, n);

    printf("P: ");
    scanf("%d", &p);
    reallocArray(arr, &n, p, 2*100, 3*100);
    printArray(arr, n);

    free(arr);
}

int main()
{
    //printf_time("%d %d ", 10, 20);
    //int num = my_printf("Proba proba edno %d dve %f tri %c kraj\n", 1, 2.222, -3.03);
    task2();
    
    return 0; 
}