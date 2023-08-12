#include "stack.h"

Stack init_stack(size_t capacity)
{
    Stack res;
    res.capacity = capacity;
    res.size = 0; 
    res.arr = (A*)calloc(capacity, sizeof(A));

    return res;
}

void push(Stack* stack, A elem)
{
    if(stack->capacity == stack->capacity) 
    {
        printf("Full...\n");
        return;
    }
    
    stack->arr[stack->size++] = elem;
}

void pop(Stack* stack)
{
    if(stack->size == 0) 
    {
        printf("Empty...\n");
        return;
    }
    
    stack->size--;
}

A peek(Stack stack)
{
    return stack.arr[0];
}

void print_stack(Stack stack)
{
    for(size_t i = 0; i < stack.size; i++) 
    {
        printf("%3d ", stack.arr[i].data);
    }

    printf("\n");
}

void deinit_stack(Stack stack)
{
    free(stack.arr);
}