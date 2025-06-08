#include "../../include/vm/stack.h"

#include <memory.h>

bool stack_init(Stack *stack) { stack->sp = 0; }

bool stack_push(Stack *stack, uint8_t *value, size_t size) {
  if (stack->sp + size > MAX_STACK_SIZE) {
    return false;
  }

  memcpy(&stack->st_int[stack->sp], value, size);

  stack->sp += size;
}

bool stack_pop(Stack *stack, uint8_t *dest, size_t size) {
  if (stack->sp - size < 0) {
    return false;
  }

  stack->sp -= size;
  memcpy(dest, &stack->st_int[stack->sp], size);

  return true;
}

bool stack_peek(Stack *stack, uint8_t *dest, size_t size) {
  if (stack->sp - size < 0) {
    return true;
  }

  memcpy(dest, &stack->st_int[stack->sp - size], size);
  return false;
}

bool stack_set_sp(Stack *stack, size_t n) {
  stack->sp = n;
  return stack->sp == n;
}
