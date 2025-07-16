#ifndef LOAD_STORE_H
#define LOAD_STORE_H

#include "types.h"
#include "instructions.h"
#include "reader.h"
#include "helper.h"
#include "array.h"
#include "string.h"

int aconst_null(Frame * frame, Instruction instruction);
int iconst_m1(Frame * frame, Instruction instruction);
int iconst_0(Frame * frame, Instruction instruction);
int iconst_1(Frame * frame, Instruction instruction);
int iconst_2(Frame * frame, Instruction instruction);
int iconst_3(Frame * frame, Instruction instruction);
int iconst_4(Frame * frame, Instruction instruction);
int iconst_5(Frame * frame, Instruction instruction);
int lconst_0(Frame * frame, Instruction instruction);
int lconst_1(Frame * frame, Instruction instruction);
int fconst_0(Frame * frame, Instruction instruction);
int fconst_1(Frame * frame, Instruction instruction);
int fconst_2(Frame * frame, Instruction instruction);
int dconst_0(Frame * frame, Instruction instruction);
int dconst_1(Frame * frame, Instruction instruction);
int bipush(Frame * frame, Instruction instruction);
int sipush(Frame * frame, Instruction instruction);
int ldc(Frame * frame, Instruction instruction);
int ldc_w(Frame * frame, Instruction instruction);
int ldc2_w(Frame * frame, Instruction instruction);
int iload(Frame * frame, Instruction instruction);
int lload(Frame * frame, Instruction instruction);
int fload(Frame * frame, Instruction instruction);
int dload(Frame * frame, Instruction instruction);
int aload(Frame * frame, Instruction instruction);
int iload_0(Frame * frame, Instruction instruction);
int iload_1(Frame * frame, Instruction instruction);
int iload_2(Frame * frame, Instruction instruction);
int iload_3(Frame * frame, Instruction instruction);
int lload_0(Frame * frame, Instruction instruction);
int lload_1(Frame * frame, Instruction instruction);
int lload_2(Frame * frame, Instruction instruction);
int lload_3(Frame * frame, Instruction instruction);
int fload_0(Frame * frame, Instruction instruction);
int fload_1(Frame * frame, Instruction instruction);
int fload_2(Frame * frame, Instruction instruction);
int fload_3(Frame * frame, Instruction instruction);
int dload_0(Frame * frame, Instruction instruction);
int dload_1(Frame * frame, Instruction instruction);
int dload_2(Frame * frame, Instruction instruction);
int dload_3(Frame * frame, Instruction instruction);
int aload_0(Frame * frame, Instruction instruction);
int aload_1(Frame * frame, Instruction instruction);
int aload_2(Frame * frame, Instruction instruction);
int aload_3(Frame * frame, Instruction instruction);
int iaload(Frame * frame, Instruction instruction);
int laload(Frame * frame, Instruction instruction);
int faload(Frame * frame, Instruction instruction);
int daload(Frame * frame, Instruction instruction);
int aaload(Frame * frame, Instruction instruction);
int baload(Frame * frame, Instruction instruction);
int caload(Frame * frame, Instruction instruction);
int saload(Frame * frame, Instruction instruction);
int istore(Frame * frame, Instruction instruction);
int lstore(Frame * frame, Instruction instruction);
int fstore(Frame * frame, Instruction instruction);
int dstore(Frame * frame, Instruction instruction);
int astore(Frame * frame, Instruction instruction);
int istore_0(Frame * frame, Instruction instruction);
int istore_1(Frame * frame, Instruction instruction);
int istore_2(Frame * frame, Instruction instruction);
int istore_3(Frame * frame, Instruction instruction);
int lstore_0(Frame * frame, Instruction instruction);
int lstore_1(Frame * frame, Instruction instruction);
int lstore_2(Frame * frame, Instruction instruction);
int lstore_3(Frame * frame, Instruction instruction);
int fstore_0(Frame * frame, Instruction instruction);
int fstore_1(Frame * frame, Instruction instruction);
int fstore_2(Frame * frame, Instruction instruction);
int fstore_3(Frame * frame, Instruction instruction);
int dstore_0(Frame * frame, Instruction instruction);
int dstore_1(Frame * frame, Instruction instruction);
int dstore_2(Frame * frame, Instruction instruction);
int dstore_3(Frame * frame, Instruction instruction);
int astore_0(Frame * frame, Instruction instruction);
int astore_1(Frame * frame, Instruction instruction);
int astore_2(Frame * frame, Instruction instruction);
int astore_3(Frame * frame, Instruction instruction);
int iastore(Frame * frame, Instruction instruction);
int lastore(Frame * frame, Instruction instruction);
int fastore(Frame * frame, Instruction instruction);
int dastore(Frame * frame, Instruction instruction);
int aastore(Frame * frame, Instruction instruction);
int bastore(Frame * frame, Instruction instruction);
int castore(Frame * frame, Instruction instruction);
int sastore(Frame * frame, Instruction instruction);

#endif