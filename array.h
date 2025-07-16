/**
 * @file array.h
 * @brief arquivo cabecalho das instrucoes de array basicas da jvm
 * @author Nicolas Paulin
 * @see array.c
 */

#ifndef ARRAY_H
#define ARRAY_H
#include "types.h"
#include "instructions.h"

/**
 * @brief recupera endereco estatico de lista de arrays da jvm
 * @return ponteiro para lista de array
 * @see get_array_list() implemetacao (em array.c)
 */
ArrayList * get_array_list();

/**
 * @brief adiciona um novo array para a lista de arrays da jvm
 * @return a nova quatidade de itens na lista de arrays
 * @param array ponteiro para array que será adicionado a lista de arrays
 * @see add_array() implemetacao (em array.c)
 */
u4 add_array(Array * array);

/**
 * @brief retorna ponteiro para array da lista de arrays jvm através de seu index
 * @return ponteiro para o array
 * @param index numero da posicao do array desejado na lista de arrays
 * @see get_array() implemetacao (em array.c)
 */
Array * get_array(uint32_t index);

/**
 * @brief funcao para criacao de novo array de tipo nao-referencia
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return ponteiro para array criado
 * @see newarray() implemetacao (em array.c)
 */
int newarray(Frame * frame, Instruction instruction);

/**
 * @brief funcao para criacao novo array de referencia
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see anewarray() implemetacao (em array.c)
 */

 int anewarray(Frame * frame, Instruction instruction);

/**
 * @brief funcao que retorna o tamanho do arrau no topo da pilha de frames
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see arraylength() implemetacao (em array.c)
 */
int arraylength(Frame * frame, Instruction instruction);

/**
 * @brief funcao cria novo array bi-dimensional
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see multianewarray() implemetacao (em array.c)
 */
int multianewarray(Frame * frame, Instruction instruction);

#endif