/*
 * stm32dev_usart_f4.h
 *
 *  Created on: 18-okt.-2015
 *      Author: Robbe
 */

#ifndef STM32DEV_INCLUDE_STM32F4_STM32DEV_USART_F4_H_
#define STM32DEV_INCLUDE_STM32F4_STM32DEV_USART_F4_H_

#include <stdbool.h>

#include "stm32dev_boards.h"

#include "stm32dev_gpio_f4.h"
#include "stm32dev_rcc_f4.h"
#include "stm32dev_dma_f4.h"
#include "stm32dev_nvic_f4.h"

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
	#include "stm32f4xx_hal_usart.h"
#endif

typedef enum stm32dev_usart_Stopbits_list{
	stm32dev_usart_Stopbits_0_5	= 1,
	stm32dev_usart_Stopbits_1	= 0,
	stm32dev_usart_Stopbits_1_5	= 3,
	stm32dev_usart_Stopbits_2	= 2
}stm32dev_usart_Stopbits_list;

/*	UART REGISTERS	*/
	//	USART_SR - Status register
	//	USART_DR - Data register
	//	USART_BRR - Baud rate register
	//	USART_CR1 - Control register 1
	//	USART_CR2 - Control register 2
	//	USART_CR3 - Control register 3
	//	USART_GTPR - Guard time and prescaler register

void stm32dev_usart_initRX(USART_TypeDef* ua, GPIO_TypeDef* bank, uint8_t pin);
void stm32dev_usart_initTX(USART_TypeDef* ua, GPIO_TypeDef* bank, uint8_t pin);
void stm32dev_usart_initPolling8bNoPar1StopNoHardwcontrOversamp16(USART_TypeDef* ua, uint32_t baudrate);

bool stm32dev_usart_status_getCTS(USART_TypeDef* ua);
bool stm32dev_usart_status_getLINBreakDetection(USART_TypeDef* ua);
bool stm32dev_usart_status_getTXEmpty(USART_TypeDef* ua);
bool stm32dev_usart_status_getTComplete(USART_TypeDef* ua);
bool stm32dev_usart_status_getRXNotEmpty(USART_TypeDef* ua);
bool stm32dev_usart_status_getIDLE(USART_TypeDef* ua);
bool stm32dev_usart_status_getOverrunError(USART_TypeDef* ua);
bool stm32dev_usart_status_getNoiseDetected(USART_TypeDef* ua);
bool stm32dev_usart_status_getFramingError(USART_TypeDef* ua);
bool stm32dev_usart_status_getParityError(USART_TypeDef* ua);
uint16_t stm32dev_usart_getData(USART_TypeDef* ua);
uint16_t stm32dev_usart_getBaudrateMantissa(USART_TypeDef* ua);
uint8_t stm32dev_usart_getBaudrateFraction(USART_TypeDef* ua);
bool stm32dev_usart_control_getOversampling8(USART_TypeDef* ua);
bool stm32dev_usart_control_getUSARTEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getWordLength9(USART_TypeDef* ua);
bool stm32dev_usart_control_getWAKE(USART_TypeDef* ua);
bool stm32dev_usart_control_getParitycontrolEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getParityOdd(USART_TypeDef* ua);
bool stm32dev_usart_control_getParityInterruptEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getTXEInterruptEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getTCompleteInterruptEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getRXNotEmptyInterruptEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getIDLEInterruptEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getTransmitterEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getReceiverEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getReceiverMutemode(USART_TypeDef* ua);
bool stm32dev_usart_control_getBreaktransmitEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getLINModeEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getClockEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getClockPolarityHigh(USART_TypeDef* ua);
bool stm32dev_usart_control_getClockPhaseSecond(USART_TypeDef* ua);
bool stm32dev_usart_control_getLastbitclockpulsEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getLINbreakdetectionInterruptEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getLINbreakdetectionLength11(USART_TypeDef* ua);
stm32dev_usart_Stopbits_list stm32dev_usart_control_getSTOP(USART_TypeDef* ua);
uint8_t stm32dev_usart_control_getAddress(USART_TypeDef* ua);
bool stm32dev_usart_control_getOnesamplebitmethodEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getCTSInterruptEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getCTSEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getRTSEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getDMAEnableTransmitter(USART_TypeDef* ua);
bool stm32dev_usart_control_getDMAEnableReceiver(USART_TypeDef* ua);
bool stm32dev_usart_control_getSmartcardModeEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getSmartcardNACKEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getHalfduplexSelected(USART_TypeDef* ua);
bool stm32dev_usart_control_getIRDALowpowerEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getIRDAModeEnable(USART_TypeDef* ua);
bool stm32dev_usart_control_getErrorInterruptEnable(USART_TypeDef* ua);
uint8_t stm32dev_usart_control_getGuardtime(USART_TypeDef* ua);
uint8_t stm32dev_usart_control_getPrescaler(USART_TypeDef* ua);

void stm32dev_usart_setData(USART_TypeDef* ua, uint16_t data);
void stm32dev_usart_setBaudrateMantissa(USART_TypeDef* ua, uint16_t newVal);
void stm32dev_usart_setBaudrateFraction(USART_TypeDef* ua, uint8_t newVal);
void stm32dev_usart_control_setOversampling8(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setUSARTEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setWordLength9(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setWAKE(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setParitycontrolEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setParityOdd(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setParityInterruptEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setTXEInterruptEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setTCompleteInterruptEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setRXNotEmptyInterruptEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setIDLEInterruptEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setTransmitterEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setReceiverEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setReceiverMutemode(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setBreaktransmitEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setLINModeEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setClockEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setClockPolarityHigh(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setClockPhaseSecond(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setLastbitclockpulsEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setLINbreakdetectionInterruptEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setLINbreakdetectionLength11(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setSTOP(USART_TypeDef* ua, stm32dev_usart_Stopbits_list newVal);
void stm32dev_usart_control_setAddress(USART_TypeDef* ua, uint8_t newVal);
void stm32dev_usart_control_setOnesamplebitmethodEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setCTSInterruptEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setCTSEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setRTSEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setDMAEnableTransmitter(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setDMAEnableReceiver(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setSmartcardModeEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setSmartcardNACKEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setHalfduplexSelected(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setIRDALowpowerEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setIRDAModeEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setErrorInterruptEnable(USART_TypeDef* ua, bool newVal);
void stm32dev_usart_control_setGuardtime(USART_TypeDef* ua, uint8_t newVal);
void stm32dev_usart_control_setPrescaler(USART_TypeDef* ua, uint8_t newVal);

#endif /* STM32DEV_INCLUDE_STM32F4_STM32DEV_USART_F4_H_ */
