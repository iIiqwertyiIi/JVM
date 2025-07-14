#include "array.h"

ArrayList * get_array_list() {
    static ArrayList array_list;
    return &array_list;
}

Array * get_array(uint32_t index) {
  ArrayList * array_list = get_array_list();
  if (index >= array_list->size) {
    return NULL;
  }
  return array_list->array[index];
}

u4 add_array(Array * array) {
    ArrayList * array_list = get_array_list();
    array_list->size++;
    array_list->array = realloc(array_list->array, sizeof(Array *) * array_list->size);
    array_list->array[array_list->size - 1] = array;
    return array_list->size - 1;
}

int newarray(Frame * frame, Instruction instruction) {
    u4 size = remove_from_stack(frame);
    Array * array = malloc(sizeof(Array));
    if (instruction.operands[0] == 7 || instruction.operands[0] == 11) {
        array->size = size * 2;
    } else {
        array->size = size;
    }
    array->array = malloc(sizeof(ArrayTypes) * size);
    u4 index = add_array(array);
    add_to_stack(frame, index);
    return 0;
}

int anewarray(Frame * frame, Instruction instruction) {
    u4 size = remove_from_stack(frame);
    Array * array = malloc(sizeof(Array));
    array->size = size;
    array->array = malloc(sizeof(ArrayTypes) * size);
    u4 index = add_array(array);
    add_to_stack(frame, index);
    return 0;
}

int arraylength(Frame * frame, Instruction instruction) {
    u4 index = remove_from_stack(frame);
    Array * array = get_array(index);
    add_to_stack(frame, array->size);
    return 0;
}

int multianewarray(Frame * frame, Instruction instruction) {
    u1 dimensions = instruction.operands[2];
    u4 size_2 = remove_from_stack(frame);
    u4 size_1 = remove_from_stack(frame);

    Array * array = malloc(sizeof(Array));
    array->size = size_1;
    array->array = malloc(sizeof(ArrayTypes) * size_1);

    for (int i = 0; i < size_1; i++) {
        Array * inner_array = malloc(sizeof(Array));
        inner_array->size = size_2;
        inner_array->array = malloc(sizeof(ArrayTypes) * size_2);
        u4 inner = add_array(inner_array);
        array->array[i].reference = inner;
    }
    u4 index = add_array(array);

    add_to_stack(frame, index);

    return 0;
}