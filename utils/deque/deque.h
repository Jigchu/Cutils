#pragma once

#include <stdbool.h>

typedef struct deque deque;

deque *init_deque(void **values, unsigned long size, unsigned long count);
void **dlt_deque(deque *deque);
int push(deque *stack, void *value);
void *pop(deque *stack);
int queue(deque *queue, void *value);
void *dequeue(deque *queue);
void *rmv(deque *dequeue, unsigned long index);
void **clear(deque *dequeue);
void *get_element(deque *dequeue, unsigned long index);
unsigned long get_count(deque *dequeue);
deque *search(deque *dequeue, void *value, bool same(const void *, const void *));