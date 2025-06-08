#include "method_info.h"


method_info * read_method_info() {
    method_info * method = malloc(sizeof(method_info));

    method->access_flags = u2read();
    method->name_index = u2read();
    method->descriptor_index = u2read();
    method-> attributes_count = u2read();
    method->attributes = malloc(sizeof(attribute_info *) * class_file->attributes_count);
    for (u2 i = 0; i < class_file->attributes_count; i++) {
        class_file->attributes[i] = read_attribute_info();
    }
}