#include "vm.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>


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

typedef struct PasrseOps {
    ti_vm *vm;
    uint8_t immsize;
    opsize *regsrc;
    opsize *regdst;
} ParseOps;

typedef void (*parsefn)(ParseOps *ops);

static void regselect (ParseOps *ops) {
    uint8_t index = *ops->vm->codeptr++;
    ops->regdst = &ops->vm->gpr[index];
}

static void reg2reg(ParseOps *ops) {
    uint8_t byte = *ops->vm->codeptr;
    uint8_t hnib = byte >> 4 & 0b1111;
    uint8_t lnib = byte & 0b1111; 
    ops->vm->codeptr++;
    ops->regdst = &ops->vm->gpr[hnib];
    ops->regsrc = &ops->vm->gpr[lnib];
}

static void imm2reg(ParseOps *ops) {
    uint8_t byte = *ops->vm->codeptr;
    uint8_t lnib = byte & 0b1111; 
    uint8_t hnib = byte >> 4 & 0b1111;
    ops->vm->codeptr++;
    ops->regdst = &ops->vm->gpr[hnib];
    ops->immsize = lnib;
}

static void compare(ParseOps *ops) {
    memcpy(&ops->vm->cmpbuf1, ops->regdst, sizeof(opsize));
    memcpy(&ops->vm->cmpbuf2, ops->regsrc, sizeof(opsize));
}

static void jmp(ParseOps *ops) {
    uint8_t bytesz = *ops->vm->codeptr++; //todo: read 4byte addr instead of 1byte
    opsize index = 0;
    memcpy(&index, ops->vm->codeptr, bytesz);
    ops->vm->codeptr = &ops->vm->codebase[index];
}

static void nojmp(ParseOps *ops) {
    uint8_t bytesz = *ops->vm->codeptr++;
    ops->vm->codeptr += bytesz;
}

static void jmp_eq(ParseOps *ops) {
    if (ops->vm->cmpbuf1 == ops->vm->cmpbuf2)
        jmp(ops);
    else
        nojmp(ops);
}

static void jmp_ge(ParseOps *ops) {
    if (ops->vm->cmpbuf1 >= ops->vm->cmpbuf2)
        jmp(ops);
    else
        nojmp(ops);
}

static void jmp_le(ParseOps *ops) {
    if (ops->vm->cmpbuf1 <= ops->vm->cmpbuf2)
        jmp(ops);
    else
        nojmp(ops);
}

static void jmp_gt(ParseOps *ops) {
    if (ops->vm->cmpbuf1 > ops->vm->cmpbuf2)
        jmp(ops);
    else
        nojmp(ops);
}

static void jmp_lt(ParseOps *ops) {
    if (ops->vm->cmpbuf1 < ops->vm->cmpbuf2)
        jmp(ops);
    else
        nojmp(ops);
}

static void push_reg(ParseOps *ops) {
    push(ops->vm, ops->regdst);
}

static void add_reg2reg(ParseOps *ops) {
    *ops->regdst += *ops->regsrc;
}

static void sub_reg2reg(ParseOps *ops) {
    *ops->regdst -= *ops->regsrc;
}

static void mul_reg2reg(ParseOps *ops) {
    *ops->regdst *= *ops->regsrc;
}

static void set_imm2reg(ParseOps *ops) {
    *ops->regdst = 0;
    memcpy(ops->regdst, ops->vm->codeptr, ops->immsize);
    ops->vm->codeptr += ops->immsize;
}

static void chain_parse(ti_vm* vm, size_t count, ...) {
    va_list parsers;
    ParseOps ops;

    ops.regsrc = NULL;
    ops.regdst = NULL;
    ops.vm = vm;

    ops.vm->codeptr++; // consume opcode

    va_start(parsers, count);
    for(size_t i = 0; i < count; ++i) {
        parsefn fn = va_arg(parsers, parsefn);
        fn(&ops);
    }

    va_end(parsers);
}

void ti_execute_byte(ti_vm *vm) {
    while (vm->codeptr - vm->codebase < vm->codesz) {
        switch (*vm->codeptr) {
            case ASM_CMP: chain_parse(vm, 2, reg2reg, compare); break;
            case ASM_JMP: chain_parse(vm, 1, jmp); break;
            case ASM_JMP_EQ: chain_parse(vm, 1, jmp_eq); break;
            case ASM_JMP_GE: chain_parse(vm, 1, jmp_ge); break;
            case ASM_JMP_LE: chain_parse(vm, 1, jmp_le); break;
            case ASM_JMP_GT: chain_parse(vm, 1, jmp_gt); break;
            case ASM_JMP_LT: chain_parse(vm, 1, jmp_lt); break;
            case ASM_PUSH_REG: chain_parse(vm, 2, regselect, push_reg); break;
            case ASM_SET_IMM2REG: chain_parse(vm, 2, imm2reg, set_imm2reg); break;
            case ASM_ADD_REG2REG: chain_parse(vm, 2, reg2reg, add_reg2reg); break;
            case ASM_SUB_REG2REG: chain_parse(vm, 2, reg2reg, sub_reg2reg); break;
            case ASM_MUL_REG2REG: chain_parse(vm, 2, reg2reg, mul_reg2reg); break;
        }
    }
}
