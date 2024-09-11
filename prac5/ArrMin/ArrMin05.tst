// Test file 05 for ArrMin.asm
// test for full zeros

load ArrMin.asm,
output-file ArrMin05.out,
compare-to ArrMin05.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[55]%D2.6.2 RAM[56]%D2.6.2 RAM[57]%D2.6.2 RAM[58]%D2.6.2 RAM[59]%D2.6.2 RAM[60]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  55, // Set R1
set RAM[2]  6,  // Set R2
set RAM[55] 0,  // Set Arr[0]
set RAM[56] 0,  // Set Arr[1]
set RAM[57] 0,  // Set Arr[2]
set RAM[58] 0,  // Set Arr[3]
set RAM[59] 0,  // Set Arr[4]
set RAM[60] 0,  // Set Arr[5]
repeat 300 {
  ticktock;    // Run for 300 clock cycles
}
set RAM[1] 55,  // Restore arguments in case program used them
set RAM[2] 6,
set RAM[55] 0, 
set RAM[56] 0,  
set RAM[57] 0,  
set RAM[58] 0,  
set RAM[59] 0,  
set RAM[60] 0,  
output;        // Output to file

