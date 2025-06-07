#include "../../include/vm/stack.hpp"
#include <cstring>
#include <stdexcept>

void Stack::push(uint8_t *value, size_t size) {
  if (sp + size > MAX_STACK_SIZE) {
    std::overflow_error("Stack overflow.");
  }

  std::memcpy(&st_int[sp], value, size);

  sp += size;
}

void Stack::pop(uint8_t *dest, size_t size) {
  if (sp - size < 0) {
    std::underflow_error("Stack underflow");
  }

  sp -= size;
  std::memcpy(dest, &st_int[sp], size);
}

void Stack::peek(uint8_t *dest, size_t size) {
  if (sp - size < 0) {
    std::underflow_error("Stack underflow");
  }

  std::memcpy(dest, &st_int[sp - size], size);
}

void Stack::set_sp(size_t n) { sp = n; }
