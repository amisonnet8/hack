#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "hack.h"
#include "symbol.h"
#include "util.h"

int main(int argc, char *argv[]) {
  FILE *in, *out;

  if (argc < 2) {
    in  = stdin;
    out = stdout;
  } else {
    in = utilFileOpen(argv[1], "r");

    for (int32_t i = strlen(argv[1]) - 1; i >= 0; i--) {
      if (argv[1][i] == '.') {
        argv[1][i] = '\0';
        break;
      }
    }
    const char *outfname = utilDupString(argv[1], ".hack");

    out = utilFileOpen(outfname, "w");
  }

  CommandList *list  = commandListNew();
  SymbolTable *table = symbolTableNew();

  symbolSequence(table, "R0");
  symbolSequence(table, "R1");
  symbolSequence(table, "R2");
  symbolSequence(table, "R3");
  symbolSequence(table, "R4");
  symbolSequence(table, "R5");
  symbolSequence(table, "R6");
  symbolSequence(table, "R7");
  symbolSequence(table, "R8");
  symbolSequence(table, "R9");
  symbolSequence(table, "R10");
  symbolSequence(table, "R11");
  symbolSequence(table, "R12");
  symbolSequence(table, "R13");
  symbolSequence(table, "R14");
  symbolSequence(table, "R15");

  symbolAddEntry(table, "SP", 0);
  symbolAddEntry(table, "LCL", 1);
  symbolAddEntry(table, "ARG", 2);
  symbolAddEntry(table, "THIS", 3);
  symbolAddEntry(table, "THAT", 4);
  symbolAddEntry(table, "SCREEN", 16384);
  symbolAddEntry(table, "KBD", 24576);

  Hack *hack = hackNew(in, out, list, table);
  hackParse(hack);
  hackOutput(hack);

  exit(EXIT_SUCCESS);
}
