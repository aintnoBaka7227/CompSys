// this is test script 02 for Mult.tst
// For my implementation logic, RAM[2] value has to be >=0 for the Loop condition
// so for this test case, I will set RAM[2] to a negative value of -5 to check if
// my code can handle multiplication with negative values stored in RAM[2].
// RAM[1] is set to a positive value of 6
// The expected output is -120 and stored in RAM[0]
// RAM[0] is initially set to 0 to ensure it is different to the expected output

load Mult.asm,
output-file Mult02.out,
compare-to Mult02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 6,  // Set R1
set RAM[2] -20;  // Set R2
repeat 200 {
  ticktock;    // Run for 200 clock cycles
}
set RAM[1] 6,  // Restore arguments in case program used them
set RAM[2] -20,
output;        // Output to file

