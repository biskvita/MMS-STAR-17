#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef struct Car
{
    char model[20];
    uint8_t maxSpeed; 
    double price;
} Car; 

int cmpCarModels(Car* a, Car* b)
{
    return strcmp(a->model, b->model);
}

int cmpModelASC(const void* a, const void* b)
{
    return cmpCarModels((Car*)a, (Car*)b) > 0; 
}

int cmpModelDESC(const void* a, const void* b)
{
    return cmpCarModels((Car*)a, (Car*)b) < 0; 
}

int cmpCarSpeeds(Car* a, Car* b)
{
    return a->maxSpeed - b->maxSpeed;
}

int cmpSpeedASC(const void* a, const void* b)
{
    return cmpCarSpeeds((Car*)a, (Car*)b) > 0; 
}

int cmpSpeedDESC(const void* a, const void* b)
{
    return cmpCarSpeeds((Car*)a, (Car*)b) < 0; 
}

int cmpCarPrice(Car* a, Car* b)
{
    return a->price - b->price;
}

int cmpPriceASC(const void* a, const void* b)
{
    return cmpCarPrice((Car*)a, (Car*)b); 
}

int cmpPriceDESC(const void* a, const void* b)
{
    return cmpCarPrice((Car*)b, (Car*)a); 
}

int (*getComparator(int n))(const void*, const void*)
{
    switch (n)
    {
    case 1:
        return &cmpModelASC; 
    case 2:
        return &cmpModelDESC;
    case 3:
        return &cmpSpeedASC; 
    case 4:
        return &cmpSpeedDESC; 
    case 5:
        return &cmpPriceASC; 
    case 6:
        return &cmpPriceDESC; 
    }

    return NULL; 
}

char randomChar()
{
    int token = rand() % (10 - (-10) + 1) + (-10);

    if (token > 0)
    {
        return rand() % (90 - 65 + 1) + 65;
    }
    else
    {
        return rand() % (122 - 97 + 1) + 97;
    }
    
    return 'a';
}

char* randomCharArray()
{
    int length = rand() % (10 - 4 + 1) + 4;
    int size = 0;
    char str[20] = "";

    while (size < length)
    {
        char c[2];
        c[1] = '\0';
        c[0] = randomChar();
        
        strcat(str, c);
        ++size; 
    }

    char* str2 = &str[0];

    return str2;
}

Car* createArray()
{
    Car* cars = (Car*)malloc(10 * sizeof(Car));

    for (size_t i = 0; i < 10; i++)
    {
        cars[i].price = (rand() % (100000 - 1000 + 1))/1000. + 1000.0;
        cars[i].maxSpeed = rand() % (300 - 100 + 1) + 100;
        strcpy(cars[i].model, randomCharArray());
    }
    
    return cars; 
}

int main()
{
    srand(time(0));

    Car* cars = createArray();

    for (size_t i = 0; i < 10; i++)
    {
        printf("MODEL: %10s, MAXSPEED: %6d, PRICE: %8.2lf\n", cars[i].model, cars[i].maxSpeed, cars[i].price);
    }
    
    int n; 

    printf("Pick N: ");
    scanf("%d", &n);

    int (*cmp)(const void*, const void*) = getComparator(n);

    if (n >= 1 && n <= 6)
    {
        qsort(cars, 10, sizeof(Car), cmp);
    }
    
    for (size_t i = 0; i < 10; i++)
    {
        printf("MODEL: %10s, MAXSPEED: %6d, PRICE: %8.2lf\n", cars[i].model, cars[i].maxSpeed, cars[i].price);
    }
    
    free(cars);
    return 0; 
}
