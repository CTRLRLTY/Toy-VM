#include <stdio.h>
#include <stdlib.h>

#include "assembler.h"
#include "compiler.h"
#include "vm.h"


static char* read_file(const char* path) {
    FILE* file = fopen(path, "rb");

    if (file == NULL) goto CANT_OPEN_FILE;

    fseek(file, 0L, SEEK_END);
    size_t filesz = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(filesz + 1);
    size_t bytes_read = fread(buffer, sizeof(char), filesz, file);

    if (bytes_read < filesz) goto CANT_OPEN_FILE;

    buffer[bytes_read] = '\0';
    fclose(file);

    return buffer;

CANT_OPEN_FILE:
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(74);
}

static void run_file(const char* path) {
    char* source = read_file(path);
    Scanner scanner;
    init_scanner(&scanner, source);
    start_scanner(&scanner);

    Compiler compiler;
    init_compiler(&compiler, &scanner.tokens);
    compile(&compiler);

    ti_vm vm;
    ti_init_vm(&vm);
    ti_execute_byte(&vm, compiler.bytes.d, compiler.bytes.capacity);
}


int main(int argc, char** argv) {

    switch (argc)
    {
        case 2:
            run_file(argv[1]);
            break;
    }

    return 0;
}
