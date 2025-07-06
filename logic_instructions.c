#include "logic_instructions.h"
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>


void push_int(FrameStack* frame_stack, int32_t value) {
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Erro: Frame stack inválido\n");
        return;
    }
    
    Frame* current_frame = frame_stack->top_frame;
    OperandStack* new_operand = (OperandStack*)malloc(sizeof(OperandStack));
    
    if (!new_operand) {
        printf("Erro: Falha ao alocar memória para operando\n");
        return;
    }
    
    new_operand->self = int_to_u4(value);
    new_operand->next = current_frame->stack_top;
    current_frame->stack_top = new_operand;
    current_frame->stack_size++;
    
    printf("DEBUG: Push int %d (como u4: %u)\n", value, new_operand->self);
}

int32_t pop_int(FrameStack* frame_stack) {
    if (!frame_stack || !frame_stack->top_frame || !frame_stack->top_frame->stack_top) {
        printf("Erro: Tentativa de pop em pilha vazia\n");
        return 0;
    }
    
    Frame* current_frame = frame_stack->top_frame;
    OperandStack* top = current_frame->stack_top;
    u4 u_value = top->self;
    
    current_frame->stack_top = top->next;
    current_frame->stack_size--;
    free(top);
    
    int32_t value = u4_to_int(u_value);
    printf("DEBUG: Pop int %d (era u4: %u)\n", value, u_value);
    
    return value;
}

void push_ref(FrameStack* frame_stack, u4 ref) {
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Erro: Frame stack inválido\n");
        return;
    }
    
    Frame* current_frame = frame_stack->top_frame;
    OperandStack* new_operand = (OperandStack*)malloc(sizeof(OperandStack));
    
    if (!new_operand) {
        printf("Erro: Falha ao alocar memória para operando\n");
        return;
    }
    
    new_operand->self = ref;
    new_operand->next = current_frame->stack_top;
    current_frame->stack_top = new_operand;
    current_frame->stack_size++;
    
    printf("DEBUG: Push ref %u\n", ref);
}

u4 pop_ref(FrameStack* frame_stack) {
    if (!frame_stack || !frame_stack->top_frame || !frame_stack->top_frame->stack_top) {
        printf("Erro: Tentativa de pop em pilha vazia\n");
        return 0;
    }
    
    Frame* current_frame = frame_stack->top_frame;
    OperandStack* top = current_frame->stack_top;
    u4 ref = top->self;
    
    current_frame->stack_top = top->next;
    current_frame->stack_size--;
    free(top);
    
    printf("DEBUG: Pop ref %u\n", ref);
    return ref;
}


void instruction_ixor(FrameStack* frame_stack) {
    printf("Executando IXOR\n");
    
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Erro: Frame stack inválido\n");
        return;
    }
    
    // Verificar se há pelo menos 2 elementos na pilha
    if (frame_stack->top_frame->stack_size < 2) {
        printf("Erro: Pilha insuficiente para IXOR (precisa de 2 elementos)\n");
        return;
    }
    
    int32_t value2 = pop_int(frame_stack);
    int32_t value1 = pop_int(frame_stack);
    int32_t result = value1 ^ value2;
    
    push_int(frame_stack, result);
    
    printf("IXOR: %d ^ %d = %d\n", value1, value2, result);
}

void instruction_ior(FrameStack* frame_stack) {
    printf("Executando IOR\n");
    
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Erro: Frame stack inválido\n");
        return;
    }
    
    // Verificar se há pelo menos 2 elementos na pilha
    if (frame_stack->top_frame->stack_size < 2) {
        printf("Erro: Pilha insuficiente para IOR (precisa de 2 elementos)\n");
        return;
    }
    
    int32_t value2 = pop_int(frame_stack);
    int32_t value1 = pop_int(frame_stack);
    int32_t result = value1 | value2;
    
    push_int(frame_stack, result);
    
    printf("IOR: %d | %d = %d\n", value1, value2, result);
}

void instruction_iand(FrameStack* frame_stack) {
    printf("Executando IAND\n");
    
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Erro: Frame stack inválido\n");
        return;
    }
    
    if (frame_stack->top_frame->stack_size < 2) {
        printf("Erro: Pilha insuficiente para IAND (precisa de 2 elementos)\n");
        return;
    }
    
    int32_t value2 = pop_int(frame_stack);
    int32_t value1 = pop_int(frame_stack);
    int32_t result = value1 & value2;
    
    push_int(frame_stack, result);
    
    printf("IAND: %d & %d = %d\n", value1, value2, result);
}

void instruction_inot(FrameStack* frame_stack) {
    printf("Executando INOT\n");
    
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Erro: Frame stack inválido\n");
        return;
    }
    
    // Verificar se há pelo menos 1 elemento na pilha
    if (frame_stack->top_frame->stack_size < 1) {
        printf("Erro: Pilha insuficiente para INOT (precisa de 1 elemento)\n");
        return;
    }
    
    int32_t value = pop_int(frame_stack);
    int32_t result = ~value;
    
    push_int(frame_stack, result);
    
    printf("INOT: ~%d = %d\n", value, result);
}


void instruction_if_icmpeq(FrameStack* frame_stack, int16_t branch_offset) {
    printf("Executando IF_ICMPEQ (offset: %d)\n", branch_offset);
    
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Erro: Frame stack inválido\n");
        return;
    }
    
    if (frame_stack->top_frame->stack_size < 2) {
        printf("Erro: Pilha insuficiente para IF_ICMPEQ\n");
        return;
    }
    
    int32_t value2 = pop_int(frame_stack);
    int32_t value1 = pop_int(frame_stack);
    
    if (value1 == value2) {
        frame_stack->top_frame->pc.position += branch_offset;
        printf("IF_ICMPEQ: %d == %d → SALTANDO para PC+%d (nova posição: %lu)\n", 
               value1, value2, branch_offset, frame_stack->top_frame->pc.position);
    } else {
        printf("IF_ICMPEQ: %d != %d → NÃO SALTANDO\n", value1, value2);
    }
}

void instruction_if_icmpne(FrameStack* frame_stack, int16_t branch_offset) {
    printf("Executando IF_ICMPNE (offset: %d)\n", branch_offset);
    
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Erro: Frame stack inválido\n");
        return;
    }
    
    if (frame_stack->top_frame->stack_size < 2) {
        printf("Erro: Pilha insuficiente para IF_ICMPNE\n");
        return;
    }
    
    int32_t value2 = pop_int(frame_stack);
    int32_t value1 = pop_int(frame_stack);
    
    if (value1 != value2) {
        frame_stack->top_frame->pc.position += branch_offset;
        printf("IF_ICMPNE: %d != %d → SALTANDO para PC+%d (nova posição: %lu)\n", 
               value1, value2, branch_offset, frame_stack->top_frame->pc.position);
    } else {
        printf("IF_ICMPNE: %d == %d → NÃO SALTANDO\n", value1, value2);
    }
}

void instruction_if_icmplt(FrameStack* frame_stack, int16_t branch_offset) {
    printf("Executando IF_ICMPLT (offset: %d)\n", branch_offset);
    
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Erro: Frame stack inválido\n");
        return;
    }
    
    if (frame_stack->top_frame->stack_size < 2) {
        printf("Erro: Pilha insuficiente para IF_ICMPLT\n");
        return;
    }
    
    int32_t value2 = pop_int(frame_stack);
    int32_t value1 = pop_int(frame_stack);
    
    if (value1 < value2) {
        frame_stack->top_frame->pc.position += branch_offset;
        printf("IF_ICMPLT: %d < %d → SALTANDO para PC+%d (nova posição: %lu)\n", 
               value1, value2, branch_offset, frame_stack->top_frame->pc.position);
    } else {
        printf("IF_ICMPLT: %d >= %d → NÃO SALTANDO\n", value1, value2);
    }
}

void instruction_if_icmpge(FrameStack* frame_stack, int16_t branch_offset) {
    printf("Executando IF_ICMPGE (offset: %d)\n", branch_offset);
    
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Erro: Frame stack inválido\n");
        return;
    }
    
    if (frame_stack->top_frame->stack_size < 2) {
        printf("Erro: Pilha insuficiente para IF_ICMPGE\n");
        return;
    }
    
    int32_t value2 = pop_int(frame_stack);
    int32_t value1 = pop_int(frame_stack);
    
    if (value1 >= value2) {
        frame_stack->top_frame->pc.position += branch_offset;
        printf("IF_ICMPGE: %d >= %d → SALTANDO para PC+%d (nova posição: %lu)\n", 
               value1, value2, branch_offset, frame_stack->top_frame->pc.position);
    } else {
        printf("IF_ICMPGE: %d < %d → NÃO SALTANDO\n", value1, value2);
    }
}

void instruction_if_icmpgt(FrameStack* frame_stack, int16_t branch_offset) {
    printf("Executando IF_ICMPGT (offset: %d)\n", branch_offset);
    
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Erro: Frame stack inválido\n");
        return;
    }
    
    if (frame_stack->top_frame->stack_size < 2) {
        printf("Erro: Pilha insuficiente para IF_ICMPGT\n");
        return;
    }
    
    int32_t value2 = pop_int(frame_stack);
    int32_t value1 = pop_int(frame_stack);
    
    if (value1 > value2) {
        frame_stack->top_frame->pc.position += branch_offset;
        printf("IF_ICMPGT: %d > %d → SALTANDO para PC+%d (nova posição: %lu)\n", 
               value1, value2, branch_offset, frame_stack->top_frame->pc.position);
    } else {
        printf("IF_ICMPGT: %d <= %d → NÃO SALTANDO\n", value1, value2);
    }
}

void instruction_if_icmple(FrameStack* frame_stack, int16_t branch_offset) {
    printf("Executando IF_ICMPLE (offset: %d)\n", branch_offset);
    
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Erro: Frame stack inválido\n");
        return;
    }
    
    if (frame_stack->top_frame->stack_size < 2) {
        printf("Erro: Pilha insuficiente para IF_ICMPLE\n");
        return;
    }
    
    int32_t value2 = pop_int(frame_stack);
    int32_t value1 = pop_int(frame_stack);
    
    if (value1 <= value2) {
        frame_stack->top_frame->pc.position += branch_offset;
        printf("IF_ICMPLE: %d <= %d → SALTANDO para PC+%d (nova posição: %lu)\n", 
               value1, value2, branch_offset, frame_stack->top_frame->pc.position);
    } else {
        printf("IF_ICMPLE: %d > %d → NÃO SALTANDO\n", value1, value2);
    }
}

// ========================= COMPARAÇÃO DE REFERÊNCIAS =========================

void instruction_if_acmpeq(FrameStack* frame_stack, int16_t branch_offset) {
    printf("Executando IF_ACMPEQ (offset: %d)\n", branch_offset);
    
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Erro: Frame stack inválido\n");
        return;
    }
    
    if (frame_stack->top_frame->stack_size < 2) {
        printf("Erro: Pilha insuficiente para IF_ACMPEQ\n");
        return;
    }
    
    u4 ref2 = pop_ref(frame_stack);
    u4 ref1 = pop_ref(frame_stack);
    
    if (ref1 == ref2) {
        frame_stack->top_frame->pc.position += branch_offset;
        printf("IF_ACMPEQ: ref1(%u) == ref2(%u) → SALTANDO para PC+%d (nova posição: %lu)\n", 
               ref1, ref2, branch_offset, frame_stack->top_frame->pc.position);
    } else {
        printf("IF_ACMPEQ: ref1(%u) != ref2(%u) → NÃO SALTANDO\n", ref1, ref2);
    }
}

void instruction_if_acmpne(FrameStack* frame_stack, int16_t branch_offset) {
    printf("Executando IF_ACMPNE (offset: %d)\n", branch_offset);
    
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Erro: Frame stack inválido\n");
        return;
    }
    
    if (frame_stack->top_frame->stack_size < 2) {
        printf("Erro: Pilha insuficiente para IF_ACMPNE\n");
        return;
    }
    
    u4 ref2 = pop_ref(frame_stack);
    u4 ref1 = pop_ref(frame_stack);
    
    if (ref1 != ref2) {
        frame_stack->top_frame->pc.position += branch_offset;
        printf("IF_ACMPNE: ref1(%u) != ref2(%u) → SALTANDO para PC+%d (nova posição: %lu)\n", 
               ref1, ref2, branch_offset, frame_stack->top_frame->pc.position);
    } else {
        printf("IF_ACMPNE: ref1(%u) == ref2(%u) → NÃO SALTANDO\n", ref1, ref2);
    }
}


int execute_instruction(FrameStack* frame_stack, u1 opcode, u1* bytecode, u8* pc) {
    printf("\n--- Executando instrução 0x%02x na posição %lu ---\n", opcode, *pc);
    
    switch (opcode) {
        case IXOR:
            instruction_ixor(frame_stack);
            break;
            
        case IOR:
            instruction_ior(frame_stack);
            break;
            
        case IAND:
            instruction_iand(frame_stack);
            break;
            
        case INOT:
            instruction_inot(frame_stack);
            break;
            
        case IF_ICMPEQ: {
            // Ler offset de 2 bytes
            int16_t offset = (int16_t)((bytecode[*pc + 1] << 8) | bytecode[*pc + 2]);
            *pc += 2; // Avançar PC pelos 2 bytes do offset
            instruction_if_icmpeq(frame_stack, offset);
            break;
        }
        
        case IF_ICMPNE: {
            int16_t offset = (int16_t)((bytecode[*pc + 1] << 8) | bytecode[*pc + 2]);
            *pc += 2;
            instruction_if_icmpne(frame_stack, offset);
            break;
        }
        
        case IF_ICMPLT: {
            int16_t offset = (int16_t)((bytecode[*pc + 1] << 8) | bytecode[*pc + 2]);
            *pc += 2;
            instruction_if_icmplt(frame_stack, offset);
            break;
        }
        
        case IF_ICMPGE: {
            int16_t offset = (int16_t)((bytecode[*pc + 1] << 8) | bytecode[*pc + 2]);
            *pc += 2;
            instruction_if_icmpge(frame_stack, offset);
            break;
        }
        
        case IF_ICMPGT: {
            int16_t offset = (int16_t)((bytecode[*pc + 1] << 8) | bytecode[*pc + 2]);
            *pc += 2;
            instruction_if_icmpgt(frame_stack, offset);
            break;
        }
        
        case IF_ICMPLE: {
            int16_t offset = (int16_t)((bytecode[*pc + 1] << 8) | bytecode[*pc + 2]);
            *pc += 2;
            instruction_if_icmple(frame_stack, offset);
            break;
        }
        
        case IF_ACMPEQ: {
            int16_t offset = (int16_t)((bytecode[*pc + 1] << 8) | bytecode[*pc + 2]);
            *pc += 2;
            instruction_if_acmpeq(frame_stack, offset);
            break;
        }
        
        case IF_ACMPNE: {
            int16_t offset = (int16_t)((bytecode[*pc + 1] << 8) | bytecode[*pc + 2]);
            *pc += 2;
            instruction_if_acmpne(frame_stack, offset);
            break;
        }
        
        default:
            printf("Erro: Instrução 0x%02x não implementada\n", opcode);
            return -1;
    }
    
    printf("--- Instrução 0x%02x concluída ---\n\n", opcode);
    return 0;
}


void print_operand_stack(FrameStack* frame_stack, int max_elements) {
    if (!frame_stack || !frame_stack->top_frame) {
        printf("Stack: [vazia ou inválida]\n");
        return;
    }
    
    Frame* current_frame = frame_stack->top_frame;
    OperandStack* current = current_frame->stack_top;
    
    printf("Stack (tamanho: %u): [", current_frame->stack_size);
    
    for (int i = 0; i < max_elements && current; i++) {
        if (i > 0) printf(", ");
        printf("%u", current->self);
        current = current->next;
    }
    
    if (current && max_elements < (int)current_frame->stack_size) {
        printf(", ...");
    }
    
    printf("]\n");
}