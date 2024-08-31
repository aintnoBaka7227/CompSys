// This is test script 02 for Abs.asm
// We will check a case where input is positive
// Set RAM[1] to 100
// Expected output is 100 and is stored in RAM[0]
// RAM[0] is initially set to 0 to ensure it it different with expected end result

load Abs.asm,
output-file Abs02.out,
compare-to Abs02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 100;  // Set R1
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] 100,  // Restore arguments in case program used them
output;        // Output to file