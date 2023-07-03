#ifndef TI_TOKEN
#define TI_TOKEN

typedef enum TOKEN {
    TOKEN_SET,
    TOKEN_JMP,
    TOKEN_INTEGER,
    TOKEN_DECIMAL,
    TOKEN_MUL,
    TOKEN_ERROR,
    TOKEN_PUSH,
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


void init_token_list(TokenList* tokens);
void free_token_list(TokenList* tokens);
void add_token(TokenList* tokens, Token tkn);
#endif