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


int if_icmpeq(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  
  if (u4_to_int(value1) == u4_to_int(value2)) {
    // Retorna o offset para fazer o jump
    int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
    return offset;
  }
  
  return 0; // Continua execução normal
}

int if_icmpgt(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  
  if (u4_to_int(value1) > u4_to_int(value2)) {
    int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
    return offset;
  }
  
  return 0;
}

int if_icmpge(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  
  if (u4_to_int(value1) >= u4_to_int(value2)) {
    int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
    return offset;
  }
  
  return 0;
}

int if_icmplt(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  
  if (u4_to_int(value1) < u4_to_int(value2)) {
    int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
    return offset;
  }
  
  return 0;
}

int if_icmple(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  
  if (u4_to_int(value1) <= u4_to_int(value2)) {
    int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
    return offset;
  }
  
  return 0;
}

int if_icmpne(Frame * frame, Instruction instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  
  if (u4_to_int(value1) != u4_to_int(value2)) {
    int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
    return offset;
  }
  
  return 0;
}


int if_acmpeq(Frame * frame, Instruction instruction) {
  uint32_t ref2 = remove_from_stack(frame);
  uint32_t ref1 = remove_from_stack(frame);
  
  if (ref1 == ref2) {
    int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
    return offset;
  }
  
  return 0;
}

int if_acmpne(Frame * frame, Instruction instruction) {
  uint32_t ref2 = remove_from_stack(frame);
  uint32_t ref1 = remove_from_stack(frame);
  
  if (ref1 != ref2) {
    int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
    return offset;
  }
  
  return 0;
}


int goto_(Frame * frame, Instruction instruction) {
  int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
  return offset;
}


int ifeq(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  
  if (u4_to_int(value) == 0) {
    int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
    return offset;
  }
  
  return 0;
}

int ifne(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  
  if (u4_to_int(value) != 0) {
    int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
    return offset;
  }
  
  return 0;
}

int ifgt(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  
  if (u4_to_int(value) > 0) {
    int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
    return offset;
  }
  
  return 0;
}

int ifge(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  
  if (u4_to_int(value) >= 0) {
    int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
    return offset;
  }
  
  return 0;
}

int iflt(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  
  if (u4_to_int(value) < 0) {
    int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
    return offset;
  }
  
  return 0;
}

int ifle(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  
  if (u4_to_int(value) <= 0) {
    int16_t offset = (int16_t)((instruction.operands[0] << 8) | instruction.operands[1]);
    return offset;
  }
  
  return 0;
}