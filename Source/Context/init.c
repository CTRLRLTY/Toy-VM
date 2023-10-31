#include "context.h"
#include "vm.h"
#include "defs.h"

#include <stdio.h>

static bool print(ti_vm* vm) {
        size_t arg1 = (size_t)*vm->stackptr;
        return true;
}

bool ctx_init() {
        ctx_set_func(print, IC_PRINT);
        return true;
}
