#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ID_LEN 5

typedef struct
{
    char name[100];
    char id[ID_LEN];
    unsigned short birthYear;
    unsigned short birthMonth;
    unsigned char birthDay;
    char gender;
} Person;

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

int getRandom()
{
    return rand() % (100 - 0 + 1) + 0;
}

void* initArray(size_t capacity)
{
    Person* people = (Person*)malloc(capacity * sizeof(Person));

    return people; 
}

int addPerson(char* name, unsigned short birthYear, unsigned short birthMonth, unsigned char birthDay, char gender, Person* people, size_t* size, size_t capacity)
{
    Person littlePerson;

    char* unique_id = convert(getRandom() + birthYear + birthMonth + (birthDay - '0'));

    strcpy(littlePerson.id, unique_id);
    strcpy(littlePerson.name, name);
    littlePerson.birthYear = birthYear;
    littlePerson.birthDay = birthDay;
    littlePerson.birthMonth = birthMonth;

    if (*size == capacity)
    {
        printf("Cannot add\n");
        return -1;
    }

    people[*size] = littlePerson;
    *size += 1;   

    printf("%s added\n", littlePerson.name);
    return 0; 
}

int removePerson(char* id, Person* people, size_t* size, size_t capacity)
{
    Person* temp = (Person*)malloc(capacity * sizeof(Person));
    int j = 0;
    int check = 0; 

    for (size_t i = 0; i < *size; i++)
    {
        if (strcmp(people[i].id, id) == 0)
        {
            ++check;
            break;
        }
    }

    if (check == 0)
    {
        printf("Remove: No such id\n");
        return -1;
    }
    
    for (size_t i = 0; i < *size; i++)
    {
        if (strcmp(people[i].id, id) != 0)
        {
            temp[j++] = people[i];
        }
    }
    
    free(people);
    people = temp; 
    *size -= 1; 

    return 0; 
}

void readPerson(Person* people, size_t* size, size_t capacity)
{
    char* name;
    unsigned short year, month, day;
    char gender;

    printf("Enter name :");
    scanf("%s", &name);
    printf("Enter year :");
    scanf("%u", &year);
    printf("Enter month :");
    scanf("%u", &month);
    printf("Enter day :");
    scanf("%u", &day);
    printf("Enter gender :");
    scanf("%c", &gender);

    addPerson(name, year, month, day, gender, people, size, capacity);
}

int printPerson(char* id, Person* people, size_t* size)
{
    for (size_t i = 0; i < *size; i++)
    {
        //printf("%s\n", people[i].id);
        if (strcmp(people[i].id, id) == 0)
        {
            printf("Name: %s, ID: %s\n", people[i].name, people[i].id);
            return 0;
        }
    }

    printf("Print: Not found\n");
    return -1; 
}

typedef struct double_comp 
{
    unsigned long long mantissa:52;
    unsigned int exponent:11;
    unsigned int sign:1;
} double_comp;

typedef union DOUBLE 
{
    double d;
    double_comp c;
} DOUBLE;

typedef union D2
{
    float f;
    int n; 
} D2; 

void toBinary(unsigned num)
{
    if (num > 1)
    {
        toBinary(num >> 1);
    }    
 
    printf("%d", num & 1);
}

void printDoubleBinary(DOUBLE dd)
{
    printf("\nNUMBER: %lf\nBINARY:", dd.d);
    toBinary(dd.c.sign);
    printf(".");
    toBinary(dd.c.exponent);
    printf(".");
    toBinary(dd.c.mantissa);
    printf("\n");
}

void printDoubleDecimal(DOUBLE dd)
{
    printf("\nNUMBER: %lf\n", dd.d);
    printf("SIGN: %u\nEXPONENT: %u\nMANTISSA: %lu\n", dd.c.sign, dd.c.exponent, dd.c.mantissa);
}


void swapBytes(uint16_t* word)
{
    uint16_t leftmostByte = (*word & 0x00FF) >> 0;
    uint16_t rightmostByte = (*word & 0xFF00) >> 8;
    leftmostByte <<= 8; 

    *word = leftmostByte | rightmostByte; 
}

void task2()
{
    DOUBLE dd;
    dd.d = 3.1415; 
    
    printDoubleBinary(dd);
    printDoubleDecimal(dd);
}

void task1()
{
    uint16_t word = 0xCAFE;
    swapBytes(&word);
    printf("CAFE: %02x\n", word);
}

void task3()
{
    Person* people = (Person*)initArray(10);
    size_t size = 0; 

    addPerson("John", 1999, 5, 5, 'M', people, &size, 10);
    printf("Size: %d\n", size);
    addPerson("Eva", 1999, 5, 5, 'F', people, &size, 10);
    printf("Size: %d\n", size);
    printPerson("aaaaa", people, &size);
    removePerson("aaaa", people, &size, 10);
    printf("Size: %d\n", size);

    free(people);
}

int main()
{
    task3();    
    printf("\n");
    task2();
    printf("\n");
    task1();
    
    return 0;
}