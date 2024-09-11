// Calculates R1 + R2 - R3 and stores the result in R0.
// (R0, R1, R2, R3 refer to RAM[0], RAM[1], RAM[2], and RAM[3], respectively.)

// Put your code here.
    @R1
    D=M // set D to RAM[1]
    @R2
    D=D+M // set D to D + RAM[2]
    @R3
    D=D-M // set D to D - RAM[3]
    @R0
    M=D // set RAM[0] to D
(END)
    @END
    0;JMP