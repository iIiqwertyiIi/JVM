#include "wide.h"

int wide(Frame * frame, Instruction instruction) {
  u1 opcode = u1read_buffer(&frame->pc);
  u2 index, const_;
  u4 value, high, low;

  switch (opcode) {
    case 0x84: // iinc
      index = u2read_buffer(&frame->pc);
      const_ = u2read_buffer(&frame->pc);
      frame->local_variables[index] = int_to_u4(u2_to_short(const_) + u4_to_int(frame->local_variables[index]));
      break;
    case 0x15: // iload
    case 0x17: // fload
    case 0x19: // aload
      index = u2read_buffer(&frame->pc);
      value = frame->local_variables[index];
      add_to_stack(frame, value);
      break;
    case 0x16: // lload
    case 0x18: // dload
      index = u2read_buffer(&frame->pc);
      high = frame->local_variables[index];
      low = frame->local_variables[index + 1];
      add_to_stack(frame, high);
      add_to_stack(frame, low);
      break;
    case 0x36: // istore
    case 0x38: // fstore
    case 0x3a: // astore
      index = u2read_buffer(&frame->pc);
      value = remove_from_stack(frame);
      frame->local_variables[index] = value;
      break;
    case 0x37: // lstore
    case 0x39: // dstore
      index = u2read_buffer(&frame->pc);
      high = remove_from_stack(frame);
      low = remove_from_stack(frame);
      frame->local_variables[index] = high;
      frame->local_variables[index + 1] = low;
      break;
    default:
      printf("Tipo de wide não tratado: %d\n", opcode);
      break;
  }

  return 0;
}