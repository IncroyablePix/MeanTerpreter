//
// Created by Benjam on 12/14/2021.
//

#include "tokenizer.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct token_t
{
    token_type type;
    int pos;
    void *value; // Value of the token || name of the operator
};

struct tokenizer_t
{
    const char* str;
    int pos;
    token_type last_type;
};

static void terminate(char* m)
{
    printf("%s\n", m);
    exit(EXIT_FAILURE);
}

static int is_number(const char* str, token_type last_type)
{
    if(!str || str[0] == '\0')
    {
        return 0;
    }

    if(isdigit(str[0]))
    {
        return 1;
    }

    if(str[1] == '\0')
    {
        return 0;
    }

    if(str[0] == '.' && isdigit(str[1]))
    {
        return 1;
    }

    if((last_type == T_LEFTPAR || last_type == T_OPERATOR || last_type == T_EQUAL) &&
        str[0] == '-' && isdigit(str[1]))
    {
        return 1;
    }

    if(str[2] == '\0')
    {
        return 0;
    }

    if((last_type == T_LEFTPAR || last_type == T_OPERATOR || last_type == T_EQUAL) &&
        str[0] == '-' && str[1] == '.' && isdigit(str[2]))
    {
        return 1;
    }

    return 0;
}

static char* create_string(int len)
{
    char *str = malloc((len + 1) * sizeof(char));
    if(!str)
    {
        terminate("Error while allocating memory for tokenizer string");
    }

    return str;
}

tokenizer* tokenizer_create(const char* expression)
{
    tokenizer* t = malloc(sizeof(tokenizer));
    if(!t)
    {
        terminate("Error while allocating memory for tokenizer");
    }

    //printf("Tokenizer expression: %s", expression);

    t->str = expression;
    t->pos = 0;
    t->last_type = T_LEFTPAR;

    return t;
}

void tokenizer_free(tokenizer* t)
{
    free(t);
}

token* tokenizer_get_next_token(tokenizer* t)
{
    int pos = t->pos;
    const char* str = t->str;

    while(isspace(str[pos])) // space ignore
    {
        pos++;
    }

    token* new_token = malloc(sizeof(token));
    if(!new_token)
    {
        terminate("Error while allocating new_token memory");
    }

    //printf("\np:%d\n", pos);
    new_token->pos = pos;

    //---
    char c, *cptr;
    while(str[pos] != '\0' && str[pos] != '\n')
    {
        c = str[pos];

        // RIGHT PARENTHESIS
        if(c == ')')
        {
            //printf("rp-");
            new_token->type = T_RIGHTPAR;
            new_token->value = NULL;
            t->pos += pos + 1;
            t->last_type = T_RIGHTPAR;
            return new_token;
        }

        // LEFT PARENTHESIS
        if(c == '(')
        {
            //printf("lp-");
            new_token->type = T_LEFTPAR;
            new_token->value = NULL;
            t->pos = pos + 1;
            t->last_type = T_LEFTPAR;
            return new_token;
        }

        // EQUAL
        if (c == '=')
        {
            //printf("eq-");
            new_token->type = T_EQUAL;
            new_token->value = NULL;
            t->pos = pos + 1;
            t->last_type = T_EQUAL;
            return new_token;
        }

        // NUMBER
        if(is_number(str + pos, t->last_type))
        {
            double *value_ptr = malloc(sizeof(double));
            if(!value_ptr)
            {
                terminate("Error while allocating memory for value");
            }

            //printf("nb-");

            *value_ptr = strtod(str + pos, &cptr); // str to double
            pos += (int) (cptr - (str + pos)); // new position = cursor that strtod has read to minus what we already had

            new_token->value = value_ptr;
            new_token->type = T_NUMBER;
            t->pos = pos;
            t->last_type = T_NUMBER;

            return new_token;
        }

        if(isalpha(c))
        {
            int l = pos + 1;
            while(str[l] != '\0' && (isalpha(str[l]) || isdigit(str[l])))
            {
                l ++;
            }

            l -= pos;
            cptr = create_string(l);
            strncpy(cptr, str + pos, l);

            //printf("txt-");

            cptr[l] = '\0';
            new_token->value = cptr;
            new_token->type = T_SYMBOL;
            t->pos = pos + l;
            t->last_type = T_SYMBOL;

            return new_token;
        }

        // Operator -> Not digit, dot, comma or letter
        cptr = create_string(1);
        strncpy(cptr, str + pos, 1);
        cptr[1] = '\0';
        //printf("op-");

        new_token->value = cptr;
        new_token->type = T_OPERATOR;
        t->pos = pos + 1;
        t->last_type = T_OPERATOR;

        return new_token;
    }

    //printf("nop-");
    new_token->type = T_STOP;
    new_token->value = NULL;
    t->pos = pos;
    t->last_type = T_STOP;
    return new_token;
}

void tokenizer_reset(tokenizer* tokenizer)
{
    tokenizer->pos = 0;
    tokenizer->last_type = T_LEFTPAR;
}

int token_get_position(token *t)
{
    return t->pos;
}

token_type token_get_type(token* t)
{
    return t->type;
}

void* token_get_value(token* token)
{
    return token->value;
}

void token_free(token* token, int free_value)
{
    if(free_value && (token->type == T_SYMBOL || token->type == T_NUMBER || token->type == T_OPERATOR))
    {
        free(token->value);
    }

    free(token);
}

void token_print(token* token)
{
    if(token)
    {
        switch (token->type)
        {
            case T_SYMBOL:
                printf("<SYMBOL,%d,%s>", token->pos, (char *)token->value);
                break;
            case T_OPERATOR:
                printf("<OPERATOR,%d,%s>", token->pos, (char *)token->value);
                break;
            case T_EQUAL:
                printf("<EQUAL,%d,NULL>", token->pos);
                break;
            case T_NUMBER:
                printf("<NUMBER,%d,%f>", token->pos, *((double *)token->value));
                break;
            case T_LEFTPAR:
                printf("<LEFTPAR,%d,NULL>", token->pos);
                break;
            case T_RIGHTPAR:
                printf("<RIGHTPAR,%d,NULL>", token->pos);
                break;
            case T_STOP:
                printf("<STOP,%d,NULL>", token->pos);
                break;
        }
    }
}