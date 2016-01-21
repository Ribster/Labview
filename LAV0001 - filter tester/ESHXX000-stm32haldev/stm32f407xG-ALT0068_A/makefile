################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include stm32dev/src/stm32f4/subdir.mk
-include stm32dev/src/general/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
ESHXX000-stm32haldev.hex \

SECONDARY_SIZE += \
ESHXX000-stm32haldev.siz \


# All Target
all: ESHXX000-stm32haldev.elf secondary-outputs

dependents:
	-cd /Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/stm32f407xG-ALT0068_A && $(MAKE) all

# Tool invocations
ESHXX000-stm32haldev.elf: $(OBJS) $(USER_OBJS) /Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/stm32f407xG-ALT0068_A/ESHXX000-stm32haldev.elf
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -T mem.ld -T libs.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/ldscripts/stm32f407xG" -Wl,-Map,"ESHXX000-stm32haldev.map" --specs=nano.specs -o "ESHXX000-stm32haldev.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ESHXX000-stm32haldev.hex: ESHXX000-stm32haldev.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "ESHXX000-stm32haldev.elf"  "ESHXX000-stm32haldev.hex"
	@echo 'Finished building: $@'
	@echo ' '

ESHXX000-stm32haldev.siz: ESHXX000-stm32haldev.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "ESHXX000-stm32haldev.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(CPP_DEPS) ESHXX000-stm32haldev.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:
/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/stm32f407xG-ALT0068_A/ESHXX000-stm32haldev.elf:

-include ../makefile.targets
