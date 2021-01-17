#include "symbol.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "heap.h"

typedef struct SymbolEntry {
  const char *symbol;
  int32_t address;
  struct SymbolEntry *next;
} SymbolEntry;

struct SymbolTable {
  SymbolEntry *head;
  int32_t seq;
};

static SymbolEntry *symbolEntryNew(const char *symbol, int32_t address, SymbolEntry *next) {
  SymbolEntry *entry = heapAllocate(sizeof(SymbolEntry));

  entry->symbol  = symbol;
  entry->address = address;
  entry->next    = next;

  return entry;
}

SymbolTable *symbolTableNew() {
  SymbolTable *table = heapAllocate(sizeof(SymbolTable));

  table->head = NULL;
  table->seq  = 0;

  return table;
}

void symbolAddEntry(SymbolTable *table, const char *symbol, int32_t address) {
  SymbolEntry *entry = symbolEntryNew(symbol, address, table->head);
  table->head        = entry;
}

int32_t symbolSequence(SymbolTable *table, const char *symbol) {
  symbolAddEntry(table, symbol, table->seq);
  table->seq++;

  return table->seq - 1;
}

bool symbolContains(const SymbolTable *table, const char *symbol) {
  for (const SymbolEntry *p = table->head; p != NULL; p = p->next) {
    if (strcmp(p->symbol, symbol) == 0) {
      return true;
    }
  }

  return false;
}

int32_t symbolGetAddress(const SymbolTable *table, const char *symbol) {
  for (const SymbolEntry *p = table->head; p != NULL; p = p->next) {
    if (strcmp(p->symbol, symbol) == 0) {
      return p->address;
    }
  }

  return -1;
}
