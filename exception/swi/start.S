	.align 2 
	.global _start
	.text
_start:
	b reset
 	.word 0
	b swi	

reset:
	mov r0,#0x70000000
	orr r0,#0x13
	mcr p15,0,r0,c15,c2,4

	ldr r0,=0x7e004000
	mov r1,#0
	str r1,[r0]

	mov sp,#0x2000

	cps #0x1f  @SVC->SYS
	mov sp,#0x1500 
	cps #0x13  @SYS->SVC
	bl main @SVC init

	cps #0x10 @SVC ->usr
	bl user

	b . 
und:
	stmfd sp!,{r0-r12,lr}
	mrs r0,cpsr
	bl do_und
	ldmfd sp!,{r0-r12,pc}^	

swi:
	stmfd sp!,{r0-r12,lr}
	bl do_swi
	ldmfd sp!,{r0-r12,pc}^
