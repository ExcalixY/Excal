#ifndef SHARED_H
#define SHARED_H

#include "err.h"

#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 65535
#define ARG_COUNT 9

#define EXT_SRC "xsc"
#define EXT_ASM "xas"
#define EXT_BIN "xbt"

char *strdup(const char *in);
char *read_file(const char *filename, size_t *out_size);
bool strieq(const char *a, const char *b);
void fgetu(char *dest, size_t dest_s, const char *delim, FILE *file);
void fgetuw(char *dest, size_t dest_s, const char *delim, FILE *file);
void fgetn(char *dest, size_t dest_s, FILE *file);
void fignoreu(const char *delim, FILE *file);
void fignoreun(const char *delim, FILE *file);
void fputv(const void *value, size_t size, FILE *file);
void fputhex(const char *value, size_t size, FILE *file);

#endif
