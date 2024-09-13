// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// going backward
// not sure why going forward lead to failure in edge cases (same implementation as in lecture)
// Check if R1 holds a valid address
    @R1
    D=M 
    @R2
    D=M+D     
    @16384
    D=D-A    
    @END
    D;JGE
// check if the length of the array >=0
    @R2
    D=M
    @END
    D;JLE
// set array[1] as min in R[0] 
    @R1
    A=M 
    D=M
    @R0
    M=D
// loop from last index
(LOOP)
    @R2
    D=M-1
    @R1
    A=M+D 
    D=M
    @R3
    M=D
// if current_value is negative, jump to check if R0 is >=0
    @NEGATIVE
    D;JLT
// if not, check if R0 is negative
    @R0
    D=M 
    @NOSWITCH
    D;JLT
// if R0 >=0,jump to same sign
    @SAMESIGN
    0;JMP
(NEGATIVE)
    @R0
    D=M
// if R0 < 0 , jump to same sign
    @SAMESIGN
    D;JLT
// if not, jump to UPDATE_MIN
    @UPDATE_MIN
    0;JMP
(SAMESIGN)
    @R3
    D=M
    @R0
    D=M-D
// if D <= 0 -> no switch
    @NOSWITCH
    D;JLE
(UPDATE_MIN)
    @R3
    D=M
    @R0
    M=D 
    @R2
    D=M
(NOSWITCH)
    @R2
    M=M-1
    D=M-1
    @LOOP
    D;JGT  
(END)
    @END
    0;JMP