#include "vm.h"

#include <string.h>

int main(void) {
    ti_vm vm;
    ti_init_vm(&vm);

    uint8_t code[] = {
        ASM_SET_IMM2REG,  0b00000001, 5,
        ASM_ADD_REG2REG,  0b00000000,
        ASM_CMP,  0b00000000,
        ASM_JMP_LT, 1, 12,
        ASM_PUSH_REG,  0b00000000,
        ASM_SUB_REG2REG, 0b00000000, 
    };
 
    vm.codebase = code;
    vm.codeptr = vm.codebase;
    vm.codesz = sizeof(code)/sizeof(code[0]);
    ti_execute_byte(&vm);

    return 0;
}