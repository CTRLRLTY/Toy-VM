#ifndef TOY_CONTEXT
#define TOY_CONTEXT

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ti_vm ti_vm;

typedef bool (*toyfunc)(ti_vm*);

bool ctx_init();
bool ctx_set_func(toyfunc, size_t index);
toyfunc ctx_get_func(size_t index);
bool ctx_call_func(ti_vm*, size_t index);

#endif
