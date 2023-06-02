#include "vm.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


void ti_init_vm(ti_vm *vm) {
    vm->stacksz = TI_STACK_MIN;
    vm->stack = (int64_t*) malloc(TI_STACK_MIN);
    vm->stackptr = vm->stack;
}

static bool is_stack_full(ti_vm *vm) {
    return vm->stackptr - vm->stack == vm->stacksz/sizeof(vm->stack[0]);
}

static void push(ti_vm *vm, int64_t *value) {
    int64_t *ptr = vm->stackptr;
    vm->stackptr++;
    memcpy(ptr, value, sizeof(int64_t));

    if(is_stack_full(vm)) {
        vm->stacksz += TI_STACK_MIN;
        vm->stack = (int64_t*) realloc(vm->stack, vm->stacksz);
        if (vm->stack == NULL) exit(1);
    }
}

void ti_execute_byte(ti_vm *vm, uint8_t code[], size_t size) {
#define FORWARD(amount) i += amount
#define ADD_REG_REG(regnum1, regnum2) \
        vm->reg_int[regnum1] += vm->reg_int[regnum2]

#define PUSH_REG(regnum) push(vm, &vm->reg_int[regnum]); 

#define SET_REG_IMM(regnum) \
        FORWARD(1); \
        memcpy(&vm->reg_int[regnum], &code[i], 8); \
        FORWARD(7);


    for (int i = 0; i < size; ++i) {
        switch (code[i])
        {
            case ASM_PUSH_R0: PUSH_REG(0); break;
            case ASM_PUSH_R1: PUSH_REG(1); break;
            case ASM_PUSH_R2: PUSH_REG(2); break;
            case ASM_PUSH_R3: PUSH_REG(3); break;

            case ASM_SET_R0_IMM: SET_REG_IMM(0); break;
            case ASM_SET_R1_IMM: SET_REG_IMM(1); break;
            case ASM_SET_R2_IMM: SET_REG_IMM(2); break;
            case ASM_SET_R3_IMM: SET_REG_IMM(3); break;

            case ASM_ADD_R0_R0: ADD_REG_REG(0, 0); break;
            case ASM_ADD_R0_R1: ADD_REG_REG(0, 1); break;
            case ASM_ADD_R0_R2: ADD_REG_REG(0, 2); break;
            case ASM_ADD_R0_R3: ADD_REG_REG(0, 3); break;

            case ASM_ADD_R1_R0: ADD_REG_REG(1, 0); break;
            case ASM_ADD_R1_R1: ADD_REG_REG(1, 1); break;
            case ASM_ADD_R1_R2: ADD_REG_REG(1, 2); break;
            case ASM_ADD_R1_R3: ADD_REG_REG(1, 3); break;

            case ASM_ADD_R2_R0: ADD_REG_REG(2, 0); break;
            case ASM_ADD_R2_R1: ADD_REG_REG(2, 1); break;
            case ASM_ADD_R2_R2: ADD_REG_REG(2, 2); break;
            case ASM_ADD_R2_R3: ADD_REG_REG(2, 3); break;

            case ASM_ADD_R3_R0: ADD_REG_REG(3, 0); break;
            case ASM_ADD_R3_R1: ADD_REG_REG(3, 1); break;
            case ASM_ADD_R3_R2: ADD_REG_REG(3, 2); break;
            case ASM_ADD_R3_R3: ADD_REG_REG(3, 3); break;

            case ASM_PRINTF: {
                FORWARD(1);
                size_t str_sz = 0;

                while (((char)code[i]) != '\0')
                {
                    str_sz++;
                    FORWARD(1);
                }
                break;
            };
        }
    }


#undef PUSH_REG 
#undef SET_REG_IMM
#undef ADD_REG_REG
#undef FORWARD
}



void ti_read_constant(ti_vm *vm, uint8_t code[], size_t size) {
#define FORWARD(amount) i += amount
    for (size_t i = 0; i < size; ++i) {
        switch (code[i]) {
            case ASM_CONSTANT: {
                FORWARD(1);
                size_t sz = code[i];
                FORWARD(1);
                char constant[sz];
                memcpy(&constant, &code[i], sz);
                FORWARD(sz);
                break;
            }
        }
    }
#undef FORWARD
}