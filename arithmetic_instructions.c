/**
 * @file arithmetic_instructions.c
 * @brief implementacao das instrucoes aritmeticas basicas da jvm
 * 
 * Esse arquivo contém a lógica das funcoes declaradas em arithmetic_instructions.h
 * 
 * @see arithmetic_instructions.h
 */

#include "arithmetic_instructions.h"

int iadd(Frame * frame, Instruction instruction) {
    u4 value2 = remove_from_stack(frame);
    u4 value1 = remove_from_stack(frame);
    int32_t a_result = u4_to_int(value1) + u4_to_int(value2);
    add_to_stack(frame, int_to_u4(a_result));
    return 0;
}

int ladd(Frame * frame, Instruction instruction) {
  u8 value2_low = (u8) remove_from_stack(frame);
  u8 value2_high = (u8) remove_from_stack(frame);
  u8 value2 = value2_high << 32;
  value2 |= value2_low;
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = u8_to_long(value1) + u8_to_long(value2);
  u8 result = long_to_u8(resultl);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int fadd(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  float result = u4_to_float(value1) + u4_to_float(value2);
  add_to_stack(frame, float_to_u4(result));

  return 0;
}

int dadd(Frame * frame, Instruction instruction){
  u8 value2_low = (u8) remove_from_stack(frame);
  u8 value2_high = (u8) remove_from_stack(frame);
  u8 value2 = value2_high << 32;
  value2 |= value2_low;
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  double resultd = u8_to_double(value1) + u8_to_double(value2);
  u8 result = double_to_u8(resultd);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int isub(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  int32_t result = u4_to_int(value1) - u4_to_int(value2);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

int lsub(Frame * frame, Instruction instruction) {
  u8 value2_low = (u8) remove_from_stack(frame);
  u8 value2_high = (u8) remove_from_stack(frame);
  u8 value2 = value2_high << 32;
  value2 |= value2_low;
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = u8_to_long(value1) - u8_to_long(value2);
  u8 result = long_to_u8(resultl);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int fsub(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  float result = u4_to_float(value1) - u4_to_float(value2);
  add_to_stack(frame, float_to_u4(result));

  return 0;
}

int dsub(Frame * frame, Instruction instruction){
  u8 value2_low = (u8) remove_from_stack(frame);
  u8 value2_high = (u8) remove_from_stack(frame);
  u8 value2 = value2_high << 32;
  value2 |= value2_low;
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  double resultd = u8_to_double(value1) - u8_to_double(value2);
  u8 result = double_to_u8(resultd);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int imul(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  int32_t result = u4_to_int(value1) * u4_to_int(value2);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

int lmul(Frame * frame, Instruction instruction) {
  u8 value2_low = (u8) remove_from_stack(frame);
  u8 value2_high = (u8) remove_from_stack(frame);
  u8 value2 = value2_high << 32;
  value2 |= value2_low;
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = u8_to_long(value1) * u8_to_long(value2);
  u8 result = long_to_u8(resultl);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int fmul(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  float result = u4_to_float(value1) * u4_to_float(value2);
  add_to_stack(frame, float_to_u4(result));

  return 0;
}

int dmul(Frame * frame, Instruction instruction){
  u8 value2_low = (u8) remove_from_stack(frame);
  u8 value2_high = (u8) remove_from_stack(frame);
  u8 value2 = value2_high << 32;
  value2 |= value2_low;
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  double resultd = u8_to_double(value1) * u8_to_double(value2);
  u8 result = double_to_u8(resultd);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int idiv(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  int32_t result = u4_to_int(value1) / u4_to_int(value2);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

int ldiv_(Frame * frame, Instruction instruction) {
  u8 value2_low = (u8) remove_from_stack(frame);
  u8 value2_high = (u8) remove_from_stack(frame);
  u8 value2 = value2_high << 32;
  value2 |= value2_low;
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = u8_to_long(value1) / u8_to_long(value2);
  u8 result = long_to_u8(resultl);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int fdiv(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  float result = u4_to_float(value1) / u4_to_float(value2);
  add_to_stack(frame, float_to_u4(result));

  return 0;
}

int ddiv(Frame * frame, Instruction instruction){
  u8 value2_low = (u8) remove_from_stack(frame);
  u8 value2_high = (u8) remove_from_stack(frame);
  u8 value2 = value2_high << 32;
  value2 |= value2_low;
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  double resultd = u8_to_double(value1) / u8_to_double(value2);
  u8 result = double_to_u8(resultd);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int irem(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  int32_t result = u4_to_int(value1) % u4_to_int(value2);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

int lrem(Frame * frame, Instruction instruction) {
  u8 value2_low = (u8) remove_from_stack(frame);
  u8 value2_high = (u8) remove_from_stack(frame);
  u8 value2 = value2_high << 32;
  value2 |= value2_low;
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = u8_to_long(value1) % u8_to_long(value2);
  u8 result = long_to_u8(resultl);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int frem(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  if (u4_to_float(value2) == 0.0f) {
    add_to_stack(frame, value1);
    return 0;
  }
  float result = fmodf(u4_to_float(value1), u4_to_float(value2));
  add_to_stack(frame, float_to_u4(result));

  return 0;
}

int drem(Frame * frame, Instruction instruction){
  u8 value2_low = (u8) remove_from_stack(frame);
  u8 value2_high = (u8) remove_from_stack(frame);
  u8 value2 = value2_high << 32;
  value2 |= value2_low;
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  if (u8_to_double(value2) == 0.0) {
    u4 result_low = (u4) (value1 & 0xFFFFFFFF);
    u4 result_high = (u4) (value1 >> 32);
    add_to_stack(frame, result_high);
    add_to_stack(frame, result_low);
    return 0;
  }
  double resultd = fmod(u8_to_double(value1), u8_to_double(value2));
  u8 result = double_to_u8(resultd);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int ineg(Frame * frame, Instruction instruction) {
  u4 value1 = remove_from_stack(frame);
  int32_t result = - u4_to_int(value1);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

int lneg(Frame * frame, Instruction instruction) {
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = - u8_to_long(value1);
  u8 result = long_to_u8(resultl);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int fneg(Frame * frame, Instruction instruction) {
  u4 value1 = remove_from_stack(frame);
  float result = - u4_to_float(value1);
  add_to_stack(frame, float_to_u4(result));

  return 0;
}

int dneg(Frame * frame, Instruction instruction){
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  double resultd = - u8_to_double(value1);
  u8 result = double_to_u8(resultd);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int ishl(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  int32_t result = u4_to_int(value1) << (u4_to_int(value2) & 0x1f);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

int ishr(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  int32_t result = u4_to_int(value1) >> (u4_to_int(value2) & 0x1f);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

int iushr(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  u4 result = value1 >> (u4_to_int(value2) & 0x1f);
  add_to_stack(frame, result);

  return 0;
}

int lshl(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = u8_to_long(value1) << (u4_to_int(value2) & 0x3f);
  u8 result = long_to_u8(resultl);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int lshr(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = u8_to_long(value1) >> (u4_to_int(value2) & 0x3f);
  u8 result = long_to_u8(resultl);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int lushr(Frame * frame, Instruction instruction) {
  u4 value2 = remove_from_stack(frame);
  u8 value1_low = (u8) remove_from_stack(frame);
  u8 value1_high = (u8) remove_from_stack(frame);
  u8 value1 = value1_high << 32;
  value1 |= value1_low;
  u8 result = value1 >> (u4_to_int(value2) & 0x3f);
  u4 result_low = (u4) (result & 0xFFFFFFFF);
  u4 result_high = (u4) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int iinc(Frame * frame, Instruction instruction) {
  u1 index = instruction.operands[0];
  u1 consti = instruction.operands[1];
  frame->local_variables[index] = int_to_u4((int32_t) u1_to_byte(consti) + u4_to_int(frame->local_variables[index]));

  return 0;
}