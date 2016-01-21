/*
 * stm32dev_rtc_f4.h
 *
 *  Created on: 18-okt.-2015
 *      Author: Robbe Van Assche
 */

#ifndef STM32DEV_INCLUDE_STM32F4_STM32DEV_RTC_F4_H_
#define STM32DEV_INCLUDE_STM32F4_STM32DEV_RTC_F4_H_

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
	#include "stm32f4xx_hal_rtc.h"
	#include "stm32f4xx_hal_rtc_ex.h"
#endif

#include "stm32dev_general.h"
#include "stm32dev_gpio_f4.h"
#include "stm32dev_usart_f4.h"
#include "stm32dev_rcc_f4.h"
#include "stm32dev_pwr_f4.h"

// structs
typedef enum stm32dev_rtc_Outputsel_list {
	stm32dev_rtc_Outputsel_Disabled = 0,
	stm32dev_rtc_Outputsel_AlarmA 	= 1,
	stm32dev_rtc_Outputsel_AlarmB 	= 2,
	stm32dev_rtc_Outputsel_Wakeup 	= 3
} stm32dev_rtc_Outputsel_list;

typedef enum stm32dev_rtc_Wakeupclock_list{
	stm32dev_rtc_Wakeupclock_div16 = 0,
	stm32dev_rtc_Wakeupclock_div8 = 1,
	stm32dev_rtc_Wakeupclock_div4 = 2,
	stm32dev_rtc_Wakeupclock_div2 = 3,
	stm32dev_rtc_Wakeupclock_spre = 4,
	stm32dev_rtc_Wakeupclock_spreWUT = 6
} stm32dev_rtc_Wakeupclock_list;

typedef struct stm32dev_rtc_TimeDate{
	bool AMPM;
	bool AMPM_enabled;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t weeknumber;
	uint8_t weekday;
}stm32dev_rtc_TimeDate;

// init RTC

// setters

void stm32dev_rtc_initLSE32k(void);

void stm32dev_rtc_setDigitalcalibrationEnable(bool newVal);	// init only
void stm32dev_rtc_setHourformat(bool newVal);	// init only
void stm32dev_rtc_setReferenceclockdetectionEnable(bool newVal);	// init only

void stm32dev_rtc_setPrescalers(uint8_t prediv_A, uint16_t prediv_S);
void stm32dev_rtc_setProtectionregister(uint8_t key);
void stm32dev_rtc_setSubseconds(uint16_t subseconds);
void stm32dev_rtc_setAddsecond(bool newVal);
void stm32dev_rtc_setSubstractSubsecond(uint16_t subseconds);

void stm32dev_rtc_setCalibrationOutput(bool newVal);
void stm32dev_rtc_setOutput(stm32dev_rtc_Outputsel_list newVal);
void stm32dev_rtc_setOutputPolarity(bool newVal);
void stm32dev_rtc_setCalibrationOutputFrequency(bool newVal);
void stm32dev_rtc_setBackupenable(bool newVal);
void stm32dev_rtc_setSubstract1hour(bool newVal);	// no read
void stm32dev_rtc_setAdd1hour(bool newVal);	// no read
void stm32dev_rtc_setTimestampInterruptEnable(bool newVal);
void stm32dev_rtc_setWakeuptimerInterruptEnable(bool newVal);
void stm32dev_rtc_setAlarmAInterruptEnable(bool newVal);
void stm32dev_rtc_setAlarmBInterruptEnable(bool newVal);
void stm32dev_rtc_setTimestampEnable(bool newVal);
void stm32dev_rtc_setWakeuptimerEnable(bool newVal);
void stm32dev_rtc_setAlarmAEnable(bool newVal);
void stm32dev_rtc_setAlarmBEnable(bool newVal);
void stm32dev_rtc_setBypassshadowregisters(bool newVal);
void stm32dev_rtc_setTimestampeventEdge(bool newVal);
void stm32dev_rtc_setWakeupclockselection(stm32dev_rtc_Wakeupclock_list newVal);
void stm32dev_rtc_setWakeuptimerARR(uint16_t newVal);

void stm32dev_rtc_setWriteprotect(bool newVal);
void stm32dev_rtc_setInitmode(bool newVal);

void stm32dev_rtc_setTime(stm32dev_rtc_TimeDate *newVal);
void stm32dev_rtc_setDate(stm32dev_rtc_TimeDate *newVal);
void stm32dev_rtc_setDateTime(stm32dev_rtc_TimeDate *newVal);

void stm32dev_rtc_clearTamper1Detection(void);
void stm32dev_rtc_clearTamper2Detection(void);
void stm32dev_rtc_clearTimestampflag(void);
void stm32dev_rtc_clearTimestampOverflowflag(void);
void stm32dev_rtc_clearWakeuptimerflag(void);
void stm32dev_rtc_clearTimerAflag(void);
void stm32dev_rtc_clearTimerBflag(void);

// getters
uint8_t stm32_rtc_getPredivA(void);
uint16_t stm32_rtc_getPredivS(void);
uint16_t stm32dev_rtc_getSubsecond(void);
bool stm32dev_rtc_getTimestampInterruptEnable(void);
bool stm32dev_rtc_getWakeuptimerInterruptEnable(void);
bool stm32dev_rtc_getAlarmAInterruptEnable(void);
bool stm32dev_rtc_getAlarmBInterruptEnable(void);
bool stm32dev_rtc_getRecalibrationPending(void);
bool stm32dev_rtc_getTamper1Detection(void);
bool stm32dev_rtc_getTamper2Detection(void);
bool stm32dev_rtc_getTimestampflag(void);
bool stm32dev_rtc_getTimestampOverflowflag(void);
bool stm32dev_rtc_getWakeuptimerflag(void);
bool stm32dev_rtc_getTimerAflag(void);
bool stm32dev_rtc_getTimerBflag(void);
bool stm32dev_rtc_getInitmode(void);
bool stm32dev_rtc_getShadowregistersSynchonized(void);
bool stm32dev_rtc_getCalenderInitialized(void);
bool stm32dev_rtc_getShiftoperationPending(void);
bool stm32dev_rtc_getWakeuptimerwriteAllowed(void);
bool stm32dev_rtc_getAlarmAwriteAllowed(void);
bool stm32dev_rtc_getAlarmBwriteAllowed(void);
uint16_t stm32dev_rtc_getWakeuptimerARR(void);

void stm32dev_rtc_getTime(stm32dev_rtc_TimeDate *retVal);
void stm32dev_rtc_getDate(stm32dev_rtc_TimeDate *retVal);
void stm32dev_rtc_getDateTime(stm32dev_rtc_TimeDate *retVal);


#endif /* STM32DEV_INCLUDE_STM32F4_STM32DEV_RTC_F4_H_ */
