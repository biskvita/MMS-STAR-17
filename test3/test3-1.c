#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert(int n) 
{
    long long bin = 0;
    char keep[10];
    int rem, i = 1;
    int j = 0;

    while (n != 0) 
    {
        rem = n % 2;
        n /= 2;
        keep[j++] = rem;
    }

    for (int i = j-1; i >= 0; i--)
    {
        printf("%d", keep[i]);
    }
}

void xxd(int argc, char* argv[])
{
    if (argc > 3)
    {
        printf("Problem...\n");
        return; 
    }
    
    char buffer[255];
    FILE* f1 = fopen(argv[1], "rb");

    if (!f1)
    {
        perror("File problem...\n");
        exit(-1);
    }

    fseek(f1, 0, SEEK_CUR);
    int j = 0; 
    int c; 

    while ((c = fgetc(f1)) != EOF)
    {
        buffer[j++] = (char)c;
    }

    if (strcmp(argv[2], "-H") == 0)
    {
        for (int i = 0; i <= j; i++)
        {
            printf("%02x ", buffer[i]);
        }
    }
    else if (strcmp(argv[2], "-B") == 0)
    {
        for (int i = 0; i <= j; i++)
        {
            convert(buffer[i]);
            printf(" ");
        }
    }
    else
    {
        printf("Unknown...\n");
    }
    
    fclose(f1);
}

int main(int argc, char* argv[])
{
    xxd(argc, argv);

    return 0; 
}