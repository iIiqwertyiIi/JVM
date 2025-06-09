#ifndef FIELD_INFO_H
#define FIELD_INFO_H
#include "types.h"

field_info * read_field_info();
void free_field_info(field_info* field, cp_info** constant_pool);
#endif