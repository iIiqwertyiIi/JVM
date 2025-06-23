#ifndef HELPER_H
#define HELPER_H
#include "types.h"

  extern union ConverterU1Byte {
    u1 u1;
    int8_t b;
  } converterU1Byte;

    extern union ConverterU2Short {
    u2 u2;
    int16_t s;
  } converterU2Short;

  extern union ConverterU4Int {
    u4 u4;
    int32_t i;
  } converterU4Int;

    extern union ConverterU4Float {
    u4 u4;
    float f;
  } converterU4Float;

  extern union ConverterU8Long {
    u8 u8;
    int64_t l;
  } converterU8Long;

    extern union ConverterU8Double {
    u8 u8;
    double d;
  } converterU8Double;


int8_t u1_to_byte(u1 value);
u1 byte_to_u1(int8_t value);
int16_t u2_to_short(u2 value);
u2 short_to_u2(int16_t value);
int32_t u4_to_int(u4 value);
u4 int_to_u4(int32_t value);
float u4_to_float(u4 value);
u4 float_to_u4(float value);
int64_t u8_to_long(u8 value);
u8 long_to_u8(int64_t value);
double u8_to_double(u8 value);
u8 double_to_u8(double value);
#endif