// Test file 01 for ArrSort.asm
// This case we test an array of all duplicated elements
// no changes should be made

load ArrSort.asm,
output-file ArrSort01.out,
compare-to ArrSort01.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[70]%D2.6.2 RAM[71]%D2.6.2 RAM[72]%D2.6.2 RAM[73]%D2.6.2 RAM[74]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  70, // Set R1
set RAM[2]  5,  // Set R2
set RAM[70] 1,  // Set Arr[0]
set RAM[71] 1,  // Set Arr[1]
set RAM[72] 1,  // Set Arr[2]
set RAM[73] 1;  // Set Arr[3]
set RAM[74] 1;  // Set Arr[4]
repeat 600 {
  ticktock;    // Run for 600 clock cycles
}
set RAM[1] 70,  // Restore arguments in case program used them
set RAM[2] 5,
output;        // Output to file

