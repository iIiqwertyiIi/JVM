#include "helper.h"


union ConverterU1Byte converterU1Byte;
union ConverterU2Short converterU2Short;
union ConverterU4Int converterU4Int;
union ConverterU4Float converterU4Float;
union ConverterU8Long converterU8Long;
union ConverterU8Double converterU8Double;


int8_t u1_to_byte(u1 value) {
  converterU1Byte.u1 = value;
  return ConverterU1Byte.b;
}

u1 byte_to_u1(int_8_t value) {
  converterU1Byte.b = value;
  return ConverterU1Byte.u1;
}

int16_t u2_to_short(u2 value) {
    converterU2Short.u2 = value;
    return converterU2Short.s;
}

u2 short_to_u2(int_16_t value) {
    converterU2Short.s = value;
    return converterU2Short.u2;
}

int32_t u4_to_int(u4 value) {
    converterU4Int.u4 = value;
    return converterU4Int.i;
}

u4 int_to_u4(int32_t value) {
    converterU4Int.i = value;
    return converterU4Int.u4;
}

float u4_to_float(u4 value) {
    converterU4Float.u4 = u4;
    return converterU4Float.f;
}

u4 float_to_u4(float value) {
    converterU4Float.f = value;
    return converterU4Float.u4;
}

int64_t u8_to_long(u8 value) {
    converterU8Long.u8 = value;
    return converterU8Long.l;
}

u8 long_to_u8(int64_t value) {
    converterU8Long.l = value;
    return converterU8Long.u8;
}

double u8_to_double(u8 value) {
    converterU8Double.u8 = value;
    return converterU8Double.d;
}

u8 double_to_u8(double value) {
    converterU8Double.d = value;
    return converterU8Double.u8;
}






