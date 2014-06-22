#include "regs.h"
void vic_request(unsigned int irq,void (*handle)(void))
{//irq 中断号  handle 对应的中断处理函数
//将ISR地址写到对应的向量地址寄存器 同时使能该中断
	if(irq < 32){
		*(&VIC0VECTADDR0 + irq) = (unsigned long)handle;
		VIC0INTENABLE = (1 << irq);
	} else if(irq >= 32 && irq < 64){
		*(&VIC1VECTADDR0 + (irq - 32)) = (unsigned long)handle;
		VIC1INTENABLE = (1 << (irq - 32));
	}
}


void irq_enable(unsigned int irq)
{
	if(irq < 32){
		VIC0INTENABLE = (1 << irq);
	} else if(irq >= 32 && irq < 64){
		VIC1INTENABLE = (1 << (irq - 32));
	}
}
void irq_disable(unsigned int irq)
{
	if(irq < 32){
		VIC0INTENCLEAR = (1 << irq);
	} else if(irq >= 32 && irq < 64){
		VIC1INTENCLEAR = (1 << (irq - 32));
	}
}













