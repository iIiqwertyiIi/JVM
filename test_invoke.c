#include <stdio.h>
#include <stdlib.h>
#include "method_invocation.h"
#include "types.h"

// Teste simples para verificar se as funções estão sendo reconhecidas
int main() {
    printf("=== Teste das Instruções Invoke ===\n\n");
    
    // Teste 1: Verificar se as funções estão definidas
    printf("1. Verificando se as funções estão definidas:\n");
    printf("   - invokevirtual: %p\n", (void*)invokevirtual);
    printf("   - invokespecial: %p\n", (void*)invokespecial);
    printf("   - invokestatic: %p\n", (void*)invokestatic);
    printf("   - invokeinterface: %p\n", (void*)invokeinterface);
    
    // Teste 2: Verificar se as estruturas estão definidas
    printf("\n2. Verificando estruturas:\n");
    printf("   - Tamanho de ResolvedMethod: %zu bytes\n", sizeof(ResolvedMethod));
    printf("   - Tamanho de Frame: %zu bytes\n", sizeof(Frame));
    printf("   - Tamanho de FrameStack: %zu bytes\n", sizeof(FrameStack));
    
    // Teste 3: Verificar constantes
    printf("\n3. Verificando constantes do constant pool:\n");
    printf("   - CONSTANT_Methodref: %d\n", CONSTANT_Methodref);
    printf("   - CONSTANT_InterfaceMethodref: %d\n", CONSTANT_InterfaceMethodref);
    printf("   - CONSTANT_NameAndType: %d\n", CONSTANT_NameAndType);
    printf("   - CONSTANT_Utf8: %d\n", CONSTANT_Utf8);
    
    // Teste 4: Verificar opcodes das instruções
    printf("\n4. Verificando opcodes das instruções invoke:\n");
    printf("   - invokevirtual: 0x%02x\n", 0xb6);
    printf("   - invokespecial: 0x%02x\n", 0xb7);
    printf("   - invokestatic: 0x%02x\n", 0xb8);
    printf("   - invokeinterface: 0x%02x\n", 0xb9);
    
    printf("\n=== Teste Concluído ===\n");
    printf("Se você vê endereços diferentes de zero para as funções,\n");
    printf("significa que elas estão sendo compiladas corretamente!\n");
    
    return 0;
} 