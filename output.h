#ifndef OUTPUT_H
#define OUTPUT_H
#include "types.h"

void print_class_file(ClassFile * class_file);
void print_cp_info(cp_info * cp_info);
void print_field_info(field_info * field_info);
void print_method_info(method_info * method_info);
void print_attribute_info(attribute_info * attribute_info);

#endif