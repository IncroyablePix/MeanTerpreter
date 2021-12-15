//
// Created by Benjam on 12/14/2021.
//

#include "dict.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
    char* key;
    void *value;
    struct node_t* next;
} node;

struct dict_t
{
    node **array;
    int array_size;
};

static unsigned int h(dict* dict, char* key)
{
    unsigned long hash = 5381;
    while(*key != '\0')
    {
        hash = hash * 33 + *key;
        key ++;
    }

    return hash % dict->array_size;
}

static void terminate(char* m)
{
    printf("%s\n", m);
    exit(EXIT_FAILURE);
}

dict* dict_create(int m)
{
    dict* d = malloc(sizeof(dict));

    if(!d)
    {
        terminate("Dictionary cannot be created");
    }

    d->array = calloc(m, sizeof(node));
    if(!d->array)
    {
        terminate("Dictionary cannot be created");
    }

    d->array_size = m;

    return d;
}

void dict_free(dict* d)
{
    node *n, *nn;
    for (int i = 0; i < d->array_size; i++)
    {
        n = d->array[i];
        while (n != NULL)
        {
            nn = n->next;
            free(n->key);
            free(n);
            n = nn;
        }
    }

    free(d->array);
    free(d);
}

void* dict_get(dict* d, char* key)
{
    node *p = d->array[h(d, key)];
    while (p != NULL && strcmp(p->key, key) != 0)
    {
        p = p->next;
    }

    if (p != NULL)
    {
        return p->value;
    }
    else
    {
        return NULL;
    }
}

int dict_contains(dict* d, char* key)
{
    node *p = d->array[h(d, key)];

    while (p != NULL && strcmp(p->key, key) != 0)
    {
        p = p->next;
    }

    return (p != NULL);
}

void dict_insert(dict* d, char* key, void* value)
{
    int hashval = h(d,key);
    node *p = d->array[hashval];
    while (p != NULL && strcmp(p->key, key) != 0)
    {
        p = p->next;
    }

    if (p != NULL)
    {
        p->value = value;
    }
    else
    {
        node *newNode = malloc(sizeof(node));
        if (!newNode)
            terminate("New node cannot be created.");

        int len = strlen(key);
        char *k = malloc((len + 1) * sizeof(char));
        if (!k)
            terminate("New node cannot be created.");

        strcpy(k, key);

        newNode->key = k;
        newNode->value = value;
        newNode->next = d->array[hashval];
        d->array[hashval] = newNode;
    }
}