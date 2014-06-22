#include <stdio.h>
int my_fork(void)
{
	int out;
	__asm__ __volatile__(
		"swi	(0x900000 + 2)\n"
		"mov	%0,r0\n"
		:"=&r"(out)
	);
	return out;
}

int main()
{
	int pid = my_fork();
	if(pid < 0){
		exit(1);
	}
	while(1);
}

