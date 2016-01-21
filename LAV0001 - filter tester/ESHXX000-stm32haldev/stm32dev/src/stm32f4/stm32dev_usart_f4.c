/*
 * stm32dev_usart_f4.c
 *
 *  Created on: 18-okt.-2015
 *      Author: Robbe Van Assche
 */

#include "stm32dev_usart_f4.h"

// local pin settings
static GPIO_TypeDef* _bank_rx;
static uint8_t _pin_rx;
static bool _pin_rx_init = false;

static GPIO_TypeDef* _bank_tx;
static uint8_t _pin_tx;
static bool _pin_tx_init = false;

void stm32dev_usart_initRX(USART_TypeDef* ua, GPIO_TypeDef* bank, uint8_t pin){
	stm32dev_gpio_initPinAlternatePP(bank, pin, stm32dev_gpio_getAFUSART(ua), stm32dev_gpio_pinPullup_Up);
	_bank_rx = bank;
	_pin_rx = pin;
	_pin_rx_init = true;
}

void stm32dev_usart_initTX(USART_TypeDef* ua, GPIO_TypeDef* bank, uint8_t pin){
	stm32dev_gpio_initPinAlternatePP(bank, pin, stm32dev_gpio_getAFUSART(ua), stm32dev_gpio_pinPullup_Up);
	_bank_tx = bank;
	_pin_tx = pin;
	_pin_tx_init = true;
}

void stm32dev_usart_initPolling8bNoPar1StopNoHardwcontrOversamp16(USART_TypeDef* ua, uint32_t baudrate){
	if(_pin_rx_init == false) return;
	if(_pin_tx_init == false) return;

	// disable uart
	stm32dev_usart_control_setUSARTEnable(ua, false);

	// set uart parameters
	stm32dev_usart_control_setSTOP(ua, stm32dev_usart_Stopbits_1);
	stm32dev_usart_control_setWordLength9(ua, false);
	stm32dev_usart_control_setParitycontrolEnable(ua, false);
	stm32dev_usart_control_setTransmitterEnable(ua, true);
	stm32dev_usart_control_setReceiverEnable(ua, true);
	stm32dev_usart_control_setOversampling8(ua, false);
	stm32dev_usart_control_setParityOdd(ua, false);
	stm32dev_usart_control_setRTSEnable(ua, false);
	stm32dev_usart_control_setCTSEnable(ua, false);

	// asynchronous mode
	stm32dev_usart_control_setLINModeEnable(ua, false);
	stm32dev_usart_control_setClockEnable(ua, false);
	stm32dev_usart_control_setSmartcardModeEnable(ua, false);
	stm32dev_usart_control_setHalfduplexSelected(ua, false);
	stm32dev_usart_control_setIRDAModeEnable(ua, false);

	// enable peripheral
	stm32dev_usart_control_setUSARTEnable(ua, true);

}

bool stm32dev_usart_status_getCTS(USART_TypeDef* ua){
	// not available for UART4 & UART5
	return ( (ua->SR & (1<<9)) == (1<<9));
}
bool stm32dev_usart_status_getLINBreakDetection(USART_TypeDef* ua){
	return ( (ua->SR & (1<<8)) == (1<<8));
}
bool stm32dev_usart_status_getTXEmpty(USART_TypeDef* ua){
	return ( (ua->SR & (1<<7)) == (1<<7));
}
bool stm32dev_usart_status_getTComplete(USART_TypeDef* ua){
	return ( (ua->SR & (1<<6)) == (1<<6));
}
bool stm32dev_usart_status_getRXNotEmpty(USART_TypeDef* ua){
	return ( (ua->SR & (1<<5)) == (1<<5));
}
bool stm32dev_usart_status_getIDLE(USART_TypeDef* ua){
	return ( (ua->SR & (1<<4)) == (1<<4));
}
bool stm32dev_usart_status_getOverrunError(USART_TypeDef* ua){
	return ( (ua->SR & (1<<3)) == (1<<3));
}
bool stm32dev_usart_status_getNoiseDetected(USART_TypeDef* ua){
	return ( (ua->SR & (1<<2)) == (1<<2));
}
bool stm32dev_usart_status_getFramingError(USART_TypeDef* ua){
	return ( (ua->SR & (1<<1)) == (1<<1));
}
bool stm32dev_usart_status_getParityError(USART_TypeDef* ua){
	return ( (ua->SR & (1<<0)) == (1<<0));
}
uint16_t stm32dev_usart_getData(USART_TypeDef* ua){
	return (ua->DR & 0x1F);
}
uint16_t stm32dev_usart_getBaudrateMantissa(USART_TypeDef* ua){
	return ((ua->BRR >>4) & 0xFFF);
}
uint8_t stm32dev_usart_getBaudrateFraction(USART_TypeDef* ua){
	return ((ua->BRR >>0) & 0xF);
}
bool stm32dev_usart_control_getOversampling8(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<15)) == (1<<15));
}
bool stm32dev_usart_control_getUSARTEnable(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<13)) == (1<<13));
}
bool stm32dev_usart_control_getWordLength9(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<12)) == (1<<12));
}
bool stm32dev_usart_control_getWAKE(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<11)) == (1<<11));
}
bool stm32dev_usart_control_getParitycontrolEnable(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<10)) == (1<<10));
}
bool stm32dev_usart_control_getParityOdd(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<9)) == (1<<9));
}
bool stm32dev_usart_control_getParityInterruptEnable(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<8)) == (1<<8));
}
bool stm32dev_usart_control_getTXEInterruptEnable(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<7)) == (1<<7));
}
bool stm32dev_usart_control_getTCompleteInterruptEnable(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<6)) == (1<<6));
}
bool stm32dev_usart_control_getRXNotEmptyInterruptEnable(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<5)) == (1<<5));
}
bool stm32dev_usart_control_getIDLEInterruptEnable(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<4)) == (1<<4));
}
bool stm32dev_usart_control_getTransmitterEnable(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<3)) == (1<<3));
}
bool stm32dev_usart_control_getReceiverEnable(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<2)) == (1<<2));
}
bool stm32dev_usart_control_getReceiverMutemode(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<1)) == (1<<1));
}
bool stm32dev_usart_control_getBreaktransmitEnable(USART_TypeDef* ua){
	return ( (ua->CR1 & (1<<0)) == (1<<0));
}
bool stm32dev_usart_control_getLINModeEnable(USART_TypeDef* ua){
	return ( (ua->CR2 & (1<<14)) == (1<<14));
}
bool stm32dev_usart_control_getClockEnable(USART_TypeDef* ua){
	return ( (ua->CR2 & (1<<11)) == (1<<11));
}
bool stm32dev_usart_control_getClockPolarityHigh(USART_TypeDef* ua){
	return ( (ua->CR2 & (1<<10)) == (1<<10));
}
bool stm32dev_usart_control_getClockPhaseSecond(USART_TypeDef* ua){
	return ( (ua->CR2 & (1<<9)) == (1<<9));
}
bool stm32dev_usart_control_getLastbitclockpulsEnable(USART_TypeDef* ua){
	return ( (ua->CR2 & (1<<8)) == (1<<8));
}
bool stm32dev_usart_control_getLINbreakdetectionInterruptEnable(USART_TypeDef* ua){
	return ( (ua->CR2 & (1<<6)) == (1<<6));
}
bool stm32dev_usart_control_getLINbreakdetectionLength11(USART_TypeDef* ua){
	return ( (ua->CR2 & (1<<5)) == (1<<5));
}
stm32dev_usart_Stopbits_list stm32dev_usart_control_getSTOP(USART_TypeDef* ua){
	return ( (ua->CR2 >> 12) & 0x3);
}
uint8_t stm32dev_usart_control_getAddress(USART_TypeDef* ua){
	return ( (ua->CR2) & 0xF);
}
bool stm32dev_usart_control_getOnesamplebitmethodEnable(USART_TypeDef* ua){
	return ( (ua->CR3 & (1<<11)) == (1<<11));
}
bool stm32dev_usart_control_getCTSInterruptEnable(USART_TypeDef* ua){
	return ( (ua->CR3 & (1<<10)) == (1<<10));
}
bool stm32dev_usart_control_getCTSEnable(USART_TypeDef* ua){
	return ( (ua->CR3 & (1<<9)) == (1<<9));
}
bool stm32dev_usart_control_getRTSEnable(USART_TypeDef* ua){
	return ( (ua->CR3 & (1<<8)) == (1<<8));
}
bool stm32dev_usart_control_getDMAEnableTransmitter(USART_TypeDef* ua){
	return ( (ua->CR3 & (1<<7)) == (1<<7));
}
bool stm32dev_usart_control_getDMAEnableReceiver(USART_TypeDef* ua){
	return ( (ua->CR3 & (1<<6)) == (1<<6));
}
bool stm32dev_usart_control_getSmartcardModeEnable(USART_TypeDef* ua){
	return ( (ua->CR3 & (1<<5)) == (1<<5));
}
bool stm32dev_usart_control_getSmartcardNACKEnable(USART_TypeDef* ua){
	return ( (ua->CR3 & (1<<4)) == (1<<4));
}
bool stm32dev_usart_control_getHalfduplexSelected(USART_TypeDef* ua){
	return ( (ua->CR3 & (1<<3)) == (1<<3));
}
bool stm32dev_usart_control_getIRDALowpowerEnable(USART_TypeDef* ua){
	return ( (ua->CR3 & (1<<2)) == (1<<2));
}
bool stm32dev_usart_control_getIRDAModeEnable(USART_TypeDef* ua){
	return ( (ua->CR3 & (1<<1)) == (1<<1));
}
bool stm32dev_usart_control_getErrorInterruptEnable(USART_TypeDef* ua){
	return ( (ua->CR3 & (1<<0)) == (1<<0));
}

uint8_t stm32dev_usart_control_getGuardtime(USART_TypeDef* ua){
	return (ua->GTPR >> 8) & 0xF;
}

uint8_t stm32dev_usart_control_getPrescaler(USART_TypeDef* ua){
	return (ua->GTPR) & 0xF;
}

void stm32dev_usart_setData(USART_TypeDef* ua, uint16_t data){
	ua->DR = (data & 0x1F);
}
void stm32dev_usart_setBaudrateMantissa(USART_TypeDef* ua, uint16_t newVal){
	uint32_t tmp = ua->BRR & 0xF;
	ua->BRR = tmp | ((newVal & 0xFFF)<<4);
}
void stm32dev_usart_setBaudrateFraction(USART_TypeDef* ua, uint8_t newVal){
	uint32_t tmp = ua->BRR & 0xFFF0;
	ua->BRR = tmp | (newVal & 0xF);
}
void stm32dev_usart_control_setOversampling8(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<15);
	} else {
		ua->CR1 &= ~(1<<15);
	}
}
void stm32dev_usart_control_setUSARTEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<13);
	} else {
		ua->CR1 &= ~(1<<13);
	}
}
void stm32dev_usart_control_setWordLength9(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<12);
	} else {
		ua->CR1 &= ~(1<<12);
	}
}
void stm32dev_usart_control_setWAKE(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<11);
	} else {
		ua->CR1 &= ~(1<<11);
	}
}
void stm32dev_usart_control_setParitycontrolEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<10);
	} else {
		ua->CR1 &= ~(1<<10);
	}
}
void stm32dev_usart_control_setParityOdd(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<9);
	} else {
		ua->CR1 &= ~(1<<9);
	}
}
void stm32dev_usart_control_setParityInterruptEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<8);
	} else {
		ua->CR1 &= ~(1<<8);
	}
}
void stm32dev_usart_control_setTXEInterruptEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<7);
	} else {
		ua->CR1 &= ~(1<<7);
	}
}
void stm32dev_usart_control_setTCompleteInterruptEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<6);
	} else {
		ua->CR1 &= ~(1<<6);
	}
}
void stm32dev_usart_control_setRXNotEmptyInterruptEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<5);
	} else {
		ua->CR1 &= ~(1<<5);
	}
}
void stm32dev_usart_control_setIDLEInterruptEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<4);
	} else {
		ua->CR1 &= ~(1<<4);
	}
}
void stm32dev_usart_control_setTransmitterEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<3);
	} else {
		ua->CR1 &= ~(1<<3);
	}
}
void stm32dev_usart_control_setReceiverEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<2);
	} else {
		ua->CR1 &= ~(1<<2);
	}
}
void stm32dev_usart_control_setReceiverMutemode(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<1);
	} else {
		ua->CR1 &= ~(1<<1);
	}
}
void stm32dev_usart_control_setBreaktransmitEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR1 |= (1<<0);
	} else {
		ua->CR1 &= ~(1<<0);
	}
}
void stm32dev_usart_control_setLINModeEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR2 |= (1<<14);
	} else {
		ua->CR2 &= ~(1<<14);
	}
}
void stm32dev_usart_control_setClockEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR2 |= (1<<11);
	} else {
		ua->CR2 &= ~(1<<11);
	}
}
void stm32dev_usart_control_setClockPolarityHigh(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR2 |= (1<<10);
	} else {
		ua->CR2 &= ~(1<<10);
	}
}
void stm32dev_usart_control_setClockPhaseSecond(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR2 |= (1<<9);
	} else {
		ua->CR2 &= ~(1<<9);
	}
}
void stm32dev_usart_control_setLastbitclockpulsEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR2 |= (1<<8);
	} else {
		ua->CR2 &= ~(1<<8);
	}
}
void stm32dev_usart_control_setLINbreakdetectionInterruptEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR2 |= (1<<6);
	} else {
		ua->CR2 &= ~(1<<6);
	}
}
void stm32dev_usart_control_setLINbreakdetectionLength11(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR2 |= (1<<5);
	} else {
		ua->CR2 &= ~(1<<5);
	}
}
void stm32dev_usart_control_setSTOP(USART_TypeDef* ua, stm32dev_usart_Stopbits_list newVal){
	uint32_t tmp = ua->CR2 & 0xCFFF;
	ua->CR2 = (tmp) | ( (newVal & 0x3) << 12 );
}
void stm32dev_usart_control_setAddress(USART_TypeDef* ua, uint8_t newVal){
	uint32_t tmp = ua->CR2 & 0xFFF0;
	ua->CR2 = tmp | (newVal & 0xF);
}

void stm32dev_usart_control_setOnesamplebitmethodEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR3 |= (1<<11);
	} else {
		ua->CR3 &= ~(1<<11);
	}
}

void stm32dev_usart_control_setCTSInterruptEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR3 |= (1<<10);
	} else {
		ua->CR3 &= ~(1<<10);
	}
}

void stm32dev_usart_control_setCTSEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR3 |= (1<<9);
	} else {
		ua->CR3 &= ~(1<<9);
	}
}

void stm32dev_usart_control_setRTSEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR3 |= (1<<8);
	} else {
		ua->CR3 &= ~(1<<8);
	}
}

void stm32dev_usart_control_setDMAEnableTransmitter(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR3 |= (1<<7);
	} else {
		ua->CR3 &= ~(1<<7);
	}
}

void stm32dev_usart_control_setDMAEnableReceiver(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR3 |= (1<<6);
	} else {
		ua->CR3 &= ~(1<<6);
	}
}

void stm32dev_usart_control_setSmartcardModeEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR3 |= (1<<5);
	} else {
		ua->CR3 &= ~(1<<5);
	}
}

void stm32dev_usart_control_setSmartcardNACKEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR3 |= (1<<4);
	} else {
		ua->CR3 &= ~(1<<4);
	}
}

void stm32dev_usart_control_setHalfduplexSelected(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR3 |= (1<<3);
	} else {
		ua->CR3 &= ~(1<<3);
	}
}

void stm32dev_usart_control_setIRDALowpowerEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR3 |= (1<<2);
	} else {
		ua->CR3 &= ~(1<<2);
	}
}

void stm32dev_usart_control_setIRDAModeEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR3 |= (1<<1);
	} else {
		ua->CR3 &= ~(1<<1);
	}
}

void stm32dev_usart_control_setErrorInterruptEnable(USART_TypeDef* ua, bool newVal){
	if(newVal){
		ua->CR3 |= (1<<0);
	} else {
		ua->CR3 &= ~(1<<0);
	}
}


void stm32dev_usart_control_setGuardtime(USART_TypeDef* ua, uint8_t newVal){
	uint32_t tmp = ((ua->GTPR & 0xF));
	ua->GTPR = tmp | (newVal << 8);
}

void stm32dev_usart_control_setPrescaler(USART_TypeDef* ua, uint8_t newVal){
	uint32_t tmp = ((ua->GTPR & 0xF0));
	ua->GTPR = tmp | (newVal);
}
