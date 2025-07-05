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

int lconst_0(Frame * frame, Instruction instruction) {
    u8 ul = long_to_u8(0L);
    u4 high = (u4) (ul & 0xFFFFFFFF);
    u4 low = (u4) (ul >> 32);
    add_to_stack(frame, high);
    add_to_stack(frame, low);
    return 0;
}

int lconst_1(Frame * frame, Instruction instruction) {
    u8 ul = long_to_u8(1L);
    u4 high = (u4) (ul & 0xFFFFFFFF);
    u4 low = (u4) (ul >> 32);
    add_to_stack(frame, high);
    add_to_stack(frame, low);
    return 0;
}

int fconst_0(Frame * frame, Instruction instruction) {
    add_to_stack(frame, float_to_u4(0.0));
    return 0;
}

int fconst_1(Frame * frame, Instruction instruction) {
    add_to_stack(frame, float_to_u4(1.0));
    return 0;
}

int fconst_2(Frame * frame, Instruction instruction) {
    add_to_stack(frame, float_to_u4(2.0));
    return 0;
}

int dconst_0(Frame * frame, Instruction instruction) {
    u8 ud = double_to_u8(0.0);
    u4 high = (u4) (ud & 0xFFFFFFFF);
    u4 low = (u4) (ud >> 32);
    add_to_stack(frame, high);
    add_to_stack(frame, low);
    return 0;
}

int dconst_1(Frame * frame, Instruction instruction) {
    u8 ud = double_to_u8(1.0);
    u4 high = (u4) (ud & 0xFFFFFFFF);
    u4 low = (u4) (ud >> 32);
    add_to_stack(frame, high);
    add_to_stack(frame, low);
    return 0;
}

int bipush(Frame * frame, Instruction instruction) {
    u1 ub = instruction.operands[0];
    int8_t byte = u1_to_byte(ub);
    int32_t b32 = (int32_t) byte;
    add_to_stack(frame, int_to_u4(b32));
    return 0;
}

int sipush(Frame * frame, Instruction instruction) {
    u2 us = (instruction.operands[0] << 8) | instruction.operands[1];
    int16_t sh = u2_to_short(us);
    int32_t s32 = (int32_t) sh;
    add_to_stack(frame, int_to_u4(s32));
    return 0;
}

int ldc(Frame * frame, Instruction instruction) {
    u1 index = instruction.operands[0];
    cp_info * constant = frame->this_class->constant_pool[index - 1];
    switch (constant->tag) {
        case 3:
            add_to_stack(frame, constant->Integer.bytes);
            break;
        case 4:
            add_to_stack(frame, constant->Float.bytes);
            break;
        case 8:
            add_to_stack(frame, constant->String.string_index);
            break;
        default:
            break;
    }
    return 0;
}

int ldc_w(Frame * frame, Instruction instruction) {
    u2 index = (instruction.operands[0] << 8) | instruction.operands[1];
    cp_info * constant = frame->this_class->constant_pool[index - 1];
    switch (constant->tag) {
        case 3:
            add_to_stack(frame, constant->Integer.bytes);
            break;
        case 4:
            add_to_stack(frame, constant->Float.bytes);
            break;
        case 8:
            add_to_stack(frame, constant->String.string_index);
            break;
        default:
            break;
    }
    return 0;
}

int ldc2_w(Frame * frame, Instruction instruction) {
    u2 index = (instruction.operands[0] << 8) | instruction.operands[1];
    cp_info * constant = frame->this_class->constant_pool[index - 1];
    switch (constant->tag) {
        case 5:
            add_to_stack(frame, constant->Long.high_bytes);
            add_to_stack(frame, constant->Long.low_bytes);
            break;
        case 6:
            add_to_stack(frame, constant->Double.high_bytes);
            add_to_stack(frame, constant->Double.low_bytes);
            break;
        default:
            break;
    }
    return 0;
}

int iload(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[instruction.operands[0]]);
    return 0;
}

int lload(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[instruction.operands[0]]);
    add_to_stack(frame, frame->local_variables[instruction.operands[0] + 1]);
    return 0;
}

int fload(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[instruction.operands[0]]);
    return 0;
}

int dload(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[instruction.operands[0]]);
    add_to_stack(frame, frame->local_variables[instruction.operands[0] + 1]);
    return 0;
}

int aload(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[instruction.operands[0]]);
    return 0;
}

int iload_0(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[0]);
    return 0;
}

int iload_1(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[1]);
    return 0;
}

int iload_2(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[2]);
    return 0;
}

int iload_3(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[3]);
    return 0;
}

int lload_0(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[0]);
    add_to_stack(frame, frame->local_variables[1]);
    return 0;
}

int lload_1(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[1]);
    add_to_stack(frame, frame->local_variables[2]);
    return 0;
}

int lload_2(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[2]);
    add_to_stack(frame, frame->local_variables[3]);
    return 0;
}

int lload_3(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[3]);
    add_to_stack(frame, frame->local_variables[4]);
    return 0;
}

int fload_0(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[0]);
    return 0;
}

int fload_1(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[1]);
    return 0;
}

int fload_2(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[2]);
    return 0;
}

int fload_3(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[3]);
    return 0;
}

int dload_0(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[0]);
    add_to_stack(frame, frame->local_variables[1]);
    return 0;
}

int dload_1(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[1]);
    add_to_stack(frame, frame->local_variables[2]);
    return 0;
}

int dload_2(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[2]);
    add_to_stack(frame, frame->local_variables[3]);
    return 0;
}

int dload_3(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[3]);
    add_to_stack(frame, frame->local_variables[4]);
    return 0;
}

int aload_0(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[0]);
    return 0;
}

int aload_1(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[1]);
    return 0;
}

int aload_2(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[2]);
    return 0;
}

int aload_3(Frame * frame, Instruction instruction) {
    add_to_stack(frame, frame->local_variables[3]);
    return 0;
}

int iaload(Frame * frame, Instruction instruction) {

    return 0;
}

int laload(Frame * frame, Instruction instruction) {
    
    return 0;
}

int faload(Frame * frame, Instruction instruction) {
    
    return 0;
}

int daload(Frame * frame, Instruction instruction) {
    
    return 0;
}

int aaload(Frame * frame, Instruction instruction) {
    
    return 0;
}

int baload(Frame * frame, Instruction instruction) {
    
    return 0;
}

int caload(Frame * frame, Instruction instruction) {
    
    return 0;
}

int saload(Frame * frame, Instruction instruction) {
    
    return 0;
}

int istore(Frame * frame, Instruction instruction) {
    frame->local_variables[instruction.operands[0]] = remove_from_stack(frame);
    return 0;
}

int lstore(Frame * frame, Instruction instruction) {
    frame->local_variables[instruction.operands[0] + 1] = remove_from_stack(frame);
    frame->local_variables[instruction.operands[0]] = remove_from_stack(frame);
    return 0;
}

int fstore(Frame * frame, Instruction instruction) {
    frame->local_variables[instruction.operands[0]] = remove_from_stack(frame);
    return 0;
}

int dstore(Frame * frame, Instruction instruction) {
    frame->local_variables[instruction.operands[0] + 1] = remove_from_stack(frame);
    frame->local_variables[instruction.operands[0]] = remove_from_stack(frame);
    return 0;
}

int astore(Frame * frame, Instruction instruction) {
    frame->local_variables[instruction.operands[0]] = remove_from_stack(frame);
    return 0;
}

int istore_0(Frame * frame, Instruction instruction) {
    frame->local_variables[0] = remove_from_stack(frame);
    return 0;
}

int istore_1(Frame * frame, Instruction instruction) {
    frame->local_variables[1] = remove_from_stack(frame);
    return 0;
}

int istore_2(Frame * frame, Instruction instruction) {
    frame->local_variables[2] = remove_from_stack(frame);
    return 0;
}

int istore_3(Frame * frame, Instruction instruction) {
    frame->local_variables[3] = remove_from_stack(frame);
    return 0;
}

int lstore_0(Frame * frame, Instruction instruction) {
    frame->local_variables[1] = remove_from_stack(frame);
    frame->local_variables[0] = remove_from_stack(frame);
    return 0;
}

int lstore_1(Frame * frame, Instruction instruction) {
    frame->local_variables[2] = remove_from_stack(frame);
    frame->local_variables[1] = remove_from_stack(frame);
    return 0;
}

int lstore_2(Frame * frame, Instruction instruction) {
    frame->local_variables[3] = remove_from_stack(frame);
    frame->local_variables[2] = remove_from_stack(frame);
    return 0;
}

int lstore_3(Frame * frame, Instruction instruction) {
    frame->local_variables[4] = remove_from_stack(frame);
    frame->local_variables[3] = remove_from_stack(frame);
    return 0;
}

int fstore_0(Frame * frame, Instruction instruction) {
    frame->local_variables[0] = remove_from_stack(frame);
    return 0;
}

int fstore_1(Frame * frame, Instruction instruction) {
    frame->local_variables[1] = remove_from_stack(frame);
    return 0;
}

int fstore_2(Frame * frame, Instruction instruction) {
    frame->local_variables[2] = remove_from_stack(frame);
    return 0;
}

int fstore_3(Frame * frame, Instruction instruction) {
    frame->local_variables[3] = remove_from_stack(frame);
    return 0;
}

int dstore_0(Frame * frame, Instruction instruction) {
    frame->local_variables[1] = remove_from_stack(frame);
    frame->local_variables[0] = remove_from_stack(frame);
    return 0;
}

int dstore_1(Frame * frame, Instruction instruction) {
    frame->local_variables[2] = remove_from_stack(frame);
    frame->local_variables[1] = remove_from_stack(frame);
    return 0;
}

int dstore_2(Frame * frame, Instruction instruction) {
    frame->local_variables[3] = remove_from_stack(frame);
    frame->local_variables[2] = remove_from_stack(frame);
    return 0;
}

int dstore_3(Frame * frame, Instruction instruction) {
    frame->local_variables[4] = remove_from_stack(frame);
    frame->local_variables[3] = remove_from_stack(frame);
    return 0;
}

int astore_0(Frame * frame, Instruction instruction) {
    frame->local_variables[0] = remove_from_stack(frame);
    return 0;
}

int astore_1(Frame * frame, Instruction instruction) {
    frame->local_variables[1] = remove_from_stack(frame);
    return 0;
}

int astore_2(Frame * frame, Instruction instruction) {
    frame->local_variables[2] = remove_from_stack(frame);
    return 0;
}

int astore_3(Frame * frame, Instruction instruction) {
    frame->local_variables[3] = remove_from_stack(frame);
    return 0;
}

int iastore(Frame * frame, Instruction instruction) {

    return 0;
}

int lastore(Frame * frame, Instruction instruction) {
    
    return 0;
}

int fastore(Frame * frame, Instruction instruction) {
    
    return 0;
}

int dastore(Frame * frame, Instruction instruction) {
    
    return 0;
}

int aastore(Frame * frame, Instruction instruction) {
    
    return 0;
}

int bastore(Frame * frame, Instruction instruction) {
    
    return 0;
}

int castore(Frame * frame, Instruction instruction) {
    
    return 0;
}

int sastore(Frame * frame, Instruction instruction) {
    
    return 0;
}