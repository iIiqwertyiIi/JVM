#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <math.h>
#include "types.h"
#include "helper.h"
#include "instructions.h"

int iadd(Frame * frame, Instruction instruction);
int ladd(Frame * frame, Instruction instruction);
int fadd(Frame * frame, Instruction instruction);
int dadd(Frame * frame, Instruction instruction);
int isub(Frame * frame, Instruction instruction);
int lsub(Frame * frame, Instruction instruction);
int fsub(Frame * frame, Instruction instruction);
int dsub(Frame * frame, Instruction instruction);
int imul(Frame * frame, Instruction instruction);
int lmul(Frame * frame, Instruction instruction);
int fmul(Frame * frame, Instruction instruction);
int dmul(Frame * frame, Instruction instruction);
int idiv(Frame * frame, Instruction instruction);
int ldiv_(Frame * frame, Instruction instruction);
int fdiv(Frame * frame, Instruction instruction);
int ddiv(Frame * frame, Instruction instruction);
int irem(Frame * frame, Instruction instruction);
int lrem(Frame * frame, Instruction instruction);
int frem(Frame * frame, Instruction instruction);
int drem(Frame * frame, Instruction instruction);
int ineg(Frame * frame, Instruction instruction);
int lneg(Frame * frame, Instruction instruction);
int fneg(Frame * frame, Instruction instruction);
int dneg(Frame * frame, Instruction instruction);
int ishl(Frame * frame, Instruction instruction);
int lshl(Frame * frame, Instruction instruction);
int ishr(Frame * frame, Instruction instruction);
int lshr(Frame * frame, Instruction instruction);
int iushr(Frame * frame, Instruction instruction);
int lushr(Frame * frame, Instruction instruction);

int iinc(Frame * frame, Instruction instruction);



#endif // ARITHMETIC_H