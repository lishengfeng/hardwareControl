#include "regs.h"
#include <stdarg.h>
void uart_init(void)
{
	GPACON &=~0xff;
	GPACON |= 0x22;

	ULCON0=3;
	UCON0 =(1<<2)|(1<<0);
	UFCON0 = 0;
	UMCON0 = 0;
	UBRDIV0 = 34;
	UDIVSLOT0 =0xdfdd; 
}
void uart_putchar(char c)
{
	UTXH0=c;
	while(!(UTRSTAT0&(1<<2)));
}
char uart_getchar(void )
{
	while(!(UTRSTAT0&1));
	return URXH0;
}
void __uart_puts(char *str)
{
	//字符串的0 在十进制是48OB
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
char Uart_recv[128];          //只能是全局的,不随函数结束清除,用来模拟malloc，不能太大只有8k内存
char *uart_gets(void)
{
	int i = 0;
	char c;
	do{
		c=uart_getchar();
		uart_putchar(c);//为了回显
		if(c=='\r'){
			uart_putchar('\n');//否则再次打印时回显会被覆盖,看不出效果OD
		}
		Uart_recv[i]=c;
		i++;
	}while(c!='\r');
	Uart_recv[i-1]='\0'; //将\r改成\0
	return Uart_recv;
}

char U_tmp_buf[64];
char *itoa(unsigned long num)
{
	int i=0;
	if(num<10){
		U_tmp_buf[0]=num+'0';
		U_tmp_buf[1]='\0';
	}else{
		itoa(num/10);
		while(U_tmp_buf[i]){
			i++;
		}
		U_tmp_buf[i]=num%10+'0';
		U_tmp_buf[i+i]='\0';
	}
	return U_tmp_buf;
}
char *xtoa(unsigned long num)
{
	int i=0;
	if(num < 10){
		U_tmp_buf[0]=num+'0';
		U_tmp_buf[1]='\0';
	}else if(num>=10&& num<16){
		U_tmp_buf[0]=num-10+'A';
		U_tmp_buf[1]='\0';
	}else{
		xtoa(num/16);
		while(U_tmp_buf[i]){
			i++;
		}
		if(num%16<10){
			U_tmp_buf[i]=num%16+'0';
		}else{
			U_tmp_buf[i]=num%16-10+'A';
		}
		U_tmp_buf[i+1]='\0';
	}
	return U_tmp_buf;
}

void uart_printf(char *fmt,...)
{
	//未完成版本
	char buffer[64];
	int tmp;
	va_list ap;
	int i=0;
	va_start(ap,fmt);
	while(fmt[i]){
		if(fmt[i]!='%'){
			uart_putchar(fmt[i]);
			if(fmt[i] == '\n' ){
				uart_putchar('\r');
			}
			i++;	
		} else {
			switch(fmt[i+1]){
				case 'd':
					__uart_puts(itoa(va_arg(ap,int)));
				break;
				case 'x':
					__uart_puts("0x");
					__uart_puts(xtoa(va_arg(ap,int)));
				break;
				case 'c':
					uart_putchar(va_arg(ap,int));
				break;
				case 's':
					__uart_puts(va_arg(ap,char*));
				break;
				default:
					uart_putchar(fmt[i]);
					i-=1;
				break;
			}
			i+=2;
		}
	}
	va_end(ap);
}
