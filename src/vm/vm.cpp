#include "../../include/vm/vm.hpp"

bool VM::adv_ptr() {
  ip++;

  if (ip > bt_size) {
    return false;
  }

  return true;
}

void VM::exec_inst() {}
