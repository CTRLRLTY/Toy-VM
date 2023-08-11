#ifndef TI_TOKEN
#define TI_TOKEN

#include <stdbool.h>

typedef enum TOKEN {
    TOKEN_SET,
    TOKEN_JMP,
    TOKEN_INTEGER,
    TOKEN_DECIMAL,
    TOKEN_MUL,
    TOKEN_ERROR,
    TOKEN_PUSH,
    TOKEN_COMMA,
    TOKEN_R1,
    TOKEN_R2,
    TOKEN_R3,
    TOKEN_R4,
    TOKEN_R5,
    TOKEN_R6,
    TOKEN_R7,
    TOKEN_R8,
    TOKEN_R9,
    TOKEN_R10,
    TOKEN_R11,
    TOKEN_R12,
    TOKEN_R13,
    TOKEN_R14,
    TOKEN_R15,
    TOKEN_R16,
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

bool is_regint_token(Token* token, TokenType* reginttype);
bool is_token_type(Token* token, TokenType type);

void init_token_list(TokenList* tokens);
void free_token_list(TokenList* tokens);
void add_token(TokenList* tokens, Token tkn);
Token* get_token(TokenList* tokens, size_t idx);
#endif