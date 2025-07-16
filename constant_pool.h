/**
 * @file constant_pool.h
 * @brief arquivo cabecalho de leitura e desalocacao de memória da constant_pool
 * @author Ana Paula Nobrega
 * @see constant_pool.c
 */

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

/**
 * @brief Faz leitura e aloca na memória lista de constant_pools presente
 * @param constant_pool_count quantidade de constant_pool
 * @return ponteiro de ponteiro para primeiro item da lista de constant_pool
 * @see read_constant_pool() implemetacao (em constant_pool.c)
 */
cp_info ** read_constant_pool(u2 constant_pool_count);

/**
 * @brief Desaloca memoria usada pela constant_pool lidas pela JVM
 * @param constant_pool_count quantidade de constant_pool
 * @param constant_pool ponteiro de ponteiro para primeiro item da lista de constant_pools
 * @see read_constant_pool() implemetacao (em constant_pool.c)
 */
void free_constant_pool(u2 constant_pool_count, cp_info ** constant_pool);

#endif