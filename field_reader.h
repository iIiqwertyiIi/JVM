#ifndef FIELD_READER_H
#define FIELD_READER_H
#include "types.h"
#include "reader.h"

// Função para ler todos os fields
field_info ** read_all_fields(u2 fields_count);

// Função para liberar a memória dos fields
void free_all_fields(field_info ** fields, u2 fields_count);

#endif