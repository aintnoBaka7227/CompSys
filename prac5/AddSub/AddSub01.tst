// This is test file 01 for AddSub.asm
// We will check an edge case 
// In this test case, all RAM[1], RAM[2], RAM[3] is set to 0
// Expected output is 0 and is stored in RAM[0]
// RAM[0] is initially set to 1 to ensure it it different with expected end result

load AddSub.asm,
output-file AddSub01.out,
compare-to AddSub01.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[3]%D2.6.2;

set PC 0,
set RAM[0] 1,  // Set R0
set RAM[1] 0,  // Set R1
set RAM[2] 0,  // Set R2
set RAM[3] 0;  // Set R3
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] 0,  // Restore arguments in case program used them
set RAM[2] 0,
set RAM[3] 0,
output;        // Output to file