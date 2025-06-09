#ifndef CONSTANT_POOL_H
#define CONSTANT_POOL_H
#include "types.h"
#include "reader.h"

// Tags do Constant Pool
#define CONSTANT_Class              7
#define CONSTANT_Fieldref           9
#define CONSTANT_Methodref          10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String             8
#define CONSTANT_Integer            3
#define CONSTANT_Float              4
#define CONSTANT_Long               5
#define CONSTANT_Double             6
#define CONSTANT_NameAndType        12
#define CONSTANT_Utf8               1

// Função para ler o constant pool completo
cp_info ** read_constant_pool(u2 constant_pool_count);

void free_constant_pool(u2 count, cp_info** pool);

#endif