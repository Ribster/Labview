/*
 * stm32devboard.h
 *
 *  Created on: 25-jul.-2015
 *      Author: Robbe
 */

#ifndef STM32DEV_BOARDS_STM32DEVBOARD_H_
#define STM32DEV_BOARDS_STM32DEVBOARD_H_

/*	Board specific files													*/
#if defined(stm32dev_alt0064_A)
	#include "alt0064_A.h"
#elif defined(stm32dev_alt0065_A)
	#include "alt0065_A.h"
#elif defined(stm32dev_alt0068_A)
	#include "alt0068_A.h"
#elif defined(stm32dev_f429disco)
	#include "f429disco.h"
#endif

/*	Device library															*/
#include "stm32dev_devicelib.h"

/*	Custom driver files														*/
#include "stm32dev_general.h"


#if defined(stm32dev_F0)
#include "stm32dev_gpio_f0.h"
#include "stm32dev_rcc_f0.h"
#include "stm32dev_dma_f0.h"
#include "stm32dev_spi_f0.h"

#elif defined(stm32dev_F1)


#elif defined(stm32dev_F2)


#elif defined(stm32dev_F3)


#elif defined(stm32dev_F4)
#include "stm32dev_gpio_f4.h"
#include "stm32dev_rcc_f4.h"
#include "stm32dev_dma_f4.h"
#include "stm32dev_rtc_f4.h"
#include "stm32dev_spi_f4.h"
#include "stm32dev_usart_f4.h"
#include "stm32dev_exti_f4.h"
#include "stm32dev_nvic_f4.h"
#include "stm32dev_pwr_f4.h"
#include "stm32dev_tim_f4.h"

#elif defined(stm32dev_F7)


#elif defined(stm32dev_L0)


#elif defined(stm32dev_L1)


#endif



#endif /* STM32DEV_BOARDS_STM32DEVBOARD_H_ */
