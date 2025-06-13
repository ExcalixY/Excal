#include "../../include/shared/shared.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *strdup(const char *in) {
  size_t size = sizeof(in);
  char *i = (char *)malloc(size);
  memcpy(i, in, size);

  return i;
}

char *read_file(const char *filename, size_t *out_size) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    write_err(ERR_FILE_NOT_FOUND, ERR_FATAL, 0,
              "Could not find the specified file.");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  char *f_cont = malloc(size);
  if (!f_cont) {
    fclose(file);
    return NULL;
  }

  fread(f_cont, 1, size, file);
  fclose(file);

  *out_size = size;
  return f_cont;
}

bool strieq(const char *a, const char *b) {
  while (*a && *b) {
    if (tolower(*a) != tolower(*b))
      return 0;
    a++;
    b++;
  }
  return *a == *b;
}

void fgetu(char *dest, size_t dest_s, const char *delim, FILE *file) {
  size_t d_s = strlen(delim);
  char c;
  size_t j = 0;

  while ((c = fgetc(file)) != EOF) {
    for (int i = 0; i < d_s; i++) {
      if (delim[i] == c)
        goto end;
    }

    if (dest_s - 1 > j) {
      dest[j] = c;
      j++;
    } else {
      break;
    }
  }

end:
  dest[j] = '\0';
}

void fgetuw(char *dest, size_t dest_s, const char *delim, FILE *file) {
  size_t d_s = strlen(delim);
  char c;
  size_t j = 0;

  while ((c = fgetc(file)) != EOF) {
    for (int i = 0; i < d_s; i++) {
      if (delim[i] == c)
        goto end;
    }

    if (dest_s - 2 > j) {
      dest[j] = c;
      j++;
    } else {
      break;
    }
  }

end:
  j++;
  dest[j - 1] = c;
  dest[j] = '\0';
}

void fignoreu(const char *delim, FILE *file) {
  size_t d_s = strlen(delim);
  char c;

  while ((c = fgetc(file)) != EOF) {
    for (int i = 0; i < d_s; i++) {
      if (delim[i] == c)
        return;
    }
  }
}

void fignoreun(const char *delim, FILE *file) {
  size_t d_s = strlen(delim);
  char c;
  bool found = false;

  while ((c = fgetc(file)) != EOF) {
    for (int i = 0; i < d_s; i++) {
      if (delim[i] == c) {
        break;
        found = true;
      }
    }

    if (found) {
      ungetc(c, file);
      return;
    }
  }
}

void fputv(const void *value, size_t size, FILE *file) {
  const uint8_t *bytes = (const uint8_t *)value;

  for (size_t i = 0; i < size; i++) {
    fputc(bytes[i], file);
  }
}

void fputhex(const char *value, size_t size, FILE *file) {
  uint64_t val = strtoull(value, NULL, 0);

  for (size_t i = 0; i < size; i++) {
    uint8_t byte = (val >> (i * 8)) & 0xFF;
    fputc(byte, file);
  }
}
