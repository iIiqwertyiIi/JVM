#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"
#include "class_file.h"
#include "reader.h"

// Função para analisar o bytecode de um método
void analyze_method_bytecode(method_info* method, ClassFile* class_file) {
    printf("=== Análise do Bytecode do Método ===\n");
    
    // Encontra o atributo Code
    for (u2 i = 0; i < method->attributes_count; i++) {
        attribute_info* attr = method->attributes[i];
        
        // Obtém o nome do atributo
        char* attr_name = NULL;
        for (u2 j = 0; j < class_file->constant_pool_count - 1; j++) {
            if (class_file->constant_pool[j] && 
                class_file->constant_pool[j]->tag == CONSTANT_Utf8 &&
                class_file->constant_pool[j]->Utf8.bytes &&
                strcmp(class_file->constant_pool[j]->Utf8.bytes, "Code") == 0) {
                attr_name = class_file->constant_pool[j]->Utf8.bytes;
                break;
            }
        }
        
        if (attr_name && strcmp(attr_name, "Code") == 0) {
            printf("Código do método encontrado!\n");
            printf("Tamanho do código: %u bytes\n", attr->Code.code_length);
            printf("Max stack: %u\n", attr->Code.max_stack);
            printf("Max locals: %u\n", attr->Code.max_locals);
            
            printf("\n=== Instruções Encontradas ===\n");
            u4 pc = 0;
            int invoke_count = 0;
            
            while (pc < attr->Code.code_length) {
                u1 opcode = attr->Code.code[pc];
                InstructionType* instruction = get_instruction_type(opcode);
                
                if (instruction && instruction->mnemonic) {
                    printf("PC %u: %s", pc, instruction->mnemonic);
                    
                    // Verifica se é uma instrução invoke
                    if (opcode == 0xb6 || opcode == 0xb7 || opcode == 0xb8 || opcode == 0xb9) {
                        printf(" [INVOKE DETECTADO!]");
                        invoke_count++;
                        
                        // Decodifica o operando para invoke
                        if (opcode == 0xb6 || opcode == 0xb7 || opcode == 0xb8) {
                            // invokevirtual, invokespecial, invokestatic (2 bytes)
                            if (pc + 2 < attr->Code.code_length) {
                                u2 methodref_index = (attr->Code.code[pc + 1] << 8) | attr->Code.code[pc + 2];
                                printf(" (methodref #%u)", methodref_index);
                            }
                        } else if (opcode == 0xb9) {
                            // invokeinterface (4 bytes)
                            if (pc + 4 < attr->Code.code_length) {
                                u2 interface_methodref_index = (attr->Code.code[pc + 1] << 8) | attr->Code.code[pc + 2];
                                u1 count = attr->Code.code[pc + 3];
                                printf(" (interface_methodref #%u, count: %u)", interface_methodref_index, count);
                            }
                        }
                    }
                    
                    printf("\n");
                    pc += instruction->operand_count + 1;
                } else {
                    printf("PC %u: opcode 0x%02x (desconhecido)\n", pc, opcode);
                    pc++;
                }
            }
            
            printf("\n=== Resumo ===\n");
            printf("Total de instruções invoke encontradas: %d\n", invoke_count);
            
            if (invoke_count > 0) {
                printf("SUCESSO! Instruções invoke detectadas no bytecode!\n");
            } else {
                printf("Nenhuma instrução invoke encontrada neste método.\n");
            }
            
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo.class>\n", argv[0]);
        return 1;
    }
    
    printf("=== Teste de Análise de Bytecode ===\n\n");
    
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
    
    // Analisa cada método
    for (u2 i = 0; i < class_file->methods_count; i++) {
        method_info* method = class_file->methods[i];
        
        // Obtém o nome do método
        char* method_name = class_file->constant_pool[method->name_index - 1]->Utf8.bytes;
        char* method_descriptor = class_file->constant_pool[method->descriptor_index - 1]->Utf8.bytes;
        
        printf("Método %u: %s%s\n", i, method_name, method_descriptor);
        analyze_method_bytecode(method, class_file);
        printf("\n==================================================\n\n");
    }
    
    // Limpa a memória
    free_class_file(class_file);
    free_buffer();
    
    return 0;
} 