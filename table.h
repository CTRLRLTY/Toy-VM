#ifndef TOY_ASM_TABLE_H
#define TOY_ASM_TABLE_H

#include <stdbool.h>
#include <stdint.h>

typedef char ti_key[32];

typedef struct ti_entry {
    ti_key key;
    int64_t address;
} ti_entry;

typedef struct ti_table {
    size_t count;
    size_t capacity;
    ti_entry* entries;
} ti_table;

void table_init(ti_table* table);
void table_free(ti_table* table);

bool table_get(const *ti_table, const ti_key* key, int64_t address);
bool table_set(const *ti_table, const ti_key* key, int64_t address);
#endif