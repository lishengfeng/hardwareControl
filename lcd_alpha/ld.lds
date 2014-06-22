OUTPUT_FORMAT("elf32-littlearm");
OUTPUT_ARCH("arm");
ENTRY("_start");
SECTIONS
{
	. = 0;
	.text : {
		start.o(.text);
		clock.o(.text);
		ddr.o(.text);
		nand.o(.text);
		arm_boot.o(.text);
		*.o(.text);
	}
	. = ALIGN(4);
	.rodata : { *.o(.rodata);}
	. = ALIGN(4);
	.data : {*.o(.data);}
	. = ALIGN(4);
	.bss : { *.o(.bss);}

}
