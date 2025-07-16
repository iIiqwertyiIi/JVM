#include "class_file.h"
#include "attribute_info.h" 
#include <stdlib.h>
#include "field_reader.h"
#include "method_info.h"
#include "constant_pool.h"

ClassFileBuffer * get_class_file_buffer() {
    static ClassFileBuffer class_file = {
        .buffer = NULL,
        .size = 0
    };
    return &class_file;
}


void pushToClassFileList(ClassFile * class_file) {
  ClassFileBuffer * class_file_list = get_class_file_buffer();
  class_file_list->size++;
  if (class_file_list->buffer == NULL) {
    class_file_list->buffer = malloc(sizeof(ClassFile *) * class_file_list->size);
  } else {
    class_file_list->buffer = realloc(class_file_list->buffer, sizeof(ClassFile *) * class_file_list->size);
  }
  class_file_list->buffer[class_file_list->size - 1] = class_file;
}

ClassFile * read_class_file() {
    printf("Lendo arquivo..... \n");
    ClassFile * class_file = malloc(sizeof(ClassFile));
    pushToClassFileList(class_file);
    if (class_file == NULL) {
        printf("Erro: classe não carregada.\n");
        return NULL;
    } 
    class_file->magic = u4read();
    if (class_file->magic != 0xCAFEBABE){
        fprintf(stderr, "Magic incompatível com .class: %x\n", class_file->magic);
        free(class_file);
        return NULL;
    }
    class_file->minor_version = u2read();
    class_file->major_version = u2read();
    class_file->constant_pool_count = u2read();
    class_file->constant_pool = read_constant_pool(class_file->constant_pool_count);
    class_file->access_flags = u2read();
    class_file->this_class = u2read();
    class_file->super_class = u2read();
    class_file->interfaces_count = u2read();
    class_file->interfaces = malloc(sizeof(u2) * class_file->interfaces_count);
    for (u2 i = 0; i < class_file->interfaces_count; i++) {
        class_file->interfaces[i] = u2read();
    }
    class_file->fields_count = u2read();
    class_file->fields = malloc(sizeof(field_info *) * class_file->fields_count);
    class_file->fields = read_all_fields(class_file->fields_count);
    class_file->methods_count = u2read();
    class_file->methods = malloc(sizeof(method_info *) * class_file->methods_count);
    for (u2 i = 0; i < class_file->methods_count; i++) {
        class_file->methods[i] = read_method_info(class_file->constant_pool);
    }
    class_file->attributes_count = u2read();
    class_file->attributes = malloc(sizeof(attribute_info *) * class_file->attributes_count);
    for (u2 i = 0; i < class_file->attributes_count; i++) {
        class_file->attributes[i] = read_attribute_info(class_file->constant_pool);
    }
    setup_static_fields(class_file);
    return class_file;
}



void free_class_file(ClassFile* cf) {
    if (!cf) return;

    // 1. Liberta os campos e seus atributos
    if (cf->fields) {
        free_all_fields(cf->fields, cf->fields_count);
        free(cf->fields);
    }

    // 2. Liberta os métodos e seus atributos
    if (cf->methods) {
        for (u2 i = 0; i < cf->methods_count; i++) {
            free_method_info(cf->methods[i], cf->constant_pool);
        }
        free(cf->methods);
    }

    // 3. Liberta os atributos da própria classe
    if (cf->attributes) {
       for (u2 i = 0; i < cf->attributes_count; i++) {
           free_attribute_info(cf->attributes[i], cf->constant_pool);
       }
       free(cf->attributes);
    }
    
    // 4. Liberta arrays simples
    free(cf->interfaces);
    
    // 5. Liberta o Constant Pool
    free_constant_pool(cf->constant_pool_count, cf->constant_pool);
    
    // 6. liberta a estrutura ClassFile principal
    free(cf);
}

void setup_static_fields(ClassFile * class_file) {
  class_file->static_fields_count = 0;
  class_file->static_fields = NULL;
  for (int i = 0; i < class_file->fields_count; i++) {
    if (class_file->fields[i]->access_flags & 0x8) {
      class_file->static_fields_count++;
      if (class_file->static_fields == NULL) {
        class_file->static_fields = malloc(sizeof(ActiveField *) * class_file->static_fields_count);
      } else {
        class_file->static_fields = realloc(class_file->static_fields, sizeof(ActiveField *) * class_file->static_fields_count);
      }
      class_file->static_fields[class_file->static_fields_count - 1] = malloc(sizeof(ActiveField));
      class_file->static_fields[class_file->static_fields_count - 1]->field = class_file->fields[i];
      class_file->static_fields[class_file->static_fields_count - 1]->value = 0;
    }
  }
}