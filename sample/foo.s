		.text
		.align		2
		.global		Foo

Foo:	stp			x29, x30, [sp, -16]!
		bl			puts
		ldp			x29, x30, [sp], 16
		ret
