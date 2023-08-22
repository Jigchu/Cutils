#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "deque.h"

// Structs for a stack and a queue respectively
typedef struct deque
{
    void **deque;

    unsigned long size;
    unsigned long count;
} deque;

deque *init_deque(void **values, unsigned long size, unsigned long count)
{
    deque *retval = malloc(sizeof(deque));
    
    retval->deque = values == NULL && size != 0 ? malloc(sizeof(void *) * size) : values;
    if (retval->deque == NULL && values != NULL)
    {
        dlt_deque(retval);
        return NULL;
    }
    

    retval->size = values == NULL && size < 0 ? 0 : size;
    retval->count = values == NULL && count < 0 ? 0 : count;

    return retval;
}

void **dlt_deque(deque *deque)
{
    // Stores the list of pointers
    void **retval = deque->deque;
    
    deque->deque = NULL;
    deque->count = 0;
    deque->size = 0;

    free(deque);

    return retval;
}

int push(deque *stack, void *value)
{
    if (stack == NULL || value == NULL)
    {
        return -1;
    }
    
    if (stack->count++ <= stack->size)
    {
        stack->deque[stack->count-1] = value;
        return 0;
    }
    

    void **new_mem = realloc(stack->deque, sizeof(void *) * (stack->size++));
    if (new_mem == NULL)
    {
        return -2;
    }
    
    new_mem[stack->count] = value;
    
    stack->deque = NULL;

    stack->deque = new_mem;

    return 0;
}

void *pop(deque *stack)
{
    if (stack == NULL || stack->count == 0)
    {
        return NULL;
    }
    
    stack->count--;
    stack->size == 1 ?  : stack->size--;
    void *popped_val = stack->deque[stack->count];
    void **new_mem = realloc(stack->deque, sizeof(void *) * (stack->size));
    if (new_mem == NULL)
    {
        return NULL;
    }

    stack->deque = new_mem;
    
    return popped_val;
}

int queue(deque *queue, void *value)
{
    if (queue == NULL || value == NULL)
    {
        return -1;
    }
    
    if (queue->count++ <= queue->size)
    {
        queue->deque[queue->count-1] = value;
        return 0;
    }


    void **new_mem = realloc(queue->deque, sizeof(void *) * (queue->size++));
    if (new_mem == NULL)
    {
        return -2;
    }
    
    new_mem[queue->count] = value;
    
    free(queue->deque);
    queue->deque = NULL;

    queue->deque = new_mem;
    queue->count++;

    return 0;
}

void *dequeue(deque *queue)
{
    if (queue == NULL || queue->count == 0)
    {
        return NULL;
    }
    
    queue->size--;
    void *popped_val = queue->deque[0];
    void **new_mem = realloc(queue->deque, sizeof(void *) * (queue->size));
    if (new_mem == NULL)
    {
        return NULL;
    }
    
    free(queue->deque);
    queue->deque = NULL;

    queue->deque = new_mem;
    queue->count--;
    
    return popped_val;
}

void *rmv(deque *dequeue, unsigned long index)
{
    return NULL;
}

void **clear(deque *dequeue)
{
    return NULL;
}

// Accesses a certain element in the array in a deque using index
void *get_element(deque *dequeue, unsigned long index)
{
    void *retval = index > (dequeue->count - 1) ? NULL : dequeue->deque[index];

    return retval;
}

// Accesses count member of deque
unsigned long get_count(deque *dequeue)
{
    return dequeue->count;
}

deque *search(deque *dequeue, void *value, bool same(const void *, const void *))
{
    deque *retval = init_deque(NULL, 0, 0);
    if (retval == NULL)
    {
        return retval;
    }
    
    for (unsigned long i = 0, count = dequeue->count; i < count; i++)
    {
        if (push(retval, same(value, dequeue->deque[i]) ? dequeue->deque[i] : NULL) == -2)
        {
            free(dlt_deque(retval));

            return NULL;
        }
    }
    
    return retval;
}