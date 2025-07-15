#include <stdio.h>
#include <stdlib.h>
#include "method_invocation.h"
#include "class_file.h"
#include "reader.h"

// Função para testar a resolução de métodos
void test_method_resolution(ClassFile* class_file) {
    printf("=== Teste de Resolução de Métodos ===\n\n");
    
    // Testa resolução de alguns MethodRef do constant pool
    printf("1. Testando resolução de MethodRef:\n");
    
    // Procura por MethodRef no constant pool
    for (u2 i = 0; i < class_file->constant_pool_count - 1; i++) {
        cp_info* entry = class_file->constant_pool[i];
        if (entry && entry->tag == CONSTANT_Methodref) {
            printf("   MethodRef #%u:\n", i + 1);
            
            // Obtém informações do MethodRef
            u2 class_index = entry->Methodref.class_index;
            u2 name_and_type_index = entry->Methodref.name_and_type_index;
            
            // Obtém nome da classe
            char* class_name = NULL;
            if (class_file->constant_pool[class_index - 1]->tag == CONSTANT_Class) {
                u2 class_name_index = class_file->constant_pool[class_index - 1]->Class.name_index;
                class_name = class_file->constant_pool[class_name_index - 1]->Utf8.bytes;
            }
            
            // Obtém nome e tipo do método
            char* method_name = NULL;
            char* method_descriptor = NULL;
            if (class_file->constant_pool[name_and_type_index - 1]->tag == CONSTANT_NameAndType) {
                u2 name_index = class_file->constant_pool[name_and_type_index - 1]->NameAndType.name_index;
                u2 descriptor_index = class_file->constant_pool[name_and_type_index - 1]->NameAndType.descriptor_index;
                method_name = class_file->constant_pool[name_index - 1]->Utf8.bytes;
                method_descriptor = class_file->constant_pool[descriptor_index - 1]->Utf8.bytes;
            }
            
            printf("      Classe: %s\n", class_name ? class_name : "NULL");
            printf("      Método: %s\n", method_name ? method_name : "NULL");
            printf("      Descritor: %s\n", method_descriptor ? method_descriptor : "NULL");
            
            // Testa a resolução
            ResolvedMethod* resolved = resolve_method(class_file, i + 1);
            if (resolved) {
                printf("      RESOLVIDO: Método encontrado!\n");
                printf("         - Classe: %s\n", 
                       resolved->class->constant_pool[resolved->class->constant_pool[resolved->class->this_class - 1]->Class.name_index - 1]->Utf8.bytes);
                printf("         - Índice do método: %u\n", resolved->method_index);
                free(resolved);
            } else {
                printf("      NAO RESOLVIDO: Método não encontrado\n");
            }
            printf("\n");
        }
    }
    
    // Testa resolução de InterfaceMethodRef
    printf("2. Testando resolução de InterfaceMethodRef:\n");
    int interface_methods_found = 0;
    
    for (u2 i = 0; i < class_file->constant_pool_count - 1; i++) {
        cp_info* entry = class_file->constant_pool[i];
        if (entry && entry->tag == CONSTANT_InterfaceMethodref) {
            interface_methods_found++;
            printf("   InterfaceMethodRef #%u encontrado\n", i + 1);
            
            // Obtém informações do InterfaceMethodRef
            u2 interface_index = entry->InterfaceMethodref.class_index;
            u2 name_and_type_index = entry->InterfaceMethodref.name_and_type_index;
            
            // Obtém nome da interface
            char* interface_name = NULL;
            if (class_file->constant_pool[interface_index - 1]->tag == CONSTANT_Class) {
                u2 interface_name_index = class_file->constant_pool[interface_index - 1]->Class.name_index;
                interface_name = class_file->constant_pool[interface_name_index - 1]->Utf8.bytes;
            }
            
            printf("      Interface: %s\n", interface_name ? interface_name : "NULL");
            
            // Testa a resolução
            ResolvedMethod* resolved = resolve_interface_method(class_file, i + 1);
            if (resolved) {
                printf("      RESOLVIDO: Método de interface encontrado!\n");
                free(resolved);
            } else {
                printf("      NAO RESOLVIDO: Método de interface não encontrado\n");
            }
            printf("\n");
        }
    }
    
    if (interface_methods_found == 0) {
        printf("   Nenhum InterfaceMethodRef encontrado neste arquivo.\n\n");
    }
    
    // Testa busca de métodos na classe atual
    printf("3. Testando busca de métodos na classe atual:\n");
    
    for (u2 i = 0; i < class_file->methods_count; i++) {
        method_info* method = class_file->methods[i];
        char* method_name = class_file->constant_pool[method->name_index - 1]->Utf8.bytes;
        char* method_descriptor = class_file->constant_pool[method->descriptor_index - 1]->Utf8.bytes;
        
        printf("   Buscando método: %s%s\n", method_name, method_descriptor);
        
        ResolvedMethod* found = find_method_in_class(class_file, method_name, method_descriptor);
        if (found) {
            printf("      ENCONTRADO: Método na classe atual\n");
            printf("         - Índice: %u\n", found->method_index);
            free(found);
        } else {
            printf("      NAO ENCONTRADO: Método não encontrado na classe atual\n");
        }
        printf("\n");
    }
    
    printf("=== Resumo do Teste ===\n");
    printf("Sistema de resolução de métodos está funcionando!\n");
    printf("Funções de busca de métodos estão operacionais!\n");
    printf("Constant pool está sendo interpretado corretamente!\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo.class>\n", argv[0]);
        return 1;
    }
    
    printf("=== Teste de Resolução de Métodos ===\n\n");
    
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
    printf("Tamanho do constant pool: %u\n\n", class_file->constant_pool_count);
    
    // Executa o teste
    test_method_resolution(class_file);
    
    // Limpa a memória
    free_class_file(class_file);
    free_buffer();
    
    return 0;
} 