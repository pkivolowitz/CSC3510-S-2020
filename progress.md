# CSC 3510 - Spring 2020 - Progress

## February 6

We installed software. Everyone is expected to be able to run the ARM VM.

## February 11

Note - as of right now, the following are future tense and speculative.

* First project assigned with a **generous** two week due date
* We went over DON'T PANIC
* We talked about leaving behind the crutch of C++ features
* We learned about registers
    * X0 through X30 are 64 bit registers
	* X30 is the link register used to store return addresses
	* X29 is the frame pointer - avoid using it especially if mixing with C code
	* Different groups of registers must be protected in different ways
	* You can refer to W registers to get 32 bit equivalents
* We learned about calling conventions:
    * Parameters are passed in X0 through X7
	* Return values are passed in X0
	* But, for code you write called by code you write, anything goes
* We learned all variable access requires pointers
* Nothing happens to variables unless they are in registers
* We learned basic structure of an assembly language program
* We installed SFTP plug-in into Code and configured it to automatically send our source code over to the ARM VM

