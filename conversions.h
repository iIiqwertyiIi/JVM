/**
 * @file helper.h
 * @brief arquivo cabecalho das instrucoes de conversao entre tipos com sinal dos frames na pilha de frame
 * @author Eduardo Volpi
 * @see conversion.c
 */

#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include "types.h"
#include "instructions.h"

/**
 * @brief conversao double para float
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see d2f() implemetacao (em conversion.c)
 */
int d2f(Frame * frame, Instruction instruction);

/**
 * @brief conversao double para int
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see d2i() implemetacao (em conversion.c)
 */
int d2i(Frame * frame, Instruction instruction);

/**
 * @brief conversao double para long
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see d2l() implemetacao (em conversion.c)
 */
int d2l(Frame * frame, Instruction instruction);

/**
 * @brief conversao float para double
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see f2d() implemetacao (em conversion.c)
 */
int f2d(Frame * frame, Instruction instruction);

/**
 * @brief conversao float para int
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see f2i() implemetacao (em conversion.c)
 */
int f2i(Frame * frame, Instruction instruction);

/**
 * @brief conversao float para long
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see f2l() implemetacao (em conversion.c)
 */
int f2l(Frame * frame, Instruction instruction);

/**
 * @brief conversao inteiro para byte
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see i2b() implemetacao (em conversion.c)
 */
int i2b(Frame * frame, Instruction instruction);

/**
 * @brief conversao inteiro para char
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see i2c() implemetacao (em conversion.c)
 */
int i2c(Frame * frame, Instruction instruction);

/**
 * @brief conversao inteiro para double
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see i2d() implemetacao (em conversion.c)
 */
int i2d(Frame * frame, Instruction instruction);

/**
 * @brief conversao inteiro para float
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see i2f() implemetacao (em conversion.c)
 */
int i2f(Frame * frame, Instruction instruction);

/**
 * @brief conversao inteiro para long
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see i2l() implemetacao (em conversion.c)
 */
int i2l(Frame * frame, Instruction instruction);

/**
 * @brief conversao inteiro para short
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see i2s() implemetacao (em conversion.c)
 */
int i2s(Frame * frame, Instruction instruction);

/**
 * @brief conversao inteiro para double
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see i2d() implemetacao (em conversion.c)
 */
int l2d(Frame * frame, Instruction instruction);

/**
 * @brief conversao long para float
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see l2f() implemetacao (em conversion.c)
 */
int l2f(Frame * frame, Instruction instruction);

/**
 * @brief conversao long para inteiro
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see l2i() implemetacao (em conversion.c)
 */
int l2i(Frame * frame, Instruction instruction);

#endif 