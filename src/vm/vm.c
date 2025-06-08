#include "../../include/vm/vm.h"

bool vm_init(VM *vm) {
  vm->stack.sp = 0;

  return true;
}

bool vm_adv_ptr(VM *vm) {
  vm->ip++;

  if (vm->ip > vm->bt_size) {
    return false;
  }

  return true;
}

int vm_exec_inst(VM *vm) {
  while (vm_adv_ptr(vm)) {
    if (vm->bt[vm->ip] == OP_PUSH) {
    }
  }

  return 0;
}
