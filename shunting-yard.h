//
// Created by Benjam on 12/14/2021.
//

#ifndef SHOT_SHUNTING_YARD_H
#define SHOT_SHUNTING_YARD_H

#include "tokenizer.h"
#include "symboltable.h"

/**
 * Evaluates the expression output by the tokenizer
 *
 * @param t The tokenizer
 * @param st The symbol table
 * @param solution A pointer to a double where the value of the expression will be stored
 *
 * @return If no error occurred
 */
int shunting_yard_evaluate(tokenizer* t, symbol_table* st, double *solution);

#endif //SHOT_SHUNTING_YARD_H
