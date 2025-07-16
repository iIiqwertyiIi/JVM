#ifndef RETURN_H
#define RETURN_H
#include "types.h"
#include "instructions.h"

int ret(Frame * frame, Instruction instruction);
int ireturn(Frame * frame, Instruction instruction);
int lreturn(Frame * frame, Instruction instruction);
int freturn(Frame * frame, Instruction instruction);
int dreturn(Frame * frame, Instruction instruction);
int areturn(Frame * frame, Instruction instruction);
int return_(Frame * frame, Instruction instruction);

#endif