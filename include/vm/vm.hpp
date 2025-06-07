#pragma once

#include "../shared/shared.hpp"

#include "heap.hpp"
#include "stack.hpp"
#include <cstddef>
#include <cstdint>

class VM {
private:
  size_t ip;
  uint8_t reg[16][8];
  uint8_t *bytecode;
  size_t bt_size;

public:
  VM(uint8_t *bt) { this->bytecode = bt; }
  bool adv_ptr();
  void exec_inst();
};
