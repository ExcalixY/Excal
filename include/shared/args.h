#ifndef ARGS_H
#define ARGS_H

#include "shared.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef struct {
  bool output_asm;     // true if -asm is passed
  bool compile_outasm; // true if -casm is passed
  bool run_source;     // true if -r is passed
  bool run_compiled;   // true if -rc is passed
  bool compile;        // true if -c is passed
  bool show_help;      // true if -h is passed
  bool show_version;   // true if -v is passed

  char *output_dir; // value of -o (if set)
  char *input_file; // positional or from -i (if supported)
} CompileArgs;

typedef enum { GET_NEXT_STRING, SET_BOOL } ArgType;

typedef struct {
  void (*action)(CompileArgs *args, const char *value);
  const char *help_message;
  const char **options;
  size_t arg_opts_size;
  ArgType type;
} Args;

void init_args(Args *args, CompileArgs *comp_args);

void add_arg(Args *args, size_t i, const char **options, size_t opts_count,
             const char *help_message,
             void (*action)(CompileArgs *args, const char *value),
             ArgType type);

void parse_args(Args args[], CompileArgs *comp_args, int argc, char **argv);

void set_show_help(CompileArgs *args, const char *value);
void set_compile(CompileArgs *args, const char *value);
void set_run_source(CompileArgs *args, const char *value);
void set_run_compiled(CompileArgs *args, const char *value);
void set_output_dir_action(CompileArgs *args, const char *value);
void set_input_file(CompileArgs *args, const char *value);
void set_output_asm(CompileArgs *args, const char *value);
void set_compile_outasm(CompileArgs *args, const char *value);
void set_show_version(CompileArgs *args, const char *value);

#endif
