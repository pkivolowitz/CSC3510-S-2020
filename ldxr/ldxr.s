THIS IS ALL WRONG. DO NOT USE.

		.text
		.align 2
		.global main

main:	stp		x29, x30, [sp, -16]!

/*	Ordinary load using `ldr` on `lk` after having put `7`
	into that memory. The value to be printed should be `7`.
*/
		ldr		x0, =fmt1
		ldr		x1, =lk
		mov		w2, 7
		str		w2, [x1]
		ldr		w2, [x1]		// ordinary ldr
		bl		printf

/*	`ldxr` on `lk` - there is `7` still in that space so
	the printf should print that value. Next, an `stxr`
	is performed - notice w2 has `9` in it before the
	`stxr` instruction. They way the `stxr` is coded, the
	contents of w2 after the `stxr` will indicate if any
	other `ldxr` instructions have been attempted on the
	same memory. The second number printed should be `1`.
*/
		ldr		x0, =fmt2
		ldr		x1, =lk
		ldaxr	w2, [x1]
		bl		printf

		ldr		x0, =fmt3
		ldr		x1, =lk
		mov		w2, 9
		stlxr	w2, w2, [x1]
		bl		printf

/*	This will demonstrate what FAILING to get the lock looks
	like. An `ldxr` is done immediately below - this GETS the
	lock.

	Then, a second `ldxr` is done. When the next `stxr` is
	done, it will return 0 not 1 indicating someone else 
	already has the lock.

	Finally, a second `stxr` is performed simulating the first
	thread (actually, there is just one thread in this example)
	unlocking the lock.

	ldxr
		ldxr
		stxr	returns 0
	stxr		returns 1
*/
		ldr		x0, =fmt4
		ldr		x1, =lk
		ldaxr	w2, [x1]
		bl		printf

		// Second and third attempt to get the lock.
		ldr		x1, =lk
		ldaxr	w2, [x1]
		ldr		x1, =lk
		ldaxr	w2, [x1]

		// This should print 0 - telling the executive thread
		// it did NOT get the lock.
		ldr		x0, =fmt5
		ldr		x1, =lk
		mov		w2, 9
		stlxr	w2, w2, [x1]
		bl		printf

		// This should print 1 - because it is an `stxr` that
		// matches up to the original `ldxr` above.

		ldr		x0, =fmt6
		ldr		x1, =lk
		mov		w2, 11
		stlxr	w2, w2, [x1]
		bl		printf

/*	Finally, what is in `lk`. Is it 7 or 9 or 11?
*/
		ldr		x0, =fmt7
		ldr		x1, =lk
		ldr		w2, [x1]
		bl		printf

		ldp		x29, x30, [sp], 16
		mov		x0, xzr
		ret

		.data
lk:		.space	4
fmt1:	.asciz	"1 address: 0x%lx value: %d should be 7 (ordinary str)\n"
fmt2:	.asciz	"2 address: 0x%lx value: %d should be 7 (was in lk)\n"
fmt3:	.asciz	"3 address: 0x%lx value: %d should be 1 (lock was held)\n"
fmt4:	.asciz	"4 address: 0x%lx value: %d should be 7 (still in lk)\n"
fmt5:	.asciz	"5 address: 0x%lx value: %d should be 0 (lock was NOT held and overwrite of lk fails)\n"
fmt6:	.asciz	"6 address: 0x%lx value: %d should be 1 (lock was held)\n"
fmt7:	.asciz	"7 address: 0x%lx value: %d thought it would be 11 (it isn't)\n"
