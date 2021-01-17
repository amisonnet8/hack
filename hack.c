#include "hack.h"

#include <stdio.h>

#include "command.h"
#include "heap.h"
#include "symbol.h"
#include "y.tab.h"

struct Hack {
  FILE *in;
  FILE *out;
  CommandList *list;
  SymbolTable *table;
};

CommandList *yyList;
SymbolTable *yyTable;

Hack *hackNew(FILE *in, FILE *out, CommandList *list, SymbolTable *table) {
  Hack *hack = heapAllocate(sizeof(Hack));

  hack->in    = in;
  hack->out   = out;
  hack->list  = list;
  hack->table = table;

  return hack;
}

void hackParse(Hack *hack) {
  extern FILE *yyin;
  yyin    = hack->in;
  yyList  = hack->list;
  yyTable = hack->table;
  yyparse();
}

void hackOutput(Hack *hack) {
  commandListOutput(hack->list, hack->table, hack->out);
}
