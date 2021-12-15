//
// Created by Benjam on 12/14/2021.
//
#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include "tokenizer.h"
#include "symboltable.h"
#include "shunting-yard.h"

typedef intptr_t ssize_t;

ssize_t getline(char **lineptr, size_t *n, FILE *stream)
{
    size_t pos;
    int c;

    if (lineptr == NULL || stream == NULL || n == NULL)
    {
        errno = EINVAL;
        return -1;
    }

    c = getc(stream);
    if (c == EOF)
    {
        return -1;
    }

    if (*lineptr == NULL)
    {
        *lineptr = malloc(128);
        if (*lineptr == NULL)
        {
            return -1;
        }
        *n = 128;
    }

    pos = 0;
    while(c != EOF)
    {
        if (pos + 1 >= *n)
        {
            size_t new_size = *n + (*n >> 2);
            if (new_size < 128)
            {
                new_size = 128;
            }
            char *new_ptr = realloc(*lineptr, new_size);
            if (new_ptr == NULL)
            {
                return -1;
            }
            *n = new_size;
            *lineptr = new_ptr;
        }

        ((unsigned char *)(*lineptr))[pos ++] = c;
        if (c == '\n')
        {
            break;
        }
        c = getc(stream);
    }

    (*lineptr)[pos] = '\0';
    return pos;
}


static void print_waiting()
{
    printf(">>> ");
}

//--- Operators

double add(double a, double b)
{
    return a + b;
}

double subtract(double a, double b)
{
    return a - b;
}

double multiply(double a, double b)
{
    return a * b;
}

double divide(double a, double b)
{
    return a / b;
}

double power(double a, double b)
{
    return pow(a, b);
}

//--- Functions
double deg_to_rad(double degrees)
{
    return degrees * (M_PI / 180.0);
}

double deg_sin(double degrees)
{
    return sin(deg_to_rad(degrees));
}

double deg_cos(double degrees)
{
    return cos(deg_to_rad(degrees));
}

double deg_tan(double degrees)
{
    return tan(deg_to_rad(degrees));
}

symbol_table* calc_init_symbol_table()
{
    symbol_table* st = NULL;

    st = symbol_table_create();

    //--- Operators
    symbol_table_insert_op(st, "+", 1, T_ASSOC_LEFT, &add);
    symbol_table_insert_op(st, "-", 1, T_ASSOC_LEFT, &subtract);
    symbol_table_insert_op(st, "*", 2, T_ASSOC_LEFT, &multiply);
    symbol_table_insert_op(st, "/", 2, T_ASSOC_LEFT, &divide);
    symbol_table_insert_op(st, "^", 3, T_ASSOC_RIGHT, &power);

    //--- Functions
    symbol_table_insert_func(st, "sin", &deg_sin);
    symbol_table_insert_func(st, "cos", &deg_cos);
    symbol_table_insert_func(st, "tan", &deg_tan);

    return st;
}

void print_help()
{
    printf("Two types of instructions:\n1) Expr => evaluate the expression.\n2) Var = Expr => evaluate Expr and bind its value to Var.\nTo exit, enter an empty instruction.");
    print_waiting();
}

void calcul_repl()
{
    char *line = NULL; // The input line
    size_t len = 0; // The length of the line
    size_t line_size;

    symbol_table* st = calc_init_symbol_table(); // The symbol table

    printf("Calculator 0.0.1\n");
    printf("Type \"help\" for more information\n");
    print_waiting();

    while(getline(&line, &len, stdin) > 1)
    {
        tokenizer* tknizer = tokenizer_create(line);
        token* first_token = tokenizer_get_next_token(tknizer);

        if(token_get_type(first_token) == T_STOP)
        {
            token_free(first_token, 1);
            tokenizer_free(tknizer);
            break;
        }

        token* second_token = tokenizer_get_next_token(tknizer);

        if(token_get_type(first_token) == T_SYMBOL &&
                token_get_type(second_token) == T_STOP)
        {
            char* name = (char*) token_get_value(first_token);
            if(!strcmp(name, "help"))
            {
                print_help();
                token_free(first_token, 1);
                token_free(second_token, 1);
                tokenizer_free(tknizer);
                continue;
            }
        }

        if(token_get_type(first_token) == T_SYMBOL && // Assignment
                token_get_type(second_token) == T_EQUAL)
        {
            double *evaluated_result = malloc(sizeof(double));
            int return_code = shunting_yard_evaluate(tknizer, st, evaluated_result);
            if(return_code)
            {
                symbol_table_insert_var(st, (char*) token_get_value(first_token), *evaluated_result);
                printf("%f\n", *evaluated_result);
            }
            free(evaluated_result);
        }
        else
        {
            tokenizer_reset(tknizer);
            double *evaluated_result = malloc(sizeof(double));
            int return_code = shunting_yard_evaluate(tknizer, st, evaluated_result);
            if(return_code)
            {
                printf("%f\n", *evaluated_result);
            }

            free(evaluated_result);
        }

        token_free(first_token, 1);
        token_free(second_token, 1);
        tokenizer_free(tknizer);

        print_waiting();
        //free(line);
    }

    symbol_table_free(st);
}