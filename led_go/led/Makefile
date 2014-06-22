CC :=arm-linux-gcc
AS :=arm-linux-as
LD :=arm-linux-ld
OBJCOPY := arm-linux-objcopy

ELF := arm
BIN := arm.bin
OBJS := start.o main.o led.o delay.o

all:$(ELF)
	$(OBJCOPY) $< -O binary /tftpboot/$(BIN)
$(ELF):$(OBJS)
	$(LD) $^ -o $@ -Ttext 51000000
%.o:%.c
	$(CC) -c $< -o $@
%.o:%.s
	$(AS) $< -o $@
clean:
	rm -rf $(OBJS) $(ELF)

