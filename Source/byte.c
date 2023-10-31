#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "byte.h"

void init_byte_list(ByteList* bytes) {
        bytes->size = 100;
        bytes->capacity = 0;
        bytes->d = (Byte*)malloc(sizeof(bytes) * bytes->size);
}

void free_byte_list(ByteList* bytes) {
        bytes->size = 100;
        bytes->capacity = 0;
        free(bytes->d);
}

void add_byte(ByteList* bytes, Byte b) {
        size_t capacity = bytes->capacity++;

        if (capacity > bytes->size) {
                bytes->size += 100;
                bytes->d = (Byte*)realloc(bytes->d, bytes->size);

                if (bytes->d == NULL) {
                        perror("Can't add bytecode");
                        exit(1);
                }
        }

        bytes->d[capacity] = b;
}

void add_byte64(ByteList* bytes, Byte64 b64) {
        size_t capacity = bytes->capacity;
        bytes->capacity += sizeof(b64);

        if (capacity > bytes->size) {
                bytes->size += 100;
                bytes->d = (Byte*)realloc(bytes->d, sizeof(Byte64) * bytes->size);

                if (bytes->d == NULL) {
                        perror("Can't add bytecode");
                        exit(1);
                }
        }

        memcpy(bytes->d+capacity, &b64, sizeof(Byte64));
}
