#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "compiler.h"
#include "asm.h"

static Byte merge_byte(Byte highbit, Byte lowbit) {
        return (highbit << 0xf | lowbit);
}

Byte regint_byte(TokenType type) {
        switch (type) {
                case TOKEN_R1: return BYTE_R1;
                case TOKEN_R2: return BYTE_R2;
                case TOKEN_R3: return BYTE_R3;
                case TOKEN_R4: return BYTE_R4;
                case TOKEN_R5: return BYTE_R5;
                case TOKEN_R6: return BYTE_R6;
                case TOKEN_R7: return BYTE_R7;
                case TOKEN_R8: return BYTE_R8;
                case TOKEN_R9: return BYTE_R9;
                case TOKEN_R10: return BYTE_R10;
                case TOKEN_R11: return BYTE_R11;
                case TOKEN_R12: return BYTE_R12;
                case TOKEN_R13: return BYTE_R13;
                case TOKEN_R14: return BYTE_R14;
                case TOKEN_R15: return BYTE_R15;
                case TOKEN_R16: return BYTE_R16;
        }
}

void init_compiler(Compiler* compiler, TokenList* tokens) {
        compiler->current = 0;
        compiler->had_error = 0;
        compiler->panic_mode = 0;
        compiler->tokens = tokens;
        init_byte_list(&compiler->bytes);
}

void free_compiler(Compiler* compiler) {
        compiler->current = 0;
        compiler->had_error = 0;
        compiler->panic_mode = 0;
        free_byte_list(&compiler->bytes);
}

void compile(Compiler* compiler) {
        for (size_t i = 0; i < compiler->tokens->size; ++i) {
                Token* tkn = get_token(compiler->tokens, i);

                if (tkn == NULL) 
                        return;

                switch (tkn->type) {
                        case TOKEN_SET: 
                                {
                                        Token* ntkn = ntkn = get_token(compiler->tokens, ++i);
                                        Token *nntkn = get_token(compiler->tokens, ++i);
                                        Token *nnntkn = get_token(compiler->tokens, ++i);

                                        Byte regint_src_byte;

                                        if (is_regint_token(ntkn, &regint_src_byte)) {
                                                Byte regint_dst_byte;

                                                if (is_token_type(nntkn, TOKEN_COMMA)) {
                                                        if (is_token_type(nnntkn, TOKEN_INTEGER)) {
                                                                add_byte(&compiler->bytes, ASM_SET_IMM2REG);
                                                                add_byte(&compiler->bytes, merge_byte(regint_src_byte, 8));
                                                                add_byte64(&compiler->bytes, atol(nnntkn->start));
                                                        }
                                                        else if (is_regint_token(nnntkn, &regint_dst_byte)) {
                                                                add_byte(&compiler->bytes, ASM_SET_REG2REG);
                                                                add_byte(&compiler->bytes, merge_byte(regint_dst_byte, regint_src_byte));
                                                        }
                                                }
                                        }

                                        break;
                                }
                        case TOKEN_JMP: 
                                {
                                        Token* ntkn = ntkn = get_token(compiler->tokens, ++i);
                                        Token *nntkn = get_token(compiler->tokens, ++i);
                                        Token *nnntkn = get_token(compiler->tokens, ++i);

                                        if (is_regint_token(ntkn, NULL)) {
                                                if (is_token_type(nntkn, TOKEN_COMMA)) {
                                                        if (is_token_type(nnntkn, TOKEN_INTEGER)) {
                                                                add_byte(&compiler->bytes, ASM_JMP);
                                                                add_byte(&compiler->bytes, atoi(nnntkn->start));
                                                        }
                                                }
                                        }
                                        break;
                                }
                        case TOKEN_EOF:
                                return;

                }
        }
}
