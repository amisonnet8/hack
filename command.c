#include "command.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "code.h"
#include "heap.h"
#include "symbol.h"

typedef struct Command {
  enum {
    COMMAND_TYPE_ADDRESS,
    COMMAND_TYPE_SYMBOL,
    COMMAND_TYPE_C,
  } type;
  union {
    struct {
      int32_t address;
    } a;
    struct {
      const char *symbol;
    } s;
    struct {
      int32_t comp;
      int32_t dest;
      int32_t jump;
    } c;
  };
  struct Command *next;
} Command;

struct CommandList {
  Command *head;
  Command *tail;
  int32_t size;
};

static Command *commandAddressNew(int32_t address) {
  Command *command = heapAllocate(sizeof(Command));

  command->type      = COMMAND_TYPE_ADDRESS;
  command->a.address = address;
  command->next      = NULL;

  return command;
}

static Command *commandSymbolNew(const char *symbol) {
  Command *command = heapAllocate(sizeof(Command));

  command->type     = COMMAND_TYPE_SYMBOL;
  command->s.symbol = symbol;
  command->next     = NULL;

  return command;
}

static Command *commandCNew(int32_t comp, int32_t dest, int32_t jump) {
  Command *command = heapAllocate(sizeof(Command));

  command->type   = COMMAND_TYPE_C;
  command->c.comp = comp;
  command->c.dest = dest;
  command->c.jump = jump;
  command->next   = NULL;

  return command;
}

static void commandAdd(CommandList *list, Command *command) {
  if (list->head == NULL) {
    list->head = command;
  } else {
    list->tail->next = command;
  }
  list->tail = command;
  list->size++;
}

static void commandAddressOutput(const Command *command, FILE *out) {
  fprintf(out, "0%s\r\n", codeAddressToBinary(command->a.address));
}

static void commandSymbolOutput(const Command *command, SymbolTable *table, FILE *out) {
  int32_t address;

  if (symbolContains(table, command->s.symbol)) {
    address = symbolGetAddress(table, command->s.symbol);
  } else {
    address = symbolSequence(table, command->s.symbol);
  }

  fprintf(out, "0%s\r\n", codeAddressToBinary(address));
}

static void commandCOutput(const Command *command, FILE *out) {
  fprintf(out, "111%s%s%s\r\n", codeCompToBinary(command->c.comp), codeDestToBinary(command->c.dest), codeJumpToBinary(command->c.jump));
}

CommandList *commandListNew() {
  CommandList *list = heapAllocate(sizeof(CommandList));

  list->head = NULL;
  list->tail = NULL;
  list->size = 0;

  return list;
}

void commandAddressAdd(CommandList *list, int32_t address) {
  Command *command = commandAddressNew(address);
  commandAdd(list, command);
}

void commandSymbolAdd(CommandList *list, const char *symbol) {
  Command *command = commandSymbolNew(symbol);
  commandAdd(list, command);
}

void commandCAdd(CommandList *list, int32_t comp, int32_t dest, int32_t jump) {
  Command *command = commandCNew(comp, dest, jump);
  commandAdd(list, command);
}

void commandListOutput(const CommandList *list, SymbolTable *table, FILE *out) {
  for (const Command *p = list->head; p != NULL; p = p->next) {
    switch (p->type) {
    case COMMAND_TYPE_ADDRESS:
      commandAddressOutput(p, out);
      break;
    case COMMAND_TYPE_SYMBOL:
      commandSymbolOutput(p, table, out);
      break;
    case COMMAND_TYPE_C:
      commandCOutput(p, out);
      break;
    }
  }
}

int32_t commandListSize(const CommandList *list) {
  return list->size;
}
