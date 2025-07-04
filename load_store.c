#include "load_store.h"

int aconst_null(Frame * frame, Instruction instruction) {
    add_to_stack(frame, (u4) NULL);
    return 0;
}

int iconst_m1(Frame * frame, Instruction instruction) {
    add_to_stack(frame, int_to_u4(-1));
    return 0;
}

int iconst_0(Frame * frame, Instruction instruction) {
    add_to_stack(frame, int_to_u4(0));
    return 0;
}

int iconst_1(Frame * frame, Instruction instruction) {
    add_to_stack(frame, int_to_u4(1));
    return 0;
}

int iconst_2(Frame * frame, Instruction instruction) {
    add_to_stack(frame, int_to_u4(2));
    return 0;
}

int iconst_3(Frame * frame, Instruction instruction) {
    add_to_stack(frame, int_to_u4(3));
    return 0;
}

int iconst_4(Frame * frame, Instruction instruction) {
    add_to_stack(frame, int_to_u4(4));
    return 0;
}

int iconst_5(Frame * frame, Instruction instruction) {
    add_to_stack(frame, int_to_u4(5));
    return 0;
}