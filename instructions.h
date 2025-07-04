#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "types.h"
#include "load_store.h"

int nop(Frame * frame, Instruction instruction);

InstructionType * get_instruction_type(u1 opcode);
void add_to_stack(Frame * frame, u4 value);
u4 remove_from_stack(Frame * frame);

int filler(Frame * frame, Instruction instruction);

#endif