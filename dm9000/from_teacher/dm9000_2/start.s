	.align 2
	.global _start
	.text
_start:
	
	mov	r0,#0x70000000
	orr	r0,#0x13
	mcr	p15,0,r0,c15,c2,4

	ldr	r0,=0x7e004000
	mov	r1,#0
	str	r1,[r0]

	mrc	p15,0,r0,c1,c0,0
	orr	r0,#(1 << 24)
	mcr	p15,0,r0,c1,c0,0


	mov	sp,#0x2000  @SVC
	bl	arm_boot
	mov	sp,#0x58000000

	cps	#0x12		@SVC->IRQ
	mov	sp,#0x57000000	@IRQ
	cpsie i,#0x13

	ldr	r0,=__bss_start
	ldr r1,=__bss_end

	
	ldr	pc,=main





