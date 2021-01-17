%{
#include <stdlib.h>

#include "util.h"
#include "y.tab.h"
%}

white [ ]
lf [\n\r]

%s COMMENT

%%

"/"{white}*"/" {
  BEGIN COMMENT;
}

<COMMENT>.*{lf} {
  BEGIN 0;
  return TOK_LF;
}

{lf} {
  return TOK_LF;
}

@{white}*[0-9]([0-9]|{white})* {
  const char *val = utilWhiteSkip(yytext + 1, '\0');
  yylval.intVal = atoi(val);
  return TOK_ADDRESS;
}

@{white}*[A-Za-z_.$:]([A-Za-z0-9_.$:]|{white})* {
  yylval.strVal = utilWhiteSkip(yytext + 1, '\0');
  return TOK_SYMBOL;
}

\({white}*[A-Za-z_.$:]([A-Za-z0-9_.$:]|{white})*\) {
  yylval.strVal = utilWhiteSkip(yytext + 1, ')');
  return TOK_LABEL;
}

0 {
  return TOK_ZERO;
}

1 {
  return TOK_ONE;
}

A {
  return TOK_A;
}

D {
  return TOK_D;
}

M {
  return TOK_M;
}

\+ {
  return TOK_PLUS;
}

- {
  return TOK_MINUS;
}

! {
  return TOK_NOT;
}

& {
  return TOK_AND;
}

\| {
  return TOK_OR;
}

= {
  return TOK_EQ;
}

; {
  return TOK_SEM;
}

J{white}*G{white}*T {
  return TOK_JGT;
}

J{white}*E{white}*Q {
  return TOK_JEQ;
}

J{white}*G{white}*E {
  return TOK_JGE;
}

J{white}*L{white}*T {
  return TOK_JLT;
}

J{white}*N{white}*E {
  return TOK_JNE;
}

J{white}*L{white}*E {
  return TOK_JLE;
}

J{white}*M{white}*P {
  return TOK_JMP;
}

{white} ;

. {
  utilErrQuit("lexer error\n");
}

%%

int yywrap(void) {
  return 1;
}
