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

typedef void (*mbhandlerFn)(opsize *left, opsize *right, uint8_t* code);

static void handle_add(opsize *left, opsize *right, uint8_t* code) {
    *left += *right;
}

static void handle_modbyte(ti_vm *vm, uint8_t *code, mbhandlerFn handler) {
    uint8_t mod = *code >> 6;
    uint8_t reg = *code >> 3 & 0b111; 
    uint8_t rm = *code & 0b111; 

    opsize *left = &vm->reg_int[reg];

    switch (mod)
    {
        case 0b11:
            opsize *right = &vm->reg_int[rm];
            code++;
            handler(left, right, code);
    }
}

void ti_execute_byte(ti_vm *vm, uint8_t code[], size_t size) {
#define FORWARD(amount) code += amount
#define PUSH_REG(regnum) push(vm, &vm->reg_int[regnum]); 

#define SET_REG_IMM(regnum) { \
        FORWARD(1); \
        memcpy(&vm->reg_int[regnum], code, 8); \
        FORWARD(8); }
    
    uint8_t *base = code;

    while (code - base < size) {
        switch (*code) {
            case ASM_PUSH_R0: PUSH_REG(0); break;
            case ASM_PUSH_R1: PUSH_REG(1); break;
            case ASM_PUSH_R2: PUSH_REG(2); break;
            case ASM_PUSH_R3: PUSH_REG(3); break;

            case ASM_SET_R0_IMM: SET_REG_IMM(0); break;
            case ASM_SET_R1_IMM: SET_REG_IMM(1); break;
            case ASM_SET_R2_IMM: SET_REG_IMM(2); break;
            case ASM_SET_R3_IMM: SET_REG_IMM(3); break;

            // case ASM_ADD_R0_R0: ADD_REG_REG(0, 0); break;
            case ASM_ADD: {
                FORWARD(1);
                handle_modbyte(vm, code, handle_add);
                break;
            } 
        }
    }


#undef PUSH_REG 
#undef SET_REG_IMM
#undef ADD_REG_REG
#undef FORWARD
}