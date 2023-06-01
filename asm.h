#ifndef TOY_ASM_H
#define TOY_ASM_H

typedef enum TI_ASM {
    ASM_SET_R0_IMM,
    ASM_SET_R1_IMM,
    ASM_SET_R2_IMM,
    ASM_SET_R3_IMM,

    ASM_ADD_R0_R0,
    ASM_ADD_R0_R1,
    ASM_ADD_R0_R2,
    ASM_ADD_R0_R3,

    ASM_ADD_R1_R0,
    ASM_ADD_R1_R1,
    ASM_ADD_R1_R2,
    ASM_ADD_R1_R3,

    ASM_ADD_R2_R0,
    ASM_ADD_R2_R1,
    ASM_ADD_R2_R2,
    ASM_ADD_R2_R3,

    ASM_ADD_R3_R0,
    ASM_ADD_R3_R1,
    ASM_ADD_R3_R2,
    ASM_ADD_R3_R3,

    ASM_PRINTF
} TI_ASM;

#endif // TOY_ASM_H