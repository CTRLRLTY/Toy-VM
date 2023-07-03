#ifndef TOY_SCANNER_H
#define TOY_SCANNER_H

typedef enum TOKEN {
    TOKEN_SET,
    TOKEN_JMP,
    TOKEN_INTEGER,
    TOKEN_DECIMAL,
    TOKEN_MUL,
    TOKEN_ERROR,
} TokenType;

typedef struct Token {
    TokenType type;
    const char* start;
    int length;
    int line;

} Token;

typedef struct TokenList {
    size_t size;
    size_t capacity;
    Token* d;
} TokenList;

typedef struct Scanner {
    char* start;
    char* current;
    int line;
    TokenList tokens;
} Scanner;

void init_scanner(Scanner* scanner, char* source);
void start_scanner(Scanner* scanner);

#endif