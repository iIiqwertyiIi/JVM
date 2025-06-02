#include "reader.h"

Buffer * get_buffer() {
    static Buffer buffer;
    return &buffer;
}

void read_file(char * filename) {
    Buffer * buffer = get_buffer();
    if (buffer->buffer != NULL) {
        free(buffer);
    }

    FILE * file = fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    
    buffer->buffer = malloc(size);
    fread(buffer->buffer, 1, size, file);
    fclose(file);

    buffer->position = 0;
}

u1 u1read() {
    Buffer * buffer = get_buffer();
    u1 value = buffer->buffer[buffer->position];
    buffer->position++;
    return value;
}

u2 u2read() {
    Buffer * buffer = get_buffer();
    u2 value = buffer->buffer[buffer->position] << 8;
    value |= buffer->buffer[buffer->position + 1];
    buffer->position += 2;
    return value;
}

u4 u4read() {
    Buffer * buffer = get_buffer();
    u4 value = buffer->buffer[buffer->position] << 24;
    value |= buffer->buffer[buffer->position + 1] << 16;
    value |= buffer->buffer[buffer->position + 2] << 8;
    value |= buffer->buffer[buffer->position + 3];
    buffer->position += 4;
    return value;
}