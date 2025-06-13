#ifndef OPCODES_H
#define OPCODES_H

#include <stdint.h>

typedef enum {
  // --- Stack Manipulation (0x00–0x0F) ---
  OP_PUSH = 0x00,    // push <value>
  OP_POP = 0x01,     // pop
  OP_DUP = 0x02,     // duplicate top
  OP_SWAP = 0x03,    // swap top two
  OP_OVER = 0x04,    // copy second to top
  OP_DROP = 0x05,    // discard top
  OP_MOV = 0x06,     // move from addr to addr
  OP_SPALLOC = 0x07, // move stack pointer forward by a specified number
  OP_SPFREE = 0x08,  // move stack pointer back by a specified number

  // --- Arithmetic (0x10–0x1F) ---
  OP_ADD = 0x10, // a + b
  OP_SUB = 0x11, // a - b
  OP_MUL = 0x12, // a * b
  OP_DIV = 0x13, // a / b
  OP_MOD = 0x14, // a % b

  // --- Floating Point Arithmetic (0x20–0x2F) ---
  OP_FADD = 0x20, // float a + b
  OP_FSUB = 0x21, // float a - b
  OP_FMUL = 0x22, // float a * b
  OP_FDIV = 0x23, // float a / b
  OP_FNEG = 0x24, // float negate
  OP_FABS = 0x25, // float absolute value

  // --- Comparison / Logic (0x30–0x3F) ---
  OP_EQ = 0x30,  // a == b
  OP_NEQ = 0x31, // a != b
  OP_LT = 0x32,  // a < b
  OP_LTE = 0x33, // a <= b
  OP_GT = 0x34,  // a > b
  OP_GTE = 0x35, // a >= b

  // --- Control Flow (0x40–0x4F) ---
  OP_JMP = 0x40,     // jump <addr>
  OP_JMP_IF = 0x41,  // jump if top != 0
  OP_CALL = 0x42,    // call <addr>
  OP_RET = 0x43,     // return
  OP_SYSCALL = 0x44, // call a system function

  // --- Bitwise / Boolean (0x50–0x5F) ---
  OP_AND = 0x50, // a & b
  OP_OR = 0x51,  // a | b
  OP_XOR = 0x52, // a ^ b
  OP_NOT = 0x53, // ~a
  OP_SHL = 0x54, // a << b
  OP_SHR = 0x55, // a >> b

  // --- Memory Access (0x60–0x6F) ---
  OP_LOAD = 0x60, // load [addr]
  OP_STORE = 0x61 // store [addr]
} OpCodes;

#endif // !DEBUG
