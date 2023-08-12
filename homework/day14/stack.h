#include<stdio.h>
#include<stdlib.h>

#ifndef STACK__H
#define STACK__H 1

typedef struct A 
{
    int data;
} A;

typedef struct Stack 
{
    A* arr;
    size_t capacity;
    size_t size;
} Stack;

Stack init_stack(size_t capacity);
void push(Stack* stack, A elem);
void pop(Stack* stack);
A peek(Stack stack);
void print_stack(Stack stack);
void deinit_stack(Stack stack);

#endif