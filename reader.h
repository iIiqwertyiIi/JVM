#ifndef READER_H
#define READER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

u1 u1read();
u1 u1read_buffer(Buffer * buffer);
u2 u2read();
u4 u4read();
u4 u4read_buffer(Buffer * buffer);

void read_file(char * filename);

Buffer * get_buffer();
void free_buffer();

#endif