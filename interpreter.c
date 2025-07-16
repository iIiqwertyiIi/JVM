#include "interpreter.h"

ClassFile * get_class_file(char * class_name) {
    ClassFileBuffer * class_file_list = get_class_file_buffer();
    for (u2 i = 0; i < class_file_list->size; i++) {
        ClassFile * class_file = class_file_list->buffer[i];
        char * class_file_name = (char *) class_file->constant_pool[class_file->constant_pool[class_file->this_class - 1]->Class.name_index - 1]->Utf8.bytes;
        if (strcmp(class_file_name, class_name) == 0) {
            return class_file;
        }
    }
    return load_class_file(class_name);
}

ClassFile * load_class_file(char * class_name) {
  char class_file_path[100] = "./exemplos/";
  strcat(class_file_path, class_name);
  strcat(class_file_path, ".class");
  read_file(class_file_path);
  ClassFile * class_file = read_class_file();
  pushToClassFileList(class_file);
  return class_file;
}

int run_class_file(ClassFile * class_file) {
  //printf("[DEBUG] Procurando método main em run_class_file\n");
  char * super_name = getNestedString(class_file, class_file->super_class);

  if (strcmp(super_name, "java/lang/Object") != 0) {
    read_file(strcat("exemplos/", strcat(super_name, ".class")));
    ClassFile * super_class_file = read_class_file();
    class_file->super_class_class = super_class_file;
    pushToClassFileList(super_class_file);
  }

  method_info * main_method = get_method(class_file, "main", "([Ljava/lang/String;)V");
  if (main_method == NULL) {
    //printf("[DEBUG] main_method é NULL!\n");
    printf("main method not found\n");
    return -1;
  }
  //printf("[DEBUG] main_method encontrado! Chamando call_method\n");

  int res = call_method(NULL, class_file, main_method, NULL).status;
  //printf("[DEBUG] call_method retornou, status=%d\n", res);
  if (res < 0) {
    printf("Erro ao executar o método main\n");
    return -1;
  }

  //printf("[DEBUG] Fim de run_class_file\n");
  //printf("[DEBUG] run_class_file terminou normalmente, retornando para main\n");
  return 0;
}

method_info * get_method(ClassFile * class_file, char * method_name, char * method_descriptor) {
  for (int i = 0; i < class_file->methods_count; i++) {
    method_info * method = class_file->methods[i];
    char * name = getNestedString(class_file, method->name_index);
    char * descriptor = getNestedString(class_file, method->descriptor_index);
    //printf("[DEBUG] get_method: name=%s, descriptor=%s\n", name, descriptor);
    if (strcmp(method_name, name) == 0 && strcmp(method_descriptor, descriptor) == 0) {
      //printf("[DEBUG] get_method: método encontrado!\n");
      return method;
    }
  }
  return NULL;
}

cp_info * getFromConstantPool(ClassFile * class_file, uint16_t index) {
  return class_file->constant_pool[index - 1];
};

char * getNestedString(ClassFile * class_file, uint16_t index) {
  cp_info * info = getFromConstantPool(class_file, index);
  if (info->tag == 1) {
    return (char*) info->Utf8.bytes;
  }
  return getNestedString(class_file, info->Class.name_index);
}

MethodResponses call_method(Frame * current_frame, ClassFile * class_file, method_info * method, Arguments * arguments) {
  MethodResponses res = {
    .status = 0,
    .value = 0,
  };

  Frame * call_frame = malloc(sizeof(Frame));
  call_frame->next = current_frame;

  attribute_info * code_attribute = NULL;
  //printf("[DEBUG] method->attributes_count = %d\n", method->attributes_count);
  for (int i = 0; i < method->attributes_count; i++) {
    attribute_info * attribute = method->attributes[i];
    char * attr_name = (char *) class_file->constant_pool[attribute->attribute_name_index - 1]->Utf8.bytes;
    //printf("[DEBUG] Atributo %d: %s\n", i, attr_name);
    if (strcmp(attr_name, "Code") == 0){
      code_attribute = attribute;
      //printf("[DEBUG] Encontrou atributo Code!\n");
      break;
    }
  }

  if (code_attribute == NULL) {
    //printf("[DEBUG] Code attribute not found\n");
    res.status = -2;
    return res;
  }

  call_frame->this_class = class_file;
  call_frame->this_method = method;
  call_frame->stack_top = NULL;
  call_frame->stack_size = 0;
  call_frame->local_variables = malloc(sizeof(uint32_t) * code_attribute->Code.max_locals);
  if (arguments != NULL) {
    for (int i = 0; i < arguments->size; i++) {
      call_frame->local_variables[i] = arguments->arguments[i];
    }
  }

  call_frame->pc.position = 0;
  call_frame->pc.buffer = code_attribute->Code.code;
  for (; call_frame->pc.position < code_attribute->Code.code_length;) {
    //printf("[DEBUG] Antes de ler instrução: pc.position=%lu\n", (unsigned long)call_frame->pc.position);
    Instruction instruction = read_instruction_buffer(&call_frame->pc);
    //printf("[DEBUG] Depois de ler instrução: pc.position=%lu\n", (unsigned long)call_frame->pc.position);
    if (!instruction.type || !instruction.type->opcode_function) {
      // Mostra o opcode e a posição do erro
      printf("[ERRO] Opcode inválido: 0x%02x na posição %lu\n", 
        call_frame->pc.buffer[call_frame->pc.position], 
        (unsigned long)call_frame->pc.position);
      printf("[ERRO] Instrução inválida ou não implementada! Encerrando execução do método.\n");
      break;
    }
    int result = instruction.type->opcode_function(call_frame, instruction);
    if (result != 0) {
      //printf("[DEBUG] call_method: retorno especial result=%d\n", result);
      // deal with responses
      if (result == 1) {
        res.value = (uint32_t) 0;
      } else if (result == 2 && call_frame != NULL) {
        //printf("[DEBUG] call_method: tentando acessar pilha do call_frame=%p\n", (void*)call_frame);
        res.value = remove_from_stack(call_frame);
      } else if (result == 3) {
        res.status = 1;
      }
      break;
    }
  }

  while (call_frame->stack_top != NULL) {
    if (call_frame->stack_top->next == NULL) {
      free(call_frame->stack_top);
      call_frame->stack_top = NULL;
      break;
    }
    OperandStack * stack = call_frame->stack_top->next;
    free(call_frame->stack_top);
    call_frame->stack_top = stack;
  }
  free(call_frame->local_variables);

  //printf("[DEBUG] call_method: retornando status=%d, value=%u\n", res.status, res.value);
  return res;
}

Instruction read_instruction_buffer(Buffer * code_buffer) {
  InstructionType * instruction_type = get_instruction_type(u1read_buffer(code_buffer));
  Instruction instruction;
  instruction.type = instruction_type;
  if (instruction_type->operand_count == 0) {
    return instruction;
  }

  instruction.operands = malloc(instruction_type->operand_count * sizeof(uint8_t));
  for (int i = 0; i < instruction_type->operand_count; i++) {
    instruction.operands[i] = u1read_buffer(code_buffer);
  }
  return instruction;
}