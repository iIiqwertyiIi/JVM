#include "class_file.h"

ClassFile * read_class_file() {
    ClassFile * class_file = malloc(sizeof(ClassFile));
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
    // Leitura dos fields
    class_file->fields_count = u2read();
    class_file->fields = read_all_fields(class_file->fields_count);
    class_file->methods_count = u2read();
    class_file->methods = malloc(sizeof(method_info *) * class_file->methods_count);
    for (u2 i = 0; i < class_file->methods_count; i++) {
        class_file->methods[i] = read_method_info();
    }
    class_file->attributes_count = u2read();
    class_file->attributes = malloc(sizeof(attribute_info *) * class_file->attributes_count);
    for (u2 i = 0; i < class_file->attributes_count; i++) {
        class_file->attributes[i] = read_attribute_info();
    }
    return class_file;
}
#include "class_file.h"

ClassFile * read_class_file() {
    ClassFile * class_file = malloc(sizeof(ClassFile));
    class_file->magic = u4read();
    if (class_file->magic != 0xCAFEBABE){
        fprintf(stderr, "Magic incompatível com .class: %x\n", class_file->magic);
        free(class_file);
        return NULL;
    }
    class_file->minor_version = u2read();
    class_file->major_version = u2read();
    class_file->constant_pool_count = u2read();
    
    // Usa a nova função
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
    
    // Usa a nova função
    class_file->fields = read_all_fields(class_file->fields_count);
    
    class_file->methods_count = u2read();
    class_file->methods = malloc(sizeof(method_info *) * class_file->methods_count);
    for (u2 i = 0; i < class_file->methods_count; i++) {
        class_file->methods[i] = read_method_info();
    }
    class_file->attributes_count = u2read();
    class_file->attributes = malloc(sizeof(attribute_info *) * class_file->attributes_count);
    for (u2 i = 0; i < class_file->attributes_count; i++) {
        class_file->attributes[i] = read_attribute_info();
    }
    return class_file;
}

void free_class_file(ClassFile * class_file) {
    if (class_file == NULL) {
        return;
    }
    
    // Libera o constant pool
    if (class_file->constant_pool != NULL) {
        free_constant_pool(class_file->constant_pool, class_file->constant_pool_count);
    }
    
    // Libera as interfaces
    if (class_file->interfaces != NULL) {
        free(class_file->interfaces);
    }
    
    // Libera os fields
    if (class_file->fields != NULL) {
        free_all_fields(class_file->fields, class_file->fields_count);
    }
    
    // Libera os methods (quando você implementar)
    if (class_file->methods != NULL) {
        for (u2 i = 0; i < class_file->methods_count; i++) {
            free(class_file->methods[i]);
        }
        free(class_file->methods);
    }
    
    // Libera os attributes (quando você implementar)
    if (class_file->attributes != NULL) {
        for (u2 i = 0; i < class_file->attributes_count; i++) {
            free(class_file->attributes[i]);
        }
        free(class_file->attributes);
    }
    
    // Libera a estrutura ClassFile
    free(class_file);
}


