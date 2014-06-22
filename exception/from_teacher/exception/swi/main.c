int main()
{
	int i;
	clock_init();
	uart_init();
	__asm__ __volatile__(
		"mrs	r0,cpsr\n"
		"mov	%0,r0\n"
		:"=&r"(i)
		:
		:"r0"
	);
	uart_printf("%s cpsr.M %x\n",__FUNCTION__,i & 0x1f);
}
void do_swi(unsigned long ins)
{
	int out;
	__asm__ __volatile__(
		"mrs	%0,cpsr\n"
		:"=&r"(out)
	);
	uart_printf("%s cpsr.M %x\n",__FUNCTION__,out & 0x1f);
	uart_printf("%x\n",ins & 0xffffff);
}
void user(void)
{
	int out;
	__asm__ __volatile__(
		"mrs	%0,cpsr\n"
		:"=&r"(out)
	);
	uart_printf("%s cpsr.M %x\n",__FUNCTION__,out & 0x1f);
	__asm__ __volatile__(
		"nop\n"
		"swi	#0x123\n"
		"nop\n"
		);
	__asm__ __volatile__(
			"mrs    %0,cpsr\n"
			:"=&r"(out)
			);
	uart_printf("%s cpsr.M %x\n",__FUNCTION__,out & 0x1f);
}








