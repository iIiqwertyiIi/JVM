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
    return NULL;
}