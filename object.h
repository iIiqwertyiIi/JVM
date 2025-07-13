#ifndef OBJECT_H
#define OBJECT_H
#include "types.h"
#include "interpreter.h"
#include "instructions.h"

ObjectList * get_object_list();
u4 add_object(Object * object);

int new_(Frame * frame, Instruction instruction);

#endif