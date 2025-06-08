#include "class_file.h"

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
    class_file->constant_pool = malloc(sizeof(cp_info *) * (class_file->constant_pool_count - 1));
    for (u2 i = 0; i < (class_file->constant_pool_count - 1); i++) {
        class_file->constant_pool[i] = read_cp_info();
    }
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
        class_file->methods[i] = read_method_info();
    }
    class_file->attributes_count = u2read();
    class_file->attributes = malloc(sizeof(attribute_info *) * class_file->attributes_count);
    for (u2 i = 0; i < class_file->attributes_count; i++) {
        class_file->attributes[i] = read_attribute_info();
    }
    return class_file;
}

ClassFileBuffer * get_current_class_file() {
    static ClassFileBuffer class_file;
    return &class_file;
}
