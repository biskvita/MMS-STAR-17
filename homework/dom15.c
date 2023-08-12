#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void myCat(int argc, char* argv[])
{
    char buffer[100];
    int currentFile = 1; 

    if (argc == 1)
    {
        while (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            buffer[strlen(buffer)-1] = '\0';
            fprintf(stdout, "%s\n", buffer);
        }

        return;  
    }
    
    while (currentFile < argc)
    {
        FILE* f1 = fopen(argv[currentFile], "r");

        if (!f1)
        {
            perror("File problem...\n");
            exit(-1);
        }

        fseek(f1, 0, SEEK_CUR);

        while (fgets(buffer, sizeof(buffer), f1) != NULL)
        {
            buffer[strlen(buffer)-1] = '\0';
            fprintf(stdout, "%s\n", buffer);
        }

        fclose(f1);
        ++currentFile; 
    }
}

int cmpArgv(const void* a, const void* b)
{
    return strcmp( *(char**)a, *(char**)b) > 0; 
}

void sortFiles(int argc, char* argv[])
{
    char file[20];

    printf("File name: ");
    scanf("%s", file);

    FILE* f1 = fopen(file, "w");

    if (!f1)
    {
        perror("File problem...\n");
        exit(-1);
    }

    qsort(argv, argc, sizeof(argv[0]), cmpArgv);

    for (int i = 1; i <= argc; i++)
    {
        fprintf(f1, "%s\n", argv[i]);
    }
    
    fclose(f1);
}

void task4(int argc, char* argv[])
{
    if (argc > 2)
    {
        printf("Wrong arguments...\n");
        return; 
    }

    char c; 
    int newbyte; 
    int startindex = 0; 
    int endindex = 0;
    
    FILE* f1 = fopen(argv[1], "ab");

    if (!f1)
    {
        perror("File problem...\n");
        exit(-1);
    }
  
    do
    {
        printf("C: ");
        scanf("%c", &c);
        int len = ftell(f1);
        char buffer[100];

        if (c == 'd')
        {
            
            fseek(f1, 0, SEEK_SET);
            fread(buffer, len, 1, f1);
            
            for(int i = 0; i < len; i++)
            {       
                printf("%02x ", buffer[i]);
            }

            printf("\n");
        }
        else if (c == 't')
        {
            // int len = ftell(f1);
	        // fseek(f1, 0, SEEK_SET);
            // char buffer[100];
            // fread(buffer, len, 1, f1);
            
            // for(int i = 0; i < len; i++)
            // {       
            //     printf("%s ", buffer[i]);
            // }

            // printf("\n");
        }
        else if (c == 'a')
        {
            printf("newbyte: ");
            scanf("%x", newbyte);
            fwrite(&newbyte, sizeof(newbyte), 1, f1);
            //putc(newbyte, f1);
        }
        else if (c == 'c')
        {
            scanf("%d %d", startindex, endindex);
        }
        else if (c == 'e')
        {
            scanf("%d", startindex);
            scanf("%x", newbyte);
        }
        
    } while (c != EOF);
    
    fclose(f1);
}

int main(int argc, char* argv[])
{
    //myCat(argc, argv);
    //sortFiles(argc, argv);
    task4(argc, argv);

    return 0;
}