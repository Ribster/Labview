################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include stm32haldev/system/src/newlib/subdir.mk
-include stm32haldev/system/src/diag/subdir.mk
-include stm32haldev/system/src/cortexm/subdir.mk
-include stm32haldev/system/STM32F4xx_HAL_Driver/Src/subdir.mk
-include stm32haldev/system/CMSIS/Device/ST/STM32F4xx/Source/system/subdir.mk
-include stm32haldev/system/CMSIS/Device/ST/STM32F4xx/Source/stm32f429/subdir.mk
-include stm32haldev/stm32dev/src/stm32f4/subdir.mk
-include stm32haldev/stm32dev/src/general/subdir.mk
-include stm32haldev/stm32dev/boards/subdir.mk
-include src/usbcore/subdir.mk
-include src/cdc/subdir.mk
-include src/subdir.mk
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
ESHF4-0007-F429-Filtertester_REV_C.hex \

SECONDARY_SIZE += \
ESHF4-0007-F429-Filtertester_REV_C.siz \


# All Target
all: ESHF4-0007-F429-Filtertester_REV_C.elf secondary-outputs

# Tool invocations
ESHF4-0007-F429-Filtertester_REV_C.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall  -g -T mem.ld -T libs.ld -T sections.ld -nostartfiles -Xlinker --gc-sections -L"/Users/Robbe/GITHUB/ECLIPSE/STM32_HAL/ESHXX000-stm32haldev/ldscripts/stm32f429ZI" -Wl,-Map,"ESHF4-0007-F429-Filtertester_REV_C.map" --specs=nano.specs -o "ESHF4-0007-F429-Filtertester_REV_C.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ESHF4-0007-F429-Filtertester_REV_C.hex: ESHF4-0007-F429-Filtertester_REV_C.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "ESHF4-0007-F429-Filtertester_REV_C.elf"  "ESHF4-0007-F429-Filtertester_REV_C.hex"
	@echo 'Finished building: $@'
	@echo ' '

ESHF4-0007-F429-Filtertester_REV_C.siz: ESHF4-0007-F429-Filtertester_REV_C.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "ESHF4-0007-F429-Filtertester_REV_C.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(CPP_DEPS) ESHF4-0007-F429-Filtertester_REV_C.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
