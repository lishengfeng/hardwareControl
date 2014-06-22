	.align 2
	.global main
	.text
main:
	stmfd	sp!,{r0-r12,lr}
	mov	r0,#3
	mov	r1,#5
	bl	my_add
	mov	r1,r0
	ldr	r0,=fmt
	bl	printf
	ldmfd	sp!,{r0-r12,pc}

my_add:
	add	r0,r1
	mov	pc,lr

	.data
fmt:
	.ascii "%d\n\0"






