//
// Created by Benjam on 12/14/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

typedef struct node_t
{
    void *data;
    struct node_t* next;
} node;

struct list_t
{
    node* first;
};

static void terminate(char* m)
{
    printf("%s\n", m);
    exit(EXIT_FAILURE);
}

list* list_create()
{
    list* l = malloc(sizeof(list));

    if(!l)
    {
        terminate("List cannot be created");
    }

    l->first = NULL;

    return l;
}

void list_add(list* l, void* data)
{
    node* newNode = malloc(sizeof(node));

    if(!newNode)
    {
        terminate("Node cannot be created");
    }

    newNode->next = l->first;
    l->first = newNode;

    newNode->data = data;
}

void list_free(list* l)
{
    node* current = l->first;

    while(current)
    {
        node* next = current->next;

        free(current->data);
        free(current);

        current = next;
    }

    free(l);
}
