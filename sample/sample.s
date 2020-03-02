/*
*	Sample program to assist in doing linked list program.
*
*	This program  allocates  NUM_NODES  nodes putting each new node
*	at the FRONT of the linked list. The payload is a random number
*	from 0 to 255 with no seed so the numbers will be the same each
*	time.
*
*	Then, the list is deleted printing each node as it goes.
*/
			.text
			.align		2
			.global		main

			.equ	O_PAYLOAD, 8
			.equ	O_NEXT, 0
			.equ	NODE_SIZE, 16
			.equ	NUM_NODES, 10

/*	Dictionary:
	x20		number of nodes to allocate.
	x21		root
*/

main:		stp			x29, x30, [sp, -16]!
			stp			x20, x21, [sp, -16]!
			mov			x21, xzr
			mov			x20, NUM_NODES

1:			cbz			x20, 10f
			bl			allocnode
			str			x0, [sp, -16]!
			bl			rand
			and 		x0, x0, 0xFF
			ldr			x1, [sp], 16
			str			w0, [x1, O_PAYLOAD]
			str			x21, [x1, O_NEXT]
			mov			x21, x1
			sub			x20, x20, 1
			b 			1b

10:			bl			dellist

			ldp			x20, x21, [sp], 16
			ldp			x29, x30, [sp], 16
			ret

allocnode:	stp			x29, x30, [sp, -16]!
			mov			x0, NODE_SIZE
			bl			malloc
			str			xzr, [x0, O_NEXT]
			str			wzr, [x0, O_PAYLOAD]
			ldp			x29, x30, [sp], 16
			ret

dellist:	stp			x29, x30, [sp, -16]!
1:			cbz			x21, 2f
			ldr			x0, =delfmt
			mov			x1, x21
			ldr			w2, [x21, O_PAYLOAD]
			bl			printf
			mov			x0, x21
			ldr			x21, [x21, O_NEXT]
			bl			free
			b 			1b
2:			ldp			x29, x30, [sp], 16
			ret

			.data
delfmt:		.asciz		"Deleting node at 0x%lx with payload: %d\n"

			.end
