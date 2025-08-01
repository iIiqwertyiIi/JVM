/**
 * @file instructions.c
 * @brief implementacao das instrucoes de adição e remoção da pilha de frames e retorno de instrução sendo executada
 * Esse arquivo contém a lógica das funcoes declaradas em instructions.h
 * 
 * @see instructions.h
 */

#include "instructions.h"
#include "logic_instructions.h"
#include "arithmetic_instructions.h"
void add_to_stack(Frame * frame, u4 value) {
  OperandStack * stack = malloc(sizeof(OperandStack));
  frame->stack_size++;
  stack->self = value;
  stack->next = frame->stack_top;
  frame->stack_top = stack;
}

uint32_t remove_from_stack(Frame * frame) {
  OperandStack * stack = frame->stack_top;
  frame->stack_size--;
  uint32_t value = stack->self;
  frame->stack_top = stack->next;
  free(stack);
  return value;
  
}

InstructionType * get_instruction_type(u1 opcode) {
  //printf("[DEBUG] get_instruction_type: opcode=0x%02x\n", opcode);
  //if (opcode == 0xa7) printf("[DEBUG] get_instruction_type: opcode 0xa7 (goto) encontrado!\n");
  static InstructionType instructions[] = {
    //inicio funcoes de load_store
    {0x00, 0, "nop", nop},
    {0x01, 0, "aconst_null", aconst_null},
    {0x02, 0, "iconst_m1", iconst_m1},
    {0x03, 0, "iconst_0", iconst_0},
    {0x04, 0, "iconst_1", iconst_1},
    {0x05, 0, "iconst_2", iconst_2},
    {0x06, 0, "iconst_3", iconst_3},
    {0x07, 0, "iconst_4", iconst_4},
    {0x08, 0, "iconst_5", iconst_5},
    {0x09, 0, "lconst_0", lconst_0},
    {0x0a, 0, "lconst_1", lconst_1},
    {0x0b, 0, "fconst_0", fconst_0},
    {0x0c, 0, "fconst_1", fconst_1},
    {0x0d, 0, "fconst_2", fconst_2},
    {0x0e, 0, "dconst_0", dconst_0},
    {0x0f, 0, "dconst_1", dconst_1},
    {0x10, 1, "bipush", bipush},
    {0x11, 2, "sipush", sipush},
    {0x12, 1, "ldc", ldc},
    {0x13, 2, "ldc_w", ldc_w},
    {0x14, 2, "ldc2_w", ldc2_w},
    {0x15, 1, "iload", iload},
    {0x16, 1, "lload", lload},
    {0x17, 1, "fload", fload},
    {0x18, 1, "dload", dload},
    {0x19, 1, "aload", aload},
    {0x1a, 0, "iload_0", iload_0},
    {0x1b, 0, "iload_1", iload_1},
    {0x1c, 0, "iload_2", iload_2},
    {0x1d, 0, "iload_3", iload_3},
    {0x1e, 0, "lload_0", lload_0},
    {0x1f, 0, "lload_1", lload_1},
    {0x20, 0, "lload_2", lload_2},
    {0x21, 0, "lload_3", lload_3},
    {0x22, 0, "fload_0", fload_0},
    {0x23, 0, "fload_1", fload_1},
    {0x24, 0, "fload_2", fload_2},
    {0x25, 0, "fload_3", fload_3},
    {0x26, 0, "dload_0", dload_0},
    {0x27, 0, "dload_1", dload_1},
    {0x28, 0, "dload_2", dload_2},
    {0x29, 0, "dload_3", dload_3},
    {0x2a, 0, "aload_0", aload_0},
    {0x2b, 0, "aload_1", aload_1},
    {0x2c, 0, "aload_2", aload_2},
    {0x2d, 0, "aload_3", aload_3},
    {0x2e, 0, "iaload", iaload},
    {0x2f, 0, "laload", laload},
    {0x30, 0, "faload", faload},
    {0x31, 0, "daload", daload},
    {0x32, 0, "aaload", aaload},
    {0x33, 0, "baload", baload},
    {0x34, 0, "caload", caload},
    {0x35, 0, "saload", saload},
    {0x36, 1, "istore", istore},
    {0x37, 1, "lstore", lstore},
    {0x38, 1, "fstore", fstore},
    {0x39, 1, "dstore", dstore},
    {0x3a, 1, "astore", astore},
    {0x3b, 0, "istore_0", istore_0},
    {0x3c, 0, "istore_1", istore_1},
    {0x3d, 0, "istore_2", istore_2},
    {0x3e, 0, "istore_3", istore_3},
    {0x3f, 0, "lstore_0", lstore_0},
    {0x40, 0, "lstore_1", lstore_1},
    {0x41, 0, "lstore_2", lstore_2},
    {0x42, 0, "lstore_3", lstore_3},
    {0x43, 0, "fstore_0", fstore_0},
    {0x44, 0, "fstore_1", fstore_1},
    {0x45, 0, "fstore_2", fstore_2},
    {0x46, 0, "fstore_3", fstore_3},
    {0x47, 0, "dstore_0", dstore_0},
    {0x48, 0, "dstore_1", dstore_1},
    {0x49, 0, "dstore_2", dstore_2},
    {0x4a, 0, "dstore_3", dstore_3},
    {0x4b, 0, "astore_0", astore_0},
    {0x4c, 0, "astore_1", astore_1},
    {0x4d, 0, "astore_2", astore_2},
    {0x4e, 0, "astore_3", astore_3},
    {0x4f, 0, "iastore", iastore},
    {0x50, 0, "lastore", lastore},
    {0x51, 0, "fastore", fastore},
    {0x52, 0, "dastore", dastore},
    {0x53, 0, "aastore", aastore},
    {0x54, 0, "bastore", bastore},
    {0x55, 0, "castore", castore},
    {0x56, 0, "sastore", sastore},
    //fim das instruções load_store
    //inicio nao precisam ser implementadas
    {0x57, 0, "pop", filler},
    {0x58, 0, "pop2", filler},
    {0x59, 0, "dup", filler},
    {0x5a, 0, "dup_x1", filler},
    {0x5b, 0, "dup_x2", filler},
    {0x5c, 0, "dup2", filler},
    {0x5d, 0, "dup2_x1", filler},
    {0x5e, 0, "dup2_x2", filler},
    {0x5f, 0, "swap", filler},
    // fim nao precisam ser implementadas
    //inicio instrucoes aritméticas
    {0x60, 0, "iadd", iadd},
    {0x61, 0, "ladd", ladd},
    {0x62, 0, "fadd", fadd},
    {0x63, 0, "dadd", dadd},
    {0x64, 0, "isub", isub},
    {0x65, 0, "lsub", lsub},
    {0x66, 0, "fsub", fsub},
    {0x67, 0, "dsub", dsub},
    {0x68, 0, "imul", imul},
    {0x69, 0, "lmul", lmul},
    {0x6a, 0, "fmul", fmul},
    {0x6b, 0, "dmul", dmul},
    {0x6c, 0, "idiv", idiv},
    {0x6d, 0, "ldiv", ldiv_},
    {0x6e, 0, "fdiv", fdiv},
    {0x6f, 0, "ddiv", ddiv},
    {0x70, 0, "irem", irem},
    {0x71, 0, "lrem", lrem},
    {0x72, 0, "frem", frem},
    {0x73, 0, "drem", drem},
    {0x74, 0, "ineg", ineg},
    {0x75, 0, "lneg", lneg},
    {0x76, 0, "fneg", fneg},
    {0x77, 0, "dneg", dneg},
    {0x78, 0, "ishl", ishl},
    {0x79, 0, "lshl", lshl},
    {0x7a, 0, "ishr", ishr},
    {0x7b, 0, "lshr", lshr},
    {0x7c, 0, "iushr", iushr},
    {0x7d, 0, "lushr", lushr},
    //fim instrucoes aritmeticas
    //inicio instrucoes logicas
    {0x7e, 0, "iand", iand},
    {0x7f, 0, "land", land},
    {0x80, 0, "ior", ior},
    {0x81, 0, "lor",lor},
    {0x82, 0, "ixor", ixor},
    {0x83, 0, "lxor", lxor},    
    //fim instrucoes logicas
    //incremento
    {0x84, 2, "iinc", iinc},
    //inicio instrucoes conversoes
    {0x85, 0, "i2l", i2l},
    {0x86, 0, "i2f", i2f},
    {0x87, 0, "i2d", i2d},
    {0x88, 0, "l2i", l2i},
    {0x89, 0, "l2f", l2f},
    {0x8a, 0, "l2d", l2d},
    {0x8b, 0, "f2i", f2i},
    {0x8c, 0, "f2l", f2l},
    {0x8d, 0, "f2d", f2d},
    {0x8e, 0, "d2i", d2i},
    {0x8f, 0, "d2l", d2l},
    {0x90, 0, "d2f", d2f},
    {0x91, 0, "i2b", i2b},
    {0x92, 0, "i2c", i2c},
    {0x93, 0, "i2s", i2s},
    //fim instrucoes conversion
    //incio das instrucoes comparativas
    {0x94, 0, "lcmp", lcmp},
    {0x95, 0, "fcmpl",fcmpl },
    {0x96, 0, "fcmpg", fcmpg},
    {0x97, 0, "dcmpl", dcmpl},
    {0x98, 0, "dcmpg", dcmpg},
    {0x99, 2, "ifeq", ifeq},
    {0x9a, 2, "ifne", ifne},
    {0x9b, 2, "iflt", iflt},
    {0x9c, 2, "ifge", ifge},
    {0x9d, 2, "ifgt", ifgt},
    {0x9e, 2, "ifle", ifle},
    {0x9f, 2, "if_icmpeq",if_icmpeq },
    {0xa0, 2, "if_icmpne", if_icmpne},
    {0xa1, 2, "if_icmplt", if_icmplt},
    {0xa2, 2, "if_icmpge", if_icmpge},
    {0xa3, 2, "if_icmpgt", if_icmpgt},
    {0xa4, 2, "if_icmple", if_icmple},
    {0xa5, 2, "if_acmpeq", if_acmpeq},
    {0xa6, 2, "if_acmpne", if_acmpne},
    {0xa7, 2, "goto", goto_},
    {0xa8, 2, "jsr", jsr},
    //fim das instrucoes comparativas
    {0xa9, 1, "ret", ret},
    {0xaa, 0, "tableswitch", tableswitch},
    {0xab, 0, "lookupswitch", lookupswitch},
    {0xac, 0, "ireturn", ireturn},
    {0xad, 0, "lreturn", lreturn},
    {0xae, 0, "freturn", freturn},
    {0xaf, 0, "dreturn", dreturn},
    {0xb0, 0, "areturn", areturn},
    {0xb1, 0, "return", return_},
    {0xb2, 2, "getstatic", getstatic},
    {0xb3, 2, "putstatic", putstatic},
    {0xb4, 2, "getfield", getfield},
    {0xb5, 2, "putfield", putfield},
    {0xb6, 2, "invokevirtual", invokevirtual},
    {0xb7, 2, "invokespecial", invokespecial},
    {0xb8, 2, "invokestatic", invokestatic},
    {0xb9, 4, "invokeinterface", invokeinterface},
    {0xba, 4, "invokedynamic", filler},
    {0xbb, 2, "new", new_},
    {0xbc, 1, "newarray", newarray},
    {0xbd, 2, "anewarray", anewarray},
    {0xbe, 0, "arraylength", arraylength},
    //inicio nao precisam ser implementadas
    {0xbf, 0, "athrow", filler},
    {0xc0, 2, "checkcast", filler},
    {0xc1, 2, "instanceof", filler},
    {0xc2, 0, "monitorenter", filler},
    {0xc3, 0, "monitorexit", filler},
    //fim nao precisam ser implementadas
    {0xc4, 0, "wide", wide},
    {0xc5, 3, "multianewarray", multianewarray},
    {0xc6, 2, "ifnull", ifnull},
    {0xc7, 2, "ifnonnull", ifnonnull},
    {0xc8, 4, "goto_w", goto_w},
    {0xc9, 4, "jsr_w", jsr_w},
    // A partir daqui, é apenas para preenchimento, até o 0xfe
    {0xca, 0, "breakpoint", filler},
    {0xcb, 0, "filler1",  filler},
    {0xcc, 0, "filler2",  filler},
    {0xcd, 0, "filler3",  filler},
    {0xce, 0, "filler4",  filler},
    {0xcf, 0, "filler5",  filler},
    {0xd0, 0, "filler6",  filler},
    {0xd1, 0, "filler7",  filler},
    {0xd2, 0, "filler8",  filler},
    {0xd3, 0, "filler9",  filler},
    {0xd4, 0, "filler10", filler},
    {0xd5, 0, "filler11", filler},
    {0xd6, 0, "filler12", filler},
    {0xd7, 0, "filler13", filler},
    {0xd8, 0, "filler14", filler},
    {0xd9, 0, "filler15", filler},
    {0xda, 0, "filler16", filler},
    {0xdb, 0, "filler17", filler},
    {0xdc, 0, "filler18", filler},
    {0xdd, 0, "filler19", filler},
    {0xde, 0, "filler20", filler},
    {0xdf, 0, "filler21", filler},
    {0xe0, 0, "filler22", filler},
    {0xe1, 0, "filler23", filler},
    {0xe2, 0, "filler24", filler},
    {0xe3, 0, "filler25", filler},
    {0xe4, 0, "filler26", filler},
    {0xe5, 0, "filler27", filler},
    {0xe6, 0, "filler28", filler},
    {0xe7, 0, "filler29", filler},
    {0xe8, 0, "filler30", filler},
    {0xe9, 0, "filler31", filler},
    {0xea, 0, "filler32", filler},
    {0xeb, 0, "filler33", filler},
    {0xec, 0, "filler34", filler},
    {0xed, 0, "filler35", filler},
    {0xee, 0, "filler36", filler},
    {0xef, 0, "filler37", filler},
    {0xf0, 0, "filler38", filler},
    {0xf1, 0, "filler39", filler},
    {0xf2, 0, "filler40", filler},
    {0xf3, 0, "filler41", filler},
    {0xf4, 0, "filler42", filler},
    {0xf5, 0, "filler43", filler},
    {0xf6, 0, "filler44", filler},
    {0xf7, 0, "filler45", filler},
    {0xf8, 0, "filler46", filler},
    {0xf9, 0, "filler47", filler},
    {0xfa, 0, "filler48", filler},
    {0xfb, 0, "filler49", filler},
    {0xfc, 0, "filler50", filler},
    {0xfd, 0, "filler51", filler},
    {0xfe, 0, "impdep1",  filler},
    {0xff, 0, "impdep2",  filler},
    // other instructions
  };

  int num_instructions = sizeof(instructions) / sizeof(InstructionType);
  for (int i = 0; i < num_instructions; i++) {
    if (instructions[i].opcode == opcode) {
      return &instructions[i];
    }
  }
  return NULL;
};

int nop(Frame * frame, Instruction instruction) {
  return 0;
}

int filler(Frame * frame, Instruction instruction) {
  return -1;
}
