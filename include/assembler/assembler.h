#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdint.h>

typedef struct {
  uint8_t *bt;

} Assembler;

void asm_init();

#endif
