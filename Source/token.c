#include <stdlib.h>
#include <stdio.h>

#include "scanner.h"


bool is_token_type(Token* token, TokenType type) {
    return token->type == type;
}

bool is_regint_token(Token* tkn, TokenType* reginttype) {
    bool ret = false;
    TokenType type;

    switch (tkn->type)
    {
        case TOKEN_R1: ret = true; type = TOKEN_R1; break;
        case TOKEN_R2: ret = true; type = TOKEN_R2; break;
        case TOKEN_R3: ret = true; type = TOKEN_R3; break;
        case TOKEN_R4: ret = true; type = TOKEN_R4; break;
        case TOKEN_R5: ret = true; type = TOKEN_R5; break;
        case TOKEN_R6: ret = true; type = TOKEN_R6; break;
        case TOKEN_R7: ret = true; type = TOKEN_R7; break;
        case TOKEN_R8: ret = true; type = TOKEN_R8; break;
        case TOKEN_R9: ret = true; type = TOKEN_R9; break;
        case TOKEN_R10: ret = true; type = TOKEN_R10; break;
        case TOKEN_R11: ret = true; type = TOKEN_R11; break;
        case TOKEN_R12: ret = true; type = TOKEN_R12; break;
        case TOKEN_R13: ret = true; type = TOKEN_R13; break;
        case TOKEN_R14: ret = true; type = TOKEN_R14; break;
        case TOKEN_R15: ret = true; type = TOKEN_R15; break;
        case TOKEN_R16: ret = true; type = TOKEN_R16; break;
    }

    if(reginttype != NULL)
        *reginttype = type;

    return ret;
}

void init_token_list(TokenList* tokens) {
    tokens->capacity = 0;
    tokens->size = 100;
    tokens->d = (Token*)malloc(sizeof(Token)*tokens->size);
}

void free_token_list(TokenList* tokens) {
    tokens->size = 100;
    tokens->capacity = 0;
    free(tokens->d);
}

void add_token(TokenList* tokens, Token tkn) {
    size_t capacity = tokens->capacity++;

    if (capacity > tokens->size) {
        tokens->size += 100;
        tokens->d = (Token*)realloc(tokens->d, tokens->size);

        if (tokens->d == NULL) {
            perror("Can't add token");
            exit(1);
        }
    }

    tokens->d[capacity] = tkn;
}

Token* get_token(TokenList* tokens, size_t idx) {
    if (idx < tokens->capacity) 
        return &tokens->d[idx];
    else
        return NULL;
}

