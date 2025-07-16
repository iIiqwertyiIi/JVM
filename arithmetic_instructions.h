/**
 * @file arithmetic_instructions.h
 * @brief arquivo cabecalho das instrucoes aritmeticas basicas da jvm
 * @author Tiago Buson
 * @see arithmetic_instructions.c
 */

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <math.h>
#include "types.h"
#include "helper.h"
#include "instructions.h"

/**
 * @brief recupera dois uint_32 da pilha de frame e os soma, converte resultado para int_32 e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see iadd() implemetacao (em arithmetic_instructions.c)
 */
int iadd(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_64 da pilha de frame e os soma, converte resultado para long e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see ladd() implemetacao (em arithmetic_instructions.c)
 */
int ladd(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_64 da pilha de frame e os soma, converte resultado para float e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see fadd() implemetacao (em arithmetic_instructions.c)
 */
int fadd(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_64 da pilha de frame e os soma, converte resultado para double e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see dadd() implemetacao (em arithmetic_instructions.c)
 */
int dadd(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_32 da pilha de frame e os subtrai, converte resultado para inteiro e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see isub() implemetacao (em arithmetic_instructions.c)
 */
int isub(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_64 da pilha de frame e os subtrai, converte resultado para long e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see lsub() implemetacao (em arithmetic_instructions.c)
 */
int lsub(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_32 da pilha de frame e os subtrai, converte resultado para float e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see lsub() implemetacao (em arithmetic_instructions.c)
 */
int fsub(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_64 da pilha de frame e os subtrai, converte resultado para double e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see dsub() implemetacao (em arithmetic_instructions.c)
 */
int dsub(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_32 da pilha de frame e os multiplica, converte resultado para inteiro e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see imul() implemetacao (em arithmetic_instructions.c)
 */
int imul(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_64 da pilha de frame e os multiplica, converte resultado para long e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see lmul() implemetacao (em arithmetic_instructions.c)
 */
int lmul(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_32 da pilha de frame e os multiplica, converte resultado para float e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see fmul() implemetacao (em arithmetic_instructions.c)
 */
int fmul(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_64 da pilha de frame e os multiplica, converte resultado para double e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see dmul() implemetacao (em arithmetic_instructions.c)
 */
int dmul(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_32 da pilha de frame e os divide, converte resultado para inteiro e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see idiv() implemetacao (em arithmetic_instructions.c)
 */
int idiv(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_64 da pilha de frame e os divide, converte resultado para long e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see ldiv() implemetacao (em arithmetic_instructions.c)
 */
int ldiv_(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_32 da pilha de frame e os divide, converte resultado para float e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see fdiv() implemetacao (em arithmetic_instructions.c)
 */
int fdiv(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_64 da pilha de frame e os divide, converte resultado para double e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see ddiv() implemetacao (em arithmetic_instructions.c)
 */
int ddiv(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_32 da pilha de frame e os divide, converte o resto para inteiro e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see irem() implemetacao (em arithmetic_instructions.c)
 */
int irem(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_64 da pilha de frame e os divide, converte resultado para long e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see lrem() implemetacao (em arithmetic_instructions.c)
 */
int lrem(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_32 da pilha de frame e os divide, converte resultado para float e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see frem() implemetacao (em arithmetic_instructions.c)
 */
int frem(Frame * frame, Instruction instruction);

/**
 * @brief recupera dois uint_64 da pilha de frame e os divide, converte resultado para double e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see drem() implemetacao (em arithmetic_instructions.c)
 */
int drem(Frame * frame, Instruction instruction);

/**
 * @brief recupera um uint_32 da pilha de frame e nega seu valor, converte resultado para inteiro e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see ineg() implemetacao (em arithmetic_instructions.c)
 */
int ineg(Frame * frame, Instruction instruction);

/**
 * @brief recupera um uint_64 da pilha de frame e nega seu valor, converte resultado para long e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see lneg() implemetacao (em arithmetic_instructions.c)
 */
int lneg(Frame * frame, Instruction instruction);

/**
 * @brief recupera um uint_32 da pilha de frame e nega seu valor, converte resultado para float e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see fneg() implemetacao (em arithmetic_instructions.c)
 */
int fneg(Frame * frame, Instruction instruction);

/**
 * @brief recupera um uint_64 da pilha de frame e nega seu valor, converte resultado para double e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see dneg() implemetacao (em arithmetic_instructions.c)
 */
int dneg(Frame * frame, Instruction instruction);

/**
 * @brief recupera um uint_32 da pilha de frame faz seu shif left, converte resultado para inteiro e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see ishl() implemetacao (em arithmetic_instructions.c)
 */
int ishl(Frame * frame, Instruction instruction);

/**
 * @brief recupera um uint_64 da pilha de frame faz seu shif left, converte resultado para long e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see lshl() implemetacao (em arithmetic_instructions.c)
 */
int lshl(Frame * frame, Instruction instruction);

/**
 * @brief recupera um uint_32 da pilha de frame faz seu shif right, converte resultado para inteiro e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see ishr() implemetacao (em arithmetic_instructions.c)
 */
int ishr(Frame * frame, Instruction instruction);

/**
 * @brief recupera um uint_64 da pilha de frame faz seu shif right, converte resultado para long e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see lshl() implemetacao (em arithmetic_instructions.c)
 */
int lshr(Frame * frame, Instruction instruction);

/**
 * @brief recupera um uint_32 da pilha de frame faz seu shif right, converte resultado para inteiro sem sinal e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see iushr() implemetacao (em arithmetic_instructions.c)
 */
int iushr(Frame * frame, Instruction instruction);

/**
 * @brief recupera um uint_64 da pilha de frame faz seu shif right, converte resultado para long sem sinal e adiciona-o a pilha
 * @param frame ponteiro para o frame que esta sendo executado pilha de frames
 * @param instruction instrucao da jvm sendo executada
 * @return 0 indicando sucesso da operacao
 * @see lushr() implemetacao (em arithmetic_instructions.c)
 */
int lushr(Frame * frame, Instruction instruction);

int iinc(Frame * frame, Instruction instruction);



#endif // ARITHMETIC_H