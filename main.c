#include "vm.h"

int main(void) {
    ti_vm vm;
    uint8_t code[] = {ASM_SET_R0_IMM, 2, 0, 0, 0, 0, 0, 0, 0};

    ti_execute_byte(&vm, code, 9);

    return 0;
}