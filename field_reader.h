/**
 * @file field_reader.h
 * @brief arquivo cabecalho das instrucoes de leitura e desalocacao de memoria dos field_info da JVM
 * @see field_reader.c
 */

#ifndef FIELD_READER_H
#define FIELD_READER_H
#include "types.h"
#include "reader.h"

 /**
 * @brief Faz leitura e aloca na memória lista de fields presente
 * @param fields_count quantidade de fields
 * @return ponteiro de ponteiro para primeiro item da lista de fields
 * @see read_all_fields() implemetacao (em field_reader.c)
 */
field_info ** read_all_fields(u2 fields_count);

/**
 * @brief Desaloca memoria usada para os fields_info lidos pela JVM
 * @param fields_count quantidade de fields
 * @param fields ponteiro de ponteiro para primeiro item da lista de fields
 * @return ponteiro de ponteiro para primeiro item da lista de constant_pool
 * @see free_all_fields() implemetacao (em field_reader.c)
 */
void free_all_fields(field_info ** fields, u2 fields_count);

#endif