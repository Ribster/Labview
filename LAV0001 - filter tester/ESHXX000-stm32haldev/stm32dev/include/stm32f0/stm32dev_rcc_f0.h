/*
 * stm32dev_rcc.h
 *
 *  Created on: 23-jul.-2015
 *      Author: Robbe
 */

#ifndef STM32DEV_INCLUDE_STM32DEV_RCC_H_
#define STM32DEV_INCLUDE_STM32DEV_RCC_H_

#include <stdbool.h>

#include "stm32dev_boards.h"


/**
 * Check which device we are working on
 */
#if !defined(stm32dev_F0) && !defined(stm32dev_F1) && !defined(stm32dev_F2) && !defined(stm32dev_F3) && !defined(stm32dev_F4) && !defined(stm32dev_F7) && !defined(stm32dev_L0) && !defined(stm32dev_L1)
#include "stm32dev_devicelib.h"


#endif

/**
 * include the STM32F4 HAL libraries
 */
#if defined(stm32dev_F4)
	#include "stm32f4xx_hal_rcc.h"
	#include "stm32f4xx_hal_rcc_ex.h"
#endif

#if defined(stm32dev_F0)
	#include "stm32f0xx_hal_rcc.h"
	//#include "stm32f0xx_hal_rcc_ex.h"
#endif

typedef enum stm32dev_rcc_RTCClock_list{
	stm32dev_rcc_RTCClock_noClock	= 0,
	stm32dev_rcc_RTCClock_LSE		= 1,
	stm32dev_rcc_RTCClock_LSI		= 2,
	stm32dev_rcc_RTCClock_HSE		= 3
}stm32dev_rcc_RTCClock_list;

void stm32dev_rcc_enableClock(GPIO_TypeDef* gpioBank);
void stm32dev_rcc_disableClock(GPIO_TypeDef* gpioBank);
void stm32dev_rcc_setClock(GPIO_TypeDef* gpioBank, bool newVal);
void stm32dev_rcc_setClockPWR(bool newVal);

void stm32dev_rcc_setRTCClockEnabled(bool newVal);
void stm32dev_rcc_setRTCClock(stm32dev_rcc_RTCClock_list newVal);
void stm32dev_rcc_setRTCLSEBypass(bool newVal);
void stm32dev_rcc_setRTCLSEEnabled(bool newVal);
void stm32dev_rcc_setRTCLSIEnabled(bool newVal);
void stm32dev_rcc_setBackupDomainReset(bool newVal);

bool stm32dev_rcc_getRTCClockEnabled(void);
stm32dev_rcc_RTCClock_list stm32dev_rcc_getRTCClock(void);
bool stm32dev_rcc_getRTCLSEBypassed(void);
bool stm32dev_rcc_getRTCLSEReady(void);
bool stm32dev_rcc_getRTCLSEEnabled(void);
bool stm32dev_rcc_getRTCLSIReady(void);
bool stm32dev_rcc_getRTCLSIEnabled(void);
bool stm32dev_rcc_getBackupDomainReset(void);
bool stm32dev_rcc_getClockPWR(void);

uint32_t stm32dev_rcc_getSystemClock(void);
uint32_t stm32dev_rcc_getPCLK1Clock(void);
uint32_t stm32dev_rcc_getPCLK2Clock(void);



#endif /* STM32DEV_INCLUDE_STM32DEV_RCC_H_ */
