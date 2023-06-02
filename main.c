#include "vm.h"

#include <string.h>

int main(void) {
    ti_vm vm;
    ti_init_vm(&vm);

    uint8_t code[] = {
        ASM_SET_R0_IMM, 0x68, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x77, 0x6f,
        ASM_PUSH_R0,
        ASM_SET_R0_IMM, 0x72, 0x6c, 0x64, 0x0, 0x0, 0x0, 0x0, 0x0,
        ASM_PUSH_R0
    };

    ti_execute_byte(&vm, code, sizeof(code)/sizeof(code[0]));

    return 0;
}