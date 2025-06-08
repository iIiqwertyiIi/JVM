#ifndef ATTRIBUTE_INFO_H
#define ATTRIBUTE_INFO_H

#include "types.h"

attribute_info* read_attribute_info(cp_info** constant_pool);

void free_attribute_info(attribute_info* attribute, cp_info** constant_pool);

#endif 
