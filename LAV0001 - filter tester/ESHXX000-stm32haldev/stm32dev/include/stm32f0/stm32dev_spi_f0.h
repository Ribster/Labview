/*
 * stm32dev_spi_f4.h
 *
 *  Created on: 18-okt.-2015
 *      Author: Robbe
 */

#ifndef STM32DEV_INCLUDE_STM32F4_STM32DEV_SPI_F4_H_
#define STM32DEV_INCLUDE_STM32F4_STM32DEV_SPI_F4_H_

#include <stdbool.h>

#include "stm32dev_boards.h"

#include "stm32dev_gpio_f0.h"
#include "stm32dev_rcc_f0.h"

/**
 * Check which device we are working on
 */
#if !defined(stm32dev_F0) && !defined(stm32dev_F1) && !defined(stm32dev_F2) && !defined(stm32dev_F3) && !defined(stm32dev_F4) && !defined(stm32dev_F7) && !defined(stm32dev_L0) && !defined(stm32dev_L1)
#include "stm32dev_devicelib.h"


#endif

/**
 * include the STM32F4 HAL libraries
 */
#if defined(stm32dev_F0)
	#include "stm32f0xx_hal_spi.h"
	#include "stm32f0xx_hal_spi_ex.h"
#endif



#endif /* STM32DEV_INCLUDE_STM32F4_STM32DEV_SPI_F4_H_ */
