
			.text
			.align		2
			.global		main

main:		# preserve registers for later
			stp			x29, x30, [sp, -16] !
			stp			x20, x21, [sp, -16] !

			ldr			x0, =fizz
			bl			printf

			ldr			x0, =fmt
			mov			x1, 7
			bl			printf
			
			# Dictionary:
			#	x20		as i
			#	x21		as pflag

			# restore registers
bottom:		# gap
			ldp			x20, x21, [sp], 16
			ldp			x29, x30, [sp], 16
			mov			x0, xzr
			ret

			.data

fizz:		.asciz		"Fizz"
buzz:		.asciz		"Buzz"
nl:			.asciz		"\n"
fmt:		.asciz		"%d"

			.end
