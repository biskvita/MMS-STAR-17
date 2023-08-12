#include <stdio.h>
#include <stdlib.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H 1

typedef struct Data 
{
    int val;
} Data;

typedef struct Node 
{
    Data d;
    struct Node *next;
} Node;

typedef struct LL 
{
    Node *head;
    Node *tail;
} LL;

void print(LL *ll);
void push_back(Data new_data, LL *ll);
void pop_back(LL *ll, Data *result);
void push_front(Data new_data, LL *ll);
void pop_front(LL *ll, Data *result);
LL* init_linked_list();
void deinit_linked_list(LL* ll);

#endif