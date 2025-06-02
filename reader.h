#ifndef READER_H
#define READER_H
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

u1 u1read();
u2 u2read();
u4 u4read();

void read_file(char * filename);

Buffer * get_buffer();

#endif