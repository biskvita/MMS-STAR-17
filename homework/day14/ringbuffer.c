#include "ringbuffer.h"

RingBuffer* init_RB(size_t capacity) 
{
    RingBuffer* rb = (RingBuffer*)malloc(sizeof(RingBuffer));

    if (!rb)
    {
        exit(-1);
    }

    rb->buffer_capacity = capacity;
    rb->start_index = 0;
    rb->end_index = 0; 
    rb->arr = (double*)calloc(capacity, sizeof(double));

    return rb; 
}

void deinit_RB(RingBuffer* rb) 
{
    free(rb->arr);
    free(rb);
}

void print_buffer(RingBuffer* rb) 
{
    for (size_t i = 0; i < rb->buffer_capacity; i++) 
    {
        if(rb->arr[i] != 0) 
        {
            printf("%3.2lf ", rb->arr[i]);
        } 
        else 
        {
            printf("---- ");
        }
    }
}

void enqueue(RingBuffer* rb, double data) 
{
    if (rb->start_index > rb->buffer_capacity) 
    {
        rb->start_index -= rb->buffer_capacity;
        rb->end_index -= rb->buffer_capacity;
    }
    else if (rb->end_index - rb->start_index == rb->buffer_capacity) 
    {
        perror("Ring buffer is full.");
        return;
    }

    rb->arr[rb->end_index % rb->buffer_capacity] = data;
    rb->end_index++;
}

void dequeue(RingBuffer* rb) 
{
    if (rb->end_index - rb->start_index == 0) 
    {
        perror("Ring bufffer is empty");
        return;

    }
    
    rb->arr[rb->start_index] = 0; 
    rb->start_index++;
}