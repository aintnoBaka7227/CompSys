// this is test script 04 for Mult.tst
// This will test an edge case where we multiple a number by 0. 
// Since my incrementation involves RAM[2], I will set it to 0, while RAM[1] = -30000 (big negative num)
// The expected output is 0 and stored in RAM[0]
// RAM[0] is initially set to 1 to ensure it is different to the expected output

load Mult.asm,
output-file Mult04.out,
compare-to Mult04.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 1,  // Set R0
set RAM[1] -30000,  // Set R1
set RAM[2] 0;  // Set R2
repeat 150 {
  ticktock;    // Run for 150 clock cycles
}
set RAM[1] -30000,  // Restore arguments in case program used them
set RAM[2] 0,
output;        // Output to file



