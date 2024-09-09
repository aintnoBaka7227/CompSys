// This is test file 02 for AddSub.asm
// We will check a case where negative numbers is involved 
// In this test case, set RAM[1] to 10, RAM[2] to -4, RAM[3] is set to -5
// Expected output is 11 and is stored in RAM[0]
// RAM[0] is initially set to 0 to ensure it it different with expected end result

load AddSub.asm,
output-file AddSub02.out,
compare-to AddSub02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[3]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 10,  // Set R1
set RAM[2] -4,  // Set R2
set RAM[3] -5;  // Set R3
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] 10,  // Restore arguments in case program used them
set RAM[2] -4,
set RAM[3] -5,
output;        // Output to file