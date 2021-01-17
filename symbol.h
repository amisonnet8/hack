#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct SymbolTable SymbolTable;

SymbolTable *symbolTableNew();
void symbolAddEntry(SymbolTable *, const char *, int32_t);
int32_t symbolSequence(SymbolTable *, const char *);
bool symbolContains(const SymbolTable *, const char *);
int32_t symbolGetAddress(const SymbolTable *, const char *);
