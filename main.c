#include "vm.h"

#include <string.h>

int main(void) {
    ti_vm vm;
    ti_init_vm(&vm);

    // uint8_t code[] = {
    //     ASM_SET_R0_IMM, 0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f,
    //     ASM_PUSH_R0,
    //     ASM_SET_R0_IMM, 0x72, 0x6c, 0x64, 0x0, 0x0, 0x0, 0x0, 0x0,
    //     ASM_PUSH_R0
    // };

    // uint8_t code[] = {
    //     ASM_MOV, 0b01000000, 1,
    //     ASM_PUSH, 0b10000000
    // };

    uint8_t code[] = {
        ASM_MOV, 0b01000000, 1,
        ASM_SUB, 0b01000000, 1
    };

    // uint8_t code[] = {
    //     ASM_SET_R0_IMM, 1, 0, 0, 0, 0, 0, 0, 0,
    //     ASM_ADD, 0b11000000
    // };

    // uint8_t code[] = {
    //     ASM_PRINT, 12, 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd','\n'
    // };

    ti_execute_byte(&vm, code, sizeof(code)/sizeof(code[0]));

    return 0;
}