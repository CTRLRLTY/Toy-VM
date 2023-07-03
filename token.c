#include <stdlib.h>

#include "token.h"
#include "scanner.h"

void init_token_list(TokenList* tokens) {
    tokens->capacity = 0;
    tokens->size = 100;
    tokens->d = (Token*)malloc(sizeof(Token)*tokens->size);
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

void free_token_list(TokenList* tokens) {
    tokens->size = 100;
    tokens->capacity = 0;
    free(tokens->d);
}