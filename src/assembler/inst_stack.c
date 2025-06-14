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

        fs_getuntil_prev(&a->fs_in, a->buffer, ", \n", MAX_BUFFER_SIZE);

        fs_writeb(&a->fs_out, 0x00);
        fs_writeb(&a->fs_out, type);
        fs_writen(&a->fs_out, asm_parse_value(a, type), asm_get_size(type));
      }
    } while (fs_get(&a->fs_in) == ',');
  } else if (c == '$') {
    char *reg_l[14] = {
        "R0", "R1", "R2", "R3",  "R4",  "R5",  "R6",
        "R7", "R8", "R9", "RPC", "RSP", "RBP", "RFP",
    };

    fs_getuntil(&a->fs_in, a->buffer, " \n", MAX_BUFFER_SIZE);

    for (char i = 0; i < 19; i++) {
      if (strieq(a->buffer, reg_l[i])) {
        fs_writeb(&a->fs_in, 0x20 + i);
        return;
      }
    }
  } else if (c == '[') {
    fs_getuntil(&a->fs_in, a->buffer, "]", MAX_BUFFER_SIZE);
  }
}
