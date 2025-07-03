#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <math.h>
#include "types.h"
#include "helper.h"

int iadd(Frame * frame);
int ladd(Frame * frame);
int fadd(Frame * frame);
int dadd(Frame * frame);
int isub(Frame * frame);
int lsub(Frame * frame);
int fsub(Frame * frame);
int dsub(Frame * frame);
int imul(Frame * frame);
int lmul(Frame * frame);
int fmul(Frame * frame);
int dmul(Frame * frame);
int idiv(Frame * frame);
int ldiv(Frame * frame);
int fdiv(Frame * frame);
int ddiv(Frame * frame);
int irem(Frame * frame);
int lrem(Frame * frame);
int frem(Frame * frame);
int drem(Frame * frame);
int ineg(Frame * frame);
int lneg(Frame * frame);
int fneg(Frame * frame);
int dneg(Frame * frame);



#endif // ARITHMETIC_H