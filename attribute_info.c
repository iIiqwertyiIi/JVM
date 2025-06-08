#include "attribute_info.h"

attribute_info * read_attribute_info() {
    attribute_info * attribute = malloc(sizeof(attribute_info));

    attribute->attribute_name_index = u2read();
    attribute->attribute_length = u4read();
     
    ClassFileBuffer * current_class_file = get_current_class_file();
    cp_info * cp = current_class_file->buffer[class_file->size - 1]->constant_pool[attribute->attribute_name_index - 1];
    if(cp.tag == 1) {
       char* name_cp = cp->Utf8.bytes;
       if(strcmp(name_cp, "ConstantValue") == 0) {
            attribute->ConstantValue.constantvalue_index = u2read();
       }
       else if(strcmp(name_cp, "Code") == 0) {
            attribute->Code.max_stack = u2read();
            attribute->Code.max_locals = u2read();
            attribute->Code.code_length = u4read();

            attribute->Code.code = malloc(attribute->Code.code_length);
            for(u4 k = 0; k < attribute->Code.code_length; k++) {
                attribute->Code.code[k] = u1read();
            }

            attribute->Code.exception_table_length = u2read();
            if (attribute->Code.exception_table_length > 0) {
                attribute->Code.exception_table = malloc(sizeof(exception_table) * attribute->Code.exception_table_length);
                for(u2 k = 0; k < attribute->Code.exception_table_length; k++) {
                    attribute->Code.exception_table[k].start_pc = u2read();
                    attribute->Code.exception_table[k].end_pc = u2read();
                    attribute->Code.exception_table[k].handler_pc = u2read();
                    attribute->Code.exception_table[k].catch_type = u2read();
                }
            } else {
                attribute->Code.exception_table = NULL;
            }
             attribute->Code.attributes_count = u2read();
            attribute->Code.attributes = read_attributes(attribute->Code.attributes_count, constant_pool);
       }
       else if(strcmp(name_cp, "Exceptions") == 0) {
            attribute->Exceptions.exception_index_table = u2read();
              if (attribute->Exceptions.number_of_exceptions > 0) {
                 attribute->Exceptions.exception_index_table = malloc(sizeof(u2) * attribute->Exceptions.number_of_exceptions);
                 for (u2 k = 0; k < attribute->Exceptions.number_of_exceptions; k++) {
                     attribute->Exceptions.exception_index_table[k] = u2read();
                 }
            } else {
                attribute->Exceptions.exception_index_table = NULL;
            }
       }
       else if(strcmp(name_cp, "InnerClasses") == 0) {
            attribute->InnerClasses.number_of_classes = u2read();
              if (attribute->InnerClasses.number_of_classes > 0) {
                 attribute->InnerClasses.classes = malloc(sizeof(classes) * attribute->InnerClasses.number_of_classes);
                 for (u2 k = 0; k < attribute->InnerClasses.number_of_classes; k++) {
                    attribute->InnerClasses.classes[k].inner_class_info_index = u2read();
                    attribute->InnerClasses.classes[k].outer_class_info_index = u2read();
                    attribute->InnerClasses.classes[k].inner_name_index = u2read();
                    attribute->InnerClasses.classes[k].inner_class_access_flags = u2read();
                 }
            } else {
                 attribute->InnerClasses.classes = NULL;
            }
       }
    }
}