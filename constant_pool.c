#include "constant_pool.h"
#include <stdlib.h>
#include <stdio.h>

cp_info ** read_constant_pool(u2 constant_pool_count) {
    // Aloca array de ponteiros (constant_pool_count - 1 porque índice começa em 1)
    cp_info ** constant_pool = malloc(sizeof(cp_info *) * (constant_pool_count - 1));
    
    // Lê cada entrada do constant pool
    for (u2 i = 0; i < (constant_pool_count - 1); i++) {
        // Aloca memória para a entrada
        constant_pool[i] = malloc(sizeof(cp_info));
        
        // Lê a tag
        constant_pool[i]->tag = u1read();
        
        // Lê o conteúdo baseado na tag
        switch(constant_pool[i]->tag) {
            case CONSTANT_Class:
                constant_pool[i]->Class.name_index = u2read();
                break;
                
            case CONSTANT_Fieldref:
                constant_pool[i]->Fieldref.class_index = u2read();
                constant_pool[i]->Fieldref.name_and_type_index = u2read();
                break;
                
            case CONSTANT_Methodref:
                constant_pool[i]->Methodref.class_index = u2read();
                constant_pool[i]->Methodref.name_and_type_index = u2read();
                break;
                
            case CONSTANT_InterfaceMethodref:
                constant_pool[i]->InterfaceMethodref.class_index = u2read();
                constant_pool[i]->InterfaceMethodref.name_and_type_index = u2read();
                break;
                
            case CONSTANT_String:
                constant_pool[i]->String.string_index = u2read();
                break;
                
            case CONSTANT_Integer:
                constant_pool[i]->Integer.bytes = u4read();
                break;
                
            case CONSTANT_Float:
                constant_pool[i]->Float.bytes = u4read();
                break;
                
            case CONSTANT_Long:
                constant_pool[i]->Long.high_bytes = u4read();
                constant_pool[i]->Long.low_bytes = u4read();
                // Long ocupa 2 entradas no constant pool
                i++;
                if (i < (constant_pool_count - 1)) {
                    constant_pool[i] = NULL; // Marca próxima entrada como inválida
                }
                break;
                
            case CONSTANT_Double:
                constant_pool[i]->Double.high_bytes = u4read();
                constant_pool[i]->Double.low_bytes = u4read();
                // Double ocupa 2 entradas no constant pool
                i++;
                if (i < (constant_pool_count - 1)) {
                    constant_pool[i] = NULL; // Marca próxima entrada como inválida
                }
                break;
                
            case CONSTANT_NameAndType:
                constant_pool[i]->NameAndType.name_index = u2read();
                constant_pool[i]->NameAndType.descriptor_index = u2read();
                break;
                
            case CONSTANT_Utf8:
                constant_pool[i]->Utf8.length = u2read();
                constant_pool[i]->Utf8.bytes = malloc(constant_pool[i]->Utf8.length + 1);
                
                // Lê cada byte da string UTF-8
                for (u2 j = 0; j < constant_pool[i]->Utf8.length; j++) {
                    constant_pool[i]->Utf8.bytes[j] = u1read();
                }
                // Adiciona null terminator
                constant_pool[i]->Utf8.bytes[constant_pool[i]->Utf8.length] = '\0';
                break;
                
            default:
                fprintf(stderr, "Tag desconhecida no constant pool: %d\n", constant_pool[i]->tag);
                // Para tags desconhecidas, você pode optar por retornar NULL ou continuar
                break;
        }
    }
    
    return constant_pool;
}