#ifndef TOY_ASM_H
#define TOY_ASM_H

typedef enum TI_ASM {
    ASM_PRINT,
    ASM_PUSH_R0,
    ASM_PUSH_R1,
    ASM_PUSH_R2,
    ASM_PUSH_R3,

    ASM_SET_R0_IMM,
    ASM_SET_R1_IMM,
    ASM_SET_R2_IMM,
    ASM_SET_R3_IMM,

    ASM_ADD,
} TI_ASM;

#endif // TOY_ASM_H