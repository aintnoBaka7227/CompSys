// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
@1
A=M 
D=M
@0
M=D
@i
M=1
(LOOP)
    @i 
    D=M 
    @2
    D=D-M 
    @END
    D;JGE
    @i
    D=M
    @1
    A=D+M
    D=M
    @3
    M=D 
    @0
    D=D-M
    @UPDATE_MIN
    D;JLT
    @i 
    M=M+1
    @LOOP
    0;JMP
(UPDATE_MIN)
    @3
    D=M
    @0
    M=D 
    @i 
    M=M+1
    @LOOP
    0;JMP
(END)
    @END
    0;JMP
    
