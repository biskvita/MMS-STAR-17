#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int data;
    struct Node* next; 
} Node;

void freeNodes(Node** cll)
{
    Node* current = (*cll)->next;

    do 
    {
        Node* temp = current->next;
        current->next = current->next;
        free(temp);
        
    } while (current != (*cll)->next);

    printf("Freed...\n");
}

Node* push_back(Node* last, int data) 
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;

    if (last == NULL) 
    {
        last = temp;
        last->next = last;

        return last; 
    }

    temp->next = last->next;
    last->next = temp;
    last = temp;

    return last;
}

void print(Node* cll) 
{
    if (cll == NULL) 
    {
        printf("Empty\n");
        return;
    }

    Node* current = cll->next;

    do 
    {
        printf("%d ", current->data);
        current = current->next;

    } while (current != cll->next);

    printf("\n");
}

Node* insertAfter(Node* cll, int skipCount, int newElem)
{
    if (cll == NULL || !(skipCount >= 0 && skipCount <= 1000000)) 
    {
        printf("Empty\n");
        return NULL;
    }

    Node* current = cll->next;
    int i = 1; 

    do {

        if (i == skipCount) 
        {
            Node* temp = (Node*)malloc(sizeof(Node));
            temp->data = newElem;
            temp->next = current->next;
            current->next = temp;

            if (cll == current) 
            {   
                cll = temp;
            }

            return cll;
        }

        current = current->next;
        ++i; 

    } while (current != cll->next);

    return cll;
}

int main()
{
    int N, temp; 

    do
    {
        printf("N: ");
        scanf("%d", &N);
    } while (N <= 0);

    Node* last = NULL;
    
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &temp);
        last = push_back(last, temp);
    }
    
    printf("Ready...\n");
    print(last);
    insertAfter(last, 3, 7);
    print(last);

    freeNodes(&last);
    return 0; 
}