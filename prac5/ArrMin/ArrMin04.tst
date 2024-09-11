// Test file 04 for ArrMin.asm
// test for overflow cases: >32767 and <-32768 + mix integers

load ArrMin.asm,
output-file ArrMin04.out,
compare-to ArrMin04.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[30]%D2.6.2 RAM[31]%D2.6.2 RAM[32]%D2.6.2 RAM[33]%D2.6.2 RAM[34]%D2.6.2 RAM[35]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  30, // Set R1
set RAM[2]  6,  // Set R2
set RAM[30] 32767,  // Set Arr[0]
set RAM[31] -2,  // Set Arr[1]
set RAM[32] 32766,  // Set Arr[2]
set RAM[33] -1,  // Set Arr[3]
set RAM[34] -4800,  // Set Arr[4]
set RAM[35] -32768,  // Set Arr[5]
repeat 300 {
  ticktock;    // Run for 300 clock cycles
}
set RAM[1] 30,  // Restore arguments in case program used them
set RAM[2] 6,
set RAM[30] 32767, 
set RAM[31] -2,  
set RAM[32] 32766,  
set RAM[33] -1,  
set RAM[34] -4800,  
set RAM[35] -32768,  
output;        // Output to file

