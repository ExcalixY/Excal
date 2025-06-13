#ifndef ERROR_H
#define ERROR_H

#include <stdarg.h>

typedef enum {
  ERR_WARNING,
  ERR_INFO,
  ERR_FATAL,
} ErrSeverity;

typedef enum {
  // ========== No Error ==========
  NO_ERR = 0,
  ERR_FILE_NOT_FOUND,
  ERR_FILE_UNKNOWN_TYPE,

  // ========== Compiler Errors (1000–1999) ==========
  ERR_COMP_SYNTAX = 1000,         // General syntax error
  ERR_COMP_UNDECLARED_IDENTIFIER, // Variable or symbol used before definition
  ERR_COMP_TYPE_MISMATCH,         // Conflicting types in operation
  ERR_COMP_INVALID_LITERAL,       // Malformed number, string, etc.
  ERR_COMP_INVALID_TOKEN,         // Unexpected character or token
  ERR_COMP_UNSUPPORTED_FEATURE,   // Feature not yet implemented
  ERR_COMP_OUTPUT_WRITE_FAIL,     // Couldn't write output file
  ERR_COMP_INTERNAL,              // Internal compiler error
  ERR_COMP_MISSING_ARG,           // Missing another argument in compiler call

  // ========== Assembler Errors (2000–2999) ==========
  ERR_ASM_INVALID_OPCODE = 2000, // Unknown or malformed instruction
  ERR_ASM_SYNTAX,                // Assembly syntax error
  ERR_ASM_UNDEFINED_LABEL,       // Jump/branch to unknown label
  ERR_ASM_DUPLICATE_LABEL,       // Label redefined
  ERR_ASM_INVALID_OPERAND,       // Wrong type or number of operands
  ERR_ASM_WRITE_FAIL,            // Failed to write bytecode output
  ERR_ASM_OVERFLOW,              // Instruction size or byte overflow
  ERR_ASM_INTERNAL,              // Internal assembler error
  ERR_ASM_BUFFER_OVERFLOW,       // Instruction reached over 32 characeters

  // ========== VM Runtime Errors (3000–3999) ==========
  ERR_VM_STACK_UNDERFLOW = 3000, // Tried to pop from empty stack
  ERR_VM_STACK_OVERFLOW,         // Stack exceeded max size
  ERR_VM_INVALID_INSTRUCTION,    // Unrecognized opcode
  ERR_VM_INVALID_MEMORY_ACCESS,  // Memory access out of bounds
  ERR_VM_DIVIDE_BY_ZERO,         // Division by zero
  ERR_VM_NULL_POINTER,           // Dereferencing null or invalid pointer
  ERR_VM_BAD_SYSCALL,            // Invalid or undefined syscall
  ERR_VM_HALT_UNEXPECTED,        // Halt with inconsistent state
  ERR_VM_REGISTER_UNDEFINED,     // Reading from uninitialized register
  ERR_VM_INTERNAL,               // Internal VM failure
} ErrCodes;

const char *err_get_msg(ErrCodes err_code);

void write_err(ErrCodes err_code, ErrSeverity err_sev, int pos, const char *msg,
               ...);

#endif
