#ifndef TYPES_H
#define TYPES_H
#include <stdint.h>

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

typedef struct Buffer {
    u1 * buffer;
    u8 position;
} Buffer;

typedef struct cp_info {
    u1 tag;
    union {
        struct {
            u2 name_index;
        } Class;
        struct {
            u2 class_index;
            u2 name_and_type_index;
        } Fieldref;
        struct {
            u2 class_index;
            u2 name_and_type_index;
        } Methodref;
        struct {
            u2 class_index;
            u2 name_and_type_index;
        } InterfaceMethodref;
        struct {
            u2 name_index;
            u2 descriptor_index;
        } NameAndType;
        struct {
            u2 length;
            u1 * bytes;
        } Utf8;
        struct {
            u2 string_index;
        } String;
        struct {
            u4 bytes;
        } Integer;
        struct {
            u4 bytes;
        } Float;
        struct {
            u4 high_bytes;
            u4 low_bytes;
        } Long;
        struct {
            u4 high_bytes;
            u4 low_bytes;
        } Double;
    };
} cp_info;

typedef struct exception_table {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
} exception_table;

typedef struct classes {
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
} classes;

typedef struct attribute_info {
    u2 attribute_name_index;
    u4 attribute_length;
    union {
        struct {
            u2 constantvalue_index;
        } ConstantValue;
        struct {
            u2 max_stack;
            u2 max_locals;
            u4 code_length;
            u1 * code;
            u2 exception_table_length;
            exception_table * exception_table;
            u2 attributes_count;
            attribute_info * attributes;
        } Code;
        struct {
            u2 number_of_exceptions;
            u2 * exception_index_table;
        } Exceptions;
        struct {
            u2 number_of_classes;
            classes * classes;
        } InnerClasses;
    };
} attribute_info;

typedef struct field_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info * attributes;
} field_info;

typedef struct method_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info * attributes;
} method_info;

typedef struct ClassFile {
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info * * constant_pool;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 * interfaces;
    u2 fields_count;
    field_info * * fields;
    u2 methods_count;
    method_info * * methods;
    u2 attributes_count;
    attribute_info * * attributes;
} ClassFile;

#endif