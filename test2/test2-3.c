#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int isNumber(char c)
{
    if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
    {
        return 1;
    }

    return 0;
}

int checkIfNumber(char* str)
{
    for (int i = 0; i < strlen(str); ++i)
    {
        if (isNumber(str[i]) != 1 && str[i] != '-')
        {
            return 0;
        }
    }

    return 1; 
}

int checkIfFloat(char* str)
{
    int isTherePoint = 0; 

    for (int i = 0; i < strlen(str); ++i)
    {
        if (isNumber(str[i]) != 1 && str[i] != '.' && str[i] != '-')
        {
            return 0;
        }
        if (str[i] == '.')
        {
            ++isTherePoint; 
        }
    }

    if (isTherePoint != 1)
    {
        return 0; 
    }

    return 1; 
}

int checkIfHex(char* str)
{
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        return 1;
    }

    return 0; 
}

int getHex(char c)
{
    switch (c)
    {
    case '0':
        return 0; 
    case '1':
        return 1; 
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9; 
    case 'A': case 'a':
        return 10; 
    case 'B': case 'b':
        return 11;
    case 'C': case 'c':
        return 12; 
    case 'D': case 'd':
        return 13; 
    case 'E': case 'e':
        return 14; 
    case 'F': case 'f':
        return 15; 
    }

    return -1; 
}

int convertHex(char* str)
{
    int result = 0;
    int power = 0;

    for (int i = strlen(str) - 1; i > 1; i--)
    {
        result += getHex(str[i]) * pow(16, power);
        ++power; 
    }
    
    return result; 
}

float helper(int argc, char* argv[])
{
    int decimalsSum = 0; 
    float floatsSum = 0; 
    int hexSum = 0;

    for (int i = 0; i < argc; i++)
    {
        if (checkIfNumber(argv[i]) == 1)
        {
            decimalsSum += atoi(argv[i]);
        }
        else if (checkIfFloat(argv[i]) == 1)
        {
            floatsSum += strtof(argv[i], NULL);
        }
        else if (checkIfHex(argv[i]) == 1)
        {
            hexSum += convertHex(argv[i]);
        }
    }

    return floatsSum + decimalsSum + hexSum; 
}
 
int main(int argc, char* argv[])
{
    printf("Argv: ");

    for (int i = 0; i < argc; i++)
    {
        printf("%s, ", argv[i]);
    }
    printf("\n");

    float sum = helper(argc, argv);
    printf("RESULT: %.2lf", sum);

    return 0; 
}
