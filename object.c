#include "object.h"

ObjectList * get_object_list() {
  static ObjectList object_list;
  return &object_list;
}

Object * get_object(u4 index) {
    ObjectList * object_list = get_object_list;
    return object_list->object[index];
}

u4 add_object(Object * object) {
  ObjectList * object_list = get_object_list();
  object_list->size++;
  if (object_list->object == NULL) {
    object_list->object = malloc(sizeof(Object *) * object_list->size);
  } else {
    object_list->object = realloc(object_list->object, sizeof(Object *) * object_list->size);
  }
  object_list->object[object_list->size - 1] = object;
  return object_list->size - 1;
}

int new_(Frame * frame, Instruction instruction) {
    u2 index = (((u2) instruction.operands[0]) << 8) | instruction.operands[1];
    char * class_name = frame->this_class->constant_pool[frame->this_class->constant_pool[index - 1]->Class.name_index - 1]->Utf8.bytes;
    ClassFile * class_file = get_class_file(class_name);
    Object * object = malloc(sizeof(Object));
    object->class = class_file;
    object->fields = malloc(sizeof(ActiveField **) * (class_file->fields_count - class_file->static_fields_count));
    for (int i = 0; i < class_file->fields_count; i++) {
        if (class_file->fields[i]->access_flags & 0x8) {
            continue;
        }
        object->fields[i] = malloc(sizeof(ActiveField));
        object->fields[i]->field = class_file->fields[i];
        object->fields[i]->value = 0;
    }
    u4 ref = add_object(object);
    add_to_stack(frame, ref);
    return 0;
}

ActiveField * get_static_field(ClassFile * class_file, char * field_name, char * field_descriptor) {
    for (int i = 0; i < class_file->static_fields_count; i++) {
        char * name = class_file->constant_pool[class_file->static_fields[i]->field->name_index - 1]->Utf8.bytes;
        if (strcmp(name, field_name) == 0) {
            char * descriptor = class_file->constant_pool[class_file->static_fields[i]->field->descriptor_index - 1]->Utf8.bytes;
            if (strcmp(descriptor, field_descriptor) == 0) {
                return class_file->static_fields[i];
            }
        }
    }
    return NULL;
}

int getstatic(Frame * frame, Instruction instruction) {
    u2 index = (((u2) instruction.operands[0]) << 8) | instruction.operands[1];
    cp_info * fieldref = frame->this_class->constant_pool[index - 1];
    char * class_name = frame->this_class->constant_pool[frame->this_class->constant_pool[fieldref->Fieldref.class_index - 1]->Class.name_index - 1]->Utf8.bytes;
    ClassFile * class_file = get_class_file(class_name);
    cp_info * nameandtype = frame->this_class->constant_pool[fieldref->Fieldref.name_and_type_index];
    char * field_name = frame->this_class->constant_pool[nameandtype->NameAndType.name_index - 1]->Utf8.bytes;
    char * field_descriptor = frame->this_class->constant_pool[nameandtype->NameAndType.descriptor_index - 1]->Utf8.bytes;

    ActiveField * field = get_static_field(class_file, field_name, field_descriptor);
    if (field_descriptor[0] == 'J' || field_descriptor[0] == 'D') {
        add_to_stack(frame, field->extra);
    }
    add_to_stack(frame, field->value);
    return 0;
}

int putstatic(Frame * frame, Instruction instruction) {
    u2 index = (((u2) instruction.operands[0]) << 8) | instruction.operands[1];
    cp_info * fieldref = frame->this_class->constant_pool[index - 1];
    char * class_name = frame->this_class->constant_pool[frame->this_class->constant_pool[fieldref->Fieldref.class_index - 1]->Class.name_index - 1]->Utf8.bytes;
    ClassFile * class_file = get_class_file(class_name);
    cp_info * nameandtype = frame->this_class->constant_pool[fieldref->Fieldref.name_and_type_index];
    char * field_name = frame->this_class->constant_pool[nameandtype->NameAndType.name_index - 1]->Utf8.bytes;
    char * field_descriptor = frame->this_class->constant_pool[nameandtype->NameAndType.descriptor_index - 1]->Utf8.bytes;

    ActiveField * field = get_static_field(class_file, field_name, field_descriptor);
    field->value = remove_from_stack(frame);
    if (field_descriptor[0] == 'J' || field_descriptor[0] == 'D') {
        field->extra = remove_from_stack(frame);
    }
    return 0;
}

ActiveField * get_field(Object * object, char * field_name, char * field_descriptor) {
    for (int i = 0; i < object->class->fields_count; i++) {
        char * name = object->class->constant_pool[object->fields[i]->field->name_index - 1]->Utf8.bytes;
        if (strcmp(name, field_name) == 0) {
            char * descriptor = object->class->constant_pool[object->fields[i]->field->descriptor_index - 1]->Utf8.bytes;
            if (strcmp(descriptor, field_descriptor) == 0) {
                return object->fields[i];
            }
        }
    }
    return NULL;
}

int getfield(Frame * frame, Instruction instruction) {
    u2 index = (((u2) instruction.operands[0]) << 8) | instruction.operands[1];
    cp_info * fieldref = frame->this_class->constant_pool[index - 1];
    char * class_name = frame->this_class->constant_pool[frame->this_class->constant_pool[fieldref->Fieldref.class_index - 1]->Class.name_index - 1]->Utf8.bytes;
    ClassFile * class_file = get_class_file(class_name);
    cp_info * nameandtype = frame->this_class->constant_pool[fieldref->Fieldref.name_and_type_index];
    char * field_name = frame->this_class->constant_pool[nameandtype->NameAndType.name_index - 1]->Utf8.bytes;
    char * field_descriptor = frame->this_class->constant_pool[nameandtype->NameAndType.descriptor_index - 1]->Utf8.bytes;

    ActiveField * field = get_field(class_file, field_name, field_descriptor);
    if (field_descriptor[0] == 'J' || field_descriptor[0] == 'D') {
        add_to_stack(frame, field->extra);
    }
    add_to_stack(frame, field->value);
    return 0;
}

int putfield(Frame * frame, Instruction instruction) {
    u2 index = (((u2) instruction.operands[0]) << 8) | instruction.operands[1];
    cp_info * fieldref = frame->this_class->constant_pool[index - 1];
    
    cp_info * nameandtype = frame->this_class->constant_pool[fieldref->Fieldref.name_and_type_index];
    char * field_name = frame->this_class->constant_pool[nameandtype->NameAndType.name_index - 1]->Utf8.bytes;
    char * field_descriptor = frame->this_class->constant_pool[nameandtype->NameAndType.descriptor_index - 1]->Utf8.bytes;

    u4 high = remove_from_stack(frame);
    u4 low;
    if (field_descriptor[0] == 'J' || field_descriptor[0] == 'D') {
        u4 low = remove_from_stack(frame);
    }

    Object * object = get_object(remove_from_stack(frame));

    ActiveField * field = get_field(object, field_name, field_descriptor);
    if (field_descriptor[0] == 'J' || field_descriptor[0] == 'D') {
        field->extra = low;
    }
    field->value = high;
    return 0;
}