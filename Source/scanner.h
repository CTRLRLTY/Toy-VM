#ifndef TOY_SCANNER_H
#define TOY_SCANNER_H

#include "token.h"

typedef struct Scanner {
    char* start;
    char* current;
    int line;
    TokenList tokens;
} Scanner;

void init_scanner(Scanner* scanner, char* source);
void free_scanner(Scanner* scanner);
void start_scanner(Scanner* scanner);

#endif