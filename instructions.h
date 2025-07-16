/**
 * @file instructions.h
 * @brief arquivo cabecalho das instrucoes de adição e remoção da pilha de frames e retorno de instrução sendo executada
 * @author Nicolas Paulin
 * @see instructions.c
 */

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "types.h"
#include "load_store.h"
#include "arithmetic_instructions.h"
#include "conversions.h"
#include "logic_instructions.h"
#include "object.h"
#include "array.h"
#include "method_invocation.h"
#include "table.h"
#include "return.h"
#include "wide.h"

/**
 * @brief implementacao instrucao nop
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see nop() implemetacao (em instructions.c)
 */
int nop(Frame * frame, Instruction instruction);

/**
 * @brief dado o opcode da instrucao, retornar todas as suas informacoes
 * @details minemonico, funcao em si, opcode, numero de operandos
 * @param opcode codigo opcode 
 * @return ponteiro para instrucao definida pelo opcode
 * @see get_instruction_type() implemetacao (em instructions.c)
 */
InstructionType * get_instruction_type(u1 opcode);

/**
 * @brief Adiciona frame a pilha de frames
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param value 32 bits sendo adicionado a pilha de frame
 * @see add_to_stack() implemetacao (em instructions.c)
 */
void add_to_stack(Frame * frame, u4 value);

/**
 * @brief Faz leitura e aloca na memória lista de constant_pools presente
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @return valor/posicao da pilha atual
 * @see remove_from_stack() implemetacao (em instructions.c)
 */
u4 remove_from_stack(Frame * frame);

/**
 * @brief Instrucao de preenchimento para instrucoes da JVM que nao foram requisitadas implementacao
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see filler() implemetacao (em instructions.c)
 */
int filler(Frame * frame, Instruction instruction);

#endif