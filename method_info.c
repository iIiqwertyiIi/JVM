#include "method_info.h"
#include "attribute_info.h"
#include "reader.h"
#include <stdlib.h>

method_info* read_method_info(cp_info** constant_pool) {
    method_info* method = (method_info*)malloc(sizeof(method_info));
    if (!method) {
      
        return NULL;
    }

    method->access_flags = u2read();
    method->name_index = u2read();
    method->descriptor_index = u2read();
    method->attributes_count = u2read();

    if (method->attributes_count > 0) {
        // 1. Aloca memória usando a contagem de atributos DO MÉTODO.
        method->attributes = (attribute_info**)malloc(sizeof(attribute_info*) * method->attributes_count);
        
        // 2. Itera usando a contagem de atributos DO MÉTODO.
        for (u2 i = 0; i < method->attributes_count; i++) {
            // 3. Guarda o resultado no array de atributos DO MÉTODO
            //    e passa o constant_pool recebido como parâmetro.
            method->attributes[i] = read_attribute_info(constant_pool);
        }
    } else {
        method->attributes = NULL;
    }
    
    return method;
}

void free_method_info(method_info* method, cp_info** constant_pool) {
    if (!method) return;

    if (method->attributes) {
        for (u2 i = 0; i < method->attributes_count; i++) {
            free_attribute_info(method->attributes[i], constant_pool);
        }
        free(method->attributes);
    }


    free(method);
}