#include "../../include/assembler/assembler.h"
#include "../../include/assembler/inst_stack.h"
#include "../../include/shared/err.h"
#include "../../include/shared/shared.h"

#include <ctype.h>
#include <fstream.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int asm_init(Assembler *a, const char *filename) {
  const char *ext = strrchr(filename, '.');

  if (!ext) {
    write_err(ERR_FILE_UNKNOWN_TYPE, ERR_FATAL, 0,
              "File has no extension provided.");
    return 2;
  } else if (strcmp(ext + 1, EXT_ASM) != 0) {
    write_err(ERR_FILE_UNKNOWN_TYPE, ERR_FATAL, 1,
              "Unsupported file type '.%s'", ext + 1);
    return 1;
  }

  if (fs_open(filename, &a->fs_in, F_READ) == 1) {
    write_err(ERR_FILE_NOT_FOUND, ERR_FATAL, 0,
              "Could not find the specified file.");
    return 1;
  }

  size_t str_len = strlen(filename);
  char *filename_out = malloc(str_len - 1);
  strcpy(filename_out, filename);

  strcpy(filename_out + str_len - 3, EXT_BIN);

  if (fs_open(filename_out, &a->fs_out, F_WRITE) == 0) {
    write_err(ERR_ASM_WRITE_FAIL, ERR_FATAL, 1,
              "Could not create a file of specified name");
  }

  free(filename_out);

  return 0;
}

size_t asm_get_size(char type) {
  switch (type) {
  case 0x00:
    return 4;
  case 0x01:
    return 1;
  case 0x02:
    return 2;
  case 0x03:
    return 4;
  case 0x04:
    return 8;
  case 0x05:
    return -1;
  default:
    return 4;
  }
}

void asm_write_string(Assembler *a) {
  char c;

  while ((c = fs_get(&a->fs_in)) != '\"') {
    if (c == '\\') {
      c = fs_get(&a->fs_in);

      switch (c) {
      case 'n':
        fs_writeb(&a->fs_out, '\n');
        break;
      case 't':
        fs_writeb(&a->fs_out, '\t');
        break;
      case 'r':
        fs_writeb(&a->fs_out, '\r');
        break;
      case 'a':
        fs_writeb(&a->fs_out, '\a');
        break;
      case 'b':
        fs_writeb(&a->fs_out, '\b');
        break;
      case 'f':
        fs_writeb(&a->fs_out, '\f');
        break;
      case 'v':
        fs_writeb(&a->fs_out, '\v');
        break;
      case '\\':
        fs_writeb(&a->fs_out, '\\');
        break;
      case '\'':
        fs_writeb(&a->fs_out, '\'');
        break;
      case '\"':
        fs_writeb(&a->fs_out, '\"');
        break;
      case '?':
        fs_writeb(&a->fs_out, '\?');
        break;
      default:
        write_err(ERR_ASM_WRITE_FAIL, ERR_FATAL, 0,
                  "Invalid escape code \'\\%c\'", c);
      }
    } else {
      fs_writeb(&a->fs_out, c);
    }
  }
  fs_writeb(&a->fs_out, '\0');
}

char asm_write_type(Assembler *a) {
  if (strieq(a->buffer, "PTR")) { // 4 byte address
    return 0x00;
  } else if (strieq(a->buffer, "BYTE")) { // 1 byte
    return 0x01;
  } else if (strieq(a->buffer, "WORD")) { // 2 bytes
    return 0x02;
  } else if (strieq(a->buffer, "DWORD")) { // 4 bytes
    return 0x03;
  } else if (strieq(a->buffer, "QWORD")) { // 8 bytes
    return 0x04;
  } else if (strieq(a->buffer, "STR")) { // array of bytes
    return 0x05;
  } else {
    write_err(ERR_ASM_INVALID_OPERAND, ERR_FATAL, 0, "Unknown type provided %s",
              a->buffer);
    return -1;
  }
}

uint8_t *asm_parse_value(Assembler *a, char type) {
  size_t size = asm_get_size(type);
  uint8_t *value = malloc(size);

  printf("%s", a->buffer);
  if (a->buffer[0] == '0' && a->buffer[1] == 'x') {
    // HEX — e.g. 0x1A2B
  }

  // else if (a->buffer[0] == '0' && a->buffer[1] == 'b') {
  //   // BITS — e.g. 0b10101100
  // }
  else if (a->buffer[0] == '-' && a->buffer[1] == 'f') {
    if (size < 4) {
      write_err(ERR_ASM_INVALID_OPCODE, ERR_FATAL, 0,
                "Given TYPE is too small for a FLOAT value.");
    } else if (size == 4) {
      float val_b = -strtof(a->buffer + 2, NULL);
      memcpy(value, &val_b, 4);
    } else if (size == 8) {
      double val_b = -strtod(a->buffer + 2, NULL);
      memcpy(value, &val_b, 4);
    }
    // NEGATIVE FLOAT — e.g. -f3.14
  } else if (a->buffer[0] == 'f') {
    if (size < 4) {
      write_err(ERR_ASM_INVALID_OPCODE, ERR_FATAL, 0,
                "Given TYPE is too small for a FLOAT value.");
    } else if (size == 4) {
      float val_b = strtof(a->buffer + 1, NULL);
      memcpy(value, &val_b, 4);
    } else if (size == 8) {
      double val_b = strtod(a->buffer + 1, NULL);
      memcpy(value, &val_b, 4);
    }
    // POSITIVE FLOAT — e.g. f3.14
  } else if (a->buffer[0] == 'u') {
    if (size == 1) {
      uint8_t val = (uint8_t)strtoul(a->buffer + 1, NULL, 10);
      memcpy(value, &val, sizeof(val));
    } else if (size == 2) {
      uint16_t val = (uint16_t)strtoul(a->buffer + 1, NULL, 10);
      memcpy(value, &val, sizeof(val));
    } else if (size == 4) {
      uint32_t val = (uint32_t)strtoul(a->buffer + 1, NULL, 10);
      memcpy(value, &val, sizeof(val));
    } else if (size == 8) {
      uint64_t val = (uint64_t)strtoull(a->buffer + 1, NULL,
                                        10); // use strtoull for 64-bit
      memcpy(value, &val, sizeof(val));
    }
    // UNSIGNED INT — e.g. u1234
  } else if (a->buffer[0] == '-' && isdigit(a->buffer[1])) {
    if (size == 1) {
      int8_t val = (int8_t)strtol(a->buffer + 1, NULL, 10);
      memcpy(value, &val, sizeof(val));
    } else if (size == 2) {
      int16_t val = (int16_t)strtol(a->buffer + 1, NULL, 10);
      memcpy(value, &val, sizeof(val));
    } else if (size == 4) {
      int32_t val = (int32_t)strtol(a->buffer + 1, NULL, 10);
      memcpy(value, &val, sizeof(val));
    } else if (size == 8) {
      int64_t val = (int64_t)strtoll(a->buffer + 1, NULL,
                                     10); // use strtoull for 64-bit
      memcpy(value, &val, sizeof(val));
    }
    // SIGNED NEGATIVE INT — e.g. -42
  } else if (isdigit(a->buffer[0])) {
    if (size == 1) {
      int8_t val = (int8_t)strtol(a->buffer, NULL, 10);
      memcpy(value, &val, sizeof(val));
    } else if (size == 2) {
      int16_t val = (int16_t)strtol(a->buffer, NULL, 10);
      memcpy(value, &val, sizeof(val));
    } else if (size == 4) {
      int32_t val = (int32_t)strtol(a->buffer, NULL, 10);
      memcpy(value, &val, sizeof(val));
    } else if (size == 8) {
      int64_t val = (int64_t)strtoll(a->buffer, NULL,
                                     10); // use strtoull for 64-bit
      memcpy(value, &val, sizeof(val));
    }
    // SIGNED POSITIVE INT — e.g. 42
  } else {
    // Unknown / invalid value
  }

  return value;
}

bool asm_write_def(Assembler *a) {
  if (strieq(a->buffer, "push")) {
    asm_op_push(a);
  }

  else {
    return false;
  }

  return true;
}

void asm_compile(Assembler *a) {
  char c;

  // COMPILE FILE
  while ((c = fs_get(&a->fs_in)) != EOF) {
    if (c == ';') {
      fs_ignoreuntil(&a->fs_in, ";\n");
    } else if (isspace(c)) {
      continue;
    } else {
      a->buffer[0] = c;
      fs_getuntil(&a->fs_in, a->buffer + 1, " \n", MAX_BUFFER_SIZE);
      asm_write_def(a);
    }
  }
}

void asm_stop(Assembler *a) {
  fs_close(&a->fs_in);
  fs_close(&a->fs_out);
}
