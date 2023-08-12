#include "linkedlist.h"

void print(LL* ll) 
{
    Node* head = ll->head;
    
    for(;head != NULL; head=head->next) 
    {
        printf("%d ", head->d.val);
    }
    printf("\n");
}

void push_back(Data new_data, LL* ll) 
{
    Node** head = &(ll->head);
    Node** tail = &(ll->tail);
    Node* new_last_node = (Node*)malloc(sizeof(Node));

    if(!new_last_node) 
    {
        perror("Could not malloc\n");
        exit(-1);
    }

    new_last_node->d = new_data;
    new_last_node->next = NULL;

    if(*head == NULL) 
    {
        *head = new_last_node;
        *tail = new_last_node;
        return;
    }

    (*tail) -> next = new_last_node;
    *tail = (*tail) -> next;
}

void pop_back(LL* ll, Data* result) 
{
    Node** head = &(ll->head);
    Node** tail = &(ll->tail);

    if(!(*head)) 
    { 
        perror("Cannot pop from empty linked list\n");
        exit(-1);
    }
    
    if((*head)->next == NULL) 
    {
        *result = (*head)->d;
        free(*head);
        *head = NULL; 
        *tail = NULL;
        return;
    }
    
    Node* cur_node = *head;
    
    while(cur_node->next->next != NULL) 
    {
        cur_node = cur_node->next;
    }
    
    *result = cur_node->next->d;
    free(cur_node->next);
    cur_node->next = NULL;

    *tail = cur_node;
}
void push_front(Data new_data, LL* ll) 
{
    Node** head = &(ll->head);
    Node* new_first_node = (Node*)malloc(sizeof(Node));

    if(new_first_node == NULL) 
    {
        perror("Could not malloc\n");
        exit(-1);
    }

    new_first_node->d = new_data;
    new_first_node->next = *head;
    *head = new_first_node;

    if(ll->tail == NULL) 
    {
        ll->tail = new_first_node;
    }
}

void pop_front(LL* ll, Data* result) 
{
    Node** head = &(ll->head);

    if(*head == NULL) 
    {
        perror("Cannot pop from empty linked list\n");
        exit(-1);
    }
    
    if(result != NULL) 
    {
        *result = (*head)->d;
    }

    Node* second_node = (*head)->next;
    free(*head);
    *head = second_node;

    if(*head == NULL) 
    {
        ll->tail = NULL;
    }
}

LL* init_linked_list() 
{
    LL* ll = (LL*)malloc(sizeof(LL));

    if(!ll) 
    {
        perror("Could not malloc\n");
        exit(-1);
    }
    
    ll->head = NULL; 
    ll->tail = NULL;

    return ll;
}

void deinit_linked_list(LL* ll) 
{
    while(!(ll->head)) 
    {
        pop_front(ll, NULL);
    }

    free(ll);
}