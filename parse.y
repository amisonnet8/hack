%{
#include <stdint.h>

#include "code.h"
#include "command.h"
#include "hack.h"
#include "symbol.h"
#include "util.h"
%}

%union {
  int32_t intVal;
  const char *strVal;
}

%type <intVal> comp dest jump
%token <intVal> TOK_ADDRESS
%token <strVal> TOK_SYMBOL TOK_LABEL

%token
  TOK_LF
  TOK_ZERO
  TOK_ONE
  TOK_A
  TOK_D
  TOK_M
  TOK_PLUS
  TOK_MINUS
  TOK_NOT
  TOK_AND
  TOK_OR
  TOK_EQ
  TOK_SEM
  TOK_JGT
  TOK_JEQ
  TOK_JGE
  TOK_JLT
  TOK_JNE
  TOK_JLE
  TOK_JMP

%{
int yylex();
static void yyerror(const char *s);
%}

%%
program   :
          | list
          ;

list      : line
          | list line
          ;

line      : commanda TOK_LF
          | commandc TOK_LF
          | commandl TOK_LF
          | TOK_LF
          ;

commanda  : TOK_ADDRESS {
            commandAddressAdd(yyList, $1);
          }
          | TOK_SYMBOL {
            commandSymbolAdd(yyList, $1);
          }
          ;

commandc  : comp {
            commandCAdd(yyList, $1, CODE_DEST_NULL, CODE_JUMP_NULL);
          }
          | TOK_EQ comp {
            commandCAdd(yyList, $2, CODE_DEST_NULL, CODE_JUMP_NULL);
          }
          | comp TOK_SEM {
            commandCAdd(yyList, $1, CODE_DEST_NULL, CODE_JUMP_NULL);
          }
          | TOK_EQ comp TOK_SEM {
            commandCAdd(yyList, $2, CODE_DEST_NULL, CODE_JUMP_NULL);
          }
          | dest TOK_EQ comp  {
            commandCAdd(yyList, $3, $1, CODE_JUMP_NULL);
          }
          | dest TOK_EQ comp TOK_SEM {
            commandCAdd(yyList, $3, $1, CODE_JUMP_NULL);
          }
          | comp TOK_SEM jump {
            commandCAdd(yyList, $1, CODE_DEST_NULL, $3);
          }
          | TOK_EQ comp TOK_SEM jump {
            commandCAdd(yyList, $2, CODE_DEST_NULL, $4);
          }
          | dest TOK_EQ comp TOK_SEM jump {
            commandCAdd(yyList, $3, $1, $5);
          }
          ;

commandl  : TOK_LABEL {
            int address = commandListSize(yyList);
            symbolAddEntry(yyTable, $1, address);
          }
          ;

comp      : TOK_ZERO {
            $$ = CODE_COMP_ZERO;
          }
          | TOK_ONE {
            $$ = CODE_COMP_ONE;
          }
          | TOK_MINUS TOK_ONE {
            $$ = CODE_COMP_MINUS_ONE;
          }
          | TOK_D {
            $$ = CODE_COMP_D;
          }
          | TOK_A {
            $$ = CODE_COMP_A;
          }
          | TOK_NOT TOK_D {
            $$ = CODE_COMP_NOT_D;
          }
          | TOK_NOT TOK_A {
            $$ = CODE_COMP_NOT_A;
          }
          | TOK_MINUS TOK_D {
            $$ = CODE_COMP_MINUS_D;
          }
          | TOK_MINUS TOK_A {
            $$ = CODE_COMP_MINUS_A;
          }
          | TOK_D TOK_PLUS TOK_ONE {
            $$ = CODE_COMP_D_PLUS_ONE;
          }
          | TOK_A TOK_PLUS TOK_ONE {
            $$ = CODE_COMP_A_PLUS_ONE;
          }
          | TOK_D TOK_MINUS TOK_ONE {
            $$ = CODE_COMP_D_MINUS_ONE;
          }
          | TOK_A TOK_MINUS TOK_ONE {
            $$ = CODE_COMP_A_MINUS_ONE;
          }
          | TOK_D TOK_PLUS TOK_A {
            $$ = CODE_COMP_D_PLUS_A;
          }
          | TOK_A TOK_PLUS TOK_D {
            $$ = CODE_COMP_D_PLUS_A;
          }
          | TOK_D TOK_MINUS TOK_A {
            $$ = CODE_COMP_D_MINUS_A;
          }
          | TOK_A TOK_MINUS TOK_D {
            $$ = CODE_COMP_A_MINUS_D;
          }
          | TOK_D TOK_AND TOK_A {
            $$ = CODE_COMP_D_AND_A;
          }
          | TOK_A TOK_AND TOK_D {
            $$ = CODE_COMP_D_AND_A;
          }
          | TOK_D TOK_OR TOK_A {
            $$ = CODE_COMP_D_OR_A;
          }
          | TOK_A TOK_OR TOK_D {
            $$ = CODE_COMP_D_OR_A;
          }
          | TOK_M {
            $$ = CODE_COMP_M;
          }
          | TOK_NOT TOK_M {
            $$ = CODE_COMP_NOT_M;
          }
          | TOK_MINUS TOK_M {
            $$ = CODE_COMP_MINUS_M;
          }
          | TOK_M TOK_PLUS TOK_ONE {
            $$ = CODE_COMP_M_PLUS_ONE;
          }
          | TOK_M TOK_MINUS TOK_ONE {
            $$ = CODE_COMP_M_MINUS_ONE;
          }
          | TOK_D TOK_PLUS TOK_M {
            $$ = CODE_COMP_D_PLUS_M;
          }
          | TOK_M TOK_PLUS TOK_D {
            $$ = CODE_COMP_D_PLUS_M;
          }
          | TOK_D TOK_MINUS TOK_M {
            $$ = CODE_COMP_D_MINUS_M;
          }
          | TOK_M TOK_MINUS TOK_D {
            $$ = CODE_COMP_M_MINUS_D;
          }
          | TOK_D TOK_AND TOK_M {
            $$ = CODE_COMP_D_AND_M;
          }
          | TOK_M TOK_AND TOK_D {
            $$ = CODE_COMP_D_AND_M;
          }
          | TOK_D TOK_OR TOK_M {
            $$ = CODE_COMP_D_OR_M;
          }
          | TOK_M TOK_OR TOK_D {
            $$ = CODE_COMP_D_OR_M;
          }
          ;

dest      : TOK_M {
            $$ = CODE_DEST_M;
          }
          | TOK_D {
            $$ = CODE_DEST_D;
          }
          | TOK_M TOK_D {
            $$ = CODE_DEST_MD;
          }
          | TOK_A {
            $$ = CODE_DEST_A;
          }
          | TOK_A TOK_M {
            $$ = CODE_DEST_AM;
          }
          | TOK_A TOK_D {
            $$ = CODE_DEST_AD;
          }
          | TOK_A TOK_M TOK_D {
            $$ = CODE_DEST_AMD;
          }
          ;

jump      : TOK_JGT {
            $$ = CODE_JUMP_JGT;
          }
          | TOK_JEQ {
            $$ = CODE_JUMP_JEQ;
          }
          | TOK_JGE {
            $$ = CODE_JUMP_JGE;
          }
          | TOK_JLT {
            $$ = CODE_JUMP_JLT;
          }
          | TOK_JNE {
            $$ = CODE_JUMP_JNE;
          }
          | TOK_JLE {
            $$ = CODE_JUMP_JLE;
          }
          | TOK_JMP {
            $$ = CODE_JUMP_JMP;
          }
          ;
%%

static void yyerror(const char* s) {
  utilErrQuit("%s\n", s);
}
