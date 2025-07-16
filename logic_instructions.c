#include "logic_instructions.h"


int iand(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = u4_to_int(value1) & u4_to_int(value2);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

int ior(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = u4_to_int(value1) | u4_to_int(value2);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

int jsr(Frame * frame, Instruction instruction) {
  uint32_t return_address = frame->pc.position + 3; // jsr tem 3 bytes (opcode + 2 bytes de offset)
  add_to_stack(frame, int_to_u4(return_address));
  
  int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
  frame->pc.position += offset - 3;

  return 0;
}

int jsr_w(Frame * frame, Instruction instruction) {
  uint32_t return_address = frame->pc.position + 5;
  add_to_stack(frame, int_to_u4(return_address));
  
  // Jump para o offset especificado (4 bytes)
  int32_t offset = u4_to_int((u4)((instruction.operands[0] << 24) | 
                             (instruction.operands[1] << 16) | 
                             (instruction.operands[2] << 8) | 
                             instruction.operands[3]));
  frame->pc.position += offset - 5;

  return 0;
}

int ifnull(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  
  if (value == 0) { // null é representado como 0
    // Constrói offset signed de 16 bits a partir dos bytes
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0; // Continua execução normal
}

int ifnonnull(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  
  if (value != 0) { // não é null
    // Constrói offset signed de 16 bits a partir dos bytes
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0; // Continua execução normal
}

int goto_(Frame * frame, Instruction instruction) {
  //printf("[DEBUG] Entrou no handler GOTO\n");
  int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
  frame->pc.position += offset - 3;
  return 0;
}

int ifeq(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  
  if (u4_to_int(value) == 0) {
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0;
}

int goto_w(Frame * frame, Instruction instruction) {
  // Jump incondicional com offset de 4 bytes
  int32_t offset = u4_to_int((u4)((instruction.operands[0] << 24) | 
                             (instruction.operands[1] << 16) | 
                             (instruction.operands[2] << 8) | 
                             instruction.operands[3]));
  frame->pc.position += offset - 5;

  return 0;
}



int ixor(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = u4_to_int(value1) ^ u4_to_int(value2);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

int inot(Frame * frame, Instruction instruction) {
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = ~u4_to_int(value1);
  add_to_stack(frame, int_to_u4(result));

  return 0;
}

// ========== INSTRUÇÕES LÓGICAS PARA LONG ==========

int land(Frame * frame, Instruction instruction) {
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = u8_to_long(value1) & u8_to_long(value2);
  uint64_t result = long_to_u8(resultl);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int lor(Frame * frame, Instruction instruction) {
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = u8_to_long(value1) | u8_to_long(value2);
  uint64_t result = long_to_u8(resultl);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int lxor(Frame * frame, Instruction instruction) {
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = u8_to_long(value1) ^ u8_to_long(value2);
  uint64_t result = long_to_u8(resultl);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

// ========== INSTRUÇÕES DE COMPARAÇÃO ==========

int if_icmpeq(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  
  if (u4_to_int(value1) == u4_to_int(value2)) {
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0;
}

int if_icmpgt(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  
  if (u4_to_int(value1) > u4_to_int(value2)) {
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0;
}

int if_icmpge(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  
  if (u4_to_int(value1) >= u4_to_int(value2)) {
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0;
}

int if_icmplt(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  
  if (u4_to_int(value1) < u4_to_int(value2)) {
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0;
}

int if_icmple(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  
  if (u4_to_int(value1) <= u4_to_int(value2)) {
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0;
}

int if_icmpne(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  
  if (u4_to_int(value1) != u4_to_int(value2)) {
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0;
}

int if_acmpeq(Frame * frame, Instruction instruction) {
  uint32_t ref2 = remove_from_stack(frame);
  uint32_t ref1 = remove_from_stack(frame);
  
  if (ref1 == ref2) {
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0;
}

int if_acmpne(Frame * frame, Instruction instruction) {
  uint32_t ref2 = remove_from_stack(frame);
  uint32_t ref1 = remove_from_stack(frame);
  
  if (ref1 != ref2) {
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0;
}


int ifne(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  
  if (u4_to_int(value) != 0) {
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0;
}

int ifgt(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  
  if (u4_to_int(value) > 0) {
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0;
}

int ifge(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  
  if (u4_to_int(value) >= 0) {
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0;
}

int iflt(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  
  if (u4_to_int(value) < 0) {
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0;
}

int ifle(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  
  if (u4_to_int(value) <= 0) {
    int16_t offset = u2_to_short((u2)((instruction.operands[0] << 8) | instruction.operands[1]));
    frame->pc.position += offset - 3;
  }
  
  return 0;
}


int lcmp(Frame * frame, Instruction instruction) {
  // Remove value2 (long)
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  
  int64_t val1 = u8_to_long(value1);
  int64_t val2 = u8_to_long(value2);
  
  int32_t result;
  if (val1 > val2) {
    result = 1;
  } else if (val1 == val2) {
    result = 0;
  } else {
    result = -1;
  }
  
  add_to_stack(frame, int_to_u4(result));
  
  return 0;
}
int fcmpl(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  
  float val1 = u4_to_float(value1);
  float val2 = u4_to_float(value2);
  
  int32_t result;
  if (isnan(val1) || isnan(val2)) {
    result = -1; // fcmpl retorna -1 para NaN
  } else if (val1 > val2) {
    result = 1;
  } else if (val1 == val2) {
    result = 0;
  } else {
    result = -1;
  }
  
  add_to_stack(frame, int_to_u4(result));
  
  return 0;
}

int fcmpg(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  
  float val1 = u4_to_float(value1);
  float val2 = u4_to_float(value2);
  
  int32_t result;
  if (isnan(val1) || isnan(val2)) {
    result = 1; // fcmpg retorna 1 para NaN
  } else if (val1 > val2) {
    result = 1;
  } else if (val1 == val2) {
    result = 0;
  } else {
    result = -1;
  }
  
  add_to_stack(frame, int_to_u4(result));
  
  return 0;
}



int dcmpl(Frame * frame, Instruction instruction) {
  // Remove value2 (double)
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  
  // Remove value1 (double)
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  
  double val1 = u8_to_double(value1);
  double val2 = u8_to_double(value2);
  
  int32_t result;
  if (isnan(val1) || isnan(val2)) {
    result = -1; // dcmpl retorna -1 para NaN
  } else if (val1 > val2) {
    result = 1;
  } else if (val1 == val2) {
    result = 0;
  } else {
    result = -1;
  }
  
  add_to_stack(frame, int_to_u4(result));
  
  return 0;
}

int dcmpg(Frame * frame, Instruction instruction) {
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  
  double val1 = u8_to_double(value1);
  double val2 = u8_to_double(value2);
  
  int32_t result;
  if (isnan(val1) || isnan(val2)) {
    result = 1; // dcmpg retorna 1 para NaN
  } else if (val1 > val2) {
    result = 1;
  } else if (val1 == val2) {
    result = 0;
  } else {
    result = -1;
  }
  
  add_to_stack(frame, int_to_u4(result));
  
  return 0;
}
