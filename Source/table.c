#include "table.h"


void table_init(ti_table* table) {
    table->count = 0;
    table->capacity = 0;
    table->entries = NULL;
}

void table_free(ti_table* table) {
    free(table->entries);
    table_init(table);
}