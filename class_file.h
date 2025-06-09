#ifndef CLASS_FILE_H
#define CLASS_FILE_H
#include "types.h"
#include "reader.h"
#include "cp_info.h"
#include "field_reader.h"
#include "method_info.h"
#include "constant_pool.h"

ClassFile * read_class_file();

void free_class_file(ClassFile* class_file);

#endif