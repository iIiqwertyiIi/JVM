#include "table.h"

int table_switch(Frame * frame, Instruction instruction) {
  const u4 start = frame->pc.position - 1;
  const u1 padding = 3 - (start % 4);
  for (int i = 0; i < padding; i++) {
    u1read_buffer(&frame->pc);
  }

  int32_t default_offset = u4_to_int(u4read_buffer(&frame->pc));
  int32_t low = u4_to_int(u4read_buffer(&frame->pc));
  int32_t high = u4_to_int(u4read_buffer(&frame->pc));
  int32_t index = u4_to_int(remove_from_stack(frame));

  TSwtich table_switch = {
    .size = high - low + 1,
    .offsets = malloc(sizeof(u4) * (high - low + 1)),
  };

  for (int i = low; i <= high; i++) {
    table_switch.offsets[i - low] = u4_to_int(u4read_buffer(&frame->pc));
  }

  if (index >= low && index <= high) {
    frame->pc.position = start + table_switch.offsets[index - low];
  } else {
    frame->pc.position = start + default_offset;
  }

  return 0;
}

int lookupswitch(Frame * frame, Instruction instruction) {
  const u4 start = frame->pc.position - 1;
  const u1 padding = 3 - (start % 4);
  for (int i = 0; i < padding; i++) {
    u1read_buffer(&frame->pc);
  }

  int32_t default_offset = u4_to_int(u4read_buffer(&frame->pc));
  u4 npairs = u4read_buffer(&frame->pc);
  int32_t key = u4_to_int(remove_from_stack(frame));

  for (int i = 0; i < npairs; i++) {
    int32_t match = u4_to_int(u4read_buffer(&frame->pc));
    int32_t offset = u4_to_int(u4read_buffer(&frame->pc));
    if (match == key) {
      frame->pc.position = start + offset;
      return 0;
    }
    if (match > key) {
      break;
    }
  }
  frame->pc.position = start + default_offset;

  return 0;
}