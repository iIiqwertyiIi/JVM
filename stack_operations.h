#ifndef STACK_OPERATIONS_H
#define STACK_OPERATIONS_H

#include "types.h"

// Funções de manipulação da pilha de operandos
u4 remove_from_stack(Frame * frame);
void add_to_stack(Frame * frame, u4 value);
u4 peek_stack(Frame * frame);

// Funções de conversão de tipo para instruções da JVM
int double_to_float(Frame * frame);
int double_to_int(Frame * frame);
int double_to_long(Frame * frame);
int float_to_double(Frame * frame);
int float_to_int(Frame * frame);
int float_to_long(Frame * frame);
int int_to_byte(Frame * frame);
int int_to_char(Frame * frame);
int int_to_double(Frame * frame);
int int_to_float(Frame * frame);
int int_to_long(Frame * frame);
int int_to_short(Frame * frame);
int int_to_double(Frame * frame);
int long_to_float(Frame * frame);
int long_to_int(Frame * frame);

#endif 