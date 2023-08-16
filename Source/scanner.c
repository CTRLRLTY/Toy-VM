#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>

#include "scanner.h"


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

static void forwardby(Scanner *scanner, size_t amount) {
        scanner->current += amount;
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

static char at(Scanner *scanner, size_t index) {
        return endofstream(scanner) ? '\0' : *(scanner->current + index);
}

static bool islexeme(Scanner *scanner, size_t length, const char *lexeme) {
        return memcmp(scanner->start, lexeme, length) == 0;
}

void init_scanner(Scanner* scanner, char* source) {
        scanner->start = source;
        scanner->current = source;
        scanner->line = 1;
        init_token_list(&scanner->tokens);
}

void free_scanner(Scanner* scanner) {
        scanner->start = NULL;
        scanner->current = NULL;
        scanner->line = 0;
        free_token_list(&scanner->tokens);
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

static Token scan_regint(Scanner *scanner) {
        forward(scanner);
        char c = current(scanner);
        forward(scanner);

        short idx = 0;
        char nc = current(scanner);
        if (nc > '0' && nc <= '9') {
                forward(scanner);
                idx = (short) (atoi(&c) + atoi(&nc));
        }

        switch (idx)
        {
                case 1:
                        return make_token(scanner, TOKEN_R1);
                case 2:
                        return make_token(scanner, TOKEN_R2);
                case 3:
                        return make_token(scanner, TOKEN_R3);
                case 4:
                        return make_token(scanner, TOKEN_R4);
                case 5:
                        return make_token(scanner, TOKEN_R5);
                case 6:
                        return make_token(scanner, TOKEN_R6);
                case 7:
                        return make_token(scanner, TOKEN_R7);
                case 8:
                        return make_token(scanner, TOKEN_R8);
                case 9:
                        return make_token(scanner, TOKEN_R9);
                case 10:
                        return make_token(scanner, TOKEN_R10);
                case 11:
                        return make_token(scanner, TOKEN_R11);
                case 12:
                        return make_token(scanner, TOKEN_R12);
                case 13:
                        return make_token(scanner, TOKEN_R13);
                case 14:
                        return make_token(scanner, TOKEN_R14);
                case 15:
                        return make_token(scanner, TOKEN_R15);
                case 16:
                        return make_token(scanner, TOKEN_R16);
        }
}

static Token scan_identifier(Scanner *scanner) {
        switch (current(scanner)) {
                case 'a':
                        return islexeme(scanner, 3, "add") ? (forwardby(scanner, 3), make_token(scanner, TOKEN_ADD)) : invalid_opcode_token(scanner);
                case 's': 
                        switch (at(scanner, 1)) {
                                case 'e': 
                                        return islexeme(scanner, 3, "set") ? (forwardby(scanner, 3), make_token(scanner, TOKEN_SET)) : invalid_opcode_token(scanner);
                                case 'u': 
                                        return islexeme(scanner, 3, "sub") ? (forwardby(scanner, 3), make_token(scanner, TOKEN_SUB)) : invalid_opcode_token(scanner);
                        }
                case 'j': 
                        return islexeme(scanner, 3, "jmp") ? (forwardby(scanner, 3), make_token(scanner, TOKEN_JMP)) : invalid_opcode_token(scanner);
                case 'm':
                        return islexeme(scanner, 3, "mul") ? (forwardby(scanner, 3), make_token(scanner, TOKEN_MUL)) : invalid_opcode_token(scanner);
                case 'p':
                        return islexeme(scanner, 4, "push") ? (forwardby(scanner, 4), make_token(scanner, TOKEN_PUSH)) : invalid_opcode_token(scanner);
                case 'r': 
                        return scan_regint(scanner);
        }
}

static Token scan_token(Scanner *scanner) {
SCAN:
        scanner->start = scanner->current;
        char c = current(scanner);

        switch (c)
        {
                case ',': 
                        forward(scanner);
                        return make_token(scanner, TOKEN_COMMA);

                case ' ':
                case '\r':
                case '\t': forward(scanner); goto SCAN;
                case '\n': forward(scanner); scanner->line++; goto SCAN;


                case '1': case '2':
                case '3': case '4':
                case '5': case '6':
                case '7': case '8':
                case '9': case '0':
                           return scan_number(scanner);

                case '\0':
                           return make_token(scanner, TOKEN_EOF);
                default:
                           return scan_identifier(scanner);
        }
}

void start_scanner(Scanner* scanner) {
        while (!endofstream(scanner)) {
                add_token(&scanner->tokens, scan_token(scanner));
        }
}
