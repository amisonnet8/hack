#include "heap.h"

#include <stddef.h>
#include <stdlib.h>

#include "util.h"

static const size_t HEAP_BLOCK_SIZE = 1024 * 1024;

static void *heapPtr;
static size_t heapStockSize = 0;

void *heapAllocate(size_t size) {
  if (size > HEAP_BLOCK_SIZE) {
    utilErrQuit("heap block size over\n");
  }

  if (size > heapStockSize) {
    heapPtr = malloc(HEAP_BLOCK_SIZE);
    if (heapPtr == NULL) {
      utilErrQuit("out of memory\n");
    }
    heapStockSize = HEAP_BLOCK_SIZE;
  }

  heapPtr += size;
  heapStockSize -= size;

  return heapPtr - size;
}
