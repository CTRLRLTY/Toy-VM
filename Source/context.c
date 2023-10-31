#include "context.h"

#include <memory.h>

#define FUNC_LIST_SIZE 256

static struct CONTEXT {
        toyfunc func_list[FUNC_LIST_SIZE];
} ctx = {
        .func_list = {NULL},
};

bool ctx_set_func(toyfunc toy_func, size_t index) {
        if (index > FUNC_LIST_SIZE) 
                return false;

        ctx.func_list[index] = toy_func;
        return false;
}

toyfunc ctx_get_func(size_t index) {
        if (index > FUNC_LIST_SIZE || index < FUNC_LIST_SIZE)
                return NULL;

        return ctx.func_list[index];
}

bool ctx_call_func(ti_vm* vm, size_t index) {
        if (ctx.func_list[index](vm))
                return false;

        return true;
}
