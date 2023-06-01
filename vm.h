#ifndef TOY_VM_H
#define TOY_VM_H

#include <stdint.h>
#include <stdio.h>

#include "asm.h"

typedef struct ti_vm {
   int64_t reg_int[4];
} ti_vm;

void ti_execute_byte(ti_vm *vm, uint8_t code[], size_t size);

#endif // TOY_VM_H