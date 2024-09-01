// this is test script 03 for Mult.tst
// For my implementation logic, RAM[2] value has to be >=0 for the Loop condition
// so for this test case, I will set both RAM[1] and RAM[2] to negative values
// -8 and -100 
// The expected output is 800 and stored in RAM[0]
// RAM[0] is initially set to 0 to ensure it is different to the expected output

load Mult.asm,
output-file Mult03.out,
compare-to Mult03.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] -8,  // Set R1
set RAM[2] -100;  // Set R2
repeat 1500 {
  ticktock;    // Run for 1500 clock cycles
}
set RAM[1] -8,  // Restore arguments in case program used them
set RAM[2] -100,
output;        // Output to file

