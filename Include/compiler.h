#ifndef TI_COMPILER
#define TI_COMPILER

#include "token.h"
#include "byte.h"

typedef struct Compiler {
    size_t current;
    bool had_error;
    bool panic_mode;
    TokenList* tokens;
    ByteList bytes;
} Compiler;

void init_compiler(Compiler* compiler, TokenList* tokens);
void free_compiler(Compiler* compiler);
void compile(Compiler* compiler);

#endif
