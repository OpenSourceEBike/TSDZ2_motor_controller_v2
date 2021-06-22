################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MidSys/bldc_scalar_current_motor.c \
../MidSys/bldc_scalar_pwm_bc.c \
../MidSys/bldc_scalar_speed_pos_hall.c \
../MidSys/bldc_scalar_volt_dcbus.c \
../MidSys/bldc_scalar_volt_potentiometer.c \
../MidSys/bldc_scalar_volt_userdef.c 

OBJS += \
./MidSys/bldc_scalar_current_motor.o \
./MidSys/bldc_scalar_pwm_bc.o \
./MidSys/bldc_scalar_speed_pos_hall.o \
./MidSys/bldc_scalar_volt_dcbus.o \
./MidSys/bldc_scalar_volt_potentiometer.o \
./MidSys/bldc_scalar_volt_userdef.o 

C_DEPS += \
./MidSys/bldc_scalar_current_motor.d \
./MidSys/bldc_scalar_pwm_bc.d \
./MidSys/bldc_scalar_speed_pos_hall.d \
./MidSys/bldc_scalar_volt_dcbus.d \
./MidSys/bldc_scalar_volt_potentiometer.d \
./MidSys/bldc_scalar_volt_userdef.d 


# Each subdirectory must supply rules for building sources it contributes
MidSys/%.o: ../MidSys/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC1302_T038x0200 -DXMC_MATH_DISABLE_DIV_ABI -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC1300_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Libraries" -O3 -ffunction-sections -fdata-sections -Wall -std=gnu99 -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m0 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

