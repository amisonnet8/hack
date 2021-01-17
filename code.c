#include "code.h"

#include <assert.h>
#include <stdint.h>

static const char *CODE_BINARY_COMP_ZERO        = "0101010";
static const char *CODE_BINARY_COMP_ONE         = "0111111";
static const char *CODE_BINARY_COMP_MINUS_ONE   = "0111010";
static const char *CODE_BINARY_COMP_D           = "0001100";
static const char *CODE_BINARY_COMP_A           = "0110000";
static const char *CODE_BINARY_COMP_NOT_D       = "0001101";
static const char *CODE_BINARY_COMP_NOT_A       = "0110001";
static const char *CODE_BINARY_COMP_MINUS_D     = "0001111";
static const char *CODE_BINARY_COMP_MINUS_A     = "0110011";
static const char *CODE_BINARY_COMP_D_PLUS_ONE  = "0011111";
static const char *CODE_BINARY_COMP_A_PLUS_ONE  = "0110111";
static const char *CODE_BINARY_COMP_D_MINUS_ONE = "0001110";
static const char *CODE_BINARY_COMP_A_MINUS_ONE = "0110010";
static const char *CODE_BINARY_COMP_D_PLUS_A    = "0000010";
static const char *CODE_BINARY_COMP_D_MINUS_A   = "0010011";
static const char *CODE_BINARY_COMP_A_MINUS_D   = "0000111";
static const char *CODE_BINARY_COMP_D_AND_A     = "0000000";
static const char *CODE_BINARY_COMP_D_OR_A      = "0010101";
static const char *CODE_BINARY_COMP_M           = "1110000";
static const char *CODE_BINARY_COMP_NOT_M       = "1110001";
static const char *CODE_BINARY_COMP_MINUS_M     = "1110011";
static const char *CODE_BINARY_COMP_M_PLUS_ONE  = "1110111";
static const char *CODE_BINARY_COMP_M_MINUS_ONE = "1110010";
static const char *CODE_BINARY_COMP_D_PLUS_M    = "1000010";
static const char *CODE_BINARY_COMP_D_MINUS_M   = "1010011";
static const char *CODE_BINARY_COMP_M_MINUS_D   = "1000111";
static const char *CODE_BINARY_COMP_D_AND_M     = "1000000";
static const char *CODE_BINARY_COMP_D_OR_M      = "1010101";

static const char *CODE_BINARY_DEST_NULL = "000";
static const char *CODE_BINARY_DEST_M    = "001";
static const char *CODE_BINARY_DEST_D    = "010";
static const char *CODE_BINARY_DEST_MD   = "011";
static const char *CODE_BINARY_DEST_A    = "100";
static const char *CODE_BINARY_DEST_AM   = "101";
static const char *CODE_BINARY_DEST_AD   = "110";
static const char *CODE_BINARY_DEST_AMD  = "111";

static const char *CODE_BINARY_JUMP_NULL = "000";
static const char *CODE_BINARY_JUMP_JGT  = "001";
static const char *CODE_BINARY_JUMP_JEQ  = "010";
static const char *CODE_BINARY_JUMP_JGE  = "011";
static const char *CODE_BINARY_JUMP_JLT  = "100";
static const char *CODE_BINARY_JUMP_JNE  = "101";
static const char *CODE_BINARY_JUMP_JLE  = "110";
static const char *CODE_BINARY_JUMP_JMP  = "111";

const char *codeAddressToBinary(int32_t address) {
  static char binary[16] = {'\0'};

  int32_t i;
  for (i = 14; address > 0; i--) {
    binary[i] = '0' + address % 2;
    address   = address / 2;
  }
  while (i >= 0) {
    binary[i] = '0';
    i--;
  }

  return binary;
}

const char *codeCompToBinary(int32_t comp) {
  switch (comp) {
  case CODE_COMP_ZERO:
    return CODE_BINARY_COMP_ZERO;
  case CODE_COMP_ONE:
    return CODE_BINARY_COMP_ONE;
  case CODE_COMP_MINUS_ONE:
    return CODE_BINARY_COMP_MINUS_ONE;
  case CODE_COMP_D:
    return CODE_BINARY_COMP_D;
  case CODE_COMP_A:
    return CODE_BINARY_COMP_A;
  case CODE_COMP_NOT_D:
    return CODE_BINARY_COMP_NOT_D;
  case CODE_COMP_NOT_A:
    return CODE_BINARY_COMP_NOT_A;
  case CODE_COMP_MINUS_D:
    return CODE_BINARY_COMP_MINUS_D;
  case CODE_COMP_MINUS_A:
    return CODE_BINARY_COMP_MINUS_A;
  case CODE_COMP_D_PLUS_ONE:
    return CODE_BINARY_COMP_D_PLUS_ONE;
  case CODE_COMP_A_PLUS_ONE:
    return CODE_BINARY_COMP_A_PLUS_ONE;
  case CODE_COMP_D_MINUS_ONE:
    return CODE_BINARY_COMP_D_MINUS_ONE;
  case CODE_COMP_A_MINUS_ONE:
    return CODE_BINARY_COMP_A_MINUS_ONE;
  case CODE_COMP_D_PLUS_A:
    return CODE_BINARY_COMP_D_PLUS_A;
  case CODE_COMP_D_MINUS_A:
    return CODE_BINARY_COMP_D_MINUS_A;
  case CODE_COMP_A_MINUS_D:
    return CODE_BINARY_COMP_A_MINUS_D;
  case CODE_COMP_D_AND_A:
    return CODE_BINARY_COMP_D_AND_A;
  case CODE_COMP_D_OR_A:
    return CODE_BINARY_COMP_D_OR_A;
  case CODE_COMP_M:
    return CODE_BINARY_COMP_M;
  case CODE_COMP_NOT_M:
    return CODE_BINARY_COMP_NOT_M;
  case CODE_COMP_MINUS_M:
    return CODE_BINARY_COMP_MINUS_M;
  case CODE_COMP_M_PLUS_ONE:
    return CODE_BINARY_COMP_M_PLUS_ONE;
  case CODE_COMP_M_MINUS_ONE:
    return CODE_BINARY_COMP_M_MINUS_ONE;
  case CODE_COMP_D_PLUS_M:
    return CODE_BINARY_COMP_D_PLUS_M;
  case CODE_COMP_D_MINUS_M:
    return CODE_BINARY_COMP_D_MINUS_M;
  case CODE_COMP_M_MINUS_D:
    return CODE_BINARY_COMP_M_MINUS_D;
  case CODE_COMP_D_AND_M:
    return CODE_BINARY_COMP_D_AND_M;
  case CODE_COMP_D_OR_M:
    return CODE_BINARY_COMP_D_OR_M;
  default:
    assert(0);
  }
}

const char *codeDestToBinary(int32_t dest) {
  switch (dest) {
  case CODE_DEST_NULL:
    return CODE_BINARY_DEST_NULL;
  case CODE_DEST_M:
    return CODE_BINARY_DEST_M;
  case CODE_DEST_D:
    return CODE_BINARY_DEST_D;
  case CODE_DEST_MD:
    return CODE_BINARY_DEST_MD;
  case CODE_DEST_A:
    return CODE_BINARY_DEST_A;
  case CODE_DEST_AM:
    return CODE_BINARY_DEST_AM;
  case CODE_DEST_AD:
    return CODE_BINARY_DEST_AD;
  case CODE_DEST_AMD:
    return CODE_BINARY_DEST_AMD;
  default:
    assert(0);
  }
}

const char *codeJumpToBinary(int32_t jump) {
  switch (jump) {
  case CODE_JUMP_NULL:
    return CODE_BINARY_JUMP_NULL;
  case CODE_JUMP_JGT:
    return CODE_BINARY_JUMP_JGT;
  case CODE_JUMP_JEQ:
    return CODE_BINARY_JUMP_JEQ;
  case CODE_JUMP_JGE:
    return CODE_BINARY_JUMP_JGE;
  case CODE_JUMP_JLT:
    return CODE_BINARY_JUMP_JLT;
  case CODE_JUMP_JNE:
    return CODE_BINARY_JUMP_JNE;
  case CODE_JUMP_JLE:
    return CODE_BINARY_JUMP_JLE;
  case CODE_JUMP_JMP:
    return CODE_BINARY_JUMP_JMP;
  default:
    assert(0);
  }
}
