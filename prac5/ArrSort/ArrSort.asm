// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// Selection sort (going backward)
// based on ArrMin implementation 
// Average case: O(n^2), unstable algo, not really work on big dataset
// Check if R1 holds a valid address
    @R1
    D=M 
    @R2
    D=M+D     
    @16384
    D=D-A    
    @ENDSORT
    D;JGE
    @R1
    D=M-1
    @ENDSORT
    D;JLE
// check if the length of the array >=0
    @R2
    D=M
    @ENDSORT
    D;JLE
// start of the nested loop
(OUTERLOOP)
    // i = 0->R2
    @R2
    D=M
    // j = i->R2
    @counter
    M=D
    // set array[1] as min in R[0] 
    @R1
    A=M 
    D=M
    @R0
    M=D
    // index of current min
    @i
    M=0
(INNERLOOP)
    @counter
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
    @counter
    D=M
    @i
    M=D-1
(NOSWITCH)
    @counter
    M=M-1
    D=M-1
    @INNERLOOP
    D;JGT
// perform swapping between the first position and the minimum
    @i
    D=M 
    @R1
    D=M+D
// store position of the minimum
    @R4
    M=D
// current first position
    @R1
    A=M 
    D=M 
// swap 
    @R4 
    A=M 
    M=D
    @R0
    D=M 
    @R1 
    A=M 
    M=D
// increment the first element by 1
    @R1
    M=M+1
// decrease the size of the sub array
    @R2
    M=M-1
    D=M-1   
    @OUTERLOOP 
    D;JGT 
(ENDSORT)
    @R0
    M=-1
(END)
    @END
    0;JMP
