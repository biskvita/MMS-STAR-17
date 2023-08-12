#include "stack-list.h"

StackList* init_stack_list()
{
    StackList* stack = (StackList*)malloc(sizeof(StackList));

    if (!stack)
    {
        exit(-1);
    }

    stack->top = NULL; 
    stack->size = 0; 

    return stack; 
}

int isEmpty(StackList* stack)
{
    if (stack->size == 0 && stack->top == NULL)
    {
        return 1;
    }

    return 0; 
}

void push(Data new_data, StackList* stack)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->d = new_data; 
    temp->next = NULL;

    if (isEmpty(stack) == 1)
    {
        stack->top = temp;
        return; 
    }

    temp->next = stack->top;
    stack->top = temp; 
}

void pop(StackList* stack)
{
    if (isEmpty(stack) == 1)
    {
        printf("Empty...\n");
        return; 
    }

    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
}

Data peek(StackList* stack)
{
    if (isEmpty(stack) == 1)
    {
        printf("Empty...\n");
        exit(-1);
    }

    return stack->top->d;  
}  

void deinit_stack_list(StackList* stack)
{
    while (!stack->top)
    {
        pop(stack);
    }

    free(stack);
}

void print_stack(StackList* stack)
{
    Node* temp;
 
    if (isEmpty(stack) == 0)
    {
        temp = stack->top;

        while (temp != NULL) 
        {
            printf("%d ", temp->d.val);
            temp = temp->next;
        }
    }

    printf("\n");
}