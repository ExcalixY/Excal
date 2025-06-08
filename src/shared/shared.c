#include "../../include/shared/shared.h"

char *strdup(const char *in) {
  size_t size = sizeof(in);
  char *i = (char *)malloc(size);
  memcpy(i, in, size);

  return i;
}
