#ifndef STACK_H
#define STACK_H

#include "../shared/shared.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct stack {
  uint8_t st_int[MAX_STACK_SIZE];
  size_t sp;
} Stack;

bool stack_push(Stack *stack, uint8_t value[], size_t size);
bool stack_pop(Stack *stack, uint8_t dest[], size_t size);
bool stack_peek(Stack *stack, uint8_t dest[], size_t size);
bool stack_set_sp(Stack *stack, size_t n);

#endif // !DEBUG
