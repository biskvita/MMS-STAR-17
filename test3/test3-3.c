#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max_rand 1000000L

char* arr[] = {"aa", "ab", "ac", "ca", "cc", "bb"};

typedef struct Product
{
    double old_price;
    double new_price;
    unsigned int id;
    char product_type;
    char product_name[3];
} Product;

char randomChar()
{
    int token = rand() % (10 - (-10) + 1) + (-10);

    if (token > 4)
    {
        return 'A';
    }
    else if (token < -4)
    {
        return 'B';
    }
    else if (token == 0)
    {
        return 'D';
    }
    
    return 'C';
}

Product* create()
{
    Product* products = (Product*)malloc(40 * sizeof(Product));
    unsigned int random = rand() / 100; 

    for (size_t i = 0; i < 40; i++)
    {
        products[i].old_price = 4.99 + (100.45 - 4.99) * (rand() % max_rand) / max_rand;
        products[i].new_price = 4.99 + (100.45 - 4.99) * (rand() % max_rand) / max_rand;
        products[i].id = random++;
        products[i].product_type = randomChar();
        strcpy(products[i].product_name, arr[rand() % 6]);
    }
    
    return products; 
}

int cmpProductPrice(Product* a, Product* b)
{
    return (a->new_price - a->old_price) - (b->new_price - b->old_price);
}

int cmpPriceDESC(const void* a, const void* b)
{
    return cmpProductPrice((Product*)b, (Product*)a); 
}

int cmpNames(Product* a, Product* b)
{
    return strcmp(a->product_name, b->product_name);
}

int cmpType(const void* a, const void* b)
{
    return cmpNames((Product*)b, (Product*)a) < 0; 
}

int main()
{
    Product* products = create();
    srand(time(0));

    for (int i = 0; i < 40; i++)
    {
        printf("OLD: %.2lf, NEW: %.2lf, ID: %u, TYPE: %c, NAME: %s\n", products[i].old_price, products[i].new_price, products[i].id, products[i].product_type, products[i].product_name);
    }
    
    qsort(products, 40, sizeof(Product), cmpType);
    printf("\n");

    for (int i = 0; i < 40; i++)
    {
        printf("OLD: %.2lf, NEW: %.2lf, ID: %u, TYPE: %c, NAME: %s\n", products[i].old_price, products[i].new_price, products[i].id, products[i].product_type, products[i].product_name);
    }

    free(products);
    return 0; 
}