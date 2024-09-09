// This is test script 03 for Abs.asm
// We will check another edge case where input is the largest negative int for 16 
// bits hack machine that the absolute value can be represented in binary
// Set RAM[1] to -32767
// Expected output is 32767 and is stored in RAM[0]
// RAM[0] is initially set to 0 to ensure it it different with expected end result

// One particular case that need to be mentioned is -32768, which is the smallest
// negative int can be represent in 16 bits. For this one, the output will always be
// -32768 since 32768 can not be represented in 2 complements 16 bits.

load Abs.asm,
output-file Abs03.out,
compare-to Abs03.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] -32767;  // Set R1
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] -32767,  // Restore arguments in case program used them
output;        // Output to file