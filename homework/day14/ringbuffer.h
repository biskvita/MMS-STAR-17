#include <stdio.h>
#include <stdlib.h>

#ifndef RING_BUFFER_H
#define RING_BUFFER_H 1

typedef struct RingBuffer 
{
    double* arr;
    size_t buffer_capacity;
    size_t start_index;
    size_t end_index;
} RingBuffer;

RingBuffer* init_RB(size_t capacity);
void deinit_RB(RingBuffer* rb);
void print_buffer(RingBuffer* rb);
void enqueue(RingBuffer* rb, double data);
void dequeue(RingBuffer* rb);

#endif