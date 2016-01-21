/*
 * stm32dev_gpio.h
 *
 *  Created on: 23-jul.-2015
 *      Author: Robbe
 */

#ifndef STM32DEV_INCLUDE_STM32DEV_GPIO_H_
#define STM32DEV_INCLUDE_STM32DEV_GPIO_H_

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
#if defined(stm32dev_F0)
	#include "stm32f0xx_hal_gpio.h"
	#include "stm32f0xx_hal_uart.h"
	#include "stm32f0xx_hal_usart.h"
#endif

#if defined(stm32dev_F0)
	#include "stm32dev_rcc_f0.h"
#endif



// macro's

// structures
typedef struct stm32dev_gpio_pinHolder_t{
	bool initialized;
	bool initState;
	IRQn_Type IRQn;
	GPIO_TypeDef* GPIOx;
	GPIO_InitTypeDef config;
}stm32dev_gpio_pinHolder_t;

typedef enum stm32dev_gpio_pinMode_list{
	stm32dev_gpio_pinMode_Input 	= 0x00,
	stm32dev_gpio_pinMode_Output_PP = 0x01,
	stm32dev_gpio_pinMode_Output_OD = 0x11,
	stm32dev_gpio_pinMode_AF_PP		= 0x02,
	stm32dev_gpio_pinMode_AF_OD		= 0x12,
	stm32dev_gpio_pinMode_Analog	= 0x03
}stm32dev_gpio_pinMode_list;

typedef enum stm32dev_gpio_pinPullup_list{
	stm32dev_gpio_pinPullup_Up		= 0x01,
	stm32dev_gpio_pinPullup_Down	= 0x02,
	stm32dev_gpio_pinPullup_NoPull	= 0x00
}stm32dev_gpio_pinPullup_list;

typedef enum stm32dev_gpio_pinSpeed_list{
	stm32dev_gpio_pinSpeed_Low			= 0x00,
	stm32dev_gpio_pinSpeed_Medium		= 0x01,
	stm32dev_gpio_pinSpeed_Fast			= 0x02,
	stm32dev_gpio_pinSpeed_High			= 0x03
}stm32dev_gpio_pinSpeed_list;

// function prototypes
void stm32dev_gpio_setPinHolderGPIO(stm32dev_gpio_pinHolder_t* pinHolder, uint32_t pin, uint32_t mode, uint32_t pull, uint32_t speed, uint32_t alternate);
void stm32dev_gpio_setPinHolder(stm32dev_gpio_pinHolder_t* pinHolder, bool initState, IRQn_Type IRQn, GPIO_TypeDef* GPIOx);

/* INITIALIZING FUNCTIONS
 *
 */
void stm32dev_gpio_initPinOutputPP(GPIO_TypeDef* pinBank, uint8_t pinPlace);
void stm32dev_gpio_initPinOutputOD(GPIO_TypeDef* pinBank, uint8_t pinPlace);
void stm32dev_gpio_initPinInput(GPIO_TypeDef* pinBank, uint8_t pinPlace);
void stm32dev_gpio_initPinAnalog(GPIO_TypeDef* pinBank, uint8_t pinPlace);
void stm32dev_gpio_initPinAlternateOD(GPIO_TypeDef* pinBank, uint8_t pinPlace, uint8_t pinAlternate, stm32dev_gpio_pinPullup_list pinPull);
void stm32dev_gpio_initPinAlternatePP(GPIO_TypeDef* pinBank, uint8_t pinPlace, uint8_t pinAlternate, stm32dev_gpio_pinPullup_list pinPull);
void stm32dev_gpio_deinitPin(GPIO_TypeDef* pinBank, uint8_t pinPlace);

void stm32dev_gpio_setPinMode(GPIO_TypeDef* pinBank, uint8_t pinPlace, stm32dev_gpio_pinMode_list pinMode);
void stm32dev_gpio_setPinPullup(GPIO_TypeDef* pinBank, uint8_t pinPlace, stm32dev_gpio_pinPullup_list pinPull);
void stm32dev_gpio_setPinSpeed(GPIO_TypeDef* pinBank, uint8_t pinPlace, stm32dev_gpio_pinSpeed_list pinSpeed);
void stm32dev_gpio_setPinAlternate(GPIO_TypeDef* pinBank, uint8_t pinPlace, uint8_t pinAlternate);

void stm32dev_gpio_clearPinMode(GPIO_TypeDef* pinBank, uint8_t pinPlace);
void stm32dev_gpio_clearPinPullup(GPIO_TypeDef* pinBank, uint8_t pinPlace);
void stm32dev_gpio_clearPinSpeed(GPIO_TypeDef* pinBank, uint8_t pinPlace);
void stm32dev_gpio_clearPinAlternate(GPIO_TypeDef* pinBank, uint8_t pinPlace);
void stm32dev_gpio_clearPinAlternate(GPIO_TypeDef* pinBank, uint8_t pinPlace);

uint8_t stm32dev_gpio_getAFUSART(USART_TypeDef* ua);


/* PIN ACCESS FUNCTIONS
 *
 */
bool
stm32dev_gpio_getPinState(GPIO_TypeDef* pinBank, uint8_t pinPlace);
void
stm32dev_gpio_setPinState(GPIO_TypeDef* pinBank, uint8_t pinPlace, bool newState);

#endif /* STM32DEV_INCLUDE_STM32DEV_GPIO_H_ */
