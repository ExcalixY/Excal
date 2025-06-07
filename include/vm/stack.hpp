#pragma once

#include "../shared/shared.hpp"

#include <cstddef>

class Stack {
private:
  uint8_t st_int[MAX_STACK_SIZE];
  size_t sp = 0;

public:
  void push(uint8_t value[], size_t size);
  void pop(uint8_t dest[], size_t size);
  void peek(uint8_t dest[], size_t size);
  void set_sp(size_t n);
};
