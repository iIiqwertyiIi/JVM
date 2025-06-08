#include "output.h"

void print_class_file(ClassFile * class_file) {
    printf("Assinatura: 0x%x\n", class_file->magic);
    printf("Minor version: %d\n", class_file->minor_version);
    printf("Major version: %d [1.%d]\n", class_file->major_version, class_file->major_version - 44);
    printf("Constant pool count: %d\n", class_file->constant_pool_count);
    printf("Access flags: 0x%x\n", class_file->access_flags);
    switch (class_file-> access_flags & 0x000f) {
        case 0x0001:
        printf("ACC_PUBLIC\n");
        break;
        default:
        break;
    }
    switch (class_file-> access_flags & 0x00f0) {
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
    switch (class_file-> access_flags & 0x0f00) {
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
    switch (class_file-> access_flags & 0xf000) {
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
        case 0x7000:
        printf("ACC_SYNTHETIC\nACC_ANNOTATION\nACC_ENUM\n");
        default:
        break;
    }
    printf("This class: cp_info#%d %s\n", class_file->this_class, class_file->constant_pool[class_file->this_class - 1]->Utf8.bytes);
    printf("Super class: cp_info#%d %s\n", class_file->super_class, class_file->constant_pool[class_file->super_class - 1]->Utf8.bytes);
    printf("Interfaces count: %d\n", class_file->interfaces_count);
    printf("Fields count: %d\n", class_file->fields_count);
    printf("Methods count: %d\n", class_file->methods_count);
    printf("Attributes count: %d\n", class_file->attributes_count);
}

void print_cp_info(cp_info * * constant_pool, u2 constant_pool_count) {
    int count = 1;
    printf("\n====================================================================\n\n");
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
            printf("Long: %ld\n\n", (u8) constant->Long.high_bytes << 32 | constant->Long.low_bytes);
            break;
            case 6:
            printf("[%d] CONSTANT_Double_info\n", i + 1);
            printf("High Bytes: 0x%x\n", constant->Double.high_bytes);
            printf("Low Bytes: 0x%x\n", constant->Double.low_bytes);
            printf("Double: %lf\n\n", ((u8) constant->Double.high_bytes << 32 | constant->Double.low_bytes));
            break;
        }
    }
}

void print_field_info(field_info * * field_info, u2 fields_count) {
    int count = 0;
    printf("\n====================================================================\n\n");
    
};