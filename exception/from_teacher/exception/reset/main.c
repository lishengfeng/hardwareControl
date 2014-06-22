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
	uart_printf("cpsr.M %x\n",i & 0x1f);


	while(1){
		uart_puts(uart_gets());
	}
}
