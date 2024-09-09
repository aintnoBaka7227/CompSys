// this is test script 05 for Mult.tst
// This will test an edge case where we multiple a large positive integer 
// RAM[1] = 31, RAM[2] = 1057
// The expected output is 32767 and stored in RAM[0]
// RAM[0] is initially set to 0 to ensure it is different to the expected output

load Mult.asm,
output-file Mult05.out,
compare-to Mult05.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 31,  // Set R1
set RAM[2] 1057;  // Set R2
repeat 15000 {
  ticktock;    // Run for 15000 clock cycles
}
set RAM[1] 31,  // Restore arguments in case program used them
set RAM[2] 1057,
output;        // Output to file



