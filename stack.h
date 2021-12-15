//
// Created by Benjam on 12/14/2021.
//

#ifndef SHOT_STACK_H
#define SHOT_STACK_H

typedef struct stack_t stack;

/**
 * Creates an empty stack
 *
 * @return Created stack
 */
stack *stack_create();

/**
 * Frees a stack
 *
 * @param s The stack to erase
 */
void stack_free(stack* s);

/**
 * Pushes a value in the stack
 *
 * @param s The stack
 * @param data The data to push into the stack
 */
void stack_push(stack* s, void* data);

/**
 * * Returns the last inserted value into the stack
 *
 * @param s The stack
 * @return The last inserted value
 */
void* stack_top(stack* s);

/**
 * Returns the last inserted value into the stack and removes the node at the head of the stack
 *
 * @param s The stack
 * @return The last inserted value
 */
void *stack_pop(stack* s);

/**
 * @param s The stack
 * @return The size of the stack
 */
int stack_size(stack* s);

/**
 * @param s The stack
 * @return If the stack is empty
 */
int stack_empty(stack* s);

#endif //SHOT_STACK_H
