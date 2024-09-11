
// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
    @1
    D=M
    @2
    D=M 
    @3
    M=1
    @NEGATIVE
    D;JLT
    @ZERO
    D;JEQ
    @LOOP
    D;JGE
(NEGATIVE)
    @3
    M=-1
    @2
    M=!M
    M=M+1
(LOOP)
    @R1
    D=M
    @R0
    M=M+D
    @2
    MD=M-1
    @LOOP
    D;JGT

    @3
    D=M
    @NEGATION
    D;JLT
    @END
    D;JGE
(NEGATION)
    @0
    M=!M
    M=M+1
    @END
    0;JMP
(ZERO)
    @0
    M=0
(END)
    @END
    0;JMP