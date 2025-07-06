#ifndef STACK_OPERATIONS_H
#define STACK_OPERATIONS_H

#include "types.h"
#include "instructions.h"


int d2f(Frame * frame, Instruction instruction);
int d2i(Frame * frame, Instruction instruction);
int d2l(Frame * frame, Instruction instruction);
int f2d(Frame * frame, Instruction instruction);
int f2i(Frame * frame, Instruction instruction);
int f2l(Frame * frame, Instruction instruction);
int i2b(Frame * frame, Instruction instruction);
int i2c(Frame * frame, Instruction instruction);
int i2d(Frame * frame, Instruction instruction);
int i2f(Frame * frame, Instruction instruction);
int i2l(Frame * frame, Instruction instruction);
int i2s(Frame * frame, Instruction instruction);
int l2d(Frame * frame, Instruction instruction);
int l2f(Frame * frame, Instruction instruction);
int l2i(Frame * frame, Instruction instruction);

#endif 