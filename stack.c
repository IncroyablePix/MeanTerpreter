//
// Created by Benjam on 12/14/2021.
//

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t
{
    void* data;
    struct node_t* next;
} node;

struct stack_t
{
    node* top;
    int size;
};

static void terminate(char *m)
{
    printf("%s\n", m);
    exit(EXIT_FAILURE);
}

stack* stack_create()
{
    stack* s = malloc(sizeof(stack));
    if(!s)
    {
        terminate("Stack could not be created");
    }

    s->top = NULL;
    s->size = 0;

    return s;
}

void stack_free(stack* stack)
{
    node *n = stack->top;
    while(n)
    {
        node* next = n->next;
        free(n);
        n = next;
    }

    free(stack);
}

void stack_push(stack* s, void* data)
{
    node *n = malloc(sizeof(node));
    if (!n)
        terminate("Stack node cannot be created");
    n->data = data;
    n->next = s->top;
    s->top = n;
    s->size++;
}

void* stack_top(stack* stack)
{
    if(!(stack->top))
    {
        terminate("\nstack_top: Stack is empty");
    }
    return stack->top->data;
}

void* stack_pop(stack* s)
{
    if (!(s->top))
    {
        terminate("Stack is empty");
    }

    node *n = s->top;
    void *data = n->data;
    s->top = n->next;
    s->size--;

    free(n);
    return data;
}

int stack_size(stack* stack)
{
    return stack->size;
}

int stack_empty(stack* stack)
{
    return stack->size == 0;
}