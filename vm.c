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

typedef void (*mbhandlerFn)(ti_vm *vm, opsize* args);

static void handle_add(ti_vm *vm, opsize *args) {
    int64_t *left = (int64_t*)args[0];
    int64_t *right = (int64_t*)args[1];
    *left += *right;
}

static void handle_sub(ti_vm *vm, opsize *args) {
    int64_t *left = (int64_t*)args[0];
    int64_t *right = (int64_t*)args[1];
    *left -= *right;
}

static void handle_push(ti_vm *vm, opsize *args) {
    push(vm, (int64_t*)args[0]);
}

static void handle_mov(ti_vm *vm, opsize *args) {
    int64_t *left = (int64_t*)args[0];
    int64_t *right = (int64_t*)args[1];
    memcpy(left, right, sizeof(int64_t));
}

static void handle_modbyte(ti_vm *vm, uint8_t **codeptr, mbhandlerFn handler) {
    uint8_t mod = **codeptr >> 6;
    uint8_t reg = **codeptr >> 3 & 0b111; 
    uint8_t rm = **codeptr & 0b111; 
    (*codeptr)++;

    opsize *left = &vm->gpr[reg];

    switch (mod)
    {
        case 0b11: {
            opsize *right = &vm->gpr[rm];
            opsize *args[] = {left, right};
            handler(vm, (opsize*)args);
            break;
        }
        case 0b10: {
            opsize *args[] = {left};
            handler(vm, (opsize*)args);
            break;
        }
        case 0b01: {
            opsize buf = 0;
            memcpy(&buf, *codeptr, rm+1);
            *codeptr += rm+1;
            opsize *args[] = {left, &buf};
            handler(vm, (opsize*)args);
            break;
        }
    }
}

void ti_execute_byte(ti_vm *vm, uint8_t code[], size_t size) {
#define FORWARD(amount) code += amount

    uint8_t *base = code;

    while (code - base < size) {
        switch (*code) {
            case ASM_PRINT: {
                FORWARD(1);
                uint8_t sz = *code;
                FORWARD(1);
                uint8_t buf[sz+1];
                buf[sz] = '\0';
                memcpy(buf, code, sz);
                FORWARD(sz);
                printf(buf);
                break;
            }
            case ASM_MOV: {
                FORWARD(1);
                handle_modbyte(vm, &code, handle_mov);
                break;
            };
            case ASM_PUSH: {
                FORWARD(1);
                handle_modbyte(vm, &code, handle_push);
                break;
            }
            case ASM_ADD: {
                FORWARD(1);
                handle_modbyte(vm, &code, handle_add);
                break;
            } 
            case ASM_SUB: {
                FORWARD(1);
                handle_modbyte(vm, &code, handle_sub);
                break;
            }
        }
    }


#undef FORWARD
}