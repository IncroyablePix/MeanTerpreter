//
// Created by Benjam on 12/14/2021.
//

#ifndef SHOT_SYMBOLTABLE_H
#define SHOT_SYMBOLTABLE_H

typedef enum
{
    T_ASSOC_LEFT = -1,
    T_ASSOC_RIGHT = 1
} operator_associativity;

typedef struct symbol_table_t symbol_table;

/**
 * Type of the C functions associated to "functions" - takes one double and returns one
 * i.e. sin, cos, etc.
 */
typedef double (*FunctionFctType)(double);

/**
 * Type of the C functions associated to "operators" - takes two doubles as arguments and returns a double
 * i.e. -, +, etc.
 */
typedef double (*OperatorFctType)(double, double);

/**
 * Creates an empty symbol table
 * @return The created symbol table
 */
symbol_table* symbol_table_create();

/**
 * Frees a symbol table
 *
 * @param st The symbol table to delete
 */
void symbol_table_free(symbol_table* st);

/**
 * Adds a new operator in the symbol table
 *
 * @param st The symbol table
 * @param symbol The name of the operator
 * @param prec The precedence of the operator
 * @param assoc The associativity of the operator
 * @param func The C function that computes the operator
 */
void symbol_table_insert_op(symbol_table* st, char* symbol, int prec, int assoc, OperatorFctType func);

/**
 * Adds a new function in the symbol table
 *
 * @param st The symbol table
 * @param symbol The name of the function
 * @param func The C function that computes the function
 */
void symbol_table_insert_func(symbol_table* st, char* symbol, FunctionFctType func);

/**
 * Adds a new variable in the symbol table
 *
 * @param st The symbol table
 * @param symbol The name of the variable
 * @param val The value of the variable
 */
void symbol_table_insert_var(symbol_table* st, char* symbol, double val);

/**
 * Checks if the operator is contained in the symbol table
 *
 * @param st The symbol table
 * @param symbol The symbol
 * @return If the symbol table contains the operator
 */
int symbol_table_contains_op(symbol_table* st, char* symbol);

/**
 * Checks if the function is contained in the symbol table
 *
 * @param st The symbol table
 * @param symbol The symbol
 * @return If the symbol table contains the functino
 */
int symbol_table_contains_func(symbol_table* st, char* symbol);

/**
 * Checks if the variable is contained in the symbol table
 *
 * @param st The symbol table
 * @param symbol The symbol
 * @return
 */
int symbol_table_contains_var(symbol_table* st, char* symbol);

/**
 * Gets a pointer to the function (of type (double, double): double) associated to an operator
 *
 * @param st The symbol table
 * @param symbol The symbol to search for
 * @return The function pointer for the function
 */
OperatorFctType symbol_table_get_op_func(symbol_table* st, char* symbol);

/**
 * Gets the precedence of an operator
 *
 * @param st The symbol table
 * @param symbol The name of the operator
 * @return The precedence of the operator or -1 if the operator was not found
 */
int symbol_table_get_op_prec(symbol_table* st, char* symbol);

/**
 * Gets the associativity of an operator
 *
 * @param st The symbol table
 * @param symbol The name of the operator
 * @return The precedence of the operator or -1 if the operator was not found
 */
int symbol_table_get_op_assoc(symbol_table* st, char* symbol);

/**
 * Gets a pointer to a function (of type (double): double) associated to a function in our language
 *
 * @param st The symbol table
 * @param symbol The name of the function
 * @return A pointer to the function.
 */
FunctionFctType symbol_table_get_func(symbol_table* st, char* symbol);

/**
 * Gets the value of a variable
 *
 * @param st The symbol table
 * @param symbol The name of the variable
 * @param result A pointer to a double to a variable that the result will be stored in
 * @return If the variable was found
 */
int symbol_table_get_var(symbol_table* st, char* symbol, double* result);


#endif //SHOT_SYMBOLTABLE_H
