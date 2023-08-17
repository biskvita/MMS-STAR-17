#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

#define ITEMS_COUNT 10

char* arr[] = {"usd", "gbr", "eun", "cad", "rub"};
uint16_t unique;

typedef struct BankAccount
{
    uint16_t id; 
    char owner[100];
    double available; 
    char currency[4];
} BankAccount;

typedef struct NodeBank
{
    BankAccount value; 
    struct NodeBank* next;
} NodeBank;

typedef struct LinkedList
{
    struct NodeBank* head;
    struct NodeBank* tail; 
    int size; 
} LinkedList; 

void setUnique()
{
    unique = rand() % 100; 
}

char* randomName()
{
    int length = rand() % (20 - 1 + 1) + 1;
    int size = 0;
    char str[20] = "";

    while (size < length)
    {
        char c[2];
        c[1] = '\0';

        if (size == 0)
        {
            c[0] = rand() % (90 - 65 + 1) + 65;
        }
        else
        {
            c[0] = rand() % (122 - 97 + 1) + 97;
        }
        
        strcat(str, c);
        ++size; 
    }

    char* str2 = &str[0];

    return str2;
}

char* randomOwner()
{
    int words = rand() % (5 - 2 + 1) + 2;
    int size = 0;
    char str[100] = "";

    while (size < words)
    {
        char* name = randomName();
        strcat(str, name);
        strcat(str, " ");
        ++size; 
    }

    char* str2 = &str[0];

    return str2;
}

LinkedList* createLinkedList()
{
    LinkedList* accounts = (LinkedList*)malloc(sizeof(NodeBank));

    if (!accounts)
    {
        perror(":(\n");
        exit(-1);
    }

    accounts->head = NULL;
    accounts->tail = NULL;
    accounts->size = 0; 

    return accounts; 
}

void fillNode(NodeBank* account)
{
    account->value.id = unique++; 
    strcpy(account->value.currency, arr[rand() % 5]);
    account->value.available = (rand() % (10000000 - 0 + 1))/100. + 0.0;
    strcpy(account->value.owner, randomOwner());
    //account->next = NULL; 
}

int isEmptyLinkedList(LinkedList* accounts)
{
    if (accounts->head == NULL && accounts->tail == NULL && accounts->size == 0)
    {
        return 1;
    }

    return 0; 
}

void push_back_LinkedList(LinkedList* accounts)
{
    if (accounts->size == ITEMS_COUNT)
    {
        printf("FULL\n");
        return; 
    }
    
    NodeBank* temp = (NodeBank*)malloc(sizeof(NodeBank));

    if (!temp)
    {
        perror(":(\n");
        exit(1);
    }

    fillNode(temp); 
    temp->next = NULL;

    if (isEmptyLinkedList(accounts) == 1)
    {
        accounts->head = temp;
        accounts->tail = accounts->head;
        accounts->size = 1; 
        return; 
    }

    accounts->tail->next = temp; 
    accounts->tail = temp;
    accounts->size += 1; 
}

void pop_front_LinkedList(LinkedList* accounts)
{
    if (isEmptyLinkedList(accounts) == 1)
    {
        printf("Empty...\n");
        return;
    }
    else if (accounts->head == accounts->tail)
    {
        free(accounts->head);
        accounts->head = NULL;
        accounts->tail = NULL; 
        accounts->size = 0; 
        return; 
    }

    NodeBank* temp = accounts->head;
    accounts->head = accounts->head->next;
    free(temp);
    accounts->size -= 1; 
}

void freeLinkedList(LinkedList* accounts)
{
    while(accounts->head != NULL)
    {
        pop_front_LinkedList(accounts);
    }

    free(accounts);
    printf("LinkedList was freed...\n");
}

void printLinkedList(LinkedList* accounts)
{
    NodeBank* current = accounts->head;

    while (current != NULL)
    {
        printf("ID: %5d, OWNER: %90s, AVAILABLE: %8.2lf, CURRENCY: %s\n", current->value.id, current->value.owner, current->value.available, current->value.currency);
        current = current->next;
    }
    
    printf("\n");
}

double totalBalance(NodeBank* head)
{
    if (!head)
    {
        return -1; 
    }

    NodeBank* current = head;
    double sum = 0; 

    while (current != NULL)
    {
        sum += current->value.available; 
        current = current->next;
    }

    return sum; 
}

NodeBank* maxBalance(NodeBank* head)
{
    if (!head)
    {
        return NULL; 
    }

    NodeBank* current = head;
    NodeBank* max = head; 

    while (current != NULL)
    {
        if (current->value.available > max->value.available)
        {
            max = current; 
        }
        
        current = current->next;
    }

    return max; 
}


int main()
{
    srand(time(0));
    setUnique();
    int size = 0;

    LinkedList* accounts = createLinkedList();

    while (size < ITEMS_COUNT)
    {
        push_back_LinkedList(accounts);
        ++size; 
    }
    
    printLinkedList(accounts);

    NodeBank* max = maxBalance(accounts->head);
    printf("SUM OF ALL AVAILABLES: %.2lf\n", totalBalance(accounts->head));
    printf("ACCOUNT WITH MAX BALANCE: %d ID with %8.2lf in %s\n", max->value.id, max->value.available, max->value.currency);

    freeLinkedList(accounts);
    return 0;
}