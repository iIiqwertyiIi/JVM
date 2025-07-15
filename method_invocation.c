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
    
    // Aqui você implementaria o loop principal de execução
    // Por enquanto, apenas um placeholder
    printf("Executando método: %s\n", 
           get_utf8_string(frame->this_class->constant_pool, frame->this_method->name_index));
}

// Implementação das instruções invoke

int invokevirtual(Frame* frame, Instruction instruction) {
    u2 methodref_index = (instruction.operands[0] << 8) | instruction.operands[1];
    
    // Resolve o método
    ResolvedMethod* resolved = resolve_method(frame->this_class, methodref_index);
    if (!resolved) {
        printf("Erro: Método não encontrado para invokevirtual\n");
        return -1;
    }
    
    remove_from_stack(frame);
    
    // Cria um novo frame para o método chamado
    Frame* new_frame = create_frame(resolved->class, resolved->method);
    if (!new_frame) {
        free(resolved);
        return -1;
    }
    
    // Copia os argumentos da pilha atual para as variáveis locais do novo frame
    // (implementação simplificada - você precisará implementar a lógica completa)
    
    // Empilha o novo frame
    push_frame(&frame_stack, new_frame);
    
    // Executa o método
    execute_method(new_frame);
    
    // Desempilha o frame
    Frame* returned_frame = pop_frame(&frame_stack);
    if (returned_frame) {
        // Copia o valor de retorno para a pilha do frame original
        // (implementação simplificada)
        free(returned_frame);
    }
    
    free(resolved);
    return 0;
}

int invokespecial(Frame* frame, Instruction instruction) {
    u2 methodref_index = (instruction.operands[0] << 8) | instruction.operands[1];
    
    // Similar ao invokevirtual, mas para métodos especiais (construtores, métodos privados)
    ResolvedMethod* resolved = resolve_method(frame->this_class, methodref_index);
    if (!resolved) {
        printf("Erro: Método não encontrado para invokespecial\n");
        return -1;
    }
    
    remove_from_stack(frame);
    
    // Cria um novo frame para o método chamado
    Frame* new_frame = create_frame(resolved->class, resolved->method);
    if (!new_frame) {
        free(resolved);
        return -1;
    }
    
    // Empilha o novo frame
    push_frame(&frame_stack, new_frame);
    
    // Executa o método
    execute_method(new_frame);
    
    // Desempilha o frame
    Frame* returned_frame = pop_frame(&frame_stack);
    if (returned_frame) {
        free(returned_frame);
    }
    
    free(resolved);
    return 0;
}

int invokestatic(Frame* frame, Instruction instruction) {
    u2 methodref_index = (instruction.operands[0] << 8) | instruction.operands[1];
    
    // Para métodos estáticos, não há receiver
    ResolvedMethod* resolved = resolve_method(frame->this_class, methodref_index);
    if (!resolved) {
        printf("Erro: Método estático não encontrado\n");
        return -1;
    }
    
    // Cria um novo frame para o método chamado
    Frame* new_frame = create_frame(resolved->class, resolved->method);
    if (!new_frame) {
        free(resolved);
        return -1;
    }
    
    // Empilha o novo frame
    push_frame(&frame_stack, new_frame);
    
    // Executa o método
    execute_method(new_frame);
    
    // Desempilha o frame
    Frame* returned_frame = pop_frame(&frame_stack);
    if (returned_frame) {
        free(returned_frame);
    }
    
    free(resolved);
    return 0;
}

int invokeinterface(Frame* frame, Instruction instruction) {
    u2 interface_methodref_index = (instruction.operands[0] << 8) | instruction.operands[1];
    //u1 count = instruction.operands[2]; 
    //u1 zero = instruction.operands[3]; 
    
    // Resolve o método da interface
    ResolvedMethod* resolved = resolve_interface_method(frame->this_class, interface_methodref_index);
    if (!resolved) {
        printf("Erro: Método de interface não encontrado\n");
        return -1;
    }
    
    remove_from_stack(frame);
    
    // Cria um novo frame para o método chamado
    Frame* new_frame = create_frame(resolved->class, resolved->method);
    if (!new_frame) {
        free(resolved);
        return -1;
    }
    
    // Empilha o novo frame
    push_frame(&frame_stack, new_frame);
    
    // Executa o método
    execute_method(new_frame);
    
    // Desempilha o frame
    Frame* returned_frame = pop_frame(&frame_stack);
    if (returned_frame) {
        free(returned_frame);
    }
    
    free(resolved);
    return 0;
} 