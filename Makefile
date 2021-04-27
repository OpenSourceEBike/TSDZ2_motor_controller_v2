CCFLAGS=-mcpu=cortex-m0 -mthumb -g -Wall -Werror -I..
LDFLAGS=-T linker.flash.ld -nostartfiles
LDFLAGS_SRAM=-T linker.sram.ld -nostartfiles
CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld

ELF=main.elf \

LIBS=peripherals/scu.o \
     peripherals/gpio.o \
     peripherals/nvic.o \

all:	$(ELF)
	@echo "done"

main.elf:	init.o peripherals/scu.o peripherals/gpio.o main.o
	$(LD) $(LDFLAGS) --cref -Map $@.map $^ -o $@
	$(LD) $(LDFLAGS_SRAM) $^ -o $@.sram
	arm-none-eabi-objcopy -O binary $@ TSDZ2_motor_controller_v2_firmware.bin
	objcopy -O ihex $@  TSDZ2_motor_controller_v2_firmware.hex

.c.o:	
	$(CC) -c $(CCFLAGS) $< -o $@

clean: 
	rm peripherals/*.o *.o *.elf *.map *.elf.sram *.bin *.hex