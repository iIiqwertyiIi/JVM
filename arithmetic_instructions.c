#include "arithmetic_instructions.h"

//precisa do Instruction?
int iadd(Frame * frame) {
    u4 value2 = remove_from_stack(frame);
    u4 value1 = remove_from_stack(frame);
    int32_t a_result = u4_to_int(value1) + u4_to_int(value2);
    add_to_stack(frame, int_to_u4(a_result));
    return 0;
}

int ladd(Frame * frame) {
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

int fadd(Frame * frame) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  float result = u4_to_float(value1) + u4_to_float(value2);
  add_to_stack(frame, float_to_u4(result));

  return 0;
}

int dadd(Frame * frame){
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

int isub(Frame * frame) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  int32_t result = u4_to_int(value1) - u4_to_int(value2);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

int lsub(Frame * frame) {
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

int fsub(Frame * frame) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  float result = u4_to_float(value1) - u4_to_float(value2);
  add_to_stack(frame, float_to_u4(result));

  return 0;
}

int dsub(Frame * frame){
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

int imul(Frame * frame) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  int32_t result = u4_to_int(value1) * u4_to_int(value2);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

int lmul(Frame * frame) {
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

int fmul(Frame * frame) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  float result = u4_to_float(value1) * u4_to_float(value2);
  add_to_stack(frame, float_to_u4(result));

  return 0;
}

int dmul(Frame * frame){
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

int idiv(Frame * frame) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  int32_t result = u4_to_int(value1) / u4_to_int(value2);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

int ldiv(Frame * frame) {
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

int fdiv(Frame * frame) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  float result = u4_to_float(value1) / u4_to_float(value2);
  add_to_stack(frame, float_to_u4(result));

  return 0;
}

int ddiv(Frame * frame){
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

int irem(Frame * frame) {
  u4 value2 = remove_from_stack(frame);
  u4 value1 = remove_from_stack(frame);
  int32_t result = u4_to_int(value1) % u4_to_int(value2);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

int lrem(Frame * frame) {
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

int frem(Frame * frame) {
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

int drem(Frame * frame){
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