#pragma once

#include <stdint.h>
#include <stdio.h>

#include "symbol.h"

typedef struct CommandList CommandList;

CommandList *commandListNew();
void commandAddressAdd(CommandList *, int32_t);
void commandSymbolAdd(CommandList *, const char *);
void commandCAdd(CommandList *, int32_t, int32_t, int32_t);
void commandListOutput(const CommandList *, SymbolTable *, FILE *);
int32_t commandListSize(const CommandList *);
