#include "../../include/shared/err.h"

#include <stdio.h>

const char *get_err_msg(ErrCodes err_code) {
  switch (err_code) {

  case NO_ERR:
    return "NO_ERR";
  case ERR_COMP_FILE_NOT_FOUND:
    return "ERR_COMP_FILE_NOT_FOUND";
  case ERR_COMP_SYNTAX:
    return "ERR_COMP_SYNTAX";
  case ERR_COMP_UNDECLARED_IDENTIFIER:
    return "ERR_COMP_UNDECLARED_IDENTIFIER";
  case ERR_COMP_TYPE_MISMATCH:
    return "ERR_COMP_TYPE_MISMATCH";
  case ERR_COMP_INVALID_LITERAL:
    return "ERR_COMP_INVALID_LITERAL";
  case ERR_COMP_INVALID_TOKEN:
    return "ERR_COMP_INVALID_TOKEN";
  case ERR_COMP_UNSUPPORTED_FEATURE:
    return "ERR_COMP_UNSUPPORTED_FEATURE";
  case ERR_COMP_OUTPUT_WRITE_FAIL:
    return "ERR_COMP_OUTPUT_WRITE_FAIL";
  case ERR_COMP_INTERNAL:
    return "ERR_COMP_INTERNAL";

  case ERR_ASM_FILE_NOT_FOUND:
    return "ERR_ASM_FILE_NOT_FOUND";
  case ERR_ASM_INVALID_OPCODE:
    return "ERR_ASM_INVALID_OPCODE";
  case ERR_ASM_SYNTAX:
    return "ERR_ASM_SYNTAX";
  case ERR_ASM_UNDEFINED_LABEL:
    return "ERR_ASM_UNDEFINED_LABEL";
  case ERR_ASM_DUPLICATE_LABEL:
    return "ERR_ASM_DUPLICATE_LABEL";
  case ERR_ASM_INVALID_OPERAND:
    return "ERR_ASM_INVALID_OPERAND";
  case ERR_ASM_WRITE_FAIL:
    return "ERR_ASM_WRITE_FAIL";
  case ERR_ASM_OVERFLOW:
    return "ERR_ASM_OVERFLOW";
  case ERR_ASM_INTERNAL:
    return "ERR_ASM_INTERNAL";

  case ERR_VM_STACK_UNDERFLOW:
    return "ERR_VM_STACK_UNDERFLOW";
  case ERR_VM_STACK_OVERFLOW:
    return "ERR_VM_STACK_OVERFLOW";
  case ERR_VM_INVALID_INSTRUCTION:
    return "ERR_VM_INVALID_INSTRUCTION";
  case ERR_VM_INVALID_MEMORY_ACCESS:
    return "ERR_VM_INVALID_MEMORY_ACCESS";
  case ERR_VM_DIVIDE_BY_ZERO:
    return "ERR_VM_DIVIDE_BY_ZERO";
  case ERR_VM_NULL_POINTER:
    return "ERR_VM_NULL_POINTER";
  case ERR_VM_BAD_SYSCALL:
    return "ERR_VM_BAD_SYSCALL";
  case ERR_VM_HALT_UNEXPECTED:
    return "ERR_VM_HALT_UNEXPECTED";
  case ERR_VM_REGISTER_UNDEFINED:
    return "ERR_VM_REGISTER_UNDEFINED";
  case ERR_VM_INTERNAL:
    return "ERR_VM_INTERNAL";

  default:
    return "UNKNOWN_ERROR";
  }
}

void write_err(ErrCodes err_code, int pos, const char *msg) {
  printf("\033[1;37mExcal: \033[1;31mERROR\n");
  printf("\033[1;33m%s [%d] \033[1;37m%s\n", get_err_msg(err_code), pos, msg);
  printf("\033[0m"); // Reset color
}
