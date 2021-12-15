//
// Created by Benjam on 12/14/2021.
//

#ifndef SHOT_CALCULATOR_H
#define SHOT_CALCULATOR_H

#include "symboltable.h"

/**
 * Starts the calculator interpreter
 */
void calcul_repl();

/**
 * Initializes the symbol table
 *
 * @return The symbol table
 */
symbol_table * calc_init_symbol_table();


#endif //SHOT_CALCULATOR_H
