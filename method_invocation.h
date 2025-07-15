#ifndef METHOD_INVOCATION_H
#define METHOD_INVOCATION_H

#include "types.h"
#include "class_file.h"

// Estrutura para armazenar informações de um método resolvido
typedef struct ResolvedMethod {
    ClassFile* class;
    method_info* method;
    u2 method_index;
} ResolvedMethod;

// Funções para resolução de métodos
ResolvedMethod* resolve_method(ClassFile* current_class, u2 methodref_index);
ResolvedMethod* resolve_interface_method(ClassFile* current_class, u2 interface_methodref_index);
ResolvedMethod* find_method_in_class(ClassFile* class, char* method_name, char* method_descriptor);
ResolvedMethod* find_method_in_superclass(ClassFile* class, char* method_name, char* method_descriptor);

// Funções para execução de métodos
Frame* create_frame(ClassFile* class, method_info* method);
void execute_method(Frame* frame);
void push_frame(FrameStack* frame_stack, Frame* frame);
Frame* pop_frame(FrameStack* frame_stack);

// Funções para obter strings do constant pool
char* get_utf8_string(cp_info** constant_pool, u2 index);
char* get_class_name(cp_info** constant_pool, u2 class_index);

// Funções para as instruções invoke
int invokevirtual(Frame* frame, Instruction instruction);
int invokespecial(Frame* frame, Instruction instruction);
int invokestatic(Frame* frame, Instruction instruction);
int invokeinterface(Frame* frame, Instruction instruction);

#endif 