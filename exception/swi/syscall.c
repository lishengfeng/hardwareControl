#include <stdio.h>
int my_fork(void)
{
	int out;
	__asm__ __volatile__(
		"swi (0x900000+2)\n"
		"mov %0,r0\n"
		:"=&r"(out)
		:
		:"r0"
	);
	printf("%d\n",out);
}

int main(void)
{
	int pid;
	pid = my_fork();
	while(1);
}
