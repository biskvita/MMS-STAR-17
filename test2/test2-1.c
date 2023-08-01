#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    while (*str)
    {
        if (isNumber(*str) != 1)
        {
            return 0;
        }

        *str++; 
    }

    return 1; 
}

char getLetter(char c)
{
    char letter; 

    switch (c)
    {
    case '0':
        letter = 'A';
        break;
    case '1':
        letter = 'B';
        break;
    case '2':
        letter = 'C';
        break;
    case '3':
        letter = 'D';
        break;
    case '4':
        letter = 'E';
        break;
    case '5':
        letter = 'F';
        break;
    case '6':
        letter = 'G';
        break;
    case '7':
        letter = 'H';
        break;
    case '8':
        letter = 'I';
        break;
    case '9':
        letter = 'J';
        break;
    }

    return letter; 
}

char getSymbol(char c)
{
    char letter; 

    switch (c)
    {
    case '0':
        letter = '!';
        break;
    case '1':
        letter = '#';
        break;
    case '2':
        letter = '/';
        break;
    case '3':
        letter = '~';
        break;
    case '4':
        letter = '=';
        break;
    case '5':
        letter = '`';
        break;
    case '6':
        letter = '\\';
        break;
    case '7':
        letter = '>';
        break;
    case '8':
        letter = '.';
        break;
    case '9':
        letter = ',';
        break;
    }

    return letter; 
}

char* encode(char* str)
{
    char* encoded = (char*)malloc(strlen(str) * sizeof(char));
    int pos = 0; 

    while (*str)
    {
        if (pos % 2 == 0)
        {
            encoded[pos] = getLetter(*str);
        }
        else
        {
            encoded[pos] = getSymbol(*str);
        }

        *str++; 
        ++pos; 
    }

    return encoded; 
}

int main()
{
    char longnumber[500]; 

    printf("Write: ");
    scanf("%s", longnumber);

    if (checkIfNumber(longnumber) == 0)
    {
        printf("This is not a number...\n");
    }
    else
    {
        char* result = encode(longnumber);
        printf("RESULT: %s\n", result);

        free(result);
    }

    return 0; 
}
