#include "vm.h"

int main(void) {
    ti_vm vm;
    ti_init_vm(&vm);

    uint8_t code[] = {
        ASM_SET_R0_IMM, 2, 0, 0, 0, 0, 0, 0, 0,
        ASM_PUSH_R0,
        ASM_PUSH_R0
    };

    ti_execute_byte(&vm, code, sizeof(code)/sizeof(code[0]));

    return 0;
}