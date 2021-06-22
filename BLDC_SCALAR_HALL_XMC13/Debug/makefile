################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include uCProbe/ProbeScope/subdir.mk
-include uCProbe/subdir.mk
-include Startup/subdir.mk
-include MidSys/subdir.mk
-include MCUInit/subdir.mk
-include Libraries/XMCLib/src/subdir.mk
-include Libraries/Newlib/subdir.mk
-include Interrupts/subdir.mk
-include ControlModule/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
BLDC_SCALAR_HALL_XMC13_uCProbe.hex \

SECONDARY_LIST += \
BLDC_SCALAR_HALL_XMC13_uCProbe.lst \

SECONDARY_SIZE += \
BLDC_SCALAR_HALL_XMC13_uCProbe.siz \


LIST_FILES = $(addsuffix .o.lst, $(basename $(OBJS))) 
MAP_FILE = "BLDC_SCALAR_HALL_XMC13_uCProbe.map"

TOOLCHAIN_ROOT=C:/Users/Jorge Pinto/Documents/DAVE-IDE-4.4.2-64Bit/eclipse/ARM-GCC-49
PROJECT_LOC=Z:/HOME_CAS/work/TSDZ2/controller_v2/Infineon-BLDC_Motor_Control_3-Hall_Sensor_Example_with_uC_Probe_for_XMC1300_series-SW-v01_00-EN/BLDC_SCALAR_HALL_XMC13_uCProbe

# All Target
all: BLDC_SCALAR_HALL_XMC13_uCProbe.elf secondary-outputs

# Tool invocations
BLDC_SCALAR_HALL_XMC13_uCProbe.elf: $(OBJS) ../linker_script.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	$(file >objects.rsp,$(OBJS))
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -T"../linker_script.ld" -nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs -Wl,-Map,$(MAP_FILE) -mcpu=cortex-m0 -mthumb -g -gdwarf-2 -o "BLDC_SCALAR_HALL_XMC13_uCProbe.elf" "@objects.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo.
BLDC_SCALAR_HALL_XMC13_uCProbe.hex: BLDC_SCALAR_HALL_XMC13_uCProbe.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objcopy" -O ihex "BLDC_SCALAR_HALL_XMC13_uCProbe.elf" "BLDC_SCALAR_HALL_XMC13_uCProbe.hex"
	@echo 'Finished building: $@'
	@echo.
BLDC_SCALAR_HALL_XMC13_uCProbe.lst: BLDC_SCALAR_HALL_XMC13_uCProbe.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objdump" -h -S "BLDC_SCALAR_HALL_XMC13_uCProbe.elf" > "BLDC_SCALAR_HALL_XMC13_uCProbe.lst"
	@echo 'Finished building: $@'
	@echo.
BLDC_SCALAR_HALL_XMC13_uCProbe.siz: BLDC_SCALAR_HALL_XMC13_uCProbe.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-size" --format=berkeley "BLDC_SCALAR_HALL_XMC13_uCProbe.elf"
	@echo 'Finished building: $@'
	@echo.
# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) BLDC_SCALAR_HALL_XMC13_uCProbe.elf $(LIST_FILES) $(MAP_FILE) objects.rsp
	-@echo.
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
