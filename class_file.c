#include "class_file.h"
#include "attribute_info.h" 
#include <stdlib.h>
#include "field_reader.h"
#include "method_info.h"
#include "constant_pool.h"

ClassFile * read_class_file() {
    ClassFile * class_file = malloc(sizeof(ClassFile));
    ClassFileBuffer * class_buffer = get_current_class_file();
    class_buffer->buffer = class_file;
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
    for (u2 i = 0; i < class_file->fields_count; i++) {
        class_file->fields[i] = read_field_info();
    }
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
    return class_file;
}

ClassFileBuffer * get_current_class_file() {
    static ClassFileBuffer class_file;
    return &class_file;
}


void free_class_file(ClassFile* cf) {
    if (!cf) return;

    // 1. Liberta os campos e seus atributos
    if (cf->fields) {
        for (u2 i = 0; i < cf->fields_count; i++) {
            free_field_info(cf->fields[i], cf->constant_pool);
        }
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