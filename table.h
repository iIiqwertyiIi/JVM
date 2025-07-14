#ifndef TABLE_H
#define TABLE_H

#include "types.h"
#include "instructions.h"
#include "reader.h"

int table_switch(Frame * frame, Instruction instruction);
int lookup_switch(Frame * frame, Instruction instruction);

#endif // TABLE_H