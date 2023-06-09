#ifndef TOY_ASM_H
#define TOY_ASM_H

typedef enum TI_ASM {
    ASM_CMP,
    ASM_JMP,
    ASM_JMP_EQ,
    ASM_JMP_GE,
    ASM_JMP_LE,
    ASM_JMP_GT,
    ASM_JMP_LT,

    ASM_PUSH_REG,

    ASM_SET_IMM2REG,
    ASM_ADD_REG2REG,
    ASM_SUB_REG2REG,
    ASM_MUL_REG2REG,

    ASM_FINISH,
    ASM_EXCEED = 256
} TI_ASM;

#endif // TOY_ASM_H