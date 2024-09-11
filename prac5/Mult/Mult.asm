// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
@counter
M=1
@R2
D=M
// check if R2 = 0 then set R0 to 0
@ZERO
D;JEQ
// check if R2 is positive (using R2 for loop)
@POSITIVE
D;JGT
// if not then negate R2
D=!D
D=D+1
@i
M=D
(POSITIVE)
// loop start from 0, end when i = R2
(LOOP)
@R1
D=M
@R0
M=M+D
@counter
MD=M+1
@i
D=D-M
@LOOP
D;JLE

// check again for R2 if it is negative then negate R0
@R2
D=M
@NEGATE
D;JLT

(END)
@END
0;JMP

(NEGATE)
@R0
M=!M
M=M+1
@END
0;JMP

(ZERO)
@R0
M=0
@END
0;JMP