int main()
{
	int i;
	clock_init();
	uart_init();
	uart_printf("test %d %c %s %x\n",100,'X',"uart",100);
	while(1){
		uart_puts(uart_gets());
	}
}
