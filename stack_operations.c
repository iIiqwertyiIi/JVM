#include "types.h"
#include "helper.h"
#include <stdlib.h>
#include <stdio.h>

// Funções de manipulação da pilha de operandos

u4 remove_from_stack(Frame * frame) {
    if (frame->stack_top == NULL) {
        fprintf(stderr, "Erro: Tentativa de remover de pilha vazia\n");
        return 0;
    }
    
    OperandStack * temp = frame->stack_top;
    u4 value = temp->self;
    frame->stack_top = temp->next;
    frame->stack_size--;
    free(temp);
    
    return value;
}

void add_to_stack(Frame * frame, u4 value) {
    OperandStack * new_stack = malloc(sizeof(OperandStack));
    if (new_stack == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para pilha\n");
        return;
    }
    
    new_stack->self = value;
    new_stack->next = frame->stack_top;
    frame->stack_top = new_stack;
    frame->stack_size++;
}

u4 peek_stack(Frame * frame) {
    if (frame->stack_top == NULL) {
        fprintf(stderr, "Erro: Tentativa de acessar pilha vazia\n");
        return 0;
    }
    return frame->stack_top->self;
}

// Funções de conversão de tipo para instruções da JVM

int d2f(Frame * frame, Instruction instruction) {
    // Remove os dois valores da pilha (double ocupa 2 slots)
    u4 low = remove_from_stack(frame);
    u4 high = remove_from_stack(frame);
    
    // Reconstrói o double (64 bits)
    u8 double_bits = ((u8)high << 32) | low;
    double double_value = u8_to_double(double_bits);
    
    // Converte double para float
    float float_value = (float)double_value;
    
    // Converte float para uint32 e empilha
    u4 float_bits = float_to_u4(float_value);
    add_to_stack(frame, float_bits);
    
    return 0;
}

int d2i(Frame * frame, Instruction instruction) {
    u4 low = remove_from_stack(frame);
    u4 high = remove_from_stack(frame);
    
    u8 double_bits = ((u8)high << 32) | low;
    double double_value = u8_to_double(double_bits);
    
    int32_t int_value = (int32_t)double_value;
    
    u4 int_bits = int_to_u4(int_value);
    add_to_stack(frame, int_bits);
    
    return 0;
}

int d2l(Frame * frame, Instruction instruction) {
    u4 low = remove_from_stack(frame);
    u4 high = remove_from_stack(frame);
    
    u8 double_bits = ((u8)high << 32) | low;
    double double_value = u8_to_double(double_bits);
    
    int64_t long_value = (int64_t)double_value;
    
    // Long ocupa 2 slots na pilha
    u8 long_bits = long_to_u8(long_value);
    u4 high_bits = (u4)(long_bits >> 32);
    u4 low_bits = (u4)(long_bits & 0xFFFFFFFF);
    
    add_to_stack(frame, low_bits);
    add_to_stack(frame, high_bits);
    
    return 0;
}

int f2d(Frame * frame, Instruction instruction) {
    u4 float_bits = remove_from_stack(frame);
    float float_value = u4_to_float(float_bits);
    
    double double_value = (double)float_value;
    
    u8 double_bits = double_to_u8(double_value);
    u4 high_bits = (u4)(double_bits >> 32);
    u4 low_bits = (u4)(double_bits & 0xFFFFFFFF);
    
    add_to_stack(frame, low_bits);
    add_to_stack(frame, high_bits);
    
    return 0;
}

int f2i(Frame * frame, Instruction instruction) {
    u4 float_bits = remove_from_stack(frame);
    float float_value = u4_to_float(float_bits);
    
    int32_t int_value = (int32_t)float_value;
    
    u4 int_bits = int_to_u4(int_value);
    add_to_stack(frame, int_bits);
    
    return 0;
}

int f2l(Frame * frame, Instruction instruction) {
    u4 float_bits = remove_from_stack(frame);
    float float_value = u4_to_float(float_bits);
    
    int64_t long_value = (int64_t)float_value;
    
    u8 long_bits = long_to_u8(long_value);
    u4 high_bits = (u4)(long_bits >> 32);
    u4 low_bits = (u4)(long_bits & 0xFFFFFFFF);
    
    add_to_stack(frame, low_bits);
    add_to_stack(frame, high_bits);
    
    return 0;
}

int i2b(Frame * frame, Instruction instruction) {
    u4 int_bits = remove_from_stack(frame);
    int32_t int_value = u4_to_int(int_bits);
    
    int8_t byte_value = (int8_t)int_value;
    
    u4 byte_bits = int_to_u4((int32_t)byte_value);
    add_to_stack(frame, byte_bits);
    
    return 0;
}

int i2c(Frame * frame, Instruction instruction) {
    u4 int_bits = remove_from_stack(frame);
    int32_t int_value = u4_to_int(int_bits);
    
    int16_t char_value = (int16_t)int_value;
    
    u4 char_bits = int_to_u4((int32_t)char_value);
    add_to_stack(frame, char_bits);
    
    return 0;
}

int i2d(Frame * frame, Instruction instruction) {
    u4 int_bits = remove_from_stack(frame);
    int32_t int_value = u4_to_int(int_bits);
    
    double double_value = (double)int_value;
    
    u8 double_bits = double_to_u8(double_value);
    u4 high_bits = (u4)(double_bits >> 32);
    u4 low_bits = (u4)(double_bits & 0xFFFFFFFF);
    
    add_to_stack(frame, low_bits);
    add_to_stack(frame, high_bits);
    
    return 0;
}

int i2f(Frame * frame, Instruction instruction) {
    u4 int_bits = remove_from_stack(frame);
    int32_t int_value = u4_to_int(int_bits);
    
    float float_value = (float)int_value;
    
    u4 float_bits = float_to_u4(float_value);
    add_to_stack(frame, float_bits);
    
    return 0;
}

int i2l(Frame * frame, Instruction instruction) {
    u4 int_bits = remove_from_stack(frame);
    int32_t int_value = u4_to_int(int_bits);
    
    int64_t long_value = (int64_t)int_value;
    
    u8 long_bits = long_to_u8(long_value);
    u4 high_bits = (u4)(long_bits >> 32);
    u4 low_bits = (u4)(long_bits & 0xFFFFFFFF);
    
    add_to_stack(frame, low_bits);
    add_to_stack(frame, high_bits);
    
    return 0;
}

int i2s(Frame * frame, Instruction instruction) {
    u4 int_bits = remove_from_stack(frame);
    int32_t int_value = u4_to_int(int_bits);
    
    int16_t short_value = (int16_t)int_value;
    
    u4 short_bits = int_to_u4((int32_t)short_value);
    add_to_stack(frame, short_bits);
    
    return 0;
}

int l2d(Frame * frame, Instruction instruction) {
    u4 low = remove_from_stack(frame);
    u4 high = remove_from_stack(frame);
    
    u8 long_bits = ((u8)high << 32) | low;
    int64_t long_value = u8_to_long(long_bits);
    
    double double_value = (double)long_value;
    
    u8 double_bits = double_to_u8(double_value);
    u4 high_bits = (u4)(double_bits >> 32);
    u4 low_bits = (u4)(double_bits & 0xFFFFFFFF);
    
    add_to_stack(frame, low_bits);
    add_to_stack(frame, high_bits);
    
    return 0;
}

int l2f(Frame * frame, Instruction instruction) {
    u4 low = remove_from_stack(frame);
    u4 high = remove_from_stack(frame);
    
    u8 long_bits = ((u8)high << 32) | low;
    int64_t long_value = u8_to_long(long_bits);
    
    float float_value = (float)long_value;
    
    u4 float_bits = float_to_u4(float_value);
    add_to_stack(frame, float_bits);
    
    return 0;
}

int l2i(Frame * frame, Instruction instruction) {
    u4 low = remove_from_stack(frame);
    u4 high = remove_from_stack(frame);
    
    u8 long_bits = ((u8)high << 32) | low;
    int64_t long_value = u8_to_long(long_bits);
    
    int32_t int_value = (int32_t)long_value;
    
    u4 int_bits = int_to_u4(int_value);
    add_to_stack(frame, int_bits);
    
    return 0;
} 