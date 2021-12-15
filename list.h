//
// Created by Benjam on 12/14/2021.
//

#ifndef SHOT_LIST_H
#define SHOT_LIST_H

// Linked list structure
typedef struct list_t list;

/**
 * Creates an empty list
 *
 * @return The new list
 */
list* list_create();

/**
 * Frees a list and the contained data
 *
 * @param l The list to delete
 */
void list_free(list* l);

/**
 * Adds an element into the list
 *
 * @param l The list to append data
 * @param data The data to append
 */
void list_add(list* l, void* data);

#endif //SHOT_LIST_H
