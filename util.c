#include "util.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

#include "heap.h"

noreturn void utilErrQuit(const char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

FILE *utilFileOpen(const char *filename, const char *mode) {
  FILE *stream = fopen(filename, mode);

  if (stream == NULL) {
    utilErrQuit("file(%s) open error\n", filename);
  }

  return stream;
}

const char *utilWhiteSkip(const char *src, char endCh) {
  char *dest = heapAllocate(strlen(src) + 1);

  int32_t dest_i = 0;
  for (int32_t src_j = 0; src[src_j] != endCh; src_j++) {
    if (src[src_j] != ' ' && src[src_j] != '\t') {
      dest[dest_i] = src[src_j];
      dest_i++;
    }
  }
  dest[dest_i] = '\0';

  return dest;
}

const char *util_DupString(const char *arg0, ...) {
  va_list ap1, ap2;
  va_start(ap1, arg0);
  va_copy(ap2, ap1);

  size_t dupLen = 0;
  for (const char *arg = arg0; arg != NULL; arg = va_arg(ap1, const char *)) {
    dupLen += strlen(arg);
  }

  char *dupStr = heapAllocate(dupLen + 1);

  int32_t dupStr_i = 0;
  for (const char *arg = arg0; arg != NULL; arg = va_arg(ap2, const char *)) {
    for (int32_t arg_j = 0; arg[arg_j] != '\0'; arg_j++) {
      dupStr[dupStr_i] = arg[arg_j];
      dupStr_i++;
    }
  }
  dupStr[dupStr_i] = '\0';

  return dupStr;
}
