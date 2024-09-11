// Test file 02 for ArrMin.asm
// test when value of R1 is 0 (address 0 in RAM)
// expected output to be 0

load ArrMin.asm,
output-file ArrMin02.out,
compare-to ArrMin02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  0, // Set R1
set RAM[2]  5,  // Set R2
repeat 300 {
  ticktock;    // Run for 300 clock cycles
}
set RAM[1] 0,  // Restore arguments in case program used them
set RAM[2] 5,
output;        // Output to file

