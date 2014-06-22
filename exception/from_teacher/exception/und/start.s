	.align 2
	.global _start
	.text
_start:
	b	reset
	b	und

reset:
	mov	r0,#0x70000000
	orr	r0,#0x13
	mcr	p15,0,r0,c15,c2,4

	ldr	r0,=0x7e004000
	mov	r1,#0
	str	r1,[r0]
	
	mov	sp,#0x2000  @SVC

	mrs  r0,cpsr
	bic  r0,#0x1f
	orr  r0,#0x1b
	msr  cpsr,r0    @SVC -> UND
	
	mov sp,#0x1500  @UND

	mrs  r0,cpsr
	bic  r0,#0x1f
	orr  r0,#0x13
	msr  cpsr,r0    @UND -> SVC

	bl	main

und:
	stmfd	sp!,{r0-r12,lr}
	mrs		r0,cpsr
	bl		do_und
	ldmfd	sp!,{r0-r12,pc}^












