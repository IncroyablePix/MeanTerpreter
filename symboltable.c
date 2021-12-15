//
// Created by Benjam on 12/14/2021.
//

#include "dict.h"
#include "list.h"
#include "symboltable.h"
#include <stdlib.h>

union function_ptr
{
    FunctionFctType fct;
    OperatorFctType opf;
};

typedef struct symbol_t
{
    char* value; // value (symbol, string)
    int precedence; // precedence
    int associativity; // associativity
    union function_ptr func; // function for the symbol
    double variable; // variable value
} symbol;

struct symbol_table_t
{
    dict* dict;
    list* list;
};

symbol_table* symbol_table_create()
{
    symbol_table* st = malloc(sizeof(symbol_table));

    st->dict = dict_create(1000);
    st->list = list_create();

    return st;
}

void symbol_table_free(symbol_table* st)
{
    dict_free(st->dict);
    list_free(st->list);
    free(st);
}

void symbol_table_insert_op(symbol_table* st, char* symb, int prec, int assoc, OperatorFctType func)
{
    symbol* sb = malloc(sizeof(symbol));
    sb->value = symb;
    sb->precedence = prec;
    sb->associativity = assoc;
    sb->func.opf = func;

    dict_insert(st->dict, symb, sb);
    list_add(st->list, sb); // ?
}

void symbol_table_insert_func(symbol_table* st, char* symb, FunctionFctType func)
{
    symbol* sb = malloc(sizeof(symbol));
    sb->value = symb;
    sb->func.fct = func;

    dict_insert(st->dict, symb, sb);
    list_add(st->list, sb); // ?
}

void symbol_table_insert_var(symbol_table* st, char* symb, double val)
{
    symbol* sb = malloc(sizeof(symbol));
    sb->value = symb;
    sb->variable = val;

    dict_insert(st->dict, symb, sb);
    list_add(st->list, sb); // ?
}

int symbol_table_contains_op(symbol_table* st, char* symb)
{
    return dict_contains(st->dict, symb);
}

int symbol_table_contains_func(symbol_table* st, char* symb)
{
    return dict_contains(st->dict, symb);
}

int symbol_table_contains_var(symbol_table* st, char* symb)
{
    return dict_contains(st->dict, symb);
}

OperatorFctType symbol_table_get_op_func(symbol_table* st, char* symb)
{
    return ((symbol*)(dict_get(st->dict, symb)))->func.opf;
}

int symbol_table_get_op_prec(symbol_table* st, char* symb)
{
    return ((symbol*)(dict_get(st->dict, symb)))->precedence;
}

int symbol_table_get_op_assoc(symbol_table* st, char* symb)
{
    return ((symbol*)(dict_get(st->dict, symb)))->associativity;
}

FunctionFctType symbol_table_get_func(symbol_table* st, char* symb)
{
    return ((symbol*)(dict_get(st->dict, symb)))->func.fct;
}

int symbol_table_get_var(symbol_table* st, char* symb, double* result)
{
    if(!symbol_table_contains_var(st, symb))
    {
        return 0;
    }

    *result = ((symbol*)dict_get(st->dict, symb))->variable;
    return 1;
}
