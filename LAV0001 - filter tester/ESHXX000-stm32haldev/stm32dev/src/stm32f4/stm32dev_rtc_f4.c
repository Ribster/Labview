/*
 * stm32dev_rtc_f4.c
 *
 *  Created on: 18-okt.-2015
 *      Author: Robbe Van Assche
 */

#include "stm32dev_rtc_f4.h"

void stm32dev_rtc_initLSE32k(void){
		stm32dev_rcc_setClockPWR(true);					// enable power clock
		stm32dev_pwr_setBackupProtectionEnabled(false);	// enable write in RTC domain control register
		while(stm32dev_pwr_getBackupProtectionEnabled() == false){
			// wait until it is ready
			// TODO: TIMEOUT
		}

		stm32dev_rcc_setRTCLSEBypass(false);
		stm32dev_rcc_setRTCLSEEnabled(false);
		while(stm32dev_rcc_getRTCLSEReady() == false){
			// wait until it is ready
			// TODO: TIMEOUT
		}

		stm32dev_rcc_setRTCLSEBypass(false);
		stm32dev_rcc_setRTCLSEEnabled(true);
		while(stm32dev_rcc_getRTCLSEReady() == false){
			// wait until it is ready
			// TODO: TIMEOUT
		}


		stm32dev_rcc_setClockPWR(true);
		stm32dev_pwr_setBackupProtectionEnabled(false);
		while(stm32dev_pwr_getBackupProtectionEnabled() == false){
			// wait until it is ready
			// TODO: TIMEOUT
		}


		//if(stm32dev_rcc_getRTCClock() != stm32dev_rcc_RTCClock_LSE){
			stm32dev_rcc_setRTCClock(stm32dev_rcc_RTCClock_noClock);	// set the RTC clock to LSE
			if(stm32dev_rcc_getRTCLSEReady()){
				while(stm32dev_rcc_getRTCLSEReady() == false){
					// wait until it is ready
					// TODO: TIMEOUT
				}
			}
			stm32dev_rcc_setRTCClock(stm32dev_rcc_RTCClock_LSE);	// set the RTC clock to LSE
		//}


		stm32dev_rcc_setRTCClockEnabled(true);			// enable RTC clock
}

void stm32dev_rtc_setDigitalcalibrationEnable(bool newVal){
	if(newVal){
		RTC->CR |= (1<<7);
	} else {
		RTC->CR &= ~(1<<7);
	}
}

void stm32dev_rtc_setHourformat(bool newVal){
	if(newVal){
		RTC->CR |= (1<<6);
	} else {
		RTC->CR &= ~(1<<6);
	}
}

void stm32dev_rtc_setReferenceclockdetectionEnable(bool newVal){
	if(newVal){
		RTC->CR |= (1<<4);
	} else {
		RTC->CR &= ~(1<<4);
	}
}

void stm32dev_rtc_setPrescalers(uint8_t prediv_A, uint16_t prediv_S){
	// reset value
	RTC->PRER = 0x007F00FF;

	// prediv_A is a 7 bit asynchronous prescaler factor
		//	ck_apre frequency = RTCCLK frequency/(PREDIV_A+1)
	// prediv_S is a 15 bit synchronous prescalor factor
		//	ck_spre frequency = ck_apre frequency/(PREDIV_S+1)

	RTC->PRER |= ( ((prediv_A & 0x7F) << 16) | ((prediv_S & 0x7FFF) << 0) );
}

void stm32dev_rtc_setProtectionregister(uint8_t key){
	RTC->WPR = key;
}

void stm32dev_rtc_setSubseconds(uint16_t subseconds){
	RTC->SSR = subseconds & 0xFFFF;
}

void stm32dev_rtc_setAddsecond(bool newVal){
	if(newVal){
		RTC->SHIFTR |= (RTC_SHIFTR_ADD1S);
	} else {
		RTC->SHIFTR &= ~(RTC_SHIFTR_ADD1S);
	}
}
void stm32dev_rtc_setSubstractSubsecond(uint16_t subseconds){
		RTC->SHIFTR = subseconds & 0x7FFF;
}

void stm32dev_rtc_setCalibrationOutput(bool newVal){
	if(newVal){
		RTC->CR |= (RTC_CR_COE);
	} else {
		RTC->CR &= ~(RTC_CR_COE);
	}
}

void stm32dev_rtc_setOutput(stm32dev_rtc_Outputsel_list newVal){
	uint32_t tmp = RTC->CR;
	tmp &= ~(RTC_CR_OSEL);
	tmp |= (newVal<<21);
	RTC->CR = tmp;
}

void stm32dev_rtc_setOutputPolarity(bool newVal){
	//	0: The pin is high when ALRAF/ALRBF/WUTF is asserted (depending on OSEL[1:0])
	//	1: The pin is low when ALRAF/ALRBF/WUTF is asserted (depending on OSEL[1:0]).
	if(newVal){
		RTC->CR |= (RTC_CR_POL);
	} else {
		RTC->CR &= ~(RTC_CR_POL);
	}
}

void stm32dev_rtc_setCalibrationOutputFrequency(bool newVal){
	//	When COE=1, this bit selects which signal is output on RTC_CALIB.
	//	0: Calibration output is 512 Hz
	//	1: Calibration output is 1 Hz

	if(newVal){
		RTC->CR |= (RTC_CR_COSEL);
	} else {
		RTC->CR &= ~(RTC_CR_COSEL);
	}
}

void stm32dev_rtc_setBackupenable(bool newVal){
	//	This bit can be written by the user to memorize whether the daylight saving time change has
	//	been performed or not.

	if(newVal){
		RTC->CR |= (1<<18);
	} else {
		RTC->CR &= ~(1<<18);
	}
}

void stm32dev_rtc_setSubstract1hour(bool newVal){
	if(newVal){
		RTC->CR |= (1<<17);
	} else {
		RTC->CR &= ~(1<<17);
	}
}


void stm32dev_rtc_setAdd1hour(bool newVal){
	if(newVal){
		RTC->CR |= (1<<16);
	} else {
		RTC->CR &= ~(1<<16);
	}
}

void stm32dev_rtc_setTimestampInterruptEnable(bool newVal){
	if(newVal){
		RTC->CR |= (1<<15);
	} else {
		RTC->CR &= ~(1<<15);
	}
}

void stm32dev_rtc_setWakeuptimerInterruptEnable(bool newVal){
	if(newVal){
		RTC->CR |= (1<<14);
	} else {
		RTC->CR &= ~(1<<14);
	}
}


void stm32dev_rtc_setAlarmAInterruptEnable(bool newVal){
	if(newVal){
		RTC->CR |= (1<<12);
	} else {
		RTC->CR &= ~(1<<12);
	}
}
void stm32dev_rtc_setAlarmBInterruptEnable(bool newVal){
	if(newVal){
		RTC->CR |= (1<<13);
	} else {
		RTC->CR &= ~(1<<13);
	}
}


void stm32dev_rtc_setTimestampEnable(bool newVal){
	if(newVal){
		RTC->CR |= (1<<11);
	} else {
		RTC->CR &= ~(1<<11);
	}
}

void stm32dev_rtc_setWakeuptimerEnable(bool newVal){
	if(newVal){
		RTC->CR |= (1<<10);
	} else {
		RTC->CR &= ~(1<<10);
	}
}

void stm32dev_rtc_setAlarmAEnable(bool newVal){
	if(newVal){
		RTC->CR |= (1<<8);
	} else {
		RTC->CR &= ~(1<<8);
	}
}

void stm32dev_rtc_setAlarmBEnable(bool newVal){
	if(newVal){
		RTC->CR |= (1<<9);
	} else {
		RTC->CR &= ~(1<<9);
	}
}

void stm32dev_rtc_setBypassshadowregisters(bool newVal){
	if(newVal){
		RTC->CR |= (1<<5);
	} else {
		RTC->CR &= ~(1<<5);
	}
}


void stm32dev_rtc_setTimestampeventEdge(bool newVal){
	if(newVal){
		RTC->CR |= (1<<3);
	} else {
		RTC->CR &= ~(1<<3);
	}
}

void stm32dev_rtc_setWakeupclockselection(stm32dev_rtc_Wakeupclock_list newVal){
	//Bits 2 to 0 of this register can be written only when RTC_CR WUTE bit = 0 and RTC_ISR WUTWF bit = 1.

	RTC->CR |= ( newVal & 0x7);
}

void stm32dev_rtc_setWakeuptimerARR(uint16_t newVal){
	RTC->WUTR = newVal & 0xFFFF;
}

void stm32dev_rtc_setWriteprotect(bool newVal){
	if(newVal){
		stm32dev_pwr_setBackupProtectionEnabled(true);
		stm32dev_rtc_setProtectionregister(0xFE);
		stm32dev_rtc_setProtectionregister(0x64);
	} else {
		// disable write protect
		stm32dev_pwr_setBackupProtectionEnabled(false);
		stm32dev_rtc_setProtectionregister(0xCA);
		stm32dev_rtc_setProtectionregister(0x53);
	}
}

void stm32dev_rtc_setInitmode(bool newVal){
	if(newVal){
		RTC->ISR |= (1<<7);
	} else {
		RTC->ISR &= ~(1<<7);
	}
}

void stm32dev_rtc_setTime(stm32dev_rtc_TimeDate *newVal){
	uint32_t temp = RTC->TR;

	temp &= ~(1<<22 | 0x3F<<16 | 0x7F<<8 | 0x7F);

	uint8_t hours = stm32dev_general_getBCDfromDec(newVal->hour);
	uint8_t minutes = stm32dev_general_getBCDfromDec(newVal->minute);
	uint8_t seconds = stm32dev_general_getBCDfromDec(newVal->second);

	temp |= ( ((hours & 0x30) >> 4) <<20);
	temp |= ( (hours & 0xF) <<16);

	temp |= ( ((minutes & 0x70) >> 4) <<12);
	temp |= ( (minutes & 0xF) <<8);

	temp |= ( ((seconds & 0x70) >> 4) <<4);
	temp |= ( (seconds & 0xF) <<0);

	temp |= ((newVal->AMPM & 0x01)<<22);

	stm32dev_rtc_setWriteprotect(false);			// disable write protection
	stm32dev_rtc_setInitmode(true);					// set the RTC in init mode
	while(stm32dev_rtc_getInitmode() == false){		// wait until init mode is set
		// wait until init is set
		// TODO: add timeout
	}
	stm32dev_rtc_setPrescalers(0x7F, 0xFF);
	RTC->TR = temp;									// write the values to the register
	stm32dev_rtc_setHourformat(newVal->AMPM_enabled);
	stm32dev_rtc_setInitmode(false);				// disable the init mode
	stm32dev_rtc_setWriteprotect(true);				// enable write protection
}

void stm32dev_rtc_setDate(stm32dev_rtc_TimeDate *newVal){
	uint32_t temp = RTC->DR;

	temp &= ~(0xFF<<16 | 0x7<<13 | 0x1F<<8 | 0x3F<<0);

	uint8_t years = stm32dev_general_getBCDfromDec(newVal->year);
	uint8_t months = stm32dev_general_getBCDfromDec(newVal->month);
	uint8_t days = stm32dev_general_getBCDfromDec(newVal->day);
	uint8_t weekday = newVal->weekday;
	if(weekday == 0) weekday = 1;

	temp |= ( ((years & 0xF0) >> 4) <<20);
	temp |= ( (years & 0xF) <<16);

	temp |= ( ((months & 0x10) >> 4) <<12);
	temp |= ( (months & 0xF) <<8);

	temp |= ( ((days & 0x30) >> 4) <<4);
	temp |= ( (days & 0xF) <<0);

	temp |= ( (weekday & 0x7) <<13);

	stm32dev_rtc_setWriteprotect(false);			// disable write protection
	stm32dev_rtc_setInitmode(true);					// set the RTC in init mode
	while(stm32dev_rtc_getInitmode() == false){		// wait until init mode is set
		// wait until init is set
		// TODO: add timeout
	}
	stm32dev_rtc_setPrescalers(0x7F, 0xFF);
	RTC->DR = temp;									// write the values to the register
	stm32dev_rtc_setInitmode(false);				// disable the init mode
	stm32dev_rtc_setWriteprotect(true);				// enable write protection
}

void stm32dev_rtc_setDateTime(stm32dev_rtc_TimeDate *newVal){
	stm32dev_rtc_setDate(newVal);
	stm32dev_rtc_setTime(newVal);
}

void stm32dev_rtc_clearTamper1Detection(void){
	RTC->ISR &= ~(1<<13);
}
void stm32dev_rtc_clearTamper2Detection(void){
	RTC->ISR &= ~(1<<14);
}

void stm32dev_rtc_clearTimestampflag(void){
	RTC->ISR &= ~(1<<11);
}

void stm32dev_rtc_clearTimestampOverflowflag(void){
	// clear pending bit
	RTC->ISR &= ~(1<<11);
	// clear time stamp overflow
	RTC->ISR &= ~(1<<12);
}

void stm32dev_rtc_clearWakeuptimerflag(void){
	RTC->ISR &= ~(1<<10);
}

void stm32dev_rtc_clearTimerAflag(void){
	RTC->ISR &= ~(1<<8);
}

void stm32dev_rtc_clearTimerBflag(void){
	RTC->ISR &= ~(1<<9);
}

uint8_t stm32_rtc_getPredivA(void){
	return (RTC->PRER >> 16)&0x7F;
}

uint16_t stm32_rtc_getPredivS(void){
	return (RTC->PRER)&0x7FFF;
}

uint16_t stm32dev_rtc_getSubsecond(void){
	return RTC->SSR & 0xFFFF;
}

bool stm32dev_rtc_getTimestampInterruptEnable(void){
	return (RTC->CR & 1<<15);
}

bool stm32dev_rtc_getWakeuptimerInterruptEnable(void){
	return (RTC->CR & 1<<14);
}

bool stm32dev_rtc_getAlarmAInterruptEnable(void){
	return (RTC->CR & 1<<12);
}
bool stm32dev_rtc_getAlarmBInterruptEnable(void){
	return (RTC->CR & 1<<13);
}

bool stm32dev_rtc_getRecalibrationPending(void){
	return (RTC->ISR & 1<<16);
}

bool stm32dev_rtc_getTamper1Detection(void){
	return (RTC->ISR & 1<<13);
}

bool stm32dev_rtc_getTamper2Detection(void){
	return (RTC->ISR & 1<<14);
}

bool stm32dev_rtc_getTimestampflag(void){
	return (RTC->ISR & 1<<11);
}

bool stm32dev_rtc_getTimestampOverflowflag(void){
	return (RTC->ISR & 1<<12);
}

bool stm32dev_rtc_getWakeuptimerflag(void){
	return (RTC->ISR & 1<<10);
}

bool stm32dev_rtc_getTimerAflag(void){
	return (RTC->ISR & 1<<8);
}

bool stm32dev_rtc_getTimerBflag(void){
	return (RTC->ISR & 1<<9);
}

bool stm32dev_rtc_getInitmode(void){
	return (RTC->ISR & 1<<6);
}

bool stm32dev_rtc_getShadowregistersSynchonized(void){
	return (RTC->ISR & 1<<5);
}

bool stm32dev_rtc_getCalenderInitialized(void){
	return (RTC->ISR & 1<<4);
}

bool stm32dev_rtc_getShiftoperationPending(void){
	return (RTC->ISR & 1<<3);
}

bool stm32dev_rtc_getWakeuptimerwriteAllowed(void){
	return (RTC->ISR & 1<<2);
}

bool stm32dev_rtc_getAlarmAwriteAllowed(void){
	return (RTC->ISR & 1<<0);
}

bool stm32dev_rtc_getAlarmBwriteAllowed(void){
	return (RTC->ISR & 1<<1);
}

uint16_t stm32dev_rtc_getWakeuptimerARR(void){
	return RTC->WUTR & 0xFFFF;
}

void stm32dev_rtc_getTime(stm32dev_rtc_TimeDate *retVal){
	uint8_t hours = (RTC->TR >> 16) & 0x3F;
	uint8_t minutes = (RTC->TR >> 8) & 0x7F;
	uint8_t seconds = (RTC->TR >> 0) & 0x7F;

	retVal->hour = stm32dev_general_getDecfromBCD(hours);
	retVal->minute = stm32dev_general_getDecfromBCD(minutes);
	retVal->second = stm32dev_general_getDecfromBCD(seconds);

	retVal->AMPM = ( ( RTC->TR & (1<<22) ) == (1<<22) );
}

void stm32dev_rtc_getDate(stm32dev_rtc_TimeDate *retVal){
	uint8_t year = (RTC->DR >> 16) & 0xFF;
	uint8_t month = (RTC->DR >> 8) & 0x1F;
	uint8_t day = (RTC->DR >> 0) & 0x3F;

	retVal->year = stm32dev_general_getDecfromBCD(year);
	retVal->month = stm32dev_general_getDecfromBCD(month);
	retVal->day = stm32dev_general_getDecfromBCD(day);

	retVal->weeknumber = (RTC->DR >> 13) & 0x7;
}

void stm32dev_rtc_getDateTime(stm32dev_rtc_TimeDate *retVal){
	stm32dev_rtc_getTime(retVal);
	stm32dev_rtc_getDate(retVal);
}
