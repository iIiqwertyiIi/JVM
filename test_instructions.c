#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"

int main() {
    printf("=== Teste do Sistema de Instruções ===\n\n");
    
    // Teste 1: Verificar se as instruções invoke estão registradas
    printf("1. Verificando instruções invoke no sistema:\n");
    
    // Testa invokevirtual (0xb6)
    InstructionType* inv_virtual = get_instruction_type(0xb6);
    if (inv_virtual && inv_virtual->mnemonic) {
        printf("   ✓ invokevirtual (0xb6): %s\n", inv_virtual->mnemonic);
        printf("      - Operandos: %d\n", inv_virtual->operand_count);
        printf("      - Função: %p\n", (void*)inv_virtual->opcode_function);
    } else {
        printf("   ✗ invokevirtual (0xb6): NÃO ENCONTRADO\n");
    }
    
    // Testa invokespecial (0xb7)
    InstructionType* inv_special = get_instruction_type(0xb7);
    if (inv_special && inv_special->mnemonic) {
        printf("   ✓ invokespecial (0xb7): %s\n", inv_special->mnemonic);
        printf("      - Operandos: %d\n", inv_special->operand_count);
        printf("      - Função: %p\n", (void*)inv_special->opcode_function);
    } else {
        printf("   ✗ invokespecial (0xb7): NÃO ENCONTRADO\n");
    }
    
    // Testa invokestatic (0xb8)
    InstructionType* inv_static = get_instruction_type(0xb8);
    if (inv_static && inv_static->mnemonic) {
        printf("   ✓ invokestatic (0xb8): %s\n", inv_static->mnemonic);
        printf("      - Operandos: %d\n", inv_static->operand_count);
        printf("      - Função: %p\n", (void*)inv_static->opcode_function);
    } else {
        printf("   ✗ invokestatic (0xb8): NÃO ENCONTRADO\n");
    }
    
    // Testa invokeinterface (0xb9)
    InstructionType* inv_interface = get_instruction_type(0xb9);
    if (inv_interface && inv_interface->mnemonic) {
        printf("   ✓ invokeinterface (0xb9): %s\n", inv_interface->mnemonic);
        printf("      - Operandos: %d\n", inv_interface->operand_count);
        printf("      - Função: %p\n", (void*)inv_interface->opcode_function);
    } else {
        printf("   ✗ invokeinterface (0xb9): NÃO ENCONTRADO\n");
    }
    
    // Teste 2: Verificar outras instruções para comparação
    printf("\n2. Verificando outras instruções para comparação:\n");
    
    // Testa nop (0x00)
    InstructionType* nop_inst = get_instruction_type(0x00);
    if (nop_inst && nop_inst->mnemonic) {
        printf("   ✓ nop (0x00): %s\n", nop_inst->mnemonic);
    } else {
        printf("   ✗ nop (0x00): NÃO ENCONTRADO\n");
    }
    
    // Testa getstatic (0xb2)
    InstructionType* getstatic_inst = get_instruction_type(0xb2);
    if (getstatic_inst && getstatic_inst->mnemonic) {
        printf("   ✓ getstatic (0xb2): %s\n", getstatic_inst->mnemonic);
    } else {
        printf("   ✗ getstatic (0xb2): NÃO ENCONTRADO\n");
    }
    
    // Teste 3: Verificar instruções inválidas
    printf("\n3. Verificando instruções inválidas:\n");
    
    // Testa opcode inválido (0xff)
    InstructionType* invalid_inst = get_instruction_type(0xff);
    if (invalid_inst && invalid_inst->mnemonic) {
        printf("   - Opcode 0xff: %s\n", invalid_inst->mnemonic);
    } else {
        printf("   - Opcode 0xff: NÃO ENCONTRADO (esperado)\n");
    }
    
    printf("\n=== Resultado do Teste ===\n");
    int total_invoke = 0;
    if (inv_virtual && inv_virtual->mnemonic) total_invoke++;
    if (inv_special && inv_special->mnemonic) total_invoke++;
    if (inv_static && inv_static->mnemonic) total_invoke++;
    if (inv_interface && inv_interface->mnemonic) total_invoke++;
    
    printf("Instruções invoke encontradas: %d/4\n", total_invoke);
    
    if (total_invoke == 4) {
        printf("🎉 SUCESSO! Todas as instruções invoke estão implementadas!\n");
    } else if (total_invoke > 0) {
        printf("⚠️  PARCIAL! Algumas instruções invoke estão implementadas.\n");
    } else {
        printf("❌ FALHA! Nenhuma instrução invoke foi encontrada.\n");
    }
    
    return 0;
} 