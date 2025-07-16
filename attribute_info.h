/**
 * @file attribute_info.h
 * @brief arquivo cabecalho das instrucoes de leitura e desalocacao de memoria dos attribute_info
 * @author Eduardo Volpi
 * @see attribute_info.c
 */

#ifndef ATTRIBUTE_INFO_H
#define ATTRIBUTE_INFO_H

#include "types.h"

/**
 * @brief Faz leitura e aloca na memória o attribute_info presente na constant_pool
 * @param constant_pool ponteiro de ponteiro da constant pool do tipo cp_info 
 * @return ponteiro para attribute_info
 * @see read_attribute_info() implemetacao (em attribute_info.c)
 */
attribute_info* read_attribute_info(cp_info** constant_pool);

/**
 * @brief faz a desalocacao de memoria do attribute info dado sua constant pool
 * @param attribute ponteiro para attribute_info
 * @param constant_pool ponteiro de ponteiro para constant_pool do tipo cp_info
 * @see free_attribute_info() implemetacao (em attribute_info.c)
 */
void free_attribute_info(attribute_info* attribute, cp_info** constant_pool);

#endif 
