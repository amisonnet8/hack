#pragma once

#include <stdio.h>

#include "command.h"
#include "symbol.h"

typedef struct Hack Hack;

extern CommandList *yyList;
extern SymbolTable *yyTable;

Hack *hackNew(FILE *, FILE *, CommandList *, SymbolTable *);
void hackParse(Hack *);
void hackOutput(Hack *);
