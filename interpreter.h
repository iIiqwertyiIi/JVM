#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "types.h"
#include "class_file.h"
#include "instructions.h"

ClassFile * get_class_file(char * class_name);
ClassFile * load_class_file(char * class_name);
int run_class_file(ClassFile * class_file);
method_info * get_method(ClassFile * class_file, char * method_name, char * method_descriptor);
cp_info * getFromConstantPool(ClassFile * class_file, uint16_t index);
char * getNestedString(ClassFile * class_file, uint16_t index);
MethodResponses call_method(Frame * current_frame, ClassFile * class_file, method_info * method, Arguments * arguments);
Instruction read_instruction_buffer(Buffer * code_buffer);

#endif