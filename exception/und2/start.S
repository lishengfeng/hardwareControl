	.align 2 
	.global _start
	.text
_start:
	b reset
	b und

reset:
	mov r0,#0x70000000
	orr r0,#0x13
	mcr p15,0,r0,c15,c2,4

	ldr r0,=0x7e004000
	mov r1,#0
	str r1,[r0]

	mov sp,#0x2000

	cps #0x1b @SVC->UND

	mov sp,#0x1500 
	
	cps #0x13 @UND->SVC

	bl main
und:
	stmfd sp!,{r0-r12,lr}
	mrs r0,cpsr
	sub lr,#4
	ldr r1,[lr]
	bl do_und
	ldmfd sp!,{r0-r12,pc}^	
