#include "../../include/shared/args.h"

#include <stdlib.h>
#include <string.h>

void add_arg(Args *args, size_t i, const char **options, size_t opts_count,
             const char *help_message,
             void (*action)(CompileArgs *args, const char *value),
             ArgType type) {
  Args arg;
  arg.help_message = help_message;
  arg.options = options;
  arg.action = action;
  arg.arg_opts_size = opts_count;
  arg.type = type;

  args[i] = arg;
}

void set_show_help(CompileArgs *args, const char *value) {
  args->show_help = true;
  (void)value;
}

void set_compile(CompileArgs *args, const char *value) {
  args->compile = true;
  (void)value;
}

void set_run_source(CompileArgs *args, const char *value) {
  args->run_source = true;
  (void)value;
}

void set_run_compiled(CompileArgs *args, const char *value) {
  args->run_compiled = true;
  (void)value;
}

void set_output_dir_action(CompileArgs *args, const char *value) {
  if (value) {
    args->output_dir = (char *)strdup(value);
  }
}

void set_input_file(CompileArgs *args, const char *value) {
  if (value) {
    args->input_file = (char *)strdup(value);
  }
}

void set_output_asm(CompileArgs *args, const char *value) {
  args->output_asm = true;
  (void)value;
}

void set_compile_outasm(CompileArgs *args, const char *value) {
  args->compile_outasm = true;
  (void)value;
}

void set_show_version(CompileArgs *args, const char *value) {
  args->show_version = true;
  (void)value;
}

bool match_arg(Args *arg, char *arg_str) {
  for (int i = 0; i < arg->arg_opts_size; i++) {
    if (strcmp(arg_str, arg->options[i]) == 0) {
      return true;
    }
  }

  return false;
}

void parse_args(Args args[], CompileArgs *comp_args, int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    for (int j = 0; j < ARG_COUNT; j++) {
      if (match_arg(&args[j], argv[i])) {
        if (args[j].type == SET_BOOL)
          args[j].action(comp_args, "");

        else if (args[j].type == GET_NEXT_STRING) {
          if (i < argc - 1) {
            args[j].action(comp_args, argv[++i]);
          } else {
            write_err(ERR_COMP_MISSING_ARG, argc, "Missing argument.");
          }
        }
      }
    }
  }
}
