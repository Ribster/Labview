################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32dev/src/stm32f4/stm32dev_dma_f4.c \
../stm32dev/src/stm32f4/stm32dev_exti_f4.c \
../stm32dev/src/stm32f4/stm32dev_gpio_f4.c \
../stm32dev/src/stm32f4/stm32dev_nvic_f4.c \
../stm32dev/src/stm32f4/stm32dev_pwr_f4.c \
../stm32dev/src/stm32f4/stm32dev_rcc_f4.c \
../stm32dev/src/stm32f4/stm32dev_rtc_f4.c \
../stm32dev/src/stm32f4/stm32dev_spi_f4.c \
../stm32dev/src/stm32f4/stm32dev_tim_f4.c \
../stm32dev/src/stm32f4/stm32dev_usart_f4.c 

OBJS += \
./stm32dev/src/stm32f4/stm32dev_dma_f4.o \
./stm32dev/src/stm32f4/stm32dev_exti_f4.o \
./stm32dev/src/stm32f4/stm32dev_gpio_f4.o \
./stm32dev/src/stm32f4/stm32dev_nvic_f4.o \
./stm32dev/src/stm32f4/stm32dev_pwr_f4.o \
./stm32dev/src/stm32f4/stm32dev_rcc_f4.o \
./stm32dev/src/stm32f4/stm32dev_rtc_f4.o \
./stm32dev/src/stm32f4/stm32dev_spi_f4.o \
./stm32dev/src/stm32f4/stm32dev_tim_f4.o \
./stm32dev/src/stm32f4/stm32dev_usart_f4.o 

C_DEPS += \
./stm32dev/src/stm32f4/stm32dev_dma_f4.d \
./stm32dev/src/stm32f4/stm32dev_exti_f4.d \
./stm32dev/src/stm32f4/stm32dev_gpio_f4.d \
./stm32dev/src/stm32f4/stm32dev_nvic_f4.d \
./stm32dev/src/stm32f4/stm32dev_pwr_f4.d \
./stm32dev/src/stm32f4/stm32dev_rcc_f4.d \
./stm32dev/src/stm32f4/stm32dev_rtc_f4.d \
./stm32dev/src/stm32f4/stm32dev_spi_f4.d \
./stm32dev/src/stm32f4/stm32dev_tim_f4.d \
./stm32dev/src/stm32f4/stm32dev_usart_f4.d 


# Each subdirectory must supply rules for building sources it contributes
stm32dev/src/stm32f4/%.o: ../stm32dev/src/stm32f4/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -DUSE_HAL_LIBRARY -DSTM32F407xx -DDEBUG -Dstm32dev_alt0068_A -I../include -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/system/include" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/system/STM32F4xx_HAL_Driver/Inc" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/system/CMSIS/Include" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/system/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/stm32dev/boards" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/stm32dev/include/general" -I"/Users/Robbe/GITHUB/ECLIPSE-STM32/ECLIPSE_OSX_HAL/ESHXX000-stm32haldev/stm32dev/include/stm32f4" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


