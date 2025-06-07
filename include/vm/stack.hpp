#pragma once

#include "../shared/shared.hpp"

#include <cstdint>
#include <stdexcept>

class Stack {
private:
  std::uint8_t st_int[MAX_STACK_SIZE];
  std::size_t sp;

public:
  template <typename T> void push(T &value);
  template <typename T> T pop();
  template <typename T> T peek();
  void set_sp(int n);
};
