#ifndef CLASS_FILE_H
#define CLASS_FILE_H
#include "types.h"
#include "reader.h"
#include "cp_info.h"
#include "field_reader.h"
#include "method_info.h"
#include "constant_pool.h"

ClassFile * read_class_file();
ClassFileBuffer * get_class_file_buffer();
void free_class_file(ClassFile* class_file);
void pushToClassFileList(ClassFile * class_file);

void setup_static_fields(ClassFile * class_file);

#endif