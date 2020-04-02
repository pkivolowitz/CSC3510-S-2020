		.text
		.align	2
		.global	main

main:	stp		x29, x30, [sp, -16]!
		mov		x1, xzr
		
		ldr		x0, =jmptbl
		mov		x2, 2
		add		x0, x0, x2, lsl #2
		br		x0

jmptbl:	add		x1, x1, 1
		add		x1, x1, 1
		add		x1, x1, 1
		add		x1, x1, 1
		add		x1, x1, 1
		add		x1, x1, 1
		add		x1, x1, 1
		add		x1, x1, 1
		ldr		x0, =fmt
		bl		printf
		ldp		x29, x30, [sp], 16
		mov		x0, xzr
		ret

		.data
fmt:	.asciz	"Sum is: %d\n"
		.end
