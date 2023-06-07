#ifndef TOY_ASM_H
#define TOY_ASM_H

typedef enum TI_ASM {
    ASM_CMP,
    ASM_JMP,
    ASM_PUSH_REG,
    ASM_SET_IMM2REG,
    ASM_ADD_REG2REG,
} TI_ASM;

#endif // TOY_ASM_H