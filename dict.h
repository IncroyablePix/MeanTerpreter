//
// Created by Benjam on 12/14/2021.
//

#ifndef SHOT_DICT_H
#define SHOT_DICT_H

typedef struct dict_t dict;

/**
 * Creates an empty dictionary
 *
 * @param m Size of the hash table
 *
 * @return Created dictionary
 */
dict* dict_create(int m);

/**
 * Frees a dictionary
 *
 * @param dict The dictionary to delete
 */
void dict_free(dict* dict);

/**
 * Searches for a value in the dictionary
 *
 * @param dict The dictionary
 * @param key The key in form of a string
 * @return The value retrieved or NULL if it could not be found
 */
void* dict_get(dict* dict, char* key);

/**
 * Checks if the dictionary has a value for the key
 *
 * @param dict The dictionary
 * @param key The key
 * @return If the dictionary contains the value
 */
int dict_contains(dict* dict, char* key);

/**
 * Removes an entry from the dictionary
 *
 * @param dict The dictionary
 * @param key The key
 */
//void dict_remove(dict* dict, char* key);

/**
 * Inserts a value in a dictionary
 *
 * @param dict The dictionary to insert into
 * @param key The key
 * @param value The value
 */
void dict_insert(dict* dict, char* key, void* value);

#endif //SHOT_DICT_H
