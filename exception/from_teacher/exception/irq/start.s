	.align 2
	.global _start
	.text
_start:
	b	reset
	.word 0
	.word 0
	.word 0
	.word 0
	.word 0
	b	irq
reset:
	mov	r0,#0x70000000
	orr	r0,#0x13
	mcr	p15,0,r0,c15,c2,4

	ldr	r0,=0x7e004000
	mov	r1,#0
	str	r1,[r0]
	
	mov	sp,#0x2000  @SVC

	cps	#0x12		@SVC->IRQ
	mov	sp,#0x1500	@IRQ
	cpsie i,#0x13
	
	bl	main

irq:
@	stmfd	sp!,{r0-r12,lr}
@	bl		do_irq
@	ldmfd	sp!,{r0-r12,lr}
@	subs	pc,lr,#4

	sub		lr,#4
	stmfd	sp!,{r0-r12,lr}
	bl		do_irq
	ldmfd	sp!,{r0-r12,pc}^








