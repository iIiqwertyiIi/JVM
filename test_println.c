#include <stdio.h>
#include <stdlib.h>
#include "class_file.h"
#include "interpreter.h"
#include "reader.h"
#include "method_info.h"
#include "object.h"
#include "method_invocation.h"

// Adicionar declaração de free_frame
void free_frame(Frame* frame);

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Uso: %s <arquivo .class>\n", argv[0]);
        return 1;
    }
    printf("=== Teste de System.out.println no invokevirtual ===\n\n");
    ClassFile* cf = read_class_file(argv[1]);
    if (!cf) {
        printf("Erro ao ler o arquivo .class!\n");
        return 1;
    }
    // Procura o método main
    method_info* main_method = NULL;
    for (int i = 0; i < cf->methods_count; i++) {
        char* name = get_utf8_string(cf->constant_pool, cf->methods[i]->name_index);
        char* desc = get_utf8_string(cf->constant_pool, cf->methods[i]->descriptor_index);
        if (strcmp(name, "main") == 0 && strcmp(desc, "([Ljava/lang/String;)V") == 0) {
            main_method = cf->methods[i];
            break;
        }
    }
    if (!main_method) {
        printf("Método main não encontrado!\n");
        return 1;
    }
    // Cria o frame inicial para o main
    Frame* main_frame = create_frame(cf, main_method);
    if (!main_frame) {
        printf("Erro ao criar frame para o main!\n");
        return 1;
    }
    // Executa o método main
    execute_method(main_frame);
    // Libera memória
    free_frame(main_frame);
    free_class_file(cf);
    printf("\n=== Fim do teste de println ===\n");
    return 0;
} 