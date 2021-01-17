// program

@status
M=0

(LOOP)
  @i
  M=0
  @KBD
  D=M
  @NOTPUSH
  D;JEQ
  
  (PUSH)
    @status
    D=M
    M=1
    @LOOP
    D;JGT
    @BLOOP
    0;JMP
  
  (NOTPUSH)
    @status
    D=M
    M=0
    @LOOP
    D;JEQ
    @WLOOP
    0;JMP
  
  (BLOOP)
    @i
    D=M
    @8191
    D=D-A
    @END
    D;JGT
    @i
    D=M
    M=M+1
    @SCREEN
    A=A+D
    M=-1
  @BLOOP
  0;JMP
  
  (WLOOP)
    @i
    D=M
    @8191
    D=D-A
    @END
    D;JGT
    @i
    D=M
    M=M+1
    @SCREEN
    A=A+D
    M=0
  @WLOOP
  0;JMP
  
  (END)
  
@LOOP
0;JMP
