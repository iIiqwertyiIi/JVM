#include "method_invocation.h"

// Variável global para a pilha de frames
static FrameStack frame_stack = {0, NULL};

// Função para obter string UTF-8 do constant pool
char* get_utf8_string(cp_info** constant_pool, u2 index) {
    if (index == 0 || index > 65535) return NULL;
    cp_info* entry = constant_pool[index - 1];
    if (entry->tag == CONSTANT_Utf8) {
        return (char *) entry->Utf8.bytes;
    }
    return NULL;
}

// Função para obter nome da classe do constant pool
char* get_class_name(cp_info** constant_pool, u2 class_index) {
    if (class_index == 0 || class_index > 65535) return NULL;
    cp_info* entry = constant_pool[class_index - 1];
    if (entry->tag == CONSTANT_Class) {
        return get_utf8_string(constant_pool, entry->Class.name_index);
    }
    return NULL;
}

// Função para encontrar um método em uma classe específica
ResolvedMethod* find_method_in_class(ClassFile* class, char* method_name, char* method_descriptor) {
    if (!class || !method_name || !method_descriptor) return NULL;
    
    for (u2 i = 0; i < class->methods_count; i++) {
        method_info* method = class->methods[i];
        char* name = get_utf8_string(class->constant_pool, method->name_index);
        char* descriptor = get_utf8_string(class->constant_pool, method->descriptor_index);
        
        if (name && descriptor && 
            strcmp(name, method_name) == 0 && 
            strcmp(descriptor, method_descriptor) == 0) {
            
            ResolvedMethod* resolved = malloc(sizeof(ResolvedMethod));
            resolved->class = class;
            resolved->method = method;
            resolved->method_index = i;
            return resolved;
        }
    }
    return NULL;
}

// Função para encontrar método na hierarquia de superclasses
ResolvedMethod* find_method_in_superclass(ClassFile* class, char* method_name, char* method_descriptor) {
    if (!class) return NULL;
    
    // Procura na classe atual
    ResolvedMethod* result = find_method_in_class(class, method_name, method_descriptor);
    if (result) return result;
    
    // Procura na superclasse (se existir)
    if (class->super_class != 0) {
        char* super_class_name = get_class_name(class->constant_pool, class->super_class);
        if (super_class_name) {
            ClassFile* super_class = get_class_file(super_class_name);
            if (super_class) {
                return find_method_in_superclass(super_class, method_name, method_descriptor);
            }
        }
    }
    
    return NULL;
}

// Função para resolver um MethodRef
ResolvedMethod* resolve_method(ClassFile* current_class, u2 methodref_index) {
    if (methodref_index == 0 || methodref_index > 65535) return NULL;
    
    cp_info* methodref = current_class->constant_pool[methodref_index - 1];
    if (methodref->tag != CONSTANT_Methodref) return NULL;
    
    // Obtém o nome da classe
    char* class_name = get_class_name(current_class->constant_pool, methodref->Methodref.class_index);
    if (!class_name) return NULL;
    
    // Obtém o nome e tipo do método
    cp_info* name_and_type = current_class->constant_pool[methodref->Methodref.name_and_type_index - 1];
    if (name_and_type->tag != CONSTANT_NameAndType) return NULL;
    
    char* method_name = get_utf8_string(current_class->constant_pool, name_and_type->NameAndType.name_index);
    char* method_descriptor = get_utf8_string(current_class->constant_pool, name_and_type->NameAndType.descriptor_index);
    
    if (!method_name || !method_descriptor) return NULL;
    
    // Carrega a classe alvo
    ClassFile* target_class = get_class_file(class_name);
    if (!target_class) return NULL;
    
    // Procura o método na hierarquia
    return find_method_in_superclass(target_class, method_name, method_descriptor);
}

// Função para resolver um InterfaceMethodRef
ResolvedMethod* resolve_interface_method(ClassFile* current_class, u2 interface_methodref_index) {
    if (interface_methodref_index == 0 || interface_methodref_index > 65535) return NULL;
    
    cp_info* interface_methodref = current_class->constant_pool[interface_methodref_index - 1];
    if (interface_methodref->tag != CONSTANT_InterfaceMethodref) return NULL;
    
    // Obtém o nome da interface
    char* interface_name = get_class_name(current_class->constant_pool, interface_methodref->InterfaceMethodref.class_index);
    if (!interface_name) return NULL;
    
    // Obtém o nome e tipo do método
    cp_info* name_and_type = current_class->constant_pool[interface_methodref->InterfaceMethodref.name_and_type_index - 1];
    if (name_and_type->tag != CONSTANT_NameAndType) return NULL;
    
    char* method_name = get_utf8_string(current_class->constant_pool, name_and_type->NameAndType.name_index);
    char* method_descriptor = get_utf8_string(current_class->constant_pool, name_and_type->NameAndType.descriptor_index);
    
    if (!method_name || !method_descriptor) return NULL;
    
    // Carrega a interface
    ClassFile* interface = get_class_file(interface_name);
    if (!interface) return NULL;
    
    // Procura o método na interface
    return find_method_in_class(interface, method_name, method_descriptor);
}

// Função para criar um novo frame
Frame* create_frame(ClassFile* class, method_info* method) {
    Frame* frame = malloc(sizeof(Frame));
    if (!frame) return NULL;
    
    frame->this_class = class;
    frame->this_method = method;
    frame->stack_top = NULL;
    frame->stack_size = 0;
    frame->next = NULL;
    
    // Inicializa variáveis locais
    frame->local_variables = calloc(65536, sizeof(u4)); // Máximo de 65536 variáveis locais
    
    // Inicializa o PC (Program Counter)
    frame->pc.buffer = NULL;
    frame->pc.position = 0;
    
    // Se o método tem código, inicializa o PC
    for (u2 i = 0; i < method->attributes_count; i++) {
        attribute_info* attr = method->attributes[i];
        char* attr_name = get_utf8_string(class->constant_pool, attr->attribute_name_index);
        if (attr_name && strcmp(attr_name, "Code") == 0) {
            frame->pc.buffer = attr->Code.code;
            frame->pc.position = 0;
            break;
        }
    }
    
    return frame;
}

// Função para empilhar um frame
void push_frame(FrameStack* frame_stack, Frame* frame) {
    if (!frame_stack || !frame) return;
    
    frame->next = frame_stack->top_frame;
    frame_stack->top_frame = frame;
    frame_stack->stack_size++;
}

// Função para desempilhar um frame
Frame* pop_frame(FrameStack* frame_stack) {
    if (!frame_stack || !frame_stack->top_frame) return NULL;
    
    Frame* frame = frame_stack->top_frame;
    frame_stack->top_frame = frame->next;
    frame_stack->stack_size--;
    
    return frame;
}

// Função para executar um método (simplificada)
void execute_method(Frame* frame) {
    if (!frame || !frame->pc.buffer) return;

    u1* code = frame->pc.buffer;
    // Descobrir o tamanho do código (procurar atributo Code)
    u4 code_length = 0;
    for (u2 i = 0; i < frame->this_method->attributes_count; i++) {
        attribute_info* attr = frame->this_method->attributes[i];
        // O nome do atributo já foi resolvido em create_frame, mas aqui repetimos para garantir
        // (ideal: guardar ponteiro para o atributo Code em create_frame)
        char* attr_name = get_utf8_string(frame->this_class->constant_pool, attr->attribute_name_index);
        if (attr_name && strcmp(attr_name, "Code") == 0) {
            code_length = attr->Code.code_length;
            break;
        }
    }

    while (frame->pc.position < code_length) {
        u1 opcode = code[frame->pc.position];
        InstructionType* type = get_instruction_type(opcode);
        if (!type || !type->opcode_function) {
            printf("Opcode 0x%02x não implementado\n", opcode);
            frame->pc.position++;
            continue;
        }

        // Ler operandos
        u1* operands = NULL;
        if (type->operand_count > 0) {
            operands = malloc(type->operand_count);
            for (u1 i = 0; i < type->operand_count; i++) {
                operands[i] = code[frame->pc.position + 1 + i];
            }
        }
        Instruction instruction = { type, operands };

        // Executa a instrução
        int result = type->opcode_function(frame, instruction);

        // Atualiza o PC
        if (type->operand_count > 0) {
            frame->pc.position += 1 + type->operand_count;
        } else {
            frame->pc.position += 1;
        }

        // Libera operandos
        if (operands) free(operands);

        // Se for uma instrução de retorno, sai do loop
        if (opcode == 0xac || opcode == 0xad || opcode == 0xae || opcode == 0xaf || opcode == 0xb0 || opcode == 0xb1) {
            // ireturn, lreturn, freturn, dreturn, areturn, return
            break;
        }
    }
}

// Implementação das instruções invoke

int invokevirtual(Frame* frame, Instruction instruction) {
    u2 methodref_index = (instruction.operands[0] << 8) | instruction.operands[1];
    // Descobrir o descriptor do método
    // Precisamos do 'this' para saber a classe real do objeto
    // 1. Descobrir quantos argumentos o método tem
    // 2. O 'this' está na pilha, logo antes dos argumentos
    // 3. Pegar o valor de 'this' (referência do objeto)
    // 4. Descobrir a classe real do objeto
    // 5. Resolver o método na classe real

    // Para isso, primeiro contamos os argumentos
    // (não removemos ainda da pilha)
    // Descobrir o método na classe declarada para pegar o descriptor
    ResolvedMethod* resolved_decl = resolve_method(frame->this_class, methodref_index);
    if (!resolved_decl) {
        printf("Erro: Método não encontrado para invokevirtual (decl)");
        return -1;
    }
    char* descriptor = get_utf8_string(resolved_decl->class->constant_pool, resolved_decl->method->descriptor_index);
    int num_args = count_method_arguments(descriptor);
    int total_args = num_args + 1; // +1 para o this

    // Pegar o 'this' sem remover da pilha (está na posição stack_size - num_args - 1)
    OperandStack* it = frame->stack_top;
    for (u4 i = 0; i < num_args; i++) {
        if (it) it = it->next;
    }
    u4 this_ref = it ? it->self : 0;
    // Aqui, assumimos que o valor de referência do objeto é o índice na lista de objetos
    // (ajuste conforme sua implementação de objetos)
    // Descobrir a classe real do objeto
    ObjectList* object_list = get_object_list(); // Supondo que existe uma função para isso
    ClassFile* real_class = NULL;
    if (object_list && this_ref < object_list->size) {
        Object* obj = object_list->object[this_ref];
        if (obj) real_class = obj->class;
    }
    if (!real_class) real_class = resolved_decl->class; // fallback

    // Agora resolve o método na classe real
    ResolvedMethod* resolved = find_method_in_superclass(real_class, get_utf8_string(resolved_decl->class->constant_pool, resolved_decl->method->name_index), descriptor);
    if (!resolved) {
        printf("Erro: Método não encontrado para invokevirtual (dinâmico)\n");
        free(resolved_decl);
        return -1;
    }
    free(resolved_decl);

    // --- TRATAMENTO ESPECIAL PARA PRINTLN/PRINT ---
    char* class_name = get_class_name(resolved->class->constant_pool, resolved->class->this_class);
    char* method_name = get_utf8_string(resolved->class->constant_pool, resolved->method->name_index);
    char* method_descriptor = get_utf8_string(resolved->class->constant_pool, resolved->method->descriptor_index);
    // Print de depuração para ver se chegou aqui
    printf("[DEBUG] invokevirtual: class=%s, method=%s, desc=%s\n", class_name, method_name, method_descriptor);
    if (strcmp(class_name, "java/io/PrintStream") == 0 && (strcmp(method_name, "println") == 0 || strcmp(method_name, "print") == 0)) {
        printf("[DEBUG] Tratamento especial de PrintStream.%s chamado!\n", method_name);
        // Descobre o tipo do argumento
        if (strcmp(method_descriptor, "(I)V") == 0) {
            u4 value = remove_from_stack(frame);
            printf("[DEBUG] Valor a ser impresso (int): %d\n", (int)value);
            printf("%d", (int)value);
            if (strcmp(method_name, "println") == 0) printf("\n");
            return 0;
        }
        // Outros tipos podem ser adicionados aqui
        printf("[DEBUG] Descriptor não suportado: %s\n", method_descriptor);
        return 0;
    }
    // --- FIM DO TRATAMENTO ESPECIAL ---

    // Agora segue igual ao anterior: remove argumentos e this, cria frame, etc.
    u4* args = malloc(sizeof(u4) * total_args);
    for (int i = total_args - 1; i >= 0; i--) {
        args[i] = remove_from_stack(frame);
    }
    Frame* new_frame = create_frame(resolved->class, resolved->method);
    if (!new_frame) {
        free(resolved);
        free(args);
        return -1;
    }
    for (int i = 0; i < total_args; i++) {
        new_frame->local_variables[i] = args[i];
    }
    free(args);
    push_frame(&frame_stack, new_frame);
    execute_method(new_frame);
    Frame* returned_frame = pop_frame(&frame_stack);
    if (returned_frame) {
        char* ret_type = strchr(descriptor, ')');
        if (ret_type && *(ret_type + 1) != 'V') {
            ret_type++;
            if (*ret_type == 'J' || *ret_type == 'D') {
                u4 high = remove_from_stack(returned_frame);
                u4 low = remove_from_stack(returned_frame);
                add_to_stack(frame, low);
                add_to_stack(frame, high);
            } else {
                u4 ret_val = remove_from_stack(returned_frame);
                add_to_stack(frame, ret_val);
            }
        }
        free_frame(returned_frame);
    }
    free(resolved);
    return 0;
}

int invokespecial(Frame* frame, Instruction instruction) {
    u2 methodref_index = (instruction.operands[0] << 8) | instruction.operands[1];
    // Resolve o método
    ResolvedMethod* resolved = resolve_method(frame->this_class, methodref_index);
    if (!resolved) {
        printf("Erro: Método não encontrado para invokespecial\n");
        return -1;
    }
    // Descobrir o descriptor do método
    char* descriptor = get_utf8_string(resolved->class->constant_pool, resolved->method->descriptor_index);
    int num_args = count_method_arguments(descriptor);
    // Para métodos de instância, o 'this' também é passado (primeiro argumento)
    int total_args = num_args + 1;
    u4* args = malloc(sizeof(u4) * total_args);
    for (int i = total_args - 1; i >= 0; i--) {
        args[i] = remove_from_stack(frame);
    }
    Frame* new_frame = create_frame(resolved->class, resolved->method);
    if (!new_frame) {
        free(resolved);
        free(args);
        return -1;
    }
    for (int i = 0; i < total_args; i++) {
        new_frame->local_variables[i] = args[i];
    }
    free(args);
    push_frame(&frame_stack, new_frame);
    execute_method(new_frame);
    Frame* returned_frame = pop_frame(&frame_stack);
    if (returned_frame) {
        char* ret_type = strchr(descriptor, ')');
        if (ret_type && *(ret_type + 1) != 'V') {
            ret_type++;
            if (*ret_type == 'J' || *ret_type == 'D') {
                u4 high = remove_from_stack(returned_frame);
                u4 low = remove_from_stack(returned_frame);
                add_to_stack(frame, low);
                add_to_stack(frame, high);
            } else {
                u4 ret_val = remove_from_stack(returned_frame);
                add_to_stack(frame, ret_val);
            }
        }
        free_frame(returned_frame);
    }
    free(resolved);
    return 0;
}

int invokestatic(Frame* frame, Instruction instruction) {
    u2 methodref_index = (instruction.operands[0] << 8) | instruction.operands[1];
    // Resolve o método
    ResolvedMethod* resolved = resolve_method(frame->this_class, methodref_index);
    if (!resolved) {
        printf("Erro: Método não encontrado para invokestatic\n");
        return -1;
    }
    // Descobrir o descriptor do método
    char* descriptor = get_utf8_string(resolved->class->constant_pool, resolved->method->descriptor_index);
    int num_args = count_method_arguments(descriptor);
    // Métodos estáticos não têm 'this'
    int total_args = num_args;
    u4* args = malloc(sizeof(u4) * total_args);
    for (int i = total_args - 1; i >= 0; i--) {
        args[i] = remove_from_stack(frame);
    }
    Frame* new_frame = create_frame(resolved->class, resolved->method);
    if (!new_frame) {
        free(resolved);
        free(args);
        return -1;
    }
    for (int i = 0; i < total_args; i++) {
        new_frame->local_variables[i] = args[i];
    }
    free(args);
    push_frame(&frame_stack, new_frame);
    execute_method(new_frame);
    Frame* returned_frame = pop_frame(&frame_stack);
    if (returned_frame) {
        char* ret_type = strchr(descriptor, ')');
        if (ret_type && *(ret_type + 1) != 'V') {
            ret_type++;
            if (*ret_type == 'J' || *ret_type == 'D') {
                u4 high = remove_from_stack(returned_frame);
                u4 low = remove_from_stack(returned_frame);
                add_to_stack(frame, low);
                add_to_stack(frame, high);
            } else {
                u4 ret_val = remove_from_stack(returned_frame);
                add_to_stack(frame, ret_val);
            }
        }
        free_frame(returned_frame);
    }
    free(resolved);
    return 0;
}

int invokeinterface(Frame* frame, Instruction instruction) {
    u2 interface_methodref_index = (instruction.operands[0] << 8) | instruction.operands[1];
    // Resolve o método da interface
    ResolvedMethod* resolved = resolve_interface_method(frame->this_class, interface_methodref_index);
    if (!resolved) {
        printf("Erro: Método de interface não encontrado\n");
        return -1;
    }
    // Descobrir o descriptor do método
    char* descriptor = get_utf8_string(resolved->class->constant_pool, resolved->method->descriptor_index);
    int num_args = count_method_arguments(descriptor);
    // Para métodos de instância, o 'this' também é passado (primeiro argumento)
    int total_args = num_args + 1;
    u4* args = malloc(sizeof(u4) * total_args);
    for (int i = total_args - 1; i >= 0; i--) {
        args[i] = remove_from_stack(frame);
    }
    Frame* new_frame = create_frame(resolved->class, resolved->method);
    if (!new_frame) {
        free(resolved);
        free(args);
        return -1;
    }
    for (int i = 0; i < total_args; i++) {
        new_frame->local_variables[i] = args[i];
    }
    free(args);
    push_frame(&frame_stack, new_frame);
    execute_method(new_frame);
    Frame* returned_frame = pop_frame(&frame_stack);
    if (returned_frame) {
        char* ret_type = strchr(descriptor, ')');
        if (ret_type && *(ret_type + 1) != 'V') {
            ret_type++;
            if (*ret_type == 'J' || *ret_type == 'D') {
                u4 high = remove_from_stack(returned_frame);
                u4 low = remove_from_stack(returned_frame);
                add_to_stack(frame, low);
                add_to_stack(frame, high);
            } else {
                u4 ret_val = remove_from_stack(returned_frame);
                add_to_stack(frame, ret_val);
            }
        }
        free_frame(returned_frame);
    }
    free(resolved);
    return 0;
} 

// Função utilitária para contar argumentos a partir do descriptor
// Exemplo de descriptor: (IDLjava/lang/String;)V
int count_method_arguments(const char* descriptor) {
    if (!descriptor || descriptor[0] != '(') return 0;
    int count = 0;
    int i = 1;
    while (descriptor[i] && descriptor[i] != ')') {
        switch (descriptor[i]) {
            case 'B': // byte
            case 'C': // char
            case 'D': // double
            case 'F': // float
            case 'I': // int
            case 'S': // short
            case 'Z': // boolean
                count++;
                i++;
                break;
            case 'J': // long
                count++;
                i++;
                break;
            case 'L': // reference type
                count++;
                while (descriptor[i] && descriptor[i] != ';') i++;
                if (descriptor[i] == ';') i++;
                break;
            case '[': // array
                while (descriptor[i] == '[') i++;
                if (descriptor[i] == 'L') {
                    while (descriptor[i] && descriptor[i] != ';') i++;
                    if (descriptor[i] == ';') i++;
                } else {
                    i++;
                }
                count++;
                break;
            default:
                i++;
                break;
        }
    }
    return count;
} 

// Função para liberar completamente um frame
void free_frame(Frame* frame) {
    if (!frame) return;
    // Libera variáveis locais
    if (frame->local_variables) free(frame->local_variables);
    // Libera operand stack
    OperandStack* op = frame->stack_top;
    while (op) {
        OperandStack* next = op->next;
        free(op);
        op = next;
    }
    free(frame);
} 