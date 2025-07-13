#include "object.h"

ObjectList * get_object_list() {
  static ObjectList object_list;
  return &object_list;
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