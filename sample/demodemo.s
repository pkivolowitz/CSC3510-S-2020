		.text
		.align	2
		.global InitializeSomething

		.equ	A, 0
		.equ	B0, 4
		.equ	B1, 5
		.equ	B2, 6
		.equ	B3, 7
		.equ	C, 8

InitializeSomething:
		mov		w1, -10
		str		w1, [x0, A]
		mov		w1, 'a'
		strb	w1, [x0, B0]
		add		w1, w1, 1		
		strb	w1, [x0, B1]
		add		w1, w1, 1		
		strb	w1, [x0, B2]
		add		w1, w1, 1		
		strb	w1, [x0, B3]
		add		w1, w1, 1
		mov		w1, 20
		str		w1, [x0, C]
		ret
			
