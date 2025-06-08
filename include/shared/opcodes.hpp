#pragma once

#include <cstdint>

enum OpCodes : uint8_t {
  // --- Stack Manipulation (0x00–0x0F) ---
  OP_PUSH = 0x00, // push <value>
  OP_POP = 0x01,  // pop
  OP_DUP = 0x02,  // duplicate top
  OP_SWAP = 0x03, // swap top two
  OP_OVER = 0x04, // copy second to top
  OP_DROP = 0x05, // discard top

  // --- Arithmetic (0x10–0x1F) ---
  OP_ADD = 0x10, // a + b
  OP_SUB = 0x11, // a - b
  OP_MUL = 0x12, // a * b
  OP_DIV = 0x13, // a / b
  OP_MOD = 0x14, // a % b

  // --- Comparison / Logic (0x20–0x2F) ---
  OP_EQ = 0x20,  // a == b
  OP_NEQ = 0x21, // a != b
  OP_LT = 0x22,  // a < b
  OP_LTE = 0x23, // a <= b
  OP_GT = 0x24,  // a > b
  OP_GTE = 0x25, // a >= b

  // --- Control Flow (0x30–0x3F) ---
  OP_JMP = 0x30,    // jump <addr>
  OP_JMP_IF = 0x31, // jump if top != 0
  OP_CALL = 0x32,   // call <addr>
  OP_RET = 0x33,    // return

  // --- Bitwise / Boolean (0x40–0x4F) ---
  OP_AND = 0x40, // a & b
  OP_OR = 0x41,  // a | b
  OP_XOR = 0x42, // a ^ b
  OP_NOT = 0x43, // ~a
  OP_SHL = 0x44, // a << b
  OP_SHR = 0x45, // a >> b

  // --- Memory Access (0x50–0x5F) ---
  OP_LOAD = 0x50, // load [addr]
  OP_STORE = 0x51 // store [addr]
};
