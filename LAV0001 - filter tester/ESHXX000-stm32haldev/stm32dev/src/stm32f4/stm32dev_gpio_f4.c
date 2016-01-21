/*
 * stm32dev_gpio.c
 *
 *  Created on: 23-jul.-2015
 *      Author: Robbe Van Assche
 */
#include "stm32dev_gpio_f4.h"

// function declarations
void
stm32dev_gpio_setPinHolderGPIO(stm32dev_gpio_pinHolder_t* pinHolder, uint32_t pin, uint32_t mode, uint32_t pull, uint32_t speed, uint32_t alternate){
	pinHolder->config.Pin = pin;
	pinHolder->config.Mode = mode;
	pinHolder->config.Pull = pull;
	pinHolder->config.Speed = speed;
	pinHolder->config.Alternate = alternate;
}
void
stm32dev_gpio_setPinHolder(stm32dev_gpio_pinHolder_t* pinHolder, bool initState, IRQn_Type IRQn, GPIO_TypeDef* GPIOx){
	pinHolder->initState = initState;
	pinHolder->IRQn = IRQn;
	pinHolder->GPIOx = GPIOx;
	pinHolder->initialized = true;
}

void
stm32dev_gpio_initPinOutputPP(GPIO_TypeDef* pinBank, uint8_t pinPlace){

	// enable clock for this bank
	stm32dev_rcc_setClock(pinBank, true);

	// set pin mode
	stm32dev_gpio_setPinMode(pinBank, pinPlace, stm32dev_gpio_pinMode_Output_PP);

	// set pin pullup
	stm32dev_gpio_setPinPullup(pinBank, pinPlace, stm32dev_gpio_pinPullup_NoPull);

	// set pin speed
	stm32dev_gpio_setPinSpeed(pinBank, pinPlace, stm32dev_gpio_pinSpeed_High);

}
void
stm32dev_gpio_initPinOutputOD(GPIO_TypeDef* pinBank, uint8_t pinPlace){

	// enable clock for this bank
	stm32dev_rcc_setClock(pinBank, true);

	// set pin mode
	stm32dev_gpio_setPinMode(pinBank, pinPlace, stm32dev_gpio_pinMode_Output_OD);

	// set pin pullup
	stm32dev_gpio_setPinPullup(pinBank, pinPlace, stm32dev_gpio_pinPullup_NoPull);

	// set pin speed
	stm32dev_gpio_setPinSpeed(pinBank, pinPlace, stm32dev_gpio_pinSpeed_High);
}
void
stm32dev_gpio_initPinInput(GPIO_TypeDef* pinBank, uint8_t pinPlace){
	// enable clock for this bank
	stm32dev_rcc_setClock(pinBank, true);

	// set pin mode
	stm32dev_gpio_setPinMode(pinBank, pinPlace, stm32dev_gpio_pinMode_Input);

	// set pin pullup
	stm32dev_gpio_setPinPullup(pinBank, pinPlace, stm32dev_gpio_pinPullup_NoPull);

	// set pin speed
	stm32dev_gpio_setPinSpeed(pinBank, pinPlace, stm32dev_gpio_pinSpeed_High);
}
void
stm32dev_gpio_initPinAnalog(GPIO_TypeDef* pinBank, uint8_t pinPlace){
	// enable clock for this bank
	stm32dev_rcc_setClock(pinBank, true);

	// set pin mode
	stm32dev_gpio_setPinMode(pinBank, pinPlace, stm32dev_gpio_pinMode_Analog);

	// set pin pullup
	stm32dev_gpio_setPinPullup(pinBank, pinPlace, stm32dev_gpio_pinPullup_NoPull);

	// set pin speed
	stm32dev_gpio_setPinSpeed(pinBank, pinPlace, stm32dev_gpio_pinSpeed_High);
}

void
stm32dev_gpio_initPinAlternateOD(GPIO_TypeDef* pinBank, uint8_t pinPlace, uint8_t pinAlternate, stm32dev_gpio_pinPullup_list pinPull){
	// enable clock for this bank
	stm32dev_rcc_setClock(pinBank, true);

	// set pin mode
	stm32dev_gpio_setPinMode(pinBank, pinPlace, stm32dev_gpio_pinMode_AF_OD);

	// set pin pullup
	stm32dev_gpio_setPinPullup(pinBank, pinPlace, pinPull);

	// set pin speed
	stm32dev_gpio_setPinSpeed(pinBank, pinPlace, stm32dev_gpio_pinSpeed_High);

	// set pin alternate
	stm32dev_gpio_setPinAlternate(pinBank, pinPlace, pinAlternate);
}

void
stm32dev_gpio_initPinAlternatePP(GPIO_TypeDef* pinBank, uint8_t pinPlace, uint8_t pinAlternate, stm32dev_gpio_pinPullup_list pinPull){
	// enable clock for this bank
	stm32dev_rcc_setClock(pinBank, true);

	// set pin mode
	stm32dev_gpio_setPinMode(pinBank, pinPlace, stm32dev_gpio_pinMode_AF_PP);

	// set pin pullup
	stm32dev_gpio_setPinPullup(pinBank, pinPlace, pinPull);

	// set pin speed
	stm32dev_gpio_setPinSpeed(pinBank, pinPlace, stm32dev_gpio_pinSpeed_High);

	// set pin alternate
	stm32dev_gpio_setPinAlternate(pinBank, pinPlace, pinAlternate);
}

void
stm32dev_gpio_deinitPin(GPIO_TypeDef* pinBank, uint8_t pinPlace){
	// set pin mode
	stm32dev_gpio_clearPinMode(pinBank, pinPlace);

	// set pin pullup
	stm32dev_gpio_clearPinPullup(pinBank, pinPlace);

	// set pin speed
	stm32dev_gpio_clearPinSpeed(pinBank, pinPlace);

	// set pin AF
	stm32dev_gpio_clearPinAlternate(pinBank, pinPlace);
}

void
stm32dev_gpio_setPinMode(GPIO_TypeDef* pinBank, uint8_t pinPlace, stm32dev_gpio_pinMode_list pinMode){
	// clear MODER && OTYPER
	pinBank->OTYPER &= ~( (0x01 << (pinPlace)) );
	pinBank->MODER &= ~( (0x03 << (pinPlace << 1)) );

	// MODER
		//	00	input
		//	01	general purpose output mode
		//	10	alternate function mode
		//	11	analog mode

	// OTYPER
		//	0	output push-pull (reset state)
		//	1	output open-drain

	switch(pinMode){
		case stm32dev_gpio_pinMode_Input:
			pinBank->MODER |= ( 0x00 << (pinPlace << 1) );
			break;
		case stm32dev_gpio_pinMode_Output_PP:
			pinBank->MODER |= ( 0x01 << (pinPlace << 1) );
			break;
		case stm32dev_gpio_pinMode_Output_OD:
			pinBank->MODER |= ( 0x01 << (pinPlace << 1) );
			pinBank->OTYPER |= ( 0x01 << pinPlace );
			break;
		case stm32dev_gpio_pinMode_AF_PP:
			pinBank->MODER |= ( 0x02 << (pinPlace << 1) );
			break;
		case stm32dev_gpio_pinMode_AF_OD:
			pinBank->MODER |= ( 0x02 << (pinPlace << 1) );
			pinBank->OTYPER |= ( 0x01 << pinPlace );
			break;
		case stm32dev_gpio_pinMode_Analog:
			pinBank->MODER |= ( 0x03 << (pinPlace << 1) );
			break;
	}
}

void
stm32dev_gpio_setPinPullup(GPIO_TypeDef* pinBank, uint8_t pinPlace, stm32dev_gpio_pinPullup_list pinPull){
	// clear PUPDR
	pinBank->PUPDR &= ~( (0x03 << (pinPlace << 1)) );

	// PUPDR
		//	00	no pull
		//	01	pull up
		//	10	pull down
		//	11	reserved

	switch(pinPull){
		case stm32dev_gpio_pinPullup_Up:
			pinBank->PUPDR |= ( (pinPull << (pinPlace << 1)) );
			break;
		case stm32dev_gpio_pinPullup_Down:
			pinBank->PUPDR |= ( (pinPull << (pinPlace << 1)) );
			break;
		case stm32dev_gpio_pinPullup_NoPull:
			pinBank->PUPDR |= ( (pinPull << (pinPlace << 1)) );
			break;
	}
}

void
stm32dev_gpio_setPinSpeed(GPIO_TypeDef* pinBank, uint8_t pinPlace, stm32dev_gpio_pinSpeed_list pinSpeed){
	// clear OSPEEDR
	pinBank->OSPEEDR &= ~( (0x03 << (pinPlace << 1)) );

	// OSPEEDR
		// 00	Low
		// 01	Medium
		// 10	Fast
		// 11	High

	pinBank->OSPEEDR |= ( (pinSpeed << (pinPlace << 1)) );
}
void
stm32dev_gpio_setPinAlternate(GPIO_TypeDef* pinBank, uint8_t pinPlace, uint8_t pinAlternate){

	// AFR
		// AFR[0] -> 0-7
		// AFR[1] -> 8-15

		// AF0 - AF15
		// 0000 - 1111

	if(pinPlace<8){
		// bank 0
		pinBank->AFR[0] &= ~ ( (0x0F << (pinPlace << 2)) );
		pinBank->AFR[0] |= ( ( (pinAlternate & 0x0F) << (pinPlace << 2)) );
	} else {
		// bank 1
		pinBank->AFR[1] &= ~ ( (0x0F << ( (pinPlace-8) << 2)) );
		pinBank->AFR[1] |= ( ( (pinAlternate & 0x0F) << ( (pinPlace-8) << 2)) );
	}
}

void
stm32dev_gpio_clearPinMode(GPIO_TypeDef* pinBank, uint8_t pinPlace){
	// clear MODER && OTYPER
	pinBank->OTYPER &= ~( (0x01 << (pinPlace)) );
	pinBank->MODER &= ~( (0x03 << (pinPlace << 1)) );
}
void
stm32dev_gpio_clearPinPullup(GPIO_TypeDef* pinBank, uint8_t pinPlace){
	// clear PUPDR
	pinBank->PUPDR &= ~( (0x03 << (pinPlace << 1)) );
}
void
stm32dev_gpio_clearPinSpeed(GPIO_TypeDef* pinBank, uint8_t pinPlace){
	// clear OSPEEDR
	pinBank->OSPEEDR &= ~( (0x03 << (pinPlace << 1)) );
}
void
stm32dev_gpio_clearPinAlternate(GPIO_TypeDef* pinBank, uint8_t pinPlace){
	// AFR
		// AFR[0] -> 0-7
		// AFR[1] -> 8-15

		// AF0 - AF15
		// 0000 - 1111

	if(pinPlace<8){
		// bank 0
		pinBank->AFR[0] &= ~ ( (0x0F << (pinPlace << 2)) );
	} else {
		// bank 1
		pinBank->AFR[1] &= ~ ( (0x0F << ( (pinPlace-8) << 2)) );
	}
}

uint8_t stm32dev_gpio_getAFUSART(USART_TypeDef* ua){
	if(ua == USART1) return 7;
	if(ua == USART2) return 7;
	if(ua == USART3) return 7;

	if(ua == UART4) return 8;
	if(ua == UART5) return 8;
	if(ua == USART6) return 8;

	return 0;
}

bool
stm32dev_gpio_getPinState(GPIO_TypeDef* pinBank, uint8_t pinPlace){
	bool returnVal = false;
	if(pinBank->IDR & (1<<pinPlace)){
		returnVal = true;
	}
	return returnVal;
}
void
stm32dev_gpio_setPinState(GPIO_TypeDef* pinBank, uint8_t pinPlace, bool newState){
	if(newState){
		pinBank->ODR |= (1<<pinPlace);
	} else {
		pinBank->ODR &= ~(1<<pinPlace);
	}
}
