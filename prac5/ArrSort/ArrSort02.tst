// Test file 02 for ArrSort.asm
// test when value of R1 is 0 (address 0 in RAM)
// nothing should happen, program ends immediately
// R0 = -1 is set to -1

load ArrSort.asm,
output-file ArrSort02.out,
compare-to ArrSort02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  0, // Set R1
set RAM[2]  8,  // Set R2
repeat 600 {
  ticktock;    // Run for 600 clock cycles
}
set RAM[1] 0,  // Restore arguments in case program used them
set RAM[2] 8,
output;        // Output to file

