################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Libraries/XMCLib/src/subdir.mk
-include Libraries/Newlib/subdir.mk
-include Dave/Generated/UART/subdir.mk
-include Dave/Generated/PWM_SVM/subdir.mk
-include Dave/Generated/PMSM_FOC/subdir.mk
-include Dave/Generated/HALL_POSIF/subdir.mk
-include Dave/Generated/GLOBAL_POSIF/subdir.mk
-include Dave/Generated/GLOBAL_CCU8/subdir.mk
-include Dave/Generated/GLOBAL_CCU4/subdir.mk
-include Dave/Generated/GLOBAL_ADC/subdir.mk
-include Dave/Generated/CPU_CTRL_XMC1/subdir.mk
-include Dave/Generated/CLOCK_XMC1/subdir.mk
-include Dave/Generated/ADC_QUEUE/subdir.mk
-include Dave/Generated/subdir.mk
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
NEW.hex \

SECONDARY_LIST += \
NEW.lst \

SECONDARY_SIZE += \
NEW.siz \


LIST_FILES = $(addsuffix .o.lst, $(basename $(OBJS))) 
MAP_FILE = "NEW.map"

TOOLCHAIN_ROOT=C:/DAVE_4-4-2_64bit_2018-02-23/DAVE-IDE-4.4.2-64Bit/eclipse/ARM-GCC-49
PROJECT_LOC=C:/Workspaces/DAVE-4.4.2-64Bit/TSDZ2/NEW

# All Target
all: NEW.elf secondary-outputs

# Tool invocations
NEW.elf: $(OBJS) ../linker_script.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	$(file >objects.rsp,$(OBJS))
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -T"../linker_script.ld" -nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs -u _printf_float -u _scanf_float -L"C:\Workspaces\DAVE-4.4.2-64Bit\TSDZ2\NEW\Dave\Generated\PMSM_FOC" -Wl,-Map,$(MAP_FILE) -mcpu=cortex-m0 -mthumb -o "NEW.elf" "@objects.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo.
NEW.hex: NEW.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objcopy" -O ihex "NEW.elf" "NEW.hex"
	@echo 'Finished building: $@'
	@echo.
NEW.lst: NEW.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objdump" -h -S "NEW.elf" > "NEW.lst"
	@echo 'Finished building: $@'
	@echo.
NEW.siz: NEW.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-size" --format=berkeley "NEW.elf"
	@echo 'Finished building: $@'
	@echo.
# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) NEW.elf $(LIST_FILES) $(MAP_FILE) objects.rsp
	-@echo.
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
