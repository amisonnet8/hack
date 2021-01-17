#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

void utilErrQuit(const char *, ...);
FILE *utilFileOpen(const char *, const char *);
const char *utilWhiteSkip(const char *, char);

const char *util_DupString(const char *, ...);
#define utilDupString(...) util_DupString(__VA_ARGS__, NULL)
