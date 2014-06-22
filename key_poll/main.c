#include "regs.h"
int main()
{
	int i;
	led_init();
	GPNCON &= ~(0xff);
	while(2){
		for(i=0;i<4;i++){
			if(GPNDAT & (1<<i)){
				//GPN0没摁
				led_off(i);
			}else{
				led_on(i);
			}
		}
	}
}
