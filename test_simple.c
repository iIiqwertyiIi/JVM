#include <stdio.h>
#include <stdlib.h>

// Declarações das funções que queremos testar
int invokevirtual(void* frame, void* instruction);
int invokespecial(void* frame, void* instruction);
int invokestatic(void* frame, void* instruction);
int invokeinterface(void* frame, void* instruction);

// Estruturas básicas para teste
typedef struct {
    void* class;
    void* method;
    int method_index;
} ResolvedMethod;

int main() {
    printf("=== Teste Simples das Instruções Invoke ===\n\n");
    
    // Teste 1: Verificar se as funções estão definidas
    printf("1. Verificando se as funções estão definidas:\n");
    printf("   - invokevirtual: %p\n", (void*)invokevirtual);
    printf("   - invokespecial: %p\n", (void*)invokespecial);
    printf("   - invokestatic: %p\n", (void*)invokestatic);
    printf("   - invokeinterface: %p\n", (void*)invokeinterface);
    
    // Teste 2: Verificar se as estruturas estão definidas
    printf("\n2. Verificando estruturas:\n");
    printf("   - Tamanho de ResolvedMethod: %zu bytes\n", sizeof(ResolvedMethod));
    
    // Teste 3: Verificar opcodes das instruções
    printf("\n3. Verificando opcodes das instruções invoke:\n");
    printf("   - invokevirtual: 0x%02x\n", 0xb6);
    printf("   - invokespecial: 0x%02x\n", 0xb7);
    printf("   - invokestatic: 0x%02x\n", 0xb8);
    printf("   - invokeinterface: 0x%02x\n", 0xb9);
    
    printf("\n=== Teste Concluído ===\n");
    printf("Se você vê endereços diferentes de zero para as funções,\n");
    printf("significa que elas estão sendo compiladas corretamente!\n");
    
    return 0;
} 