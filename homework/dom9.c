#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

typedef struct Point 
{
    double x;
    double y;
    double z;
} Point;

typedef struct Human 
{
    double weight_kg;
    uint16_t height_cm;
} Human;

typedef struct float_comp 
{
    unsigned int mantissa:23;
    unsigned int exponent:8;
    unsigned int sign:1;
} float_comp;

typedef union F 
{
    float f;
    float_comp c;
} F;

typedef union F2
{
    float f;
    int n; 
} F2; 

typedef struct MyTime
{
    unsigned short year;
    unsigned short month;
    unsigned short day;
    unsigned short hour;
    unsigned short min;
    unsigned short sec;
} MyTime;

unsigned countSetBits(F2* a)
{
    unsigned count = 0;
    int num = a->n;

    while (num) 
    {
        count += num & 1;
        num >>= 1;
    }

    return count;
}

int cmpFloat(const void* a, const void* b)
{
    return countSetBits((F2*)a) > countSetBits((F2*)b) ? -1 : 1; 
}

int distPoint(Point* a)
{
    return sqrt(a->x*a->x + a->y*a->y + a->z*a->z);
}

int bodyMassIndex(Human* a)
{
    return a->weight_kg / (a->height_cm*a->height_cm);
}

int cmpHuman(const void* a, const void* b)
{
    return bodyMassIndex((Human*)a) > bodyMassIndex((Human*)b) ? -1 : 1; 
}

int cmpPoint(const void* a, const void* b) 
{
    return distPoint((Point*)a) > distPoint((Point*)b) ? -1 : 1; 
}

int cmpInt(const void* a, const void* b) 
{
	return *(int*)a > *(int*)b ? -1 : 1;
}

int cmpUint64(const void* a, const void* b) 
{
	return *(uint64_t*)a > *(uint64_t*)b ? -1 : 1;
}

int cmpChar(const void* a, const void* b)
{
    return *(char*)a > *(char*)b ? -1 : 1;
}

void* findMax(void* arr, size_t n, size_t elem_s, int (*cmp)(const void*, const void*))
{
    void* max = arr;

    for (size_t i = 0; i < n; i++)
    {
        if (cmp( ((char*)arr + i * elem_s), max ) < 0)
        {
            max = (char*)arr + i * elem_s;  
        }
    }
    
    return max; 
}

void taskFindMax()
{
    int arr[] = {1,2,-1,3,5,11,12,13,2,100,22};
	int* max = (int*)findMax(arr, sizeof(arr)/sizeof(int), sizeof(int), cmpInt);
	printf("Result INT: %d\n", *max);	// should print 100

    char arr2[] = {'b', 's', 'c', 'a'};
	char* max2 = (char*)findMax(arr2, sizeof(arr2)/sizeof(char), sizeof(char), cmpChar);
    printf("Result CHAR: %c\n", *max2);	

    Point a = {2, 3, 4};
    Point b = {3, 45, 4};
    Point c = {0, 0, 0};
    Point points[] = {a, b, c};
    Point* maxPoint = (Point*)findMax(points, 3, sizeof(Point), cmpPoint);
    printf("Result POINT: %.2lf, %.2lf, %.2lf\n", maxPoint->x, maxPoint->y, maxPoint->z);

    Human d = {50, 175};
    Human e = {69, 185};
    Human f = {80, 185};
    Human humans[] = {d, e, f};
    Human* maxHuman = (Human*)findMax(humans, 3, sizeof(Human), cmpHuman);
    printf("Result HUMAN: %.2lf, %lu\n", maxHuman->weight_kg, maxHuman->height_cm);
    
    float arr3[] = {1.534, 24.22, 4.22, 9, 11.3};
    F2 floatArr2[5]; 

    for (int i = 0; i < 5; i++)
    {
        floatArr2[i].f = arr3[i];
    }

    // for (int i = 0; i < 5; i++)
    // {
    //     printf("FLOAT: %.2lf, SETBITS: %u \n", floatArr2[i].f, countSetBits(&floatArr2[i]));
    // }
    
	float* max3 = (float*)findMax(arr3, sizeof(arr3)/sizeof(float), sizeof(float), cmpFloat);
    printf("Result FLOAT: %.2lf\n", *max3);	
}

int isLeapYear(MyTime t)
{
    if (t.year % 400 == 0 || ((t.year % 100 != 0) && (t.year % 4 == 0)))
    {
        return 1;
    }

    return 0; 
}

int totalDaysInYear(MyTime t)
{
    unsigned int countMonth = 1;
    unsigned int countDays = 0;

    while (countMonth < t.month)
    {
        switch (countMonth)
        {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            countDays += 31; 
            break;
        case 2:
            if (isLeapYear(t) == 1)
            {
                countDays += 29;
            }
            else
            {
                countDays += 28; 
            }
            break;
        case 4: case 6: case 9: case 11:
            countDays += 30; 
        }

        ++countMonth;
    }

    return countDays + t.day; 
}

void printMonth(MyTime t)
{
    printf("Month: %u \n", t.month);
}

int secondsPassed(MyTime t)
{
    int years = t.year - 1970; 
    int days = 365*years + totalDaysInYear(t) + (years / 4) - 1;

    return days*86400 + t.hour*3600 + t.min*60 + t.sec; 
}

void taskMyTime()
{
    printf("SIZE: %lu\n", sizeof(MyTime));
    MyTime time; 
    time.year = 2004; time.month = 8; time.day = 10; 
    printf("DAYS: %d\n", totalDaysInYear(time));

    time.hour = 10; time.min = 4; time.sec = 56; 
    printf("SECONDS: %d\n", secondsPassed(time));

    time.year = 2003; 
    printf("SECONDS: %d\n", secondsPassed(time));
}

int clearBit(uint32_t mask, size_t index)
{
    return (mask & ~(1 << index));
}

int clearBits(uint32_t* maskArr, size_t nitems, size_t bit_index)
{
    for (size_t i = 0; i < nitems; i++)
    {
        maskArr[i] = clearBit(maskArr[i], bit_index) ; 
    }
    
    return 0; 
}

int setBit(uint32_t mask, size_t index)
{
    return (mask | (1 << index));
}

int setBits(uint32_t* maskArr, size_t nitems, size_t bit_index)
{
    for (size_t i = 0; i < nitems; i++)
    {
        maskArr[i] = setBit(maskArr[i], bit_index) ; 
    }
    
    return 0; 
}

int checkBit(uint32_t mask, size_t index)
{
    return mask & (1 << index) ? 1 : 0; 
}

int checkBits(uint32_t* maskArr, size_t nitems, size_t bit_index)
{
    int countSets = 0;
    int countZeros = 0;

    for (size_t i = 0; i < nitems; i++)
    {
        if (checkBit(maskArr[i], bit_index) == 1)
        {
            ++countSets;
        }
        else
        {
            ++countZeros; 
        }
    }

    if (countSets == nitems)
    {
        return 1;
    }
    else if (countZeros == nitems)
    {
        return 0; 
    }
    
    return -1; 
}

void printBit(uint32_t mask)
{
    while (mask) 
    {
        printf("%d", mask & 1);
        mask >>= 1;
    }
}

void printBits(uint32_t* arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printBit(arr[i]);
        printf("\n");
    }
}

void taskBits()
{
    uint32_t arr[3] = {41, 42, 43};

    printBits(arr, 3);
    printf("\n");
    printBits(arr, 3);

    printf("\n");
    printf("RES: %d\n",checkBits(arr, 3, 1)); 
    printf("RES: %d\n",checkBits(arr, 3, 2)); 
    printf("RES: %d\n",checkBits(arr, 3, 3)); 

    setBits(arr, 3, 1);
    printf("\n");
    printBits(arr, 3);

    clearBits(arr, 3, 1);
    printf("\n");
    printBits(arr, 3);
}

int main() 
{
	//taskFindMax();
    //taskMyTime();
    taskBits();
    

	return 0;
}
