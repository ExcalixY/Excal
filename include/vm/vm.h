#ifndef VM_H
#define VM_H

#include "../shared/opcodes.h"
#include "../shared/shared.h"

#include "heap.h"
#include "stack.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct vm {
  size_t ip;
  size_t bt_size;
  Stack stack;
  uint8_t bt[MAX_STACK_SIZE];
} VM;

bool vm_init(VM *vm);
bool vm_adv_ptr(VM *vm);
int vm_exec_inst(VM *vm);

#endif
