#include <stdlib.h>
#include <stdio.h>

#include "colours/colours.h"
#include "deque/deque.c"
#include "../tests/deque/deque_t.h"


int tmp_t[] = {8, 23, 22, 17, 27, 7, 21, 2, 26, 8, 14, 5, 0, 18, 12, 9, 8, 2, 21, 22};
int *test_vals[20];

void test_init(void)
{
    for (int i = 0; i < 20; i++)
    {
        test_vals[i] = &tmp_t[i];
    }
    
    return;
}

void deque_t(void)
{
    deque *test_var = init_deque(test_vals, 20, 20);
    if (test_var == NULL)
    {
        red();
        fprintf(stderr, ":( Could not initialise deque (deque_t)\n");
        reset();
        return;
    }

    for (unsigned long i = 0, count = test_var->count; i < count; i++)
    {
        if (test_var->deque[i] != test_vals[i])
        {
            red();
            fprintf(stderr, ":( init_deque does not work as intended. Element at %ld is supposed to be %p but is instead %p\n", i, test_vals[i], test_var->deque[i]);
            reset();
            return;
        }
    }

    green();
    fprintf(stdout, ":) init_deque works as intended\n");
    reset();
    
    int **retval = clear(test_var);

    if (retval != test_vals)
    {
        red();
        fprintf(stderr, ":( clear does not return the correct value. Return value should be %p but is instead %p\n", test_vals, retval);
        reset();
        //return;
    }

    if (test_var->deque != NULL)
    {
        red();
        fprintf(stderr, ":( clear does not clear deque correctly. Value at test_var->deque should be %p but is instead %p\n", NULL, test_var->deque);
        reset();
        //return;
    }
    
    green();
    fprintf(stdout, ":) clear works as intended\n");
    reset();

    test_var->deque = test_vals;

    retval = dlt_deque(test_var);

    if (retval != test_vals)
    {
        red();
        fprintf(stderr, ":( dlt_deque does not return the correct value. Return value should be %p but is instead %p\n", test_vals, retval);
        reset();
        return;
    }

    green();
    fprintf(stdout, ":) dlt_deque works as intended\n");
    reset();

    return;
}

void get_t(void)
{
    deque *test_var = init_deque(test_vals, 20, 20);
    if (test_var == NULL)
    {
        red();
        fprintf(stderr, ":( Could not initialise deque\n");
        reset();
        return;
    }

    int count = get_count(test_var);

    if (count != 20)
    {
        red();
        fprintf(stderr, ":( get_count does get count correctly. Return value should be %d instead return value is %d (Value in deque: %ld)\n", count, 20, test_var->count);
        reset();
        return;
    }

    green();
    fprintf(stdout, ":) get_count works correctly\n");
    reset();

    int *retval;

    for (unsigned long i = 0; i < count; i++)
    {
        retval = get_element(test_var, i);
        if (retval != test_vals[i])
        {
            red();
            fprintf(stderr, ":( get_element does not get element correctly. Return value should be %p (%d) but is instead %p (%d) (Value in deque: %p)\n", test_vals[i], *test_vals[i], retval, *retval, test_var->deque[i]);
            reset();
            return;
        }
    }
    
    green();
    fprintf(stdout, ":) get_element works correctly\n");
    reset();

    dlt_deque(test_vals);

    return;
}

void stack_t(void)
{
    deque *test_var = init_deque(NULL, 20, 0);
    if (test_var == NULL)
    {
        red();
        fprintf(stderr, ":( Could not initialise deque\n");
        reset();
        return;
    }

    int push_retval;

    for (int i = 0; i < 20; i++)
    {
        push_retval = push(test_var, test_vals[i]);

        if (push_retval != 0)
        {
            red();
            fprintf(stderr, ":( Could not push value on deque. Returns: %d\n", push_retval);
            reset();
            return;
        }

        int *retval = get_element(test_var, i);
        if (retval != test_vals[i])
        {
            red();
            fprintf(stderr, ":( Incorrect value pushed onto stack. Value should have been %d at %p but was instead %d at %p\n", *test_vals[i], test_vals[i], *retval, retval);
            reset();
            return;            
        }
        
    }

    green();
    fprintf(stdout, ":) push works correctly\n");
    reset();

    for (int i = 0; i < 20; i++)
    {
        int *pop_val = pop(test_var);
        
        if (pop_val == NULL)
        {
            red();
            fprintf(stderr, ":( Could not pop value off stack\n");
            reset();
            return;
        }

        if (pop_val != test_vals[19 - i])
        {
            red();
            fprintf(stderr, ":( Incorrect value popped off stack. Value should have been %d at %p but was instead %d at %p\n", *test_vals[i], test_vals[19 - i], *pop_val, pop_val);
            reset();
            return;   
        }
    }
    
    green();
    fprintf(stdout, ":) pop works correctly\n");
    reset();

    free(dlt_deque(test_vals));

    return;
}

void queue_t(void)
{
    deque *test_var = init_deque(0, 20, 0);
    if (test_var == NULL)
    {
        red();
        fprintf(stderr, "Could not initialise deque\n");
        reset();
        return;
    }
    
    int queue_retval;
    
    for (int i = 0; i < 20; i++)
    {
        queue_retval = queue(test_var, test_vals[i]);
        if (queue_retval != 0)
        {
            red();
            fprintf(stderr, "Could not queue value. Returns: %d\n", queue_retval);
            reset();
            return;
        }
        
        int *retval = get_element(test_var, i);
        if (retval != test_vals[i])
        {
            red();
            fprintf(stderr, ":( Incorrect value queeued. Value should have been %d at %p but was instead %d at %p\n", *test_vals[i], test_vals[i], *retval, retval);
            reset();
            return;
        }
    }
    
    green();
    fprintf(stdout, ":) queue works correctly\n");
    reset();

    int * deq_retval;
    for (int i = 0; i < 20; i++)
    {
        deq_retval = dequeue(test_var);
        if (deq_retval == NULL)
        {
            red();
            fprintf(stderr, ":( Could not dequeue value.\n");
            reset();
            return;
        }
        
        if (deq_retval != test_vals[19 - i])
        {
            red();
            fprintf(stderr, ":( Incorrect value dequeued. Value should have been %d at %p but was instead %d at %p\n", *test_vals[19 - i], test_vals[19 - i], *deq_retval, deq_retval);
            reset();
            return;
        }
    }
    

}