CCFLAGS=-DXMC1302_T038x0064 -O3 -g3 -mthumb -mcpu=cortex-m0 -MD --specs=nano.specs -lc -g -Werror -I..

LDFLAGS=-DXMC1302_T038x0064 -O3 -g3 -T DAVE_FOC_PROJECT/linker_script.ld -mcpu=cortex-m0 -mthumb
LDFLAGS += -nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs
# LDFLAGS += -u _printf_float -u _scanf_float

CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld

CCFLAGS +=\
-I . \
-I DAVE_FOC_PROJECT/Libraries/CMSIS/Include \
-I DAVE_FOC_PROJECT/Libraries/CMSIS/Infineon/XMC1300_series/Include \
-I DAVE_FOC_PROJECT/Libraries/XMCLib/inc \
-I DAVE_FOC_PROJECT/Dave/Generated \
-I DAVE_FOC_PROJECT/Dave/Generated/PWM \
-I DAVE_FOC_PROJECT/Dave/Generated/ADC_QUEUE \
-I DAVE_FOC_PROJECT/Dave/Generated/CLOCK_XMC1 \
-I DAVE_FOC_PROJECT/Dave/Generated/CPU_CTRL_XMC1 \
-I DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_ADC \
-I DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_CCU4 \
-I DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_CCU8 \
-I DAVE_FOC_PROJECT/Dave/Generated/PMSM_FOC \
-I DAVE_FOC_PROJECT/Dave/Generated/PWM_SVM \
-I DAVE_FOC_PROJECT/Dave/Generated/UART \

LIBSDIR = -LDAVE_FOC_PROJECT/Dave/Generated/PMSM_FOC
LIBS = -lPMSM_FOC_LIB

ELF=main.elf \

all: $(ELF)
	@echo "done"

main.elf: \
	DAVE_FOC_PROJECT/Startup/startup_XMC1300.o \
	DAVE_FOC_PROJECT/Startup/system_XMC1300.o \
	DAVE_FOC_PROJECT/Libraries/Newlib/syscalls.o \
	DAVE_FOC_PROJECT/main.o \
	adc.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc_vadc.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc1_scu.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc_posif.o \
	DAVE_FOC_PROJECT/Dave/Generated/DAVE.o \
	DAVE_FOC_PROJECT/Dave/Generated/PWM/pwm_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/PWM/pwm.o \
	DAVE_FOC_PROJECT/Dave/Generated/ADC_QUEUE/adc_queue_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/ADC_QUEUE/adc_queue.o \
	DAVE_FOC_PROJECT/Dave/Generated/CLOCK_XMC1/clock_xmc1_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/CLOCK_XMC1/clock_xmc1.o \
	DAVE_FOC_PROJECT/Dave/Generated/CPU_CTRL_XMC1/cpu_ctrl_xmc1_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/CPU_CTRL_XMC1/cpu_ctrl_xmc1.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_ADC/global_adc_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_ADC/global_adc.o \
	DAVE_FOC_PROJECT/Dave/Generated/UART/uart_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/UART/uart.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc_gpio.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc1_gpio.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc_uart.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc_usic.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_CCU4/global_ccu4_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_CCU4/global_ccu4.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_CCU8/global_ccu8_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_CCU8/global_ccu8.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc_ccu4.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc_ccu8.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_POSIF/global_posif_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_POSIF/global_posif.o \
	DAVE_FOC_PROJECT/Dave/Generated/HALL_POSIF/hall_posif_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/HALL_POSIF/hall_posif.o \
	DAVE_FOC_PROJECT/Dave/Generated/PWM_SVM/pwm_svm_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/PWM_SVM/pwm_svm.o \
	DAVE_FOC_PROJECT/Dave/Generated/PWM_SVM/pwm_svm_table.o \
	DAVE_FOC_PROJECT/Dave/Generated/PMSM_FOC/pmsm_foc_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/PMSM_FOC/pmsm_foc.o \
	DAVE_FOC_PROJECT/Dave/Generated/PMSM_FOC/pmsm_foc_control.o \
		
	$(CC) $(LDFLAGS) $(LIBSDIR) $^ $(LIBS) -o $@
	arm-none-eabi-objcopy -O binary $@ TSDZ2_motor_controller_v2_firmware.bin
	objcopy -O ihex $@  TSDZ2_motor_controller_v2_firmware.hex

.c.o:	
	$(CC) -c $(CCFLAGS) $< -o $@

.S.o:
	$(CC) -c $(CCFLAGS) $< -o $@

clean: 
	rm -f \
	*.o *.elf *.map *.bin *.hex \
	DAVE_FOC_PROJECT/Startup/startup_XMC1300.o \
	DAVE_FOC_PROJECT/Startup/system_XMC1300.o \
	syscalls.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc_vadc.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc1_scu.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc_posif.o \
	DAVE_FOC_PROJECT/Dave/Generated/DAVE.o \
	DAVE_FOC_PROJECT/Dave/Generated/PWM/pwm_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/PWM/pwm.o \
	DAVE_FOC_PROJECT/Dave/Generated/ADC_QUEUE/adc_queue_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/ADC_QUEUE/adc_queue.o \
	DAVE_FOC_PROJECT/Dave/Generated/CLOCK_XMC1/clock_xmc1_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/CLOCK_XMC1/clock_xmc1.o \
	DAVE_FOC_PROJECT/Dave/Generated/CPU_CTRL_XMC1/cpu_ctrl_xmc1_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/CPU_CTRL_XMC1/cpu_ctrl_xmc1.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_ADC/global_adc_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_ADC/global_adc.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_CCU4/global_ccu4_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_CCU4/global_ccu4.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_CCU8/global_ccu8_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_CCU8/global_ccu8.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_POSIF/global_posif_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/GLOBAL_POSIF/global_posif.o \
	DAVE_FOC_PROJECT/Dave/Generated/HALL_POSIF/hall_posif_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/HALL_POSIF/hall_posif.o \
	DAVE_FOC_PROJECT/Dave/Generated/PMSM_FOC/pmsm_foc_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/PMSM_FOC/pmsm_foc.o \
	DAVE_FOC_PROJECT/Dave/Generated/PMSM_FOC/pmsm_foc_control.o \
	DAVE_FOC_PROJECT/Dave/Generated/PWM_SVM/pwm_svm_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/PWM_SVM/pwm_svm.o \
	DAVE_FOC_PROJECT/Dave/Generated/PWM_SVM/pwm_svm_table.o \
	DAVE_FOC_PROJECT/Dave/Generated/UART/uart_conf.o \
	DAVE_FOC_PROJECT/Dave/Generated/UART/uart.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc_ccu4.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc_ccu8.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc_gpio.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc1_gpio.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc_uart.o \
	DAVE_FOC_PROJECT/Libraries/XMCLib/src/xmc_usic.o \
	DAVE_FOC_PROJECT/main.o \