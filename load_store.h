#ifndef LOAD_STORE_H
#define LOAD_STORE_H

#include "types.h"
#include "instructions.h"
#include "reader.h"
#include "helper.h"

int aconst_null(Frame * frame, Instruction instruction);
int iconst_m1(Frame * frame, Instruction instruction);
int iconst_0(Frame * frame, Instruction instruction);
int iconst_1(Frame * frame, Instruction instruction);
int iconst_2(Frame * frame, Instruction instruction);
int iconst_3(Frame * frame, Instruction instruction);
int iconst_4(Frame * frame, Instruction instruction);
int iconst_5(Frame * frame, Instruction instruction);

#endif