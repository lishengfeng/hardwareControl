#include "regs.h"
#include <stdarg.h>
void uart_init(void)
{
	GPACON &= ~0xff;
	GPACON |= 0x22;

	ULCON0 = 3;
	UCON0 = (1 << 2)|(1 << 0);//(1 << 2)|(1)
	UFCON0 = 0;
	UMCON0 = 0;
	UBRDIV0 = 34;
	UDIVSLOT0 = 0xdfdd;
}
void uart_putchar(char c)
{
	UTXH0 = c;
	while(!(UTRSTAT0 & (1 << 2)));
}
char uart_getchar(void)
{
	while(!(UTRSTAT0 & 1));
	return URXH0;
}
void __uart_puts(char *str)
{
	while(*str){
		uart_putchar(*str);
		str++;
	}
}
void uart_puts(char *str)
{
	__uart_puts(str);
	uart_putchar('\n');
	uart_putchar('\r');
}
char Uart_recv[128];
char *uart_gets(void)
{
	int i = 0;
	char c;
	do{
		c = uart_getchar();
		uart_putchar(c);
		if(c == '\r'){
			uart_putchar('\n');
		}
		Uart_recv[i] = c;
		i++;
	}while(c != '\r');
	Uart_recv[i - 1] = '\0';
	return Uart_recv;
}
char U_tmp_buf[64];
char *dtoa(unsigned long num)
{//  123 "123"
	int i = 0;
	if(num < 10){
		U_tmp_buf[0] = num + '0';
		U_tmp_buf[1] = '\0';
	} else {
		dtoa(num / 10);
		while(U_tmp_buf[i]){
			i++;
		}
		U_tmp_buf[i] = num % 10 + '0';
		U_tmp_buf[i + 1] = '\0';
	}
	return U_tmp_buf;
}
char *xtoa(unsigned long num)
{// 65 0X41 "0x41"
	int i = 0;
	if(num < 10){
		U_tmp_buf[0] = num + '0';
		U_tmp_buf[1] = '\0';
	} else if(num >= 10 && num < 16){
		U_tmp_buf[0] = num - 10 + 'A';
		U_tmp_buf[1] = '\0';
	} else {
		xtoa(num / 16);
		while(U_tmp_buf[i]){
			i++;
		}
		if(num % 16 < 10){
			U_tmp_buf[i] = num % 16 + '0';
		} else {
			U_tmp_buf[i] = num % 16 - 10 + 'A';
		}
		U_tmp_buf[i + 1] = '\0';
	}
	return U_tmp_buf;
}

void uart_printf(char *fmt,...)
{//uart_printf("test %d\n",10);
//uart_printf("test %s\n","test");
	int i = 0;
	va_list ap;
	va_start(ap,fmt);
	while(fmt[i]){
		if(fmt[i] != '%'){
			uart_putchar(fmt[i]);
			if(fmt[i] == '\n'){
				uart_putchar('\r');
			}
			i++;
		} else {
			switch(fmt[i + 1]){
				case 'c':
				uart_putchar(va_arg(ap,int));
				break;
				case 'd':
				__uart_puts(dtoa(va_arg(ap,int)));
				break;
				case 'x':
				//10   "a" "A"
				__uart_puts("0x");
				__uart_puts(xtoa(va_arg(ap,int)));
				break;
				case 's':
				//printf("%s\n","test");
				__uart_puts(va_arg(ap,char *));			
				break;
			}
			i += 2;
		}
	}
	va_end(ap);
}




















