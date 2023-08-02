#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int isNumber(char c)
{
    if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
    {
        return 1;
    }

    return 0;
}

int isAtoi(char* str)
{
    int count = 0;

    while (*str)
    {
        if (isNumber(*str) != 1)
        {
            return 0;
        }

        if (*str == '0')
        {
            ++count; 
        }

        *str++; 
    }
    
    return (count <= 1) ? 1 : 0; 
}

int isOperation(char c)
{
    if (c == '+' || c == '*' || c == '^')
    {
        return 1; 
    }

    return 0; 
}

int isValidChar(char c)
{
    if (isNumber(c) == 1 || c == '(' || c == ')' || isOperation(c) == 1)
    {
        return 1; 
    }

    return 0; 
}

int isValid(char* str)
{
    int count = 0;
    int countBracket = 0; 
    int countNumber = 0; 
    int operation = 0; 
    int keepOperation = 0; 

    if (isAtoi(str) == 1)
    {
        return 1; 
    }
    else
    {
        if (str[0] != '(' && str[strlen(str)] != ')')
        {
            return 0; 
        }
    }

    while (*str)
    {
        
        if (*str == '(')
        {
            ++countBracket;
        }
        else if (*str == ')')
        {
            --countBracket;
        }
        else if (isOperation(*str) == 1)
        {
            ++operation;
        }
        else if (isNumber(*str) == 1 && operation == 0)
        {
            ++countNumber;
        }
        else if (isNumber(*str) == 1 && operation == 1)
        {
            --countNumber;
            --operation;
        }

        *str++;
    }
    
    //printf("%d, %d\n", countBracket, countNumber);
    return (countBracket == 0 )? 1 : 0; 
}

void getBrackets(char* str, int* posOpen, int* posClose)
{
    int i = 0;
    int lastPosOpen;
    int firstposClose; 

    while (*str)
    {
        if (*str == '(')
        {
            lastPosOpen = i; 
        }
        else if (*str == ')')
        {
            firstposClose = i; 
            break; 
        }

        *str++;
        i++;
    }
    
    *posOpen = lastPosOpen;
    *posClose = firstposClose; 
}

int getOperator(char* str, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        if (isOperation(str[i]) == 1)
        {
            return i; 
        }
    }
    
    return 0; 
}

int calculate(int a, int b, char oper)
{
    switch (oper)
    {
    case '+':
        return a + b;
        break;
    
    case '*':
        return a * b;
        break;
    case '^':
        return pow(a, b);
        break;
    }

    return 0; 
}

int getNumber(char* str, int start, int end)
{
    int base = 1;
    int result = 0; 

    for (int i = end; i >= start; i--)
    {
        int num = str[i] - '0';
        result += base*num;
        base *= 10; 
    }

    return result; 
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

int traverse(char* str, int result)
{
    if (strlen(str) == 2 || isAtoi(str))
    {
        printf("kraj\n");
        return result; 
    }
    
    int posOpen = 0;
    int posClose = 0;
    int posOperator = 0;
    int a, b; 
    char* converted;

    getBrackets(str, &posOpen, &posClose);
    posOperator = getOperator(str, posOpen, posClose);
    a = getNumber(str, posOpen+1, posOperator-1);
    b = getNumber(str, posOperator+1, posClose-1);

    result = calculate(a, b, str[posOperator]);
    converted = convert(result);

    printf("STRING: %s\n", str);
    printf("open: %d, close: %d, operator: %d, a: %d, b: %d, res: %d, size: %d\n", posOpen, posClose, posOperator, a, b, result, strlen(str));

    char firststr[100] = "";
    strncpy(firststr, str, posOpen);
    
    char* endstr = strchr(str, ')');
    *endstr++; 
    
    return traverse(strcat(strcat(firststr, converted), endstr), result);
}

// void printDoubleBinaty(DOUBLE dd)
// {
//     unsigned long long* temp = (unsigned long long*) &dd.d; 

//     for (int i = 0; i < 63; i++)
//     {
//         if (i == 1 || i == 12)
//         {
//             printf(" ");
//         }
//         else
//         {
//             (*temp >> 63 - i) & 1 == 1 ? printf("1") : printf("0");
//         }
//     }
    
//     printf("\n");
// }

int main()
{
    char str[100];
    printf("Write: ");
    scanf("%s", str);

    printf("Valid: %d\n", isValid(str));

    if (isValid(str) == 1)
    {
        int result = traverse(str, 0);
        printf("RESULT: %d\n", result);
    }

    return 0; 
}