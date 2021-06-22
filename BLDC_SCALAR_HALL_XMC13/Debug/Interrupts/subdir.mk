################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Interrupts/bldc_scalar_control_loop.c \
../Interrupts/bldc_scalar_ctrap_periodmatch.c \
../Interrupts/bldc_scalar_hall_event.c \
../Interrupts/bldc_scalar_hall_state_machine.c \
../Interrupts/bldc_scalar_pattern_shadowtx.c \
../Interrupts/bldc_scalar_protection_error.c 

OBJS += \
./Interrupts/bldc_scalar_control_loop.o \
./Interrupts/bldc_scalar_ctrap_periodmatch.o \
./Interrupts/bldc_scalar_hall_event.o \
./Interrupts/bldc_scalar_hall_state_machine.o \
./Interrupts/bldc_scalar_pattern_shadowtx.o \
./Interrupts/bldc_scalar_protection_error.o 

C_DEPS += \
./Interrupts/bldc_scalar_control_loop.d \
./Interrupts/bldc_scalar_ctrap_periodmatch.d \
./Interrupts/bldc_scalar_hall_event.d \
./Interrupts/bldc_scalar_hall_state_machine.d \
./Interrupts/bldc_scalar_pattern_shadowtx.d \
./Interrupts/bldc_scalar_protection_error.d 


# Each subdirectory must supply rules for building sources it contributes
Interrupts/%.o: ../Interrupts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC1302_T038x0200 -DXMC_MATH_DISABLE_DIV_ABI -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC1300_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Libraries" -O3 -ffunction-sections -fdata-sections -Wall -std=gnu99 -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

