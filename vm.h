#ifndef TOY_VM_H
#define TOY_VM_H

#include <stdint.h>
#include <stdio.h>

#include "asm.h"

#define TI_STACK_MIN 256

typedef struct ti_vm {
   int64_t *stack;
   int64_t *stackptr;
   size_t stacksz;
   int64_t reg_int[4];
} ti_vm;

void ti_init_vm(ti_vm *vm);
void ti_execute_byte(ti_vm *vm, uint8_t code[], size_t size);
void ti_read_constant(ti_vm *vm, uint8_t code[], size_t size);

#endif // TOY_VM_H