#ifndef FIELD_INFO_H
#define FIELD_INFO_H
#include "types.h"

field_info * read_field_info();

void free_all_fields(field_info ** fields, u2 fields_count);


#endif