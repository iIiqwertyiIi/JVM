#include "method_invocation.h"
#include "instructions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Remover funções duplicadas e utilitários locais
// Usar apenas funções centrais: getFromConstantPool, getNestedString, get_method, call_method, add_to_stack, remove_from_stack
// Manter apenas as funções dos invokes, ajustadas

// Função utilitária para contar argumentos a partir do descriptor
int count_method_arguments(const char* descriptor) {
    if (!descriptor || descriptor[0] != '(') return 0;
    int count = 0;
    int i = 1;
    while (descriptor[i] && descriptor[i] != ')') {
        switch (descriptor[i]) {
            case 'B': case 'C': case 'D': case 'F': case 'I': case 'S': case 'Z':
                count++; i++; break;
            case 'J': count++; i++; break;
            case 'L': count++; while (descriptor[i] && descriptor[i] != ';') i++; if (descriptor[i] == ';') i++; break;
            case '[': while (descriptor[i] == '[') i++; if (descriptor[i] == 'L') { while (descriptor[i] && descriptor[i] != ';') i++; if (descriptor[i] == ';') i++; } else { i++; } count++; break;
            default: i++; break;
        }
    }
    return count;
}

// Função utilitária para obter argumentos da pilha
Arguments* get_arguments(Frame* frame, char include_this, const char* method_descriptor) {
    int num_args = count_method_arguments(method_descriptor);
    if (include_this) num_args++;
    Arguments* args = malloc(sizeof(Arguments));
    args->size = num_args;
    args->arguments = malloc(sizeof(u4) * num_args);
    for (int i = num_args - 1; i >= 0; i--) {
        args->arguments[i] = remove_from_stack(frame);
    }
    return args;
}

// Busca método na hierarquia de superclasses
method_info* find_method_in_hierarchy(ClassFile* class, char* method_name, char* method_descriptor) {
    while (class) {
        method_info* m = get_method(class, method_name, method_descriptor);
        if (m) return m;
        if (class->super_class == 0) break;
        char* super_name = getNestedString(class, class->super_class);
        if (!super_name) break;
        class = get_class_file(super_name);
    }
    return NULL;
}

// Implementação dos invokes
int common_invoke(Frame* frame, Instruction instruction, char include_this) {
    uint16_t methodref_index = (instruction.operands[0] << 8) | instruction.operands[1];
    cp_info* methodref = getFromConstantPool(frame->this_class, methodref_index);
    cp_info* name_and_type = getFromConstantPool(frame->this_class, methodref->Methodref.name_and_type_index);
    char* class_name = getNestedString(frame->this_class, methodref->Methodref.class_index);
    char* method_name = getNestedString(frame->this_class, name_and_type->NameAndType.name_index);
    char* method_descriptor = getNestedString(frame->this_class, name_and_type->NameAndType.descriptor_index);

    Arguments* args = get_arguments(frame, include_this, method_descriptor);
    ClassFile* class_file = NULL;
    if (include_this) {
        ObjectList* object_list = get_object_list();
        u4 this_ref = args->arguments[0];
        if (object_list && this_ref < object_list->size) {
            Object* obj = object_list->object[this_ref];
            if (obj) class_file = obj->class;
        }
    } else {
        class_file = get_class_file(class_name);
    }
    if (!class_file) {
        printf("Class file not found\n");
        free(args->arguments); free(args);
        return -1;
    }
    method_info* method = find_method_in_hierarchy(class_file, method_name, method_descriptor);
    if (!method) {
        printf("Method not found: %s %s %s\n", class_name, method_name, method_descriptor);
        free(args->arguments); free(args);
        return -1;
    }
    MethodResponses res = call_method(frame, class_file, method, args);
    free(args->arguments); free(args);
    if (res.status == 0) {
        add_to_stack(frame, res.value);
    }
    return res.status;
}

int invokespecial(Frame* frame, Instruction instruction) {
    return common_invoke(frame, instruction, 1);
}

int invokestatic(Frame* frame, Instruction instruction) {
    return common_invoke(frame, instruction, 0);
}

int invokeinterface(Frame* frame, Instruction instruction) {
    return common_invoke(frame, instruction, 1);
}

// invokevirtual com tratamento especial para println/print
int invokevirtual(Frame* frame, Instruction instruction) {
    uint16_t methodref_index = (instruction.operands[0] << 8) | instruction.operands[1];
    cp_info* methodref = getFromConstantPool(frame->this_class, methodref_index);
    cp_info* name_and_type = getFromConstantPool(frame->this_class, methodref->Methodref.name_and_type_index);
    char* class_name = getNestedString(frame->this_class, methodref->Methodref.class_index);
    char* method_name = getNestedString(frame->this_class, name_and_type->NameAndType.name_index);
    char* method_descriptor = getNestedString(frame->this_class, name_and_type->NameAndType.descriptor_index);
    if (strcmp(class_name, "java/io/PrintStream") == 0 && (strcmp(method_name, "println") == 0 || strcmp(method_name, "print") == 0)) {
        char type = method_descriptor[1];
        switch (type) {
            case 'I': {
                int value = (int)remove_from_stack(frame);
                printf("%d", value);
                break;
            }
            case 'J': {
                u4 low = remove_from_stack(frame);
                u4 high = remove_from_stack(frame);
                long long value = ((long long)high << 32) | low;
                printf("%lld", value);
                break;
            }
            case 'F': {
                u4 raw = remove_from_stack(frame);
                float* f = (float*)&raw;
                printf("%f", *f);
                break;
            }
            case 'D': {
                u4 low = remove_from_stack(frame);
                u4 high = remove_from_stack(frame);
                double d;
                unsigned long long bits = ((unsigned long long)high << 32) | low;
                memcpy(&d, &bits, sizeof(double));
                printf("%.15f", d);
                break;
            }
            case 'C': {
                char value = (char)remove_from_stack(frame);
                printf("%c", value);
                break;
            }
            case 'Z': {
                u4 value = remove_from_stack(frame);
                printf("%s", value ? "true" : "false");
                break;
            }
            case 'L': {
                u4 ref = remove_from_stack(frame);
                printf("[obj ref %u]", ref);
                break;
            }
            case ')':
                break;
            default:
                printf("Tipo não suportado para println: %s\n", method_descriptor);
                break;
        }
        if (strcmp(method_name, "println") == 0) printf("\n");
        return 0;
    }
    return common_invoke(frame, instruction, 1);
} 

