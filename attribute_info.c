/**
 * @file attribute_info.c
 * @brief implementacao das instrucoes de leitura e desalocacao de memoria dos attribute_info
 * 
 * Esse arquivo contém a lógica das funcoes declaradas em attribute_info.h
 * 
 * @see attribute_info.h
 */

#include "attribute_info.h"
#include "reader.h"
#include <stdlib.h>
#include <stdio.h>

// --- Protótipo da Função Auxiliar Estática ---
static attribute_info** read_nested_attributes_array(u2 count, cp_info** constant_pool);


// --- Implementação da Interface Pública ---

attribute_info* read_attribute_info(cp_info** constant_pool) {
    attribute_info* attr = (attribute_info*)malloc(sizeof(attribute_info));
    if (!attr) {
        fprintf(stderr, "ERRO: Falha na alocação de memória para o atributo.\n");
        exit(1);
    }

    attr->attribute_name_index = u2read();
    attr->attribute_length = u4read();
    
    cp_info* name_info = constant_pool[attr->attribute_name_index - 1];
    

    if (name_info == NULL || name_info->tag != 1 /* CONSTANT_Utf8 */) {
        fprintf(stderr, "AVISO: Nome de atributo inválido no índice #%u. Pulando %u bytes.\n", attr->attribute_name_index, attr->attribute_length);
        get_buffer()->position += attr->attribute_length;
        free(attr);
        return NULL; 
    }


    char* attr_name = (char*)name_info->Utf8.bytes;

    if (strcmp(attr_name, "Code") == 0) {
        attr->Code.max_stack = u2read();
        attr->Code.max_locals = u2read();
        
        attr->Code.code_length = u4read();
        attr->Code.code = (u1*)malloc(attr->Code.code_length);
        for(u4 i = 0; i < attr->Code.code_length; i++) {
            attr->Code.code[i] = u1read();
        }

        attr->Code.exception_table_length = u2read();
        if (attr->Code.exception_table_length > 0) {
            attr->Code.exception_table = (exception_table*)malloc(sizeof(exception_table) * attr->Code.exception_table_length);
            for(u2 i = 0; i < attr->Code.exception_table_length; i++) {
                attr->Code.exception_table[i].start_pc   = u2read();
                attr->Code.exception_table[i].end_pc     = u2read();
                attr->Code.exception_table[i].handler_pc = u2read();
                attr->Code.exception_table[i].catch_type = u2read();
            }
        } else {
            attr->Code.exception_table = NULL;
        }
        
        attr->Code.attributes_count = u2read();
        attr->Code.attributes = read_nested_attributes_array(attr->Code.attributes_count, constant_pool);

    } else if (strcmp(attr_name, "ConstantValue") == 0) {
        attr->ConstantValue.constantvalue_index = u2read();
    } else if (strcmp(attr_name, "Exceptions") == 0) {
        attr->Exceptions.number_of_exceptions = u2read();
        attr->Exceptions.exception_index_table = (u2*)malloc(sizeof(u2) * attr->Exceptions.number_of_exceptions);
        for(u2 i = 0; i < attr->Exceptions.number_of_exceptions; i++) {
            attr->Exceptions.exception_index_table[i] = u2read();
        }
    } else if (strcmp(attr_name, "InnerClasses") == 0) {
        attr->InnerClasses.number_of_classes = u2read();
        attr->InnerClasses.classes = (classes*)malloc(sizeof(classes) * attr->InnerClasses.number_of_classes);
        for(u2 i = 0; i < attr->InnerClasses.number_of_classes; i++) {
            attr->InnerClasses.classes[i].inner_class_info_index = u2read();
            attr->InnerClasses.classes[i].outer_class_info_index = u2read();
            attr->InnerClasses.classes[i].inner_name_index = u2read();
            attr->InnerClasses.classes[i].inner_class_access_flags = u2read();
        }
    } else {
        get_buffer()->position += attr->attribute_length;
    }

    return attr;
}


void free_attribute_info(attribute_info* attribute, cp_info** constant_pool) {
    if (!attribute) return;

    cp_info* name_info = constant_pool[attribute->attribute_name_index - 1];
    
    if (name_info != NULL && name_info->tag == 1) {
        char* attr_name = (char*)name_info->Utf8.bytes;

        if (strcmp(attr_name, "Code") == 0) {
            free(attribute->Code.code);
            free(attribute->Code.exception_table);
            
            if (attribute->Code.attributes) {
                for (u2 i = 0; i < attribute->Code.attributes_count; i++) {
                    free_attribute_info(attribute->Code.attributes[i], constant_pool);
                }
                free(attribute->Code.attributes);
            }
        } else if (strcmp(attr_name, "Exceptions") == 0) {
            free(attribute->Exceptions.exception_index_table);
        } else if (strcmp(attr_name, "InnerClasses") == 0) {
            free(attribute->InnerClasses.classes);
        }
    }

    free(attribute);
}

static attribute_info** read_nested_attributes_array(u2 count, cp_info** constant_pool) {
    if (count == 0) {
        return NULL;
    }
    attribute_info** attributes_array = (attribute_info**)malloc(sizeof(attribute_info*) * count);
    if (!attributes_array) {
        fprintf(stderr, "ERRO: Falha na alocação de memória para o array de atributos aninhados.\n");
        exit(1);
    }

    for (u2 i = 0; i < count; i++) {
        attributes_array[i] = read_attribute_info(constant_pool);
    }
    return attributes_array;
}
