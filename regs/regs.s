		.text
		.global		main

/*	This program intends to show:
	* how some registers cannot be counted upon to keep their values after a function call.
	* a triggering of valgrind
	* an opportunity to fix the triggering of valgrind

	But first, there is a bug to find before the program will run correctly.

	Another teachable is the replacement with "ldr	xn, =symbol" with "adr	xn, symbol".
	These instructions demonstrate how every ARM instruction can be 4 bytes long and STILL
	be able to access via "pointer".

	If you have not already done so in your ARM VM:
	su
	enter password
	apt install valgrind
	return
	exit
*/

/*	InitRegs()
	Sets all registers to their register number except X29 and X30.
*/

InitRegs:
		stp		x29, x30, [sp, -16]!
		mov		x0, xzr
		mov		x1, 1
		mov		x2, 2
		mov		x3, 3
		mov		x4, 4
		mov		x5, 5
		mov		x6, 6
		mov		x7, 7
		mov		x8, 8
		mov		x9, 9
		mov		x10, 10
		mov		x11, 11
		mov		x12, 12
		mov		x13, 13
		mov		x14, 14
		mov		x15, 15
		mov		x16, 16
		mov		x17, 17
		mov		x18, 18
		mov		x19, 19
		mov		x20, 20
		mov		x21, 21
		mov		x22, 22
		mov		x23, 23
		mov		x24, 24
		mov		x25, 25
		mov		x26, 26
		mov		x27, 27
		mov		x28, 28
		ldp		x29, x30, [sp], 16
		ret

main:	
		stp		x29, x30, [sp, -16]!
		bl		InitRegs
		mov		x0, 16			// suggest inf reg
		bl		malloc			// suggest inf reg
		ldr		x1, =index
		str		x0, [x1]
		str		x0, [sp, -16]!
		bl		InitRegs
		ldr		x1, [sp], 16
		ldr		x0, =s
		bl		printf
		ldp		x29, x30, [sp], 16
		mov		x0, xzr
		ret

		.data

index:	.space		4
s:		.asciz		"This is an address 0x%lx\n"
		.end



