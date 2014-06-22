CC	:= arm-linux-gcc
AS	:= arm-linux-as
LD	:= arm-linux-ld
OBJCOPY	:= arm-linux-objcopy

ELF	:= arm
BIN	:= arm.bin
OBJS := start.o main.o clock.o nand.o uart.o ddr.o arm_boot.o ac97.o vic.o delay.o


all:$(ELF)
	$(OBJCOPY) $< -O binary /tftpboot/$(BIN)
$(ELF):$(OBJS)
	$(LD) $^ -o $@ -Ttext 0x55000000 -T ld.lds
%.o:%.c
	$(CC) -c $< -o $@
%.o:%.s
	$(AS) $< -o $@

clean:
	rm -rf $(OBJS) $(ELF)






