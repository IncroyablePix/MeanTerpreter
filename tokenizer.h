//
// Created by Benjam on 12/14/2021.
//

#ifndef SHOT_TOKENIZER_H
#define SHOT_TOKENIZER_H

typedef enum
{
    T_SYMBOL,  // nom de variable
    T_OPERATOR, // Tous les autres
    T_EQUAL, // =
    T_NUMBER, // Nombre
    T_LEFTPAR, // (
    T_RIGHTPAR, // )
    T_STOP // Fin de l'expression
} token_type;

typedef struct token_t token;
typedef struct tokenizer_t tokenizer;

/**
 * Initializes a new tokenizer
 *
 * @param expression The expression to tokenize
 *
 * @return The new tokenizer
 */
tokenizer* tokenizer_create(const char* expression);

/**
 * Frees a tokenizer
 *
 * @param t The tokenizer to delete
 */
void tokenizer_free(tokenizer* t);

/**
 * Gets the next token for the tokenizer
 *
 * @param t The tokenizer to get the token from
 * @return The next token
 */
token* tokenizer_get_next_token(tokenizer* t);

/**
 * Resets a tokenizer to the beginning of the expression
 *
 * @param tokenizer The tokenizer to reset
 */
void tokenizer_reset(tokenizer* tokenizer);

/**
 * Gets the position of a token
 *
 * @param t The token
 * @return The position of the token in the expression
 */
int token_get_position(token *t);

/**
 * Gets the type of a token
 *
 * @param t The token
 * @return The type of the token
 */
token_type token_get_type(token* t);

/**
 * Gets the value of a token
 *
 * @param token The token
 * @return The value of the token
 */
void* token_get_value(token* token);

/**
 * Frees a token
 *
 * @param token The token
 * @param free_value 0 to free only the token, 1 to free its value as well
 */
void token_free(token* token, int free_value);

/**
 * Prints out the token
 *
 * @param token The token
 */
void token_print(token* token);

#endif //SHOT_TOKENIZER_H
