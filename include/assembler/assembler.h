#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "../../include/shared/shared.h"
#include "../../lib/fstream/fstream.h"

#include <fstream.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_BUFFER_SIZE 255

typedef struct {
  fstream fs_in;
  fstream fs_out;
  char buffer[MAX_BUFFER_SIZE + 1];
  size_t line;
} Assembler;

int asm_init(Assembler *a, const char *filename);
void asm_compile(Assembler *a);
void asm_stop(Assembler *a);
uint8_t *asm_parse_value(Assembler *a, char type);
size_t asm_get_size(char type);
char asm_write_type(Assembler *a);

#endif
