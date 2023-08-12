#include<stdio.h>
#include<stdlib.h>

#include "linkedlist.h"

#ifndef STACK_LIST_H
#define STACK_LIST_H 1

typedef struct StackList
{
    Node* top;
    size_t size; 

} StackList;

StackList* init_stack_list();
void deinit_stack_list(StackList* stack);
int isEmpty(StackList* stack);
void push(Data new_data, StackList* stack);
void pop(StackList* stack);
Data peek(StackList* stack);
void print_stack(StackList* stack);

#endif