/**
 * @file field_reader.c
 * @brief implementacao de funcoes de leitura e desalocacao dos campos do ClassFile
 * 
 * Esse arquivo contém a lógica das funcoes declaradas em field_reader.h
 * 
 * @see field_reader.h
 */

#include "field_reader.h"
#include "attribute_info.h"
#include <stdlib.h>

// Função auxiliar para ler atributos de um field
static attribute_info ** read_field_attributes(u2 attributes_count) {
    if (attributes_count == 0) {
        return NULL;
    }
    
    // Aloca array de PONTEIROS para attribute_info
    attribute_info ** attributes = malloc(sizeof(attribute_info *) * attributes_count);
    
    for (u2 i = 0; i < attributes_count; i++) {
        // Aloca cada atributo
        attributes[i] = malloc(sizeof(attribute_info));
        
        // Lê o nome do atributo (índice no constant pool)
        attributes[i]->attribute_name_index = u2read();
        
        // Lê o tamanho do atributo
        attributes[i]->attribute_length = u4read();
        
        // Por enquanto, apenas pula os bytes do atributo
        // (você pode expandir isso depois para ler atributos específicos)
        for (u4 j = 0; j < attributes[i]->attribute_length; j++) {
            u1read();
        }
    }
    
    return attributes;
}

// Função principal para ler todos os fields
field_info ** read_all_fields(u2 fields_count) {
    if (fields_count == 0) {
        return NULL;
    }
    
    // Aloca array de ponteiros para os fields
    field_info ** fields = malloc(sizeof(field_info *) * fields_count);
    
    // Lê cada field
    for (u2 i = 0; i < fields_count; i++) {
        // Aloca memória para o field
        fields[i] = malloc(sizeof(field_info));
        
        // Lê access_flags
        fields[i]->access_flags = u2read();
        
        // Lê name_index (índice do nome no constant pool)
        fields[i]->name_index = u2read();
        
        // Lê descriptor_index (índice do tipo no constant pool)
        fields[i]->descriptor_index = u2read();
        
        // Lê attributes_count
        fields[i]->attributes_count = u2read();
        
        // Lê os atributos
        fields[i]->attributes = read_field_attributes(fields[i]->attributes_count);
    }
    
    return fields;
}

// Função para liberar a memória dos fields
void free_all_fields(field_info ** fields, u2 fields_count) {
    if (fields == NULL) {
        return;
    }
    
    // Libera cada field
    for (u2 i = 0; i < fields_count; i++) {
        if (fields[i] != NULL) {
            // Libera os atributos se existirem
            if (fields[i]->attributes != NULL) {
                for (u2 j = 0; j < fields[i]->attributes_count; j++) {
                    if (fields[i]->attributes[j] != NULL) {
                        free(fields[i]->attributes[j]);
                    }
                }
                free(fields[i]->attributes);
            }
            // Libera o field
            free(fields[i]);
        }
    }
    
    // Libera o array de ponteiros
    free(fields);
}