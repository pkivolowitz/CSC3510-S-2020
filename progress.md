# CSC 3510 - Spring 2020 - Progress

## February 6

We installed software. Everyone is expected to be able to run the ARM VM.

## February 11

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
* We learned basic structure of an assembly language program
* We installed SFTP plug-in into Code and configured it to automatically send our source code over to the ARM VM

## February 13

We had a very productive day today. We:

* started with a C implementation of fizzbuzz and broke it down into C that is essentially assembly language.
* began coding the assembly language version
    * we learned what segments are
    * we learned we have at least two segments, text and data. Your code goes in the text segment and your global variables go in data
    * different register groups have differing requirements. For example x0 through x7 are scratch registers.
    * x29 and x30 must be preserved on the stack then restored for every function you write
    * ldp and stp are used to load and store two registers at a time into an address contained in a register (sp)
    * order going on the stack must be reversed by the order coming off the stack
    * the C runtime library is just "there"

## February 18

Either this day or the next we did a deep dive into caches.

## February 20

## February 25

I have not recorded our progress for a bit. I apologize.

Today we:

* went over P3
* answered questions abotu P2

Today we learned about:

* rotational and seek latency
* thrashing
* the concept of file systems as being software that determined where to place data on disk
* sequential access to a spinning disk can actually be faster than accessing an SSD particularly for writing

Then, we took apart 2 3 TB drives. One we left largely intact. The other was stripped down to its constituent parts.

## February 27

We will review.

Today we expect to learn about how integers and floats work. Then, will learn about the floating point unit on AARCH64.

