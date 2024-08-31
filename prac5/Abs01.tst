// This is test script 01 for Abs.asm
// We will check an edge case where input is 0
// Set RAM[1] to 0
// Expected output is 0 and is stored in RAM[0]
// RAM[0] is initially set to 1 to ensure it it different with expected end result

load Abs.asm,
output-file Abs01.out,
compare-to Abs01.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2;

set PC 0,
set RAM[0] 1,  // Set R0
set RAM[1] 0;  // Set R1
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] 0,  // Restore arguments in case program used them
output;        // Output to file