/**
 * @file helper.h
 * @brief arquivo cabecalho das funcoes de conversao entre signed e unsigned
 * @author Gabriel Cruz 
 * @see helper.c
 */

#ifndef HELPER_H
#define HELPER_H
#include "types.h"
/**
 * @brief estrutura para convertesao entre uint_8 e byte
 * @see ConverterU1Byte helper.c
 */
  extern union ConverterU1Byte {
    u1 u1;
    int8_t b;
  } converterU1Byte;

/**
 * @brief estrutura para convertesao entre uint_16 e short
 * @see ConverterU2Short helper.c
 */
    extern union ConverterU2Short {
    u2 u2;
    int16_t s;
  } converterU2Short;

/**
 * @brief estrutura para convertesao entre uint_32 e int
 * @see ConverterU4Int helper.c
 */
  extern union ConverterU4Int {
    u4 u4;
    int32_t i;
  } converterU4Int;

/**
 * @brief estrutura para convertesao entre uint_32 e float
 * @see ConverterU4Float helper.c
 */
  extern union ConverterU4Float {
    u4 u4;
    float f;
  } converterU4Float;

/**
 * @brief estrutura para convertesao entre uint_64 e long
 * @see ConverterU8Long helper.c
 */
  extern union ConverterU8Long {
    u8 u8;
    int64_t l;
  } converterU8Long;

/**
 * @brief estrutura para convertesao entre uint_64 e double
 * @see ConverterU8Double helper.c
 */
    extern union ConverterU8Double {
    u8 u8;
    double d;
  } converterU8Double;

/**
 * @brief tranformar uint_8_t em int8_t
 * @param value valor uint_u_t
 * @return valor convertido para int8_t
 * @see u1_to_byte() implemetacao (em helper.c)
 */
int8_t u1_to_byte(u1 value);

/**
 * @brief tranformar int8_t em uint8_t
 * @param value valor int8_t
 * @return valor convertido para uint8_t
 * @see byte_to_u1() implemetacao (em helper.c)
 */
u1 byte_to_u1(int8_t value);

/**
 * @brief tranformar uint16_t em int16_t
 * @param value valor uint16_t
 * @return valor convertido para int16_t
 * @see u2_to_short() implemetacao (em helper.c)
 */
int16_t u2_to_short(u2 value);

/**
 * @brief tranformar int16_t em uint16_t
 * @param value valor int16_t
 * @return valor convertido para uint16_t
 * @see short_to_u2() implemetacao (em helper.c)
 */
u2 short_to_u2(int16_t value);

/**
 * @brief tranformar uint32_t em int32_t
 * @param value valor uint32_t
 * @return valor convertido para int32_t
 * @see u4_to_int() implemetacao (em helper.c)
 */
int32_t u4_to_int(u4 value);

/**
 * @brief tranformar int32_t em uint32_t
 * @param value valor int32_t
 * @return valor convertido para uint32_t
 * @see int_to_u4() implemetacao (em helper.c)
 */
u4 int_to_u4(int32_t value);

/**
 * @brief tranformar uint32_t em float
 * @param value valor uint32_t
 * @return valor convertido para float
 * @see u4_to_float() implemetacao (em helper.c)
 */
float u4_to_float(u4 value);

/**
 * @brief tranformar float em uint32_t
 * @param value valor uint32_t
 * @return valor convertido para float
 * @see float_to_u4() implemetacao (em helper.c)
 */
u4 float_to_u4(float value);

/**
 * @brief tranformar uint64_t em long
 * @param value valor uint64_t
 * @return valor convertido para long
 * @see u8_to_long() implemetacao (em helper.c)
 */
int64_t u8_to_long(u8 value);

/**
 * @brief tranformar int64_t em uint64_t
 * @param value valor int64_t
 * @return valor convertido para uint64_t
 * @see long_to_u8() implemetacao (em helper.c)
 */
u8 long_to_u8(int64_t value);

/**
 * @brief tranformar uint64_t em double
 * @param value valor uint64_t
 * @return valor convertido para double
 * @see u8_to_double() implemetacao (em helper.c)
 */
double u8_to_double(u8 value);

/**
 * @brief tranformar double em uint64_t
 * @param value valor double
 * @return valor convertido para uint64_t
 * @see double_to_u8() implemetacao (em helper.c)
 */
u8 double_to_u8(double value);

#endif