#include "vm.h"

int main(void) {
    ti_vm vm;
    uint8_t code[] = {ASM_SET_R0_IMM, 1 ,ASM_ADD_R0_R0};

    ti_execute_byte(&vm, code, 3);

    return 0;
}