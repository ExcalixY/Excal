#include "../../include/assembler/inst_stack.h"
#include "../../include/assembler/assembler.h"

void asm_op_push(Assembler *a) {
  char c = fs_get(&a->fs_in);

  if (c == '%') {
    fs_getuntil(&a->fs_in, a->buffer, ":", MAX_BUFFER_SIZE);
    char type = asm_write_type(a);

    do {
      if (type == 0x05) {
      } else {
        uint8_t *val;

        fgetu(a->buffer, MAX_BUFFER_SIZE, ", \n", a->file_in);

        fputc(0x00, a->file_out);
        fputc(type, a->file_out);
        fputv((val = asm_parse_value(a, type)), asm_get_size(type),
              a->file_out);

        free(val);

        fseek(a->file_in, -1, SEEK_CUR);
      }
    } while (fgetc(a->file_in) == ',');
  } else if (c == '$') {
    char *reg_l[14] = {
        "R0", "R1", "R2", "R3",  "R4",  "R5",  "R6",
        "R7", "R8", "R9", "RPC", "RSP", "RBP", "RFP",
    };

    fgetu(a->buffer, MAX_BUFFER_SIZE, " \n", a->file_in);

    for (char i = 0; i < 19; i++) {
      if (strieq(a->buffer, reg_l[i])) {
        fputc(0x20 + i, a->file_out);
        return;
      }
    }
  } else if (c == '[') {
    fgetu(a->buffer, MAX_BUFFER_SIZE, "]", a->file_in);
  }
}
