#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "types.h"

// Opcodes para as operações lógicas
#define IXOR        0x82    // XOR inteiro
#define IOR         0x80    // OR inteiro  
#define IAND        0x7E    // AND inteiro
#define INOT        0x74    // NOT inteiro 

// Opcodes para comparações 
#define IF_ICMPEQ   0x9F    // Jump if ints equal
#define IF_ICMPNE   0xA0    // Jump if ints not equal
#define IF_ICMPLT   0xA1    // Jump if int1 < int2
#define IF_ICMPGE   0xA2    // Jump if int1 >= int2
#define IF_ICMPGT   0xA3    // Jump if int1 > int2
#define IF_ICMPLE   0xA4    // Jump if int1 <= int2

// Opcodes para comparação de referências
#define IF_ACMPEQ   0xA5    // Jump if references equal
#define IF_ACMPNE   0xA6    // Jump if references not equal

// Operações lógicas básicas
void instruction_ixor(FrameStack* frame_stack);
void instruction_ior(FrameStack* frame_stack);
void instruction_iand(FrameStack* frame_stack);
void instruction_inot(FrameStack* frame_stack);

// Operações de comparação e salto
void instruction_if_icmpeq(FrameStack* frame_stack, int16_t branch_offset);
void instruction_if_icmpne(FrameStack* frame_stack, int16_t branch_offset);
void instruction_if_icmplt(FrameStack* frame_stack, int16_t branch_offset);
void instruction_if_icmpge(FrameStack* frame_stack, int16_t branch_offset);
void instruction_if_icmpgt(FrameStack* frame_stack, int16_t branch_offset);
void instruction_if_icmple(FrameStack* frame_stack, int16_t branch_offset);

// Comparação de referências
void instruction_if_acmpeq(FrameStack* frame_stack, int16_t branch_offset);
void instruction_if_acmpne(FrameStack* frame_stack, int16_t branch_offset);

// Funções auxiliares para manipular a pilha de operandos
void push_int(FrameStack* frame_stack, int32_t value);
int32_t pop_int(FrameStack* frame_stack);
void push_ref(FrameStack* frame_stack, u4 ref);
u4 pop_ref(FrameStack* frame_stack);

// Função para executar uma instrução específica
int execute_instruction(FrameStack* frame_stack, u1 opcode, u1* bytecode, u8* pc);

// Função auxiliar para debug
void print_operand_stack(FrameStack* frame_stack, int max_elements);

#endif // INSTRUCTIONS_H