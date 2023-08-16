TARGET := teeny

CC := i686-elf-gcc
CCFLAGS := -g -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS := -T linker.ld -ffreestanding -O2 -nostdlib -lgcc

AS := nasm
ASFLAGS := -f elf32

C_SRCS := $(wildcard *.c)
C_OBJS := $(C_SRCS:.c=.o)
C_DEPS := $(C_SRCS:.c=.d)

AS_SRCS := $(wildcard *.s)
AS_OBJS := $(AS_SRCS:.s=.o)

all: $(TARGET)

iso: $(TARGET)
	mkdir -p target/boot/grub
	cp $(TARGET) target/boot/$(TARGET)
	cp grub.cfg target/boot/grub/grub.cfg
	grub-mkrescue -o $(TARGET).iso target

$(TARGET): $(C_OBJS) $(AS_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

-include $(C_DEPS)

%.o: %.c
	$(CC) $(CCFLAGS) -MMD -MP -c -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	rm -f $(TARGET) $(C_OBJS) $(C_DEPS) $(AS_OBJS) $(TARGET).iso
	rm -fr target
