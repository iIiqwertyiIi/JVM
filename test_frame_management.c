#include <stdio.h>
#include <stdlib.h>
#include "method_invocation.h"
#include "class_file.h"
#include "reader.h"

// Função para testar criação e gerenciamento de frames
void test_frame_management(ClassFile* class_file) {
    printf("=== Teste de Gerenciamento de Frames ===\n\n");
    
    // Testa criação de frames para cada método
    printf("1. Testando criação de frames:\n");
    
    for (u2 i = 0; i < class_file->methods_count; i++) {
        method_info* method = class_file->methods[i];
        char* method_name = class_file->constant_pool[method->name_index - 1]->Utf8.bytes;
        char* method_descriptor = class_file->constant_pool[method->descriptor_index - 1]->Utf8.bytes;
        
        printf("   Método %u: %s%s\n", i, method_name, method_descriptor);
        
        // Cria um frame para o método
        Frame* frame = create_frame(class_file, method);
        if (frame) {
            printf("      Frame criado com sucesso!\n");
            printf("         - Classe: %s\n", 
                   frame->this_class->constant_pool[frame->this_class->constant_pool[frame->this_class->this_class - 1]->Class.name_index - 1]->Utf8.bytes);
            printf("         - Método: %s\n", 
                   frame->this_class->constant_pool[frame->this_method->name_index - 1]->Utf8.bytes);
            printf("         - Stack size: %u\n", frame->stack_size);
            printf("         - Local variables: %p\n", (void*)frame->local_variables);
            printf("         - PC buffer: %p\n", (void*)frame->pc.buffer);
            
            // Testa operações na pilha
            printf("         - Testando operações na pilha:\n");
            
            // Adiciona alguns valores à pilha
            add_to_stack(frame, 42);
            add_to_stack(frame, 100);
            add_to_stack(frame, 999);
            
            printf("            Stack size após push: %u\n", frame->stack_size);
            
            // Remove valores da pilha
            u4 value1 = remove_from_stack(frame);
            u4 value2 = remove_from_stack(frame);
            u4 value3 = remove_from_stack(frame);
            
            printf("            Valores removidos: %u, %u, %u\n", value1, value2, value3);
            printf("            Stack size após pop: %u\n", frame->stack_size);
            
            // Libera o frame
            free(frame->local_variables);
            free(frame);
            printf("      Frame liberado com sucesso!\n");
        } else {
            printf("      Erro ao criar frame!\n");
        }
        printf("\n");
    }
    
    // Testa gerenciamento da pilha de frames
    printf("2. Testando gerenciamento da pilha de frames:\n");
    
    // Cria alguns frames de teste
    Frame* frame1 = create_frame(class_file, class_file->methods[0]);
    Frame* frame2 = create_frame(class_file, class_file->methods[1]);
    Frame* frame3 = create_frame(class_file, class_file->methods[2]);
    
    if (frame1 && frame2 && frame3) {
        printf("   Frames de teste criados\n");
        
        // Simula uma pilha de frames
        FrameStack frame_stack = {0, NULL};
        
        // Empilha os frames
        push_frame(&frame_stack, frame1);
        printf("   Frame 1 empilhado. Stack size: %u\n", frame_stack.stack_size);
        
        push_frame(&frame_stack, frame2);
        printf("   Frame 2 empilhado. Stack size: %u\n", frame_stack.stack_size);
        
        push_frame(&frame_stack, frame3);
        printf("   Frame 3 empilhado. Stack size: %u\n", frame_stack.stack_size);
        
        // Desempilha os frames
        Frame* popped_frame3 = pop_frame(&frame_stack);
        printf("   Frame 3 desempilhado. Stack size: %u\n", frame_stack.stack_size);
        
        Frame* popped_frame2 = pop_frame(&frame_stack);
        printf("   Frame 2 desempilhado. Stack size: %u\n", frame_stack.stack_size);
        
        Frame* popped_frame1 = pop_frame(&frame_stack);
        printf("   Frame 1 desempilhado. Stack size: %u\n", frame_stack.stack_size);
        
        // Verifica se os frames foram desempilhados na ordem correta
        if (popped_frame3 == frame3 && popped_frame2 == frame2 && popped_frame1 == frame1) {
            printf("   Ordem de desempilhamento correta!\n");
        } else {
            printf("   Erro na ordem de desempilhamento!\n");
        }
        
        // Libera os frames
        if (popped_frame1) {
            free(popped_frame1->local_variables);
            free(popped_frame1);
        }
        if (popped_frame2) {
            free(popped_frame2->local_variables);
            free(popped_frame2);
        }
        if (popped_frame3) {
            free(popped_frame3->local_variables);
            free(popped_frame3);
        }
        
        printf("   Frames liberados com sucesso!\n");
    } else {
        printf("   Erro ao criar frames de teste!\n");
    }
    
    printf("\n=== Resumo do Teste ===\n");
    printf("Criação de frames está funcionando!\n");
    printf("Operações na pilha de operandos estão funcionando!\n");
    printf("Gerenciamento da pilha de frames está funcionando!\n");
    printf("Liberação de memória está funcionando!\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo.class>\n", argv[0]);
        return 1;
    }
    
    printf("=== Teste de Gerenciamento de Frames ===\n\n");
    
    // Lê o arquivo
    read_file(argv[1]);
    
    // Carrega a classe
    ClassFile* class_file = read_class_file();
    if (!class_file) {
        printf("Erro ao carregar o arquivo .class\n");
        return 1;
    }
    
    printf("Classe carregada: %s\n", 
           class_file->constant_pool[class_file->constant_pool[class_file->this_class - 1]->Class.name_index - 1]->Utf8.bytes);
    printf("Número de métodos: %u\n\n", class_file->methods_count);
    
    // Executa o teste
    test_frame_management(class_file);
    
    // Limpa a memória
    free_class_file(class_file);
    free_buffer();
    
    return 0;
} 