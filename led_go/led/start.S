	.align 2 
	.global _start
	.text
_start:
	stmfd sp!,{r0-r12,lr}
	bl    main
	ldmfd sp!,{r0-r12,pc}
