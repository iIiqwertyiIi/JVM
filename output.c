#include "output.h"
#include <stdlib.h>
#include <stdio.h>

void print_class_file(ClassFile * class_file) {
    printf("Entrando em print_class_file...\n");
    printf("Assinatura: 0x%x\n", class_file->magic);
    printf("General Information\n");
    printf("Minor version: %d\n", class_file->minor_version);
    printf("Major version: %d [1.%d]\n", class_file->major_version, class_file->major_version - 44);
    printf("Constant pool count: %d\n", class_file->constant_pool_count);
    printf("Access flags: 0x%x\n", class_file->access_flags);
    switch (class_file->access_flags & 0x000f) {
        case 0x0001:
        printf("ACC_PUBLIC\n");
        break;
        default:
        break;
    }
    switch (class_file->access_flags & 0x00f0) {
        case 0x0010:
        printf("ACC_FINAL\n");
        break;
        case 0x0020:
        printf("ACC_SUPER\n");
        break;
        case 0x0030:
        printf("ACC_FINAL\nACC_SUPER\n");
        break;
        default:
        break;
    }
    switch (class_file->access_flags & 0x0f00) {
        case 0x0200:
        printf("ACC_INTERFACE\n");
        break;
        case 0x0400:
        printf("ACC_ABSTRACT\n");
        break;
        case 0x0600:
        printf("ACC_INTERFACE\nACC_ABSTRACT\n");
        break;
        default:
        break;
    }
    switch (class_file->access_flags & 0xf000) {
        case 0x1000:
        printf("ACC_SYNTHETIC\n");
        break;
        case 0x2000:
        printf("ACC_ANNOTATION\n");
        break;
        case 0x4000:
        printf("ACC_ENUM\n");
        break;
        case 0x3000:
        printf("ACC_SYNTHETIC\nACC_ANNOTATION\n");
        break;
        case 0x5000:
        printf("ACC_SYNTHETIC\nACC_ENUM\n");
        break;
        case 0x6000:
        printf("ACC_ANNOTATION\nACC_ENUM\n");
        break;
        case 0x7000:
        printf("ACC_SYNTHETIC\nACC_ANNOTATION\nACC_ENUM\n");
        break;
        default:
        break;
    }
    printf("This class: cp_info#%d %s\n", class_file->this_class, class_file->constant_pool[class_file->this_class - 1]->Utf8.bytes);
    printf("Super class: cp_info#%d %s\n", class_file->super_class, class_file->constant_pool[class_file->super_class - 1]->Utf8.bytes);
    printf("Interfaces count: %d\n", class_file->interfaces_count);
    printf("Fields count: %d\n", class_file->fields_count);
    printf("Methods count: %d\n", class_file->methods_count);
    printf("Attributes count: %d\n", class_file->attributes_count);
    print_cp_info(class_file->constant_pool, class_file->constant_pool_count);
    print_field_info(class_file->fields, class_file->fields_count);
    print_method_info(class_file->methods, class_file->methods_count);
}

void print_cp_info(cp_info * * constant_pool, u2 constant_pool_count) {
    //int count = 1;
    printf("\n====================================================================\nConstantPool\n");
    for (int i = 0; i < constant_pool_count - 1; i++) {
        cp_info * constant = constant_pool[i];
        switch (constant->tag) {
            case 7:
            printf("[%d] CONSTANT_Class_info\n", i + 1);
            printf("Class name: cp_info#%d %s\n\n", constant->Class.name_index, constant_pool[constant->Class.name_index - 1]->Utf8.bytes);
            break;
            case 9:
            printf("[%d] CONSTANT_Fieldref_info\n", i + 1);
            printf("Class name: cp_info#%d %s\n", constant->Fieldref.class_index, constant_pool[constant->Fieldref.class_index - 1]->Utf8.bytes);
            printf("Name and type: cp_info#%d <%s : %s>\n\n", constant->Fieldref.name_and_type_index, constant_pool[constant_pool[constant->Fieldref.name_and_type_index - 1]->NameAndType.name_index - 1]->Utf8.bytes, constant_pool[constant_pool[constant->Fieldref.name_and_type_index - 1]->NameAndType.descriptor_index - 1]->Utf8.bytes);
            break;
            case 10:
            printf("[%d] CONSTANT_Methodref_info\n", i + 1);
            printf("Class name: cp_info#%d %s\n", constant->Methodref.class_index, constant_pool[constant->Methodref.class_index - 1]->Utf8.bytes);
            printf("Name and type: cp_info#%d <%s : %s>\n\n", constant->Methodref.name_and_type_index, constant_pool[constant_pool[constant->Methodref.name_and_type_index - 1]->NameAndType.name_index - 1]->Utf8.bytes, constant_pool[constant_pool[constant->Methodref.name_and_type_index - 1]->NameAndType.descriptor_index - 1]->Utf8.bytes);
            break;
            case 11:
            printf("[%d] CONSTANT_InterfaceMethodref_info\n", i + 1);
            printf("Class name: cp_info#%d %s\n", constant->InterfaceMethodref.class_index, constant_pool[constant->InterfaceMethodref.class_index - 1]->Utf8.bytes);
            printf("Name and type: cp_info#%d <%s : %s>\n\n", constant->InterfaceMethodref.name_and_type_index, constant_pool[constant_pool[constant->InterfaceMethodref.name_and_type_index - 1]->NameAndType.name_index - 1]->Utf8.bytes, constant_pool[constant_pool[constant->InterfaceMethodref.name_and_type_index - 1]->NameAndType.descriptor_index - 1]->Utf8.bytes);
            break;
            case 12:
            printf("[%d] CONSTANT_NameAndType_info\n", i + 1);
            printf("Name: cp_info#%d <%s>\n", constant->NameAndType.name_index, constant_pool[constant->NameAndType.name_index - 1]->Utf8.bytes);
            printf("Descriptor: cp_info#%d <%s>\n\n", constant->NameAndType.descriptor_index, constant_pool[constant->NameAndType.descriptor_index - 1]->Utf8.bytes);
            break;
            case 1:
            printf("[%d] CONSTANT_Utf8_info\n", i + 1);
            printf("Length of byte array: %d\n", constant->Utf8.length);
            printf("String: %s\n\n", constant->Utf8.bytes);
            break;
            case 8:
            printf("[%d] CONSTANT_String_info\n", i + 1);
            printf("String: cp_info#%d <%s>\n\n", constant->String.string_index, constant_pool[constant->String.string_index - 1]->Utf8.bytes);
            break;
            case 3:
            printf("[%d] CONSTANT_Integer_info\n", i + 1);
            printf("Bytes: 0x%x\n", constant->Integer.bytes);
            printf("Integer: %d\n\n", (int32_t) constant->Integer.bytes);
            break;
            case 4:
            printf("[%d] CONSTANT_Float_info\n", i + 1);
            printf("Bytes: 0x%x\n", constant->Float.bytes);
            printf("Float: %f\n\n", (float) constant->Float.bytes);
            break;
            case 5:
            printf("[%d] CONSTANT_Long_info\n", i + 1);
            printf("High Bytes: 0x%x\n", constant->Long.high_bytes);
            printf("Low Bytes: 0x%x\n", constant->Long.low_bytes);
            printf("Long: %" PRIu64 "\n", (u8) constant->Long.high_bytes << 32 | constant->Long.low_bytes);
            i++;
            break;
            case 6:
            printf("[%d] CONSTANT_Double_info\n", i + 1);
            printf("High Bytes: 0x%x\n", constant->Double.high_bytes);
            printf("Low Bytes: 0x%x\n", constant->Double.low_bytes);
            printf("Double: %" PRIu64 "\n\n", ((u8) constant->Double.high_bytes << 32 | constant->Double.low_bytes));
            i++;
            break;
        }
    }
}

void print_field_info(field_info * * fields, u2 fields_count) {
    //int count = 0;
    ClassFileBuffer * classes = get_class_file_buffer();
    cp_info * * constant = classes->buffer->constant_pool;
    printf("\n====================================================================\nFields\n");
    for (int i = 0; i < fields_count; i++) {
        field_info * field = fields[i];
        printf("[%d] %s\n", i, constant[field->name_index - 1]->Utf8.bytes);
        printf("Name: cp_info#%d <%s>\n", field->name_index, constant[field->name_index - 1]->Utf8.bytes);
        printf("Descriptor: cp_info#%d <%s>\n", field->descriptor_index, constant[field->descriptor_index - 1]->Utf8.bytes);
        printf("Access flags: 0x%x", field->access_flags);
        switch (field->access_flags & 0x000f) {
            case 0x0001:
            printf("ACC_PUBLIC\n");
            break;
            case 0x0002:
            printf("ACC_PRIVATE\n");
            break;
            case 0x0004:
            printf("ACC_PROTECTED\n");
            break;
            case 0x0008:
            printf("ACC_STATIC\n");
            break;
            case 0x0003:
            printf("ACC_PUBLIC\nACC_PRIVATE\n");
            break;
            case 0x0005:
            printf("ACC_PUBLIC\nACC_PROTECTED\n");
            break;
            case 0x0009:
            printf("ACC_PUBLIC\nACC_STATIC\n");
            break;
            case 0x0006:
            printf("ACC_PRIVATE\nACC_PROTECTED\n");
            break;
            case 0x000a:
            printf("ACC_PRIVATE\nACC_STATIC\n");
            break;
            case 0x000c:
            printf("ACC_PROTECTED\nACC_STATIC\n");
            break;
            case 0x0007:
            printf("ACC_PUBLIC\nACC_PRIVATE\nACC_PROTECTED\n");
            break;
            case 0x000b:
            printf("ACC_PUBLIC\nACC_PRIVATE\nACC_STATIC\n");
            break;
            case 0x000d:
            printf("ACC_PUBLIC\nACC_PROTECTED\nACC_STATIC\n");
            break;
            case 0x000e:
            printf("ACC_PRIVATE\nACC_PROTECTED\nACC_STATIC\n");
            break;
            case 0x000f:
            printf("ACC_PUBLIC\nACC_PRIVATE\nACC_PROTECTED\nACC_STATIC\n");
            break;
            default:
            break;
        }
        switch (field->access_flags & 0x00f0) {
            case 0x0010:
            printf("ACC_FINAL\n");
            break;
            case 0x0040:
            printf("ACC_VOLATILE\n");
            break;
            case 0x0080:
            printf("ACC_TRANSIENT\n");
            break;
            case 0x0030:
            printf("ACC_FINAL\nACC_VOLATILE\n");
            break;
            case 0x0090:
            printf("ACC_FINAL\nACC_TRANSIENT\n");
            break;
            case 0x00c0:
            printf("ACC_VOLATILE\nACC_TRANSIENT\n");
            break;
            case 0x00b0:
            printf("ACC_FINAL\nACC_VOLATILE\nACC_TRANSIENT\n");
            break;
            default:
            break;
        }
        switch (field->access_flags & 0xf000) {
            case 0x1000:
            printf("ACC_SYNTHETIC\n");
            break;
            case 0x4000:
            printf("ACC_ENUM\n");
            break;
            case 0x5000:
            printf("ACC_SYNTHETIC\nACC_ENUM\n");
            break;
            default:
            break;
        }
        printf("Attributes count: %d\n\n", field->attributes_count);
    }
};

void print_method_info(method_info * * methods, u2 methods_count) {
    //int count = 0;
    ClassFileBuffer * classes = get_class_file_buffer();
    cp_info * * constant = classes->buffer->constant_pool;
    printf("\n====================================================================\nMethods\n");
    for (int i = 0; i < methods_count; i++) {
        method_info * method = methods[i];
        printf("[%d] %s", i, constant[method->name_index - 1]->Utf8.bytes);
        printf("Name: cp_info#%d <%s>\n", method->name_index, constant[method->name_index - 1]->Utf8.bytes);
        printf("Descriptor: cp_info#%d <%s>\n", method->descriptor_index, constant[method->descriptor_index - 1]->Utf8.bytes);
        printf("Access flags: 0x%x", method->access_flags);
        switch (method->access_flags & 0x000f) {
            case 0x0001:
            printf("ACC_PUBLIC\n");
            break;
            case 0x0002:
            printf("ACC_PRIVATE\n");
            break;
            case 0x0004:
            printf("ACC_PROTECTED\n");
            break;
            case 0x0008:
            printf("ACC_STATIC\n");
            break;
            case 0x0003:
            printf("ACC_PUBLIC\nACC_PRIVATE\n");
            break;
            case 0x0005:
            printf("ACC_PUBLIC\nACC_PROTECTED\n");
            break;
            case 0x0009:
            printf("ACC_PUBLIC\nACC_STATIC\n");
            break;
            case 0x0006:
            printf("ACC_PRIVATE\nACC_PROTECTED\n");
            break;
            case 0x000a:
            printf("ACC_PRIVATE\nACC_STATIC\n");
            break;
            case 0x000c:
            printf("ACC_PROTECTED\nACC_STATIC\n");
            break;
            case 0x0007:
            printf("ACC_PUBLIC\nACC_PRIVATE\nACC_PROTECTED\n");
            break;
            case 0x000b:
            printf("ACC_PUBLIC\nACC_PRIVATE\nACC_STATIC\n");
            break;
            case 0x000d:
            printf("ACC_PUBLIC\nACC_PROTECTED\nACC_STATIC\n");
            break;
            case 0x000e:
            printf("ACC_PRIVATE\nACC_PROTECTED\nACC_STATIC\n");
            break;
            case 0x000f:
            printf("ACC_PUBLIC\nACC_PRIVATE\nACC_PROTECTED\nACC_STATIC\n");
            break;
            default:
            break;
        }
        switch (method->access_flags & 0x00f0) {
            case 0x0010:
            printf("ACC_FINAL\n");
            break;
            case 0x0020:
            printf("ACC_SYNCHRONIZED\n");
            break;
            case 0x0040:
            printf("ACC_BRIDGE\n");
            break;
            case 0x0080:
            printf("ACC_VARARGS\n");
            break;
            case 0x0030:
            printf("ACC_FINAL\nACC_SYNCHRONIZED\n");
            break;
            case 0x0050:
            printf("ACC_FINAL\nACC_BRIDGE\n");
            break;
            case 0x0090:
            printf("ACC_FINAL\nACC_VARARGS\n");
            break;
            case 0x0060:
            printf("ACC_SYNCHRONIZED\nACC_BRIDGE\n");
            break;
            case 0x00a0:
            printf("ACC_SYNCHRONIZED\nACC_VARARGS\n");
            break;
            case 0x00c0:
            printf("ACC_BRIDGE\nACC_VARARGS\n");
            break;
            case 0x0070:
            printf("ACC_FINAL\nACC_SYNCHRONIZED\nACC_BRIDGE\n");
            break;
            case 0x00b0:
            printf("ACC_FINAL\nACC_SYNCHRONIZED\nACC_VARARGS\n");
            break;
            case 0x00d0:
            printf("ACC_FINAL\nACC_BRIDGE\nACC_VARARGS\n");
            break;
            case 0x00e0:
            printf("ACC_SYNCHRONIZED\nACC_BRIDGE\nACC_VARARGS\n");
            break;
            case 0x00f0:
            printf("ACC_FINAL\nACC_SYNCHRONIZED\nACC_BRIDGE\nACC_VARARGS\n");
            break;
            default:
            break;
        }
        switch (method->access_flags & 0x0f00) {
            case 0x0100:
            printf("ACC_NATIVE\n");
            break;
            case 0x0400:
            printf("ACC_ABSTRACT\n");
            break;
            case 0x0800:
            printf("ACC_STRICT\n");
            break;
            case 0x0300:
            printf("ACC_NATIVE\nACC_ABSTRACT\n");
            break;
            case 0x0900:
            printf("ACC_NATIVE\nACC_STRICT\n");
            break;
            case 0x0c00:
            printf("ACC_ABSTRACT\nACC_STRICT\n");
            break;
            case 0x0b00:
            printf("ACC_NATIVE\nACC_ABSTRACT\nACC_STRICT\n");
            break;
            default:
            break;
        }
        switch (method->access_flags & 0xf000) {
            case 0x1000:
            printf("ACC_SYNTHETIC\n");
            break;
            default:
            break;
        }
        printf("Attributes count: %d\n\n", method->attributes_count);
    }
}

/* #define CONSTANT_Utf8 1

char *get_utf8_from_constant_pool(cp_info **constant_pool, u2 index) {
    if (constant_pool == NULL || constant_pool[index] == NULL) {
        return "NULL";
    }

    if (constant_pool[index]->tag != CONSTANT_Utf8) {
        return "TIPO INVÁLIDO";
    }

    // Aloca uma nova string com terminador nulo
    u2 length = constant_pool[index]->Utf8.length;
    char *utf8_string = (char *)malloc(length + 1);
    if (utf8_string == NULL) {
        return "ERRO ALOC";
    }

    memcpy(utf8_string, constant_pool[index]->Utf8.bytes, length);
    utf8_string[length] = '\0';

    return utf8_string;
}
 */
typedef enum {
    ATTR_UNKNOWN,
    ATTR_CONSTANTVALUE,
    ATTR_CODE,
    ATTR_EXCEPTIONS,
    ATTR_INNERCLASSES,
    ATTR_SOURCEFILE,
    ATTR_LINENUMBERTABLE
} AttributeType;

AttributeType get_attribute_type(const char *name) {
    if (strcmp(name, "ConstantValue") == 0) return ATTR_CONSTANTVALUE;
    if (strcmp(name, "Code") == 0) return ATTR_CODE;
    if (strcmp(name, "Exceptions") == 0) return ATTR_EXCEPTIONS;
    if (strcmp(name, "InnerClasses") == 0) return ATTR_INNERCLASSES;
    if (strcmp(name, "SourceFile") == 0) return ATTR_SOURCEFILE;
    if (strcmp(name, "LineNumberTable") == 0) return ATTR_LINENUMBERTABLE;
    return ATTR_UNKNOWN;
}


//void print_code(u1* code, u4 code_length, cp_info** constant_pool) {
void print_code(u1* code, u4 code_length) {
    printf("          Code:\n");
    for (u4 i = 0; i < code_length; ) {
        printf("            %u: ", i);
        u1 opcode = code[i];
        switch (opcode) {
            case 0x2a: printf("aload_0\n"); i += 1; break;
            case 0x2b: printf("aload_1\n"); i += 1; break;
            case 0xb1: printf("return\n"); i += 1; break;
            case 0xb2: printf("getstatic #%u\n", (code[i+1] << 8) | code[i+2]); i += 3; break;
            case 0x12: printf("ldc #%u\n", code[i+1]); i += 2; break;
            case 0xb6: printf("invokevirtual #%u\n", (code[i+1] << 8) | code[i+2]); i += 3; break;
            case 0xb7: printf("invokespecial #%u\n", (code[i+1] << 8) | code[i+2]); i += 3; break;
            
            default:
                printf("opcode 0x%02x (não implementado)\n", opcode);
                i += 1;
                break;
        }
    }
}
void print_attribute_info(attribute_info **attributes, u2 attribute_count, cp_info** constant_pool) {
    if (attribute_count == 0) return;
    
    printf("\n    Attributes:\n");
    for (int i = 0; i < attribute_count; i++) {
        attribute_info *attr = attributes[i];
        if (attr == NULL) continue;

        // É mais seguro usar uma função auxiliar que copia a string
        char *attribute_name = (char*)constant_pool[attr->attribute_name_index - 1]->Utf8.bytes;
        AttributeType type = get_attribute_type(attribute_name);

        printf("      [%d] %s\n", i, attribute_name);
        printf("        - Attribute name index: cp_info #%u\n", attr->attribute_name_index);
        printf("        - Attribute length: %u\n", attr->attribute_length);

        switch (type) {
            case ATTR_CONSTANTVALUE:
                printf("        - Constant value index: cp_info #%u\n", attr->ConstantValue.constantvalue_index);
                break;

            case ATTR_CODE:
                printf("        Code Attribute:\n");
                printf("          - Maximum stack size: %u\n", attr->Code.max_stack);
                printf("          - Maximum local variables: %u\n", attr->Code.max_locals);
                printf("          - Code length: %u\n", attr->Code.code_length);
                //print_code(attr->Code.code, attr->Code.code_length, constant_pool);
                print_code(attr->Code.code, attr->Code.code_length);

                if (attr->Code.exception_table_length > 0) {
                    printf("          Exception table:\n");
                    for (int j = 0; j < attr->Code.exception_table_length; j++) {
                        printf("            - Exception %d: from %u to %u, target %u, type ", 
                               j,
                               attr->Code.exception_table[j].start_pc,
                               attr->Code.exception_table[j].end_pc,
                               attr->Code.exception_table[j].handler_pc);
                        if(attr->Code.exception_table[j].catch_type == 0) {
                            printf("any\n");
                        } else {
                            printf("cp_info #%u\n", attr->Code.exception_table[j].catch_type);
                        }
                    }
                }
                
                // Chamada recursiva para exibir os atributos aninhados (ex: LineNumberTable)
                if (attr->Code.attributes_count > 0) {
                    print_attribute_info(attr->Code.attributes, attr->Code.attributes_count, constant_pool);
                }
                break;

            case ATTR_EXCEPTIONS:
                printf("        - Number of exceptions: %u\n", attr->Exceptions.number_of_exceptions);
                for (int j = 0; j < attr->Exceptions.number_of_exceptions; j++) {
                    printf("          - Exception #%d: cp_info #%u\n", j, attr->Exceptions.exception_index_table[j]);
                }
                break;
            
            case ATTR_INNERCLASSES:
                 printf("        - Number of classes: %u\n", attr->InnerClasses.number_of_classes);
                 for (int j = 0; j < attr->InnerClasses.number_of_classes; j++) {
                    classes cls = attr->InnerClasses.classes[j];
                    printf("          - Inner Class #%d:\n", j);
                    printf("            - Inner class info:  cp_info #%u\n", cls.inner_class_info_index);
                    printf("            - Outer class info:  cp_info #%u\n", cls.outer_class_info_index);
                    printf("            - Inner name:        cp_info #%u\n", cls.inner_name_index);
                    printf("            - Access flags:      0x%04X\n", cls.inner_class_access_flags);
                 }
                 break;

            case ATTR_SOURCEFILE:
                // Supondo que a estrutura para SourceFile tenha sido adicionada em types.h
                // printf("        - Source file name index: cp_info #%u\n", attr->SourceFile.sourcefile_index);
                break;

            case ATTR_UNKNOWN:
            default:
                printf("        - (Atributo não implementado ou desconhecido)\n");
                break;
        }
        printf("\n");
    }
}


