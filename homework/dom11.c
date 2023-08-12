#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 20
#define COUNT 10

typedef struct Book
{
    char title[150];
    char author[100];
    int pages;
    double price;
} Book;

typedef struct littleStack 
{
    unsigned int size; 	        
	int* data; 		    
} littleStack;

littleStack createStack()
{
    littleStack stack; 

    stack.size = 0; 
    stack.data = (int*)malloc(MAX * sizeof(int)); 

    return stack;
}

void deleteStack(littleStack* stack)
{
	free(stack->data);
}

int sizeStack(littleStack* stack)
{
	if (stack == NULL)
    {
		return -1;
	} 

	return stack->size;
}

void push(littleStack* stack, int element)
{
    if (stack->size == MAX)
    {
        printf("Stack is full\n");  
        return;  
    }

    stack->data[stack->size++] = element; 
}

void pop(littleStack* stack)
{
    if (stack->size == 0)
    {
        printf("Stack is empty\n");  
        return;  
    }

    stack->size -= 1; 
}

int top(littleStack* stack)
{
    return stack->data[stack->size - 1];
}

void printStack(littleStack* stack)
{
    for (size_t i = 0; i < stack->size; i++)
    {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

int isdigit(char c)
{
    if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
    {
        return 1;
    }

    return 0;
}

int isOperation(char c)
{
    if (c == '+' || c == '*' || c == '-')
    {
        return 1; 
    }

    return 0; 
}

int reverseNumber(int num)
{
    int rev = 0;

    while (num > 0) 
    {
        rev = rev * 10 + num % 10;
        num /= 10;
    }

    return rev;
}

double calculate(char op, double arg1, double arg2)
{
    switch(op)
    {
        case '+':
            return arg1+arg2;
        case '-':
            return arg1-arg2;
        case '*':
            return arg1*arg2;        
    }

    return -1; 
}

int evaluete(const char* input)
{
    littleStack values = createStack();

    while (*input)
    {
        if (isdigit(*input) == 1)
        {
            int base = 1;
            int number = 0; 

            while (*input != ' ')
            {
                number += base * (*input - '0');
                *input++; 
                base *= 10;
            }
            
            push(&values, reverseNumber(number));
        }
        else if (isOperation(*input) == 1)
        {
            int val1 = top(&values);
            pop(&values);
            int val2 = top(&values);
            pop(&values);
            double newvalue = calculate(*input, val2, val1);
            push(&values ,newvalue);
        }

        *input++;
    }

    return top(&values); 
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
    int length = rand() % (20 - 10 + 1) + 10;
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

int cmpBooksAuthors(Book* a, Book* b)
{
    return strcmp(a->author, b->author) ; 
}

int cmpAuthorsASC(const void* a, const void* b)
{
    return cmpBooksAuthors((Book*)a, (Book*)b) >= 0; 
}

int cmpAuthorsDESC(const void* a, const void* b)
{
    return cmpBooksAuthors((Book*)a, (Book*)b) < 0; 
}

int cmpBooksTitles(Book* a, Book* b)
{
    return strcmp(a->title, b->title) ; 
}

int cmpTitlesASC(const void* a, const void* b)
{
    return cmpBooksTitles((Book*)a, (Book*)b) > 0; 
}

int cmpTitlesDESC(const void* a, const void* b)
{
    return cmpBooksTitles((Book*)a, (Book*)b) < 0; 
}

int cmpBooksPages(Book* a, Book* b)
{
    return a->pages - b->pages ; 
}

int cmpPagesASC(const void* a, const void* b)
{
    return cmpBooksPages((Book*)a, (Book*)b) > 0; 
}

int cmpPagesDESC(const void* a, const void* b)
{
    return cmpBooksPages((Book*)a, (Book*)b) < 0; 
}

int cmpBooksPrices(Book* a, Book* b)
{
    return a->price - b->price ; 
}

int cmpPricesASC(const void* a, const void* b)
{
    return cmpBooksPrices((Book*)a, (Book*)b) ; 
}

int cmpPricesDESC(const void* a, const void* b)
{
    return cmpBooksPrices((Book*)b, (Book*)a) ; 
}

Book* createArray()
{
    Book* books = (Book*)malloc(COUNT * sizeof(Book));

    for (size_t i = 0; i < COUNT; i++)
    {
        books[i].pages = rand() % (2000 - 5 + 1) + 5;
        books[i].price = (rand() % (1000 - 1 + 1))/1000. + 1.0;
        strcpy(books[i].author, randomCharArray()); 
        strcpy(books[i].title, randomCharArray()); 
    }
    
    return books; 
}

void task2()
{
    char input[] = "1 2 + 3 * 5 -";
    printf("evaluate: %d\n", evaluete(input));
}

void task1()
{
    srand(time(0));
    Book* books = createArray();

    for (size_t i = 0; i < COUNT; i++)
    {
        printf("TITLE: %25s, AUTHOR: %25s, PAGES: %5d, PRICE: %5.2lf\n", books[i].title, books[i].author, books[i].pages, books[i].price);
    }

    qsort(books, COUNT, sizeof(Book), cmpPricesASC);
    printf("\n");

    for (size_t i = 0; i < COUNT; i++)
    {
        printf("TITLE: %25s, AUTHOR: %25s, PAGES: %5d, PRICE: %5.2lf\n", books[i].title, books[i].author, books[i].pages, books[i].price);
    }

    free(books);
}

int main()
{
    task1();
    task2();
    
    return 0; 
}