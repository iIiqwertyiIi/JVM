#ifndef TABLE_H
#define TABLE_H

#include "types.h"
#include "instructions.h"
#include "reader.h"

int tableswitch(Frame * frame, Instruction instruction);
int lookupswitch(Frame * frame, Instruction instruction);

#endif // TABLE_H