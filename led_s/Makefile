CC :=arm-linux-gcc
AS :=arm-linux-as
LD :=arm-linux-ld
OBJCOPY := arm-linux-objcopy

ELF :=arm
BIN :=arm.bin
OBJS :=start.o

all:$(ELF)
	$(OBJCOPY) $< -O binary /tftpboot/$(BIN)
$(ELF):$(OBJS)
	$(LD) $^ -o $@ -Ttext 0
%.o:%.s
	$(AS) $< -o $@
clean:
	rm -rf $(OBJS) $(ELF)
