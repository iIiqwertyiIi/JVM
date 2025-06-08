#include "field_reader.h"
#include <stdlib.h>

// Função auxiliar para ler atributos de um field
attribute_info * read_field_attributes(u2 attributes_count) {
    if (attributes_count == 0) {
        return NULL;
    }
    
    attribute_info * attributes = malloc(sizeof(attribute_info) * attributes_count);
    
    for (u2 i = 0; i < attributes_count; i++) {
        // Lê o nome do atributo (índice no constant pool)
        attributes[i].attribute_name_index = u2read();
        
        // Lê o tamanho do atributo
        attributes[i].attribute_length = u4read();
        
        // Por enquanto, apenas pula os bytes do atributo
        // (você pode expandir isso depois para ler atributos específicos)
        for (u4 j = 0; j < attributes[i].attribute_length; j++) {
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