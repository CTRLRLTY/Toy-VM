#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

#include "scanner.h"


static size_t lexemelen(Scanner *scanner) {
    return scanner->current - scanner->start;
}

static char current(Scanner *scanner) {
    return *scanner->current;
}

static bool endofstream(Scanner *scanner) {
    return current(scanner) == '\0';
}

static void forward(Scanner *scanner) {
    scanner->current++;
}

static bool forward_if(Scanner *scanner, char next_char) {
    if (endofstream(scanner)) return false;
    if (current(scanner) != next_char) return false;
    forward(scanner);

    return true;
}

static char next(Scanner *scanner) {
    return endofstream(scanner) ? '\0' : *(scanner->current + 1);
}

static bool islexeme(Scanner *scanner, size_t length, const char *lexeme) {
    return memcmp(scanner->start, lexeme, length) == 0;
}

static void init_token_list(TokenList* tokens) {
    tokens->capacity = 0;
    tokens->size = 100;
    tokens->d = (Token*)malloc(sizeof(Token)*tokens->size);
}

static void add_token(TokenList* tokens, Token tkn) {
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

static void free_token_list(TokenList* tokens) {
    tokens->size = 100;
    tokens->capacity = 0;
    free(tokens->d);
}

void init_scanner(Scanner* scanner, char* source) {
    scanner->start = source;
    scanner->current = source;
    scanner->line = 1;
    init_token_list(&scanner->tokens);
}

static Token make_token(Scanner* scanner, TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner->start;
    token.length = (int)(scanner->current - scanner->start);
    token.line = scanner->line;
    return token;
}

static Token error_token(Scanner* scanner, char* errmsg) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = errmsg;
    token.line = scanner->line;
    return token;
}

static Token invalid_opcode_token(Scanner* scanner) {
    return error_token(scanner, "Unrecognized opcode");
}

static Token scan_number(Scanner* scanner) {
    #define FORWARD_TILL_ALPHA() while (isdigit(current(scanner))) forward(scanner)

    FORWARD_TILL_ALPHA();

    if (current(scanner) == '.' && isdigit(next(scanner))) {
        forward(scanner);

        FORWARD_TILL_ALPHA();
        return make_token(scanner, TOKEN_DECIMAL);
    }

    return make_token(scanner, TOKEN_INTEGER);

    #undef FORWARD_TILL_ALPHA
}

static Token scan_identifier(Scanner *scanner) {
    while (isalnum(current(scanner))) forward(scanner);

    switch (*scanner->start) {
        case 's': 
            return islexeme(scanner, 3, "set") ? make_token(scanner, TOKEN_SET) : invalid_opcode_token(scanner);
        case 'j': 
            return islexeme(scanner, 4, "jump") ? make_token(scanner, TOKEN_JMP) : invalid_opcode_token(scanner);
        case 'm':
            return islexeme(scanner, 3, "mul") ? make_token(scanner, TOKEN_MUL) : invalid_opcode_token(scanner);
    }
}

static Token scan_token(Scanner *scanner) {
SCAN:
    scanner->start = scanner->current;
    char c = current(scanner);
    forward(scanner);

    switch (c)
    {
        case ' ':
        case '\r':
        case '\t': goto SCAN;
        case '\n': scanner->line++; goto SCAN;

        case '1': case '2':
        case '3': case '4':
        case '5': case '6':
        case '7': case '8':
        case '9': case '0':
            return scan_number(scanner);
        default:
            return scan_identifier(scanner);
    }
}

void start_scanner(Scanner* scanner) {
    while (!endofstream(scanner)) {
        add_token(&scanner->tokens, scan_token(scanner));
    }
}