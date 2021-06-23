CCFLAGS=-DXMC1302_T038x0064 -MMD -MT -MP -DXMC_MATH_DISABLE_DIV_ABI -ffunction-sections -fdata-sections -Wall -std=gnu99 -pipe -c -fmessage-length=0 -O3 -g3 -mthumb -mcpu=cortex-m0 -MD --specs=nano.specs -lc -g -Werror -I..

LDFLAGS=-DXMC1302_T038x0064 -O0 -g3 -T linker_script.ld -mcpu=cortex-m0 -mthumb
LDFLAGS += -nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs

CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld

CCFLAGS +=\
-I . \
-I Configuration \
-I ControlModule \
-I Libraries/CMSIS/Include \
-I Libraries/CMSIS/Infineon/XMC1300_series/Include \
-I Libraries/XMCLib/inc \
-I MCUInit \
-I MidSys \
-I uCProbe \

ELF=main.elf \

all: $(ELF)
	@echo "done"

main.elf: \
	Startup/startup_XMC1300.o \
	Startup/system_XMC1300.o \
	main.o \
	../brake.o \
	bldc_scalar_user_interface.o \
	bldc_scalar_variables_config.o \
	ControlModule/bldc_scalar_control_hall.o \
	ControlModule/bldc_scalar_control_scheme.o \
	ControlModule/bldc_scalar_ramp_generator.o \
	Interrupts/bldc_scalar_control_loop.o \
	Interrupts/bldc_scalar_ctrap_periodmatch.o \
	Interrupts/bldc_scalar_hall_event.o \
	Interrupts/bldc_scalar_hall_state_machine.o \
	Interrupts/bldc_scalar_pattern_shadowtx.o \
	Interrupts/bldc_scalar_protection_error.o \
	Libraries/Newlib/syscalls.o \
	Libraries/XMCLib/src/xmc_ccu4.o \
	Libraries/XMCLib/src/xmc_ccu8.o \
	Libraries/XMCLib/src/xmc_common.o \
	Libraries/XMCLib/src/xmc_gpio.o \
	Libraries/XMCLib/src/xmc_posif.o \
	Libraries/XMCLib/src/xmc_vadc.o \
	Libraries/XMCLib/src/xmc1_gpio.o \
	Libraries/XMCLib/src/xmc1_scu.o \
	MCUInit/ccu4.o \
	MCUInit/ccu8.o \
	MCUInit/gpio.o \
	MCUInit/nvic.o \
	MCUInit/posif.o \
	MCUInit/systick.o \
	MCUInit/vadc.o \
  MidSys/bldc_scalar_current_motor.o \
	MidSys/bldc_scalar_pwm_bc.o \
	MidSys/bldc_scalar_speed_pos_hall.o \
	MidSys/bldc_scalar_volt_dcbus.o \
	MidSys/bldc_scalar_volt_potentiometer.o \
	MidSys/bldc_scalar_volt_userdef.o \

	$(CC) $(LDFLAGS) $^ -o $@
	arm-none-eabi-objcopy -O binary $@ firmware.bin
	arm-none-eabi-objcopy -O ihex $@  firmware.hex

.c.o:	
	$(CC) -c $(CCFLAGS) $< -o $@

.S.o:
	$(CC) -x assembler-with-cpp -c $(CCFLAGS) $< -o $@

clean: 
	rm -f \
	*.o *.elf *.map *.bin *.hex \
	Startup/startup_XMC1300.o \
	Startup/system_XMC1300.o \
	main.o \
	../brake.o \
	bldc_scalar_user_interface.o \
	bldc_scalar_variables_config.o \
	ControlModule/bldc_scalar_control_hall.o \
	ControlModule/bldc_scalar_control_scheme.o \
	ControlModule/bldc_scalar_ramp_generator.o \
	Interrupts/bldc_scalar_control_loop.o \
	Interrupts/bldc_scalar_ctrap_periodmatch.o \
	Interrupts/bldc_scalar_hall_event.o \
	Interrupts/bldc_scalar_hall_state_machine.o \
	Interrupts/bldc_scalar_pattern_shadowtx.o \
	Interrupts/bldc_scalar_protection_error.o \
	Libraries/Newlib/syscalls.o \
	Libraries/XMCLib/src/xmc_ccu4.o \
	Libraries/XMCLib/src/xmc_ccu8.o \
	Libraries/XMCLib/src/xmc_common.o \
	Libraries/XMCLib/src/xmc_gpio.o \
	Libraries/XMCLib/src/xmc_posif.o \
	Libraries/XMCLib/src/xmc_vadc.o \
	Libraries/XMCLib/src/xmc1_gpio.o \
	Libraries/XMCLib/src/xmc1_scu.o \
	MCUInit/ccu4.o \
	MCUInit/ccu8.o \
	MCUInit/gpio.o \
	MCUInit/nvic.o \
	MCUInit/posif.o \
	MCUInit/systick.o \
	MCUInit/vadc.o \
  MidSys/bldc_scalar_current_motor.o \
	MidSys/bldc_scalar_pwm_bc.o \
	MidSys/bldc_scalar_speed_pos_hall.o \
	MidSys/bldc_scalar_volt_dcbus.o \
	MidSys/bldc_scalar_volt_potentiometer.o \
	MidSys/bldc_scalar_volt_userdef.o \