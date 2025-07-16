#ifndef OBJECT_H
#define OBJECT_H
#include "types.h"
#include "interpreter.h"
#include "instructions.h"
#include "string.h"
#include "stringBuffer.h"

ObjectList * get_object_list();
Object * get_object(u4 index);
u4 add_object(Object * object);
ActiveField * get_static_field(ClassFile * class_file, char * field_name, char * field_descriptor);
ActiveField * get_field(Object * object, char * field_name, char * field_descriptor);

int new_(Frame * frame, Instruction instruction);
int getstatic(Frame * frame, Instruction instruction);
int putstatic(Frame * frame, Instruction instruction);
int getfield(Frame * frame, Instruction instruction);
int putfield(Frame * frame, Instruction instruction);

#endif