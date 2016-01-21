################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32dev/src/stm32f0/stm32dev_dma_f0.c \
../stm32dev/src/stm32f0/stm32dev_gpio_f0.c \
../stm32dev/src/stm32f0/stm32dev_rcc_f0.c \
../stm32dev/src/stm32f0/stm32dev_spi_f0.c 

OBJS += \
./stm32dev/src/stm32f0/stm32dev_dma_f0.o \
./stm32dev/src/stm32f0/stm32dev_gpio_f0.o \
./stm32dev/src/stm32f0/stm32dev_rcc_f0.o \
./stm32dev/src/stm32f0/stm32dev_spi_f0.o 

C_DEPS += \
./stm32dev/src/stm32f0/stm32dev_dma_f0.d \
./stm32dev/src/stm32f0/stm32dev_gpio_f0.d \
./stm32dev/src/stm32f0/stm32dev_rcc_f0.d \
./stm32dev/src/stm32f0/stm32dev_spi_f0.d 


# Each subdirectory must supply rules for building sources it contributes
stm32dev/src/stm32f0/%.o: ../stm32dev/src/stm32f0/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall  -g -DUSE_HAL_LIBRARY -DDEBUG -DSTM32F051x8 -Dstm32dev_alt0065_A -I../include -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/system/include" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/system/CMSIS/Include" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/system/STM32F0xx_HAL_Driver/Inc" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/system/CMSIS/Device/ST/STM32F0xx/Include" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/stm32dev/boards" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/stm32dev/include/general" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/stm32dev/include/stm32f0" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


