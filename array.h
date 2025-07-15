#ifndef ARRAY_H
#define ARRAY_H
#include "types.h"
#include "instructions.h"

ArrayList * get_array_list();
u4 add_array(Array * array);
Array * get_array(uint32_t index);

int newarray(Frame * frame, Instruction instruction);
int anewarray(Frame * frame, Instruction instruction);
int arraylength(Frame * frame, Instruction instruction);
int multianewarray(Frame * frame, Instruction instruction);

#endif