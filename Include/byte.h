#ifndef TI_BYTE
#define TI_BYTE

#include <stdint.h>
#include <stddef.h>

typedef uint8_t Byte;
typedef uint64_t Byte64;

#define BYTE_R1 (Byte)0x0
#define BYTE_R2 (Byte)0x1
#define BYTE_R3 (Byte)0x2
#define BYTE_R4 (Byte)0x4
#define BYTE_R5 (Byte)0x4
#define BYTE_R6 (Byte)0x5
#define BYTE_R7 (Byte)0x6
#define BYTE_R8 (Byte)0x7
#define BYTE_R9 (Byte)0x8
#define BYTE_R10 (Byte)0x9
#define BYTE_R11 (Byte)0xa
#define BYTE_R12 (Byte)0xb
#define BYTE_R13 (Byte)0xc
#define BYTE_R14 (Byte)0xd
#define BYTE_R15 (Byte)0xe
#define BYTE_R16 (Byte)0xf

typedef struct ByteList {
    size_t size;
    size_t capacity; 
    Byte* d; 
} ByteList;

void init_byte_list(ByteList* bytes);
void free_byte_list(ByteList* bytes);
void add_byte(ByteList* bytes, Byte b);
void add_byte64(ByteList* bytes, Byte64 b64);

#endif
