/**
 * @file types.h
 * @brief arquivo com funcoes de impressao para jvm no modo leitor-exibido
 * @details impressao baseada na estrutura do JClassLib para visualização dos dados
 * @see output.c
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include "types.h"
#include "class_file.h"
#include "instructions.h"

void print_class_file(ClassFile *class_file);

void print_cp_info(cp_info **cp_info, u2 constant_pool_count);

void print_field_info(field_info **field_info, u2 fields_count);

void print_method_info(method_info **methods, u2 methods_count);

void print_attribute_info(attribute_info **attributes, u2 attribute_count);

#endif // OUTPUT_H