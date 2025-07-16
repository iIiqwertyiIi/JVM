#include "return.h"

int ret(Frame * frame, Instruction instruction) {
    u1 index = instruction.operands[0];
    frame->pc.position = frame->local_variables[index] - 1;
    return 0;
}

int ireturn(Frame * frame, Instruction instruction) {
    return 2;
}

int lreturn(Frame * frame, Instruction instruction) {
    u4 low = remove_from_stack(frame);
    u4 high = remove_from_stack(frame);
    add_to_stack(frame->next, high);
    add_to_stack(frame, low);
    return 2;
}

int freturn(Frame * frame, Instruction instruction) {
    return 2;
}

int dreturn(Frame * frame, Instruction instruction) {
    u4 low = remove_from_stack(frame);
    u4 high = remove_from_stack(frame);
    add_to_stack(frame->next, high);
    add_to_stack(frame, low);
    return 2;
}

int areturn(Frame * frame, Instruction instruction){
    return 2;
}

int return_(Frame * frame, Instruction instruction) {
    return 3;
}
