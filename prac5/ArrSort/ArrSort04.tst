// Test file 04 for ArrSort.asm
// test an zeros array to check any unexpected behaviour: uncontrol access to mems or logic break
// sort algo should only check and do nothing since no sorts needed

load ArrSort.asm,
output-file ArrSort04.out,
compare-to ArrSort04.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[20]%D2.6.2 RAM[21]%D2.6.2 RAM[22]%D2.6.2 RAM[23]%D2.6.2 RAM[24]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  20, // Set R1
set RAM[2]  5,  // Set R2
set RAM[20] 0,  // Set Arr[0]
set RAM[21] 0,  // Set Arr[1]
set RAM[22] 0,  // Set Arr[2]
set RAM[23] 0,  // Set Arr[3]
set RAM[24] 0,  // Set Arr[4]
repeat 600 {
  ticktock;    // Run for 600 clock cycles
}
set RAM[1] 20,  // Restore arguments in case program used them
set RAM[2] 5,
output;        // Output to file

