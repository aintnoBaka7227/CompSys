// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
    @i
    M=1
    @1
    D=M
    @4
    M=D
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
    M=-M
(LOOP)
    @i
    D=M
    @2
    D=D-M
    @WRITE
    D;JGE
    @4
    D=M
    @1
    M=D+M
    @i
    M=M+1
    @LOOP
    0;JMP
(WRITE)
    @1
    D=M
    @0
    M=D
    @3
    D=M
    @NEGATION
    D;JLT
    @END
    D;JGE
(NEGATION)
    @1
    D=-M
    @0
    M=D
(ZERO)
    @0
    M=0
(END)
    @END
    0;JMP