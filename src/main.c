#include "../include/shared/args.h"
#include "../include/shared/shared.h"

#include "../include/assembler/assembler.h"
#include "../include/compiler/compiler.h"
#include "../include/vm/vm.h"

#include "../lib/fstream/fstream.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

char *ver_comp = "0.01 ALPHA";
Args args[ARG_COUNT];

const char *help_opts[] = {"-h", "--help"};
const char *compile_opts[] = {"-c", "--compile"};
const char *run_opts[] = {"-r", "--run"};
const char *run_comp_opts[] = {"-rc", "--run-compiled"};
const char *output_dir_opts[] = {"-o", "--output"};
const char *input_dir_opts[] = {"-i", "--input"};
const char *out_asm_opts[] = {"-asm", "--output-asm"};
const char *compile_asm_opts[] = {"-casm", "--compile-asm"};
const char *version_opts[] = {"-v", "--version"};

void send_help_msg() {
  printf("Excal: Usage\n\n");

  for (int i = 0; i < ARG_COUNT; i++) {
    for (int j = 0; j < args[i].arg_opts_size; j++) {
      printf("%s ", args[i].options[j]);
    }

    printf(": %s\n", args[i].help_message);
  }
}

int main(int argc, char *argv[]) {
  CompileArgs comp_args = {
      .output_asm = false,
      .compile_outasm = false,
      .run_source = false,
      .run_compiled = false,
      .compile = false,
      .show_help = false,
      .show_version = false,
      .output_dir = NULL,
      .input_file = NULL,
  };

  Compiler compiler;
  Assembler assembler;
  VM vm;

  add_arg(args, 0, help_opts, 2, "Shows this message.", set_show_help,
          SET_BOOL);
  add_arg(args, 1, compile_opts, 2, "Compiles source code.", set_compile,
          SET_BOOL);
  add_arg(args, 2, run_opts, 2, "Runs source code right after compiling.",
          set_run_source, SET_BOOL);
  add_arg(args, 3, run_comp_opts, 2, "Runs precompiled bytecode.",
          set_run_compiled, SET_BOOL);
  add_arg(args, 4, output_dir_opts, 2,
          "Sets the output directory for compiled files.",
          set_output_dir_action, GET_NEXT_STRING);
  add_arg(args, 5, input_dir_opts, 2,
          "Sets the input file that will be compiled.", set_input_file,
          GET_NEXT_STRING);
  add_arg(args, 6, out_asm_opts, 2, "Outputs intermediate assembly code.",
          set_output_asm, SET_BOOL);
  add_arg(args, 7, compile_asm_opts, 2,
          "Compiles previously outputted assembly code.", set_compile_outasm,
          SET_BOOL);
  add_arg(args, 8, version_opts, 2, "Prints the version of Excal.",
          set_show_version, SET_BOOL);

  if (argc < 2) {
    send_help_msg();
    return 0;
  }

  parse_args(args, &comp_args, argc, argv);

  if (comp_args.show_help == true) {
    send_help_msg();
    return 0;
  }

  if (comp_args.show_version) {
    printf("Excal: Version %s\n", ver_comp);
    return 0;
  }

  int asm_err;

  if (comp_args.input_file == NULL) {
    asm_err = asm_init(&assembler, argv[1]);
  } else {
    asm_err = asm_init(&assembler, comp_args.input_file);
  }

  if (asm_err != 0)
    return asm_err;

  asm_compile(&assembler);

  return 0;
}
