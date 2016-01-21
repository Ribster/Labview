/*
 * application.h
 *
 *  Created on: 2-okt.-2015
 *      Author: Robbe Van Assche
 */

#ifndef INCLUDE_APPLICATION_H_
#define INCLUDE_APPLICATION_H_

#include "main.h"

#include <stdbool.h>
#include "globals.h"
#include "stm32dev_boards.h"
#include "usbd_cdc_interface.h"
#include "usbd_desc.h"

#include "stm32dev_dds_AD9833.h"
#include "stm32dev_dds_AD9834.h"
#include "stm32dev_dds_AD9850.h"
#include "stm32dev_dds_AD9851.h"

// enums
	typedef enum application_commands_types_list{
		application_commands_types_read 		= 1,
		application_commands_types_write 		= 2,
		application_commands_types_data 		= 3,
		application_commands_types_function 	= 4,
		application_commands_types_special 		= 5,
		application_commands_types_error
	}application_commands_types_list;

	typedef enum application_commands_readwrite_list{
		application_commands_readwrite_Frequency 		= 1,
		application_commands_readwrite_Testpattern 		= 2,
		application_commands_readwrite_RTCval 			= 3,
		application_commands_readwrite_DDSType 			= 4,
		application_commands_readwrite_WaveAmplitude 	= 5,
		application_commands_readwrite_dBmCorrection 	= 6,
		application_commands_readwrite_SweepfreqStart 	= 1000,
		application_commands_readwrite_SweepfreqStop 	= 1001,
		application_commands_readwrite_SweepfreqIncr 	= 1002,
		application_commands_readwrite_SweepfreqDelay 	= 1003,
		application_commands_readwrite_Samplecount 		= 1004
	}application_commands_readwrite_list;

	typedef enum application_commands_data_list{
		application_commands_data_ADC1val 	= 1,
		application_commands_data_ADC2val 	= 2
	}application_commands_data_list;

	typedef enum application_commands_function_list{
		application_commands_function_Sweep = 1
	}application_commands_function_list;

	typedef enum application_commands_special_list{
		application_commands_special_Escape = 1,
		application_commands_special_Reboot = 2
	}application_commands_special_list;


// application var enums
	typedef enum application_vars_patterns_list{
		application_vars_patterns_sine 		= 1,
		application_vars_patterns_triangle 	= 2
	}application_vars_patterns_list;

	typedef enum application_vars_DDStype_list{
		application_vars_DDStype_AD9851 = 1,
		application_vars_DDStype_AD9850 = 2,
		application_vars_DDStype_AD9833 = 3,
		application_vars_DDStype_AD9834 = 4
	}application_vars_DDStype_list;


	extern uint16_t calvalues_lowfreq[];
	extern uint16_t calvalues_highfreq[];

/*	USB FUNCTIONS	*/
void application_scrapeUSB(uint8_t* pbuf, uint32_t len);
void application_sendUSB(uint8_t* pbuf, uint32_t len);
void application_sendUSBString(char* pbuf);

/*	DDS LOW LEVEL	*/
void application_init(void);
void application_initializeLowlevel(application_vars_DDStype_list newType);
void application_initialize_ad9851();
void application_initialize_ad9850();
void application_initialize_ad9833();
void application_initialize_ad9834();

void application_deinitializeLowlevel(application_vars_DDStype_list newType);

void application_setfrequency(uint32_t frequency);

/*	GENERAL COMMAND FUNCTIONS	*/

application_commands_types_list application_getCommandType(void);
void application_selectCommand(application_commands_types_list commandType);
void application_wrongcommand(void);

uint16_t application_getDecypher(void);
void application_setExtraSampling(uint32_t count);
void application_printCommand(void);
void application_postProcessing(application_commands_types_list commandType);

/*	READ COMMANDS	*/
void application_selectRead(application_commands_readwrite_list command);

/*	WRITE COMMANDS	*/
application_commands_readwrite_list application_getWriteCommand(uint16_t commandNr);
void application_selectWrite(application_commands_readwrite_list command);
int application_writeBufferPayloadSize(void);
void application_postProcessingWrite(application_commands_readwrite_list command);
void application_storeRTCfromBuffer(RTC_TimeTypeDef *time, RTC_DateTypeDef *date);
void application_setDAC(uint16_t newVal, uint8_t channel);
void application_getADC(uint8_t channel);
void application_stopADC(void);
/*	DATA COMMANDS	*/
void application_selectData(application_commands_data_list command);

/*	FUNCTION COMMANDS	*/
void application_selectFunction(application_commands_function_list command);
void application_function_doSweep(void);
void application_function_sampleAndSend(void);

/*	SPECIAL COMMANDS	*/
void application_selectSpecial(application_commands_special_list command);

double application_getDBmValue(uint32_t frequency, uint16_t adcValue);
uint16_t application_getVoltageConversion(uint16_t adcValue);

#endif /* INCLUDE_APPLICATION_H_ */
