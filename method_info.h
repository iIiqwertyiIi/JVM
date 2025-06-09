#ifndef MEHTOD_INFO_H
#define MEHTOD_INFO_H
#include "types.h"
#include "attribute_info.h"

method_info * read_method_info();

void free_method_info(method_info* method, cp_info** constant_pool);
#endif