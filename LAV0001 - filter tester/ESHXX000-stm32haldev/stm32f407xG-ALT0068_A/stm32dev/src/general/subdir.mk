################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32dev/src/general/stm32dev_dds_AD9833.c \
../stm32dev/src/general/stm32dev_dds_AD9834.c \
../stm32dev/src/general/stm32dev_dds_AD9850.c \
../stm32dev/src/general/stm32dev_dds_AD9851.c \
../stm32dev/src/general/stm32dev_general.c \
../stm32dev/src/general/stm32dev_screen_ssd1306.c 

OBJS += \
./stm32dev/src/general/stm32dev_dds_AD9833.o \
./stm32dev/src/general/stm32dev_dds_AD9834.o \
./stm32dev/src/general/stm32dev_dds_AD9850.o \
./stm32dev/src/general/stm32dev_dds_AD9851.o \
./stm32dev/src/general/stm32dev_general.o \
./stm32dev/src/general/stm32dev_screen_ssd1306.o 

C_DEPS += \
./stm32dev/src/general/stm32dev_dds_AD9833.d \
./stm32dev/src/general/stm32dev_dds_AD9834.d \
./stm32dev/src/general/stm32dev_dds_AD9850.d \
./stm32dev/src/general/stm32dev_dds_AD9851.d \
./stm32dev/src/general/stm32dev_general.d \
./stm32dev/src/general/stm32dev_screen_ssd1306.d 


# Each subdirectory must supply rules for building sources it contributes
stm32dev/src/general/%.o: ../stm32dev/src/general/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DUSE_HAL_LIBRARY -DSTM32F407xx -DDEBUG -Dstm32dev_alt0068_A -I../include -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/system/include" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/system/STM32F4xx_HAL_Driver/Inc" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/system/CMSIS/Include" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/system/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/stm32dev/boards" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/stm32dev/include/general" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/stm32dev/include/stm32f4" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

