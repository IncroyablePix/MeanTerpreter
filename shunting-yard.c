//
// Created by Benjam on 12/14/2021.
//

#include "shunting-yard.h"
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "list.h"

int shunting_yard_evaluate(tokenizer* t, symbol_table* st, double *solution)
{
    stack* sop = stack_create();
    stack* sval = stack_create();

    token* current_token = tokenizer_get_next_token(t);
    token* next_token = tokenizer_get_next_token(t);

    token* op2;

    while(token_get_type(current_token) != T_STOP)
    {
        /*token_print(current_token);
        printf("\n");*/
        switch(token_get_type(current_token))
        {
            case T_NUMBER:
            {
                stack_push(sval, token_get_value(current_token));
                break;
            }
            case T_LEFTPAR:
            {
                stack_push(sop, current_token);
                break;
            }
            case T_SYMBOL:
            {
                if (token_get_type(next_token) == T_LEFTPAR) // = function call!
                {
                    stack_push(sop, current_token);
                }
                else
                {
                    double *result = malloc(sizeof(double));
                    symbol_table_get_var(st, token_get_value(current_token), result);
                    stack_push(sval, result);
                }
                break;
            }
            case T_OPERATOR:
            {
                while (!stack_empty(sop) && (op2 = stack_top(sop)) && token_get_type(op2) == T_OPERATOR)
                {
                    int op1_prec = symbol_table_get_op_prec(st, token_get_value(current_token)),
                            op2_prec = symbol_table_get_op_prec(st, token_get_value(op2)),
                            op1_assoc = symbol_table_get_op_assoc(st, token_get_value(current_token));

                    if(symbol_table_contains_op(st, token_get_value(op2)) &&
                            ((op2_prec > op1_prec) || // op2 has strict higher precedence than op1
                            (op2_prec == op1_prec && op1_assoc == T_ASSOC_LEFT)))
                    {
                        token *op = stack_pop(sop);
                        double *v1 = stack_pop(sval),
                                *v2 = stack_pop(sval);

                        OperatorFctType op_func = symbol_table_get_op_func(st, token_get_value(op)); // fetching the function ptr
                        double *result = malloc(sizeof(double));
                        *result = op_func(*v2, *v1);

                        stack_push(sval, result);
                    }
                    else
                    {
                        break;
                    }
                }

                stack_push(sop, current_token);
                break;
            }
            case T_RIGHTPAR:
            {
                while (!stack_empty(sop) &&
                       (op2 = stack_top(sop)) &&
                       token_get_type(op2) != T_LEFTPAR)
                {
                    stack_pop(sop);

                    double *v1 = stack_pop(sval),
                            *v2 = stack_pop(sval);

                    OperatorFctType op_func = symbol_table_get_op_func(st, token_get_value(op2));

                    double *result = malloc(sizeof(double));
                    *result = op_func(*v2, *v1);

                    stack_push(sval, result);
                }

                stack_pop(sop); // removing left parenthesis

                //---

                if(!stack_empty(sop))
                {
                    op2 = stack_top(sop);
                    if (token_get_type(op2) == T_SYMBOL)
                    {
                        stack_pop(sop);
                        double *v = stack_pop(sval);
                        FunctionFctType f_func = symbol_table_get_func(st, token_get_value(op2));

                        double *result = malloc(sizeof(double));
                        *result = f_func(*v);
                        stack_push(sval, result);
                    }
                }

                break;
            }
            case T_EQUAL:
            case T_STOP:
                break;
        }

        current_token = next_token;
        next_token = tokenizer_get_next_token(t);
    }

    //---

    while(!stack_empty(sop))
    {
        token* t_op = stack_pop(sop);
        if(token_get_type(t_op) == T_OPERATOR)
        {

            double *v1 = stack_pop(sval),
                    *v2 = stack_pop(sval);

            OperatorFctType op_func = symbol_table_get_op_func(st, token_get_value(t_op));

            double *result = malloc(sizeof(double));
            *result = op_func(*v2, *v1);

            stack_push(sval, result);
        }
    }

    double* sol = stack_pop(sval);
    *solution = *sol;
    return 1;
}