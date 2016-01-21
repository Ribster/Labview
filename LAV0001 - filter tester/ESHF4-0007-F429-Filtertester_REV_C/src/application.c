/*
 * application.c
 *
 *  Created on: 2-okt.-2015
 *      Author: Robbe Van Assche
 */
#include "application.h"

#define APPLICATION_DEBUG 0

#define APPLICATION_RX_BUFFERSIZE 1024

#define APPLICATION_READ_PREFIX 'R'
#define APPLICATION_WRITE_PREFIX 'W'
#define APPLICATION_DATA_PREFIX 'D'
#define APPLICATION_FUNCTION_PREFIX 'F'
#define APPLICATION_SPECIAL_PREFIX 'S'

#define APPLICATION_NUMBERWIDTH 4

// local functions
static inline void application_endcommand(void);

// local variables
	static uint8_t _application_rx_buffer[APPLICATION_RX_BUFFERSIZE];
	static uint32_t _application_rx_bufferPtr = 0;
	static application_commands_types_list _application_currentcommand = application_commands_types_error;
	static uint16_t _application_currentCommandNumber = 0;
	static uint32_t _application_waitingforinfo = 0;


// storage variables for the application
	// readwrite commands
	static uint32_t _application_vars_frequency = 40000;

	static application_vars_patterns_list _application_vars_pattern = application_vars_patterns_sine;

	static application_vars_DDStype_list _application_vars_DDStype = application_vars_DDStype_AD9834;

	static uint16_t _application_vars_waveamplitude = 3300;

	static uint32_t _application_vars_sweep_frequencystart = 1000;
	static uint32_t _application_vars_sweep_frequencystop = 100000;
	static uint32_t _application_vars_sweep_frequencyincrement = 1000;
	static uint32_t _application_vars_sweep_delay = 1;

	uint32_t _application_adc_samples = 4000;
	uint32_t _application_adc_samples_count = 0;

	uint8_t _application_dbm_values = 0;

	// data commands

	// function commands

	// special commands


/*	USB FUNCTIONS	*/
void application_scrapeUSB(uint8_t* pbuf, uint32_t len){
	/* This function gets called if the USB receives a character
	 * It then matches the predefined instructions and figures out what to do next
	 *
	 */
	//CDC_Itf_Send(pbuf, len);
	//if(*pbuf == '\r') //uart_transmit("carriage\r\n");
	//if(*pbuf == '\n') //uart_transmit("newline\r\n");
	BSP_LED_On(LED4);

	// copy the new character(s) in the local buffer
	memcpy((uint8_t*)&_application_rx_buffer[_application_rx_bufferPtr], pbuf, len);
	// set the buffer pointer to the new location
	_application_rx_bufferPtr += len;
	if(application_getCommandType() == application_commands_types_error){
		application_wrongcommand();
	} else if(_application_rx_bufferPtr > (APPLICATION_NUMBERWIDTH + 1) ){

		// read a whole command in
		// now read for the escape character, be on the lookout for this!!
		if(strcmp((char*)&_application_rx_buffer[_application_rx_bufferPtr-(APPLICATION_NUMBERWIDTH+1)], (char*)"S0001") == 0){
			//uart_transmit("escape command\r\n");
			// escape character, start the buffer again!!
			application_wrongcommand();
			return;
		}
	}

	if(_application_rx_bufferPtr == (APPLICATION_NUMBERWIDTH + 1) ){
		// read a whole command in

		// get the command type from the first byte, and select the action coupled with this specific command
		application_selectCommand(application_getCommandType());

	}else if(_application_waitingforinfo > 0 && *pbuf == '\r'){
		// waited for information that is coming in..
			//uart_transmit("Processing command\r\n");
			// process it
			application_postProcessing(_application_currentcommand);
			// end the command, so a new command can be issued
			application_endcommand();
	}

	BSP_LED_Off(LED4);
}

void application_sendUSB(uint8_t* pbuf, uint32_t len){
	// send charachters to the USB layer
	CDC_Itf_Send(pbuf, len);
}

void application_sendUSBString(char* pbuf){
	CDC_Itf_Send((uint8_t*)pbuf, strlen(pbuf));
}

/*	DDS LOW LEVEL	*/
void application_init(void){
	application_initializeLowlevel(_application_vars_DDStype);
}

void application_initializeLowlevel(application_vars_DDStype_list newType){
	// deinitialize previous hardware part
	application_deinitializeLowlevel(_application_vars_DDStype);

	// INIT AD9851
	if(newType == application_vars_DDStype_AD9851){
		application_initialize_ad9851();
	}

	// INIT AD9850
	if(newType == application_vars_DDStype_AD9850){
		application_initialize_ad9850();
	}

	// INIT AD9833
	if(newType == application_vars_DDStype_AD9833){
		application_initialize_ad9833();
	}

	// INIT AD9834
	if(newType == application_vars_DDStype_AD9834){
		application_initialize_ad9834();
	}

	_application_vars_DDStype = newType;
}
void application_initialize_ad9851(){
	// stub
}
void application_initialize_ad9850(){
	// stub
}
void application_initialize_ad9833(){
	// stub
}
void application_initialize_ad9834(){

	//uint8_t msg[] = "Initializing ad9834 \r\n";

	//HAL_uart_transmit(&UartHandle, msg, sizeof(msg), 50);

	ad9834_initPin_data(GPIOE, 14);
	ad9834_initPin_clock(GPIOE, 12);
	ad9834_initPin_ss(GPIOE, 11);
	ad9834_initialize();
}

void application_deinitializeLowlevel(application_vars_DDStype_list newType){
	if(newType == application_vars_DDStype_AD9851){
		// TODO: initialize AD9851
	}

	// INIT AD9850
	if(newType == application_vars_DDStype_AD9850){
		// TODO: initialize AD9850
	}

	// INIT AD9833
	if(newType == application_vars_DDStype_AD9833){
		// TODO: initialize AD9833
	}

	// INIT AD9834
	if(newType == application_vars_DDStype_AD9834){
		//uint8_t msg[] = "Deinitializing ad9834 \r\n";

		//HAL_//uart_transmit(&UartHandle, msg, sizeof(msg), 50);
		ad9834_deinitialize();
	}
}

void application_setfrequency(uint32_t frequency){
	if(_application_vars_DDStype == application_vars_DDStype_AD9851){
		// TODO: AD9851
	}

	// AD9850
	if(_application_vars_DDStype == application_vars_DDStype_AD9850){
		// TODO: AD9850
	}

	// AD9833
	if(_application_vars_DDStype == application_vars_DDStype_AD9833){
		// TODO: AD9833
	}

	// AD9834
	if(_application_vars_DDStype == application_vars_DDStype_AD9834){
		ad9834_setFrequency(ad9834_registers_prefix_FREQ0, frequency);
		ad9834_sendFrequency(ad9834_registers_prefix_FREQ0);
	}
}

/*	GENERAL COMMAND FUNCTIONS	*/
application_commands_types_list application_getCommandType(void){
	/* Give back the command type that is currently active
	 *
	 */

	// initialize with an error
	application_commands_types_list returnVal = application_commands_types_error;

	// select the correct prefix
	switch(_application_rx_buffer[0]){
		case APPLICATION_READ_PREFIX:
				returnVal = application_commands_types_read;
			break;
		case APPLICATION_WRITE_PREFIX:
				returnVal = application_commands_types_write;
			break;
		case APPLICATION_DATA_PREFIX:
				returnVal = application_commands_types_data;
			break;
		case APPLICATION_FUNCTION_PREFIX:
				returnVal = application_commands_types_function;
			break;
		case APPLICATION_SPECIAL_PREFIX:
				returnVal = application_commands_types_special;
			break;
	}

	// return value
	return returnVal;
}

void application_selectCommand(application_commands_types_list commandType){
	/* Knowing the type of command, we can couple an action to it.
	 * First decypher the command, to select the correct enum type
	 * Then call the respective command function with the decyphered command
	 *
	 */

	// get the decyphered command
	uint16_t currentCommand = application_getDecypher();
	_application_currentCommandNumber = currentCommand;
	////uart_transmitDec(currentCommand);
	////uart_transmit(" is the current command\r\n");

	// set current command
	_application_currentcommand = commandType;

	BSP_LED_On(LED4);

#if APPLICATION_DEBUG==1
				application_printCommand();
#endif

	switch(commandType){
		case application_commands_types_read:
				application_selectRead((application_commands_readwrite_list)currentCommand);
			break;
		case application_commands_types_write:
				application_selectWrite((application_commands_readwrite_list)currentCommand);
			break;
		case application_commands_types_data:
				application_selectData((application_commands_data_list)currentCommand);
			break;
		case application_commands_types_function:
				application_selectFunction((application_commands_function_list)currentCommand);
			break;
		case application_commands_types_special:
				application_selectSpecial((application_commands_special_list)currentCommand);
			break;
		case application_commands_types_error:
				application_wrongcommand();
			break;
	}

}

void application_wrongcommand(void){
	application_endcommand();
}

static inline void application_endcommand(void){
	/* When a wrong command is entered, the buffer pointer is set to the beginning.
	 * This way, the incoming characters will be treated as a new attempt at a command
	 */

	// clear waiting bitcount
	_application_waitingforinfo = 0;
	// reset buffer pointer
	_application_rx_bufferPtr = 0;
	// set the selected command to the begin state
	_application_currentcommand = application_commands_types_error;
	// clear current buffer
	memset(_application_rx_buffer, 0, APPLICATION_RX_BUFFERSIZE);

	BSP_LED_Off(LED4);
}

uint16_t application_getDecypher(void){
	/* Take in the current command, and convert it to an integer
	 *
	 */
	char convertString[APPLICATION_NUMBERWIDTH+1];
	convertString[APPLICATION_NUMBERWIDTH] = 0;
	memcpy((uint8_t*)convertString, (uint8_t*)&_application_rx_buffer[1], APPLICATION_NUMBERWIDTH);
	return (uint16_t)atoi(convertString);
}

void application_setExtraSampling(uint32_t count){
	/* Set the extra sampling count for incoming bytes
	 *
	 */

	_application_waitingforinfo = count;
}

void application_printCommand(void){
	/* If in debug mode, print the command to the UART
	 *
	 */
	//HAL_uart_transmit(&UartHandle, _application_rx_buffer, APPLICATION_NUMBERWIDTH+1, 50);
	//HAL_uart_transmit(&UartHandle, (uint8_t*)"\r\n", sizeof("\r\n"), 50);
}

void application_postProcessing(application_commands_types_list commandType){
	/* After the command is sampled, and the remaining bytes are sampled, do the post processing
	 *
	 */

	////uart_transmitDec(commandType);
	////uart_transmit(" is the current command Type, ");
	////uart_transmitDec(application_getWriteCommand(application_getDecypher()));
	////uart_transmit(" is the current command number \r\n");


	switch(commandType){
		case application_commands_types_read:
				// no post processing exists
			break;
		case application_commands_types_write:
				application_postProcessingWrite(_application_currentCommandNumber);
			break;
		case application_commands_types_data:

			break;
		case application_commands_types_function:

			break;
		case application_commands_types_special:

			break;
		case application_commands_types_error:

			break;
	}
}


/*	READ COMMANDS	*/
void application_selectRead(application_commands_readwrite_list command){
	/* If a read function is given, get the local variable and send it via USB
	 *
	 */
	  RTC_DateTypeDef sdatestructureget;
	  RTC_TimeTypeDef stimestructureget;

    char buffer[150];

	////uart_transmit("Read command: ");
	////uart_transmitDec(command);
	////uart_transmit("\r\n");

	switch(command){
		case application_commands_readwrite_Frequency:
			snprintf(buffer, 150, "%ld\r\n", _application_vars_frequency);

			application_sendUSBString(buffer);
			//uart_transmit(buffer);
			break;
		case application_commands_readwrite_Testpattern:
			snprintf(buffer, 150, "%d\r\n", _application_vars_pattern);

			application_sendUSBString(buffer);
			//uart_transmit(buffer);
			break;
		case application_commands_readwrite_RTCval:
			  /* Get the RTC current Time */
			  HAL_RTC_GetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);
			  /* Get the RTC current Date */
			  HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);
			  /* Display time Format : hh:mm:ss */
			  sprintf(buffer,"%02d:%02d:%02d=%02d-%02d-%04d\r\n",stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds, sdatestructureget.Date, sdatestructureget.Month, 2000 + sdatestructureget.Year);

			  application_sendUSBString(buffer);
			  //uart_transmit(buffer);
			break;
		case application_commands_readwrite_DDSType:
			snprintf(buffer, 150, "%d\r\n", _application_vars_DDStype);
			application_sendUSBString(buffer);
			//uart_transmit(buffer);
			break;
		case application_commands_readwrite_WaveAmplitude:
			snprintf(buffer, 150, "%d\r\n", _application_vars_waveamplitude);
			application_sendUSBString(buffer);
			//uart_transmit(buffer);
			break;
		case application_commands_readwrite_dBmCorrection:
			snprintf(buffer, 150, "%d\r\n", _application_dbm_values);
			application_sendUSBString(buffer);
			//uart_transmit(buffer);
			break;
		case application_commands_readwrite_SweepfreqStart:
			snprintf(buffer, 150, "%ld\r\n", _application_vars_sweep_frequencystart);

			application_sendUSBString(buffer);
			//uart_transmit(buffer);
			break;
		case application_commands_readwrite_SweepfreqStop:
			snprintf(buffer, 150, "%ld\r\n", _application_vars_sweep_frequencystop);

			application_sendUSBString(buffer);
			//uart_transmit(buffer);
			break;
		case application_commands_readwrite_SweepfreqIncr:
			snprintf(buffer, 150, "%ld\r\n", _application_vars_sweep_frequencyincrement);

			application_sendUSBString(buffer);
			//uart_transmit(buffer);
			break;
		case application_commands_readwrite_SweepfreqDelay:
			snprintf(buffer, 150, "%ld\r\n", _application_vars_sweep_delay);

			application_sendUSBString(buffer);
			//uart_transmit(buffer);
			break;
		case application_commands_readwrite_Samplecount:
			snprintf(buffer, 150, "%ld\r\n", _application_adc_samples);
			application_sendUSBString(buffer);
			//uart_transmit(buffer);
			break;
	}

	application_endcommand();
}

/*	WRITE COMMANDS	*/
application_commands_readwrite_list application_getWriteCommand(uint16_t commandNr){
	switch(commandNr){
	case application_commands_readwrite_Frequency:
		return application_commands_readwrite_Frequency;
		break;
	case application_commands_readwrite_Testpattern:
		return application_commands_readwrite_Frequency;
		break;
	case application_commands_readwrite_RTCval:
		return application_commands_readwrite_RTCval;
		break;
	case application_commands_readwrite_DDSType:
		return application_commands_readwrite_DDSType;
		break;
	case application_commands_readwrite_WaveAmplitude:
		return application_commands_readwrite_WaveAmplitude;
		break;
	case application_commands_readwrite_dBmCorrection:
		return application_commands_readwrite_dBmCorrection;
		break;
	case application_commands_readwrite_SweepfreqStart:
		return application_commands_readwrite_SweepfreqStart;
		break;
	case application_commands_readwrite_SweepfreqStop:
		return application_commands_readwrite_SweepfreqStop;
		break;
	case application_commands_readwrite_SweepfreqIncr:
		return application_commands_readwrite_SweepfreqIncr;
		break;
	case application_commands_readwrite_SweepfreqDelay:
		return application_commands_readwrite_SweepfreqDelay;
		break;
	case application_commands_readwrite_Samplecount:
		return application_commands_readwrite_Samplecount;
		break;
	}
	return 0;
}

void application_selectWrite(application_commands_readwrite_list command){
	//uart_transmit("Write command: ");
	//uart_transmitDec(command);
	//uart_transmit("\r\n");

	switch(command){
		case application_commands_readwrite_Frequency:
				application_setExtraSampling(1);
			break;
		case application_commands_readwrite_Testpattern:
				application_setExtraSampling(1);
			break;
		case application_commands_readwrite_RTCval:
				application_setExtraSampling(1);
			break;
		case application_commands_readwrite_DDSType:
				application_setExtraSampling(1);
			break;
		case application_commands_readwrite_WaveAmplitude:
				application_setExtraSampling(1);
			break;
		case application_commands_readwrite_dBmCorrection:
				application_setExtraSampling(1);
			break;
		case application_commands_readwrite_SweepfreqStart:
				application_setExtraSampling(1);
			break;
		case application_commands_readwrite_SweepfreqStop:
				application_setExtraSampling(1);
			break;
		case application_commands_readwrite_SweepfreqIncr:
				application_setExtraSampling(1);
			break;
		case application_commands_readwrite_SweepfreqDelay:
				application_setExtraSampling(1);
			break;
		case application_commands_readwrite_Samplecount:
				application_setExtraSampling(1);
			break;
		default:
			application_wrongcommand();
			break;
	}
}
int application_writeBufferPayloadSize(void){
	int i;

	for(i = 0; i<(APPLICATION_RX_BUFFERSIZE+1); i++){
		if(_application_rx_buffer[i] == '\r'){
			_application_rx_buffer[i] = '\0';
			return i - (APPLICATION_RX_BUFFERSIZE+1);
		}
	}

	return 0;
}
void application_postProcessingWrite(application_commands_readwrite_list command){

	// depending on the type, read the variable in and set it to the correct variable
	//char* startPtr = (char*)_application_rx_buffer + sizeof(APPLICATION_READ_PREFIX) + (APPLICATION_NUMBERWIDTH);
	char* startPtr = (char*)_application_rx_buffer + (APPLICATION_NUMBERWIDTH) + 1;
	//int payloadSize = application_writeBufferPayloadSize();
	//if(payloadSize == 0) return;
	  RTC_DateTypeDef sdatestructureget;
	  RTC_TimeTypeDef stimestructureget;

	  //uart_transmit("write val: ");
	  //uart_transmit((char*)startPtr);
	  //uart_transmit("\r\n");
	  ////uart_transmit("write cmd: ");
	  ////uart_transmit(stm32dev_general_getDec(command));
	  ////uart_transmit("\r\n");

	  uint32_t temp;
	  char buffer[150];

	switch(command){
		case application_commands_readwrite_Frequency:
				// call payload string and convert to correct data
				_application_vars_frequency = atoi((char*)startPtr);
				application_setfrequency(_application_vars_frequency);
			break;
		case application_commands_readwrite_Testpattern:
				//

				temp = atoi((char*)startPtr);

				if(temp == 2){
					////uart_transmit("written triangle \r\n");
					_application_vars_pattern = application_vars_patterns_triangle;
				} else {
					////uart_transmit("written sine \r\n");
					_application_vars_pattern = application_vars_patterns_sine;
				}
			break;
		case application_commands_readwrite_RTCval:
			  // fill the time and date buffer
			  application_storeRTCfromBuffer(&stimestructureget, &sdatestructureget);

			  sprintf(buffer,"%02d:%02d:%02d=%02d-%02d-%04d\r\n",stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds, sdatestructureget.Date, sdatestructureget.Month, 2000 + sdatestructureget.Year);

			  /* Get the RTC current Time */
			  HAL_RTC_SetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);
			  /* Get the RTC current Date */
			  HAL_RTC_SetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);
			  /*##-3- Writes a data in a RTC Backup data Register0 #######################*/
			  HAL_RTCEx_BKUPWrite(&RtcHandle,RTC_BKP_DR0,0x32F2);
			break;
		case application_commands_readwrite_DDSType:
				//
				_application_vars_DDStype = atoi((char*)startPtr);
			break;
		case application_commands_readwrite_WaveAmplitude:
				//
				_application_vars_waveamplitude = atoi((char*)startPtr);
				application_setDAC(_application_vars_waveamplitude, 1);
			break;
		case application_commands_readwrite_dBmCorrection:
				//
				_application_dbm_values = atoi((char*)startPtr);
			break;
		case application_commands_readwrite_SweepfreqStart:
				//
			_application_vars_sweep_frequencystart = atoi((char*)startPtr);
			break;
		case application_commands_readwrite_SweepfreqStop:
				//
			_application_vars_sweep_frequencystop = atoi((char*)startPtr);
			break;
		case application_commands_readwrite_SweepfreqIncr:
				//
			_application_vars_sweep_frequencyincrement = atoi((char*)startPtr);
			break;
		case application_commands_readwrite_SweepfreqDelay:
				//
			_application_vars_sweep_delay = atoi((char*)startPtr);
			break;
		case application_commands_readwrite_Samplecount:
				//
			_application_adc_samples = atoi((char*)startPtr);
			break;
		default:
			// impossible
			break;
	}

	//application_sendUSBString("\r\n");
}
void application_storeRTCfromBuffer(RTC_TimeTypeDef *time, RTC_DateTypeDef *date){
	char* startPtr = (char*)_application_rx_buffer + (APPLICATION_NUMBERWIDTH) + 1;
	char rtcBuffer[3];

	// %02d:%02d:%02d=%02d-%02d-%04d\r\n
	// 12:05:06=01-12-2015
	memcpy(rtcBuffer, startPtr, 2);
	rtcBuffer[2] = 0;

	time->Hours = atoi(rtcBuffer);

	memcpy(rtcBuffer, startPtr+3, 2);
	time->Minutes = atoi(rtcBuffer);

	memcpy(rtcBuffer, startPtr+6, 2);
	time->Seconds = atoi(rtcBuffer);

	memcpy(rtcBuffer, startPtr+9, 2);
	date->Date = atoi(rtcBuffer);

	memcpy(rtcBuffer, startPtr+12, 2);
	date->Month = atoi(rtcBuffer);

	memcpy(rtcBuffer, startPtr+17, 2);
	rtcBuffer[2] = 0;
	date->Year = atoi(rtcBuffer);
}


void application_setDAC(uint16_t newVal, uint8_t channel){
	uint16_t wantedVoltage = newVal;
	//if(newVal <= 140) wantedVoltage = 0;
	if(newVal >= 3210) wantedVoltage = 3210;
	//wantedVoltage -= 140;
	uint16_t setVal = (4095.0 * wantedVoltage)/3210.0;

	if(channel == 1){
		HAL_DAC_SetValue(&DacHandle, DACx_CHANNEL1, DAC_ALIGN_12B_R, setVal & 0xFFF);
	} else if (channel == 2){
		HAL_DAC_SetValue(&DacHandle, DACx_CHANNEL2, DAC_ALIGN_12B_R, setVal & 0xFFF);
	}
}

void application_getADC(uint8_t channel){
	if(channel == 1){
		channelSampling = 1;
		channelSamplingEnabled = true;
		uhADCxConvertedValue1_highest = 0;
		_application_adc_samples_count = 0;
	    /*##-2- Configure ADC regular channel ######################################*/
	    sADCConfig1.Channel      = ADCx_CHANNEL1;
	    sADCConfig1.Rank         = 1;
	    sADCConfig1.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	    sADCConfig1.Offset       = 0;
	    HAL_ADC_ConfigChannel(&AdcHandle1, &sADCConfig1);
	    //HAL_ADC_Start(&AdcHandle1);
	    //HAL_ADC_PollForConversion(&AdcHandle1, 10);
	    //uhADCxConvertedValue1 = HAL_ADC_GetValue(&AdcHandle1);
	    HAL_ADC_Start_DMA(&AdcHandle1, (uint32_t*)&uhADCxConvertedValue1, 1);
	} else if (channel == 2){
		channelSampling = 2;
		channelSamplingEnabled = true;
		uhADCxConvertedValue2_highest = 0;
		_application_adc_samples_count = 0;
	    sADCConfig2.Channel      = ADCx_CHANNEL2;
	    sADCConfig2.Rank         = 1;
	    sADCConfig2.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	    sADCConfig2.Offset       = 0;
	    HAL_ADC_ConfigChannel(&AdcHandle1, &sADCConfig2);
	    //HAL_ADC_Start(&AdcHandle1);
	    //HAL_ADC_PollForConversion(&AdcHandle1, 10);
	    //uhADCxConvertedValue2 = HAL_ADC_GetValue(&AdcHandle1);
	    HAL_ADC_Start_DMA(&AdcHandle1, (uint32_t*)&uhADCxConvertedValue1, 1);
	} else if (channel == 3){
		channelSampling = 3;
		channelSamplingEnabled = true;
		uhADCxConvertedValueVREFINT_highest = 0;
	    sADCConfig2.Channel      = ADC_CHANNEL_VREFINT;
	    sADCConfig2.Rank         = 1;
	    sADCConfig2.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	    sADCConfig2.Offset       = 0;
	    HAL_ADC_ConfigChannel(&AdcHandle1, &sADCConfig2);
	    //HAL_ADC_Start(&AdcHandle1);
	    //HAL_ADC_PollForConversion(&AdcHandle1, 10);
	    //uhADCxConvertedValue2 = HAL_ADC_GetValue(&AdcHandle1);
	    HAL_ADC_Start_DMA(&AdcHandle1, (uint32_t*)&uhADCxConvertedValue1, 1);
	}
	while(channelSamplingEnabled);
}

void application_stopADC(void){
	channelSamplingEnabled = false;
	HAL_ADC_Stop_DMA(&AdcHandle1);
}

/*	DATA COMMANDS	*/
void application_selectData(application_commands_data_list command){

	char buffer[150];

	//uart_transmit("Data command: ");
	//uart_transmitDec(command);
	//uart_transmit("\r\n");

	switch(command){
		case application_commands_data_ADC1val:
			application_getADC(1);
			snprintf(buffer, 150, "%d\r\n", uhADCxConvertedValue1_highest);
			application_sendUSBString(buffer);
			//uart_transmit(buffer);
			application_endcommand();
			break;
		case application_commands_data_ADC2val:
			application_getADC(2);
			snprintf(buffer, 150, "%d\r\n", uhADCxConvertedValue2_highest);
			application_sendUSBString(buffer);
			//uart_transmit(buffer);
			application_endcommand();
			break;
		default:
			application_wrongcommand();
			break;
	}
}

/*	FUNCTION COMMANDS	*/
void application_selectFunction(application_commands_function_list command){
	//uart_transmit("Function command: ");
	//uart_transmitDec(command);
	//uart_transmit("\r\n");

	switch(command){
		case application_commands_function_Sweep:
			//application_function_doSweep();

			// push data back to the pc
			//application_function_sampleAndSend();

			doSweep = true;

			application_endcommand();
			break;
		default:
			application_wrongcommand();
			break;
	}
}

void application_function_doSweep(void){
	// do a sweep
		// sweep from startfrequency to end frequency with increments and delay in between
		for(uint32_t freq = _application_vars_sweep_frequencystart; freq<=_application_vars_sweep_frequencystop; freq += _application_vars_sweep_frequencyincrement){
			//uart_transmit("/r");
			//uart_transmitDec(freq);
			application_setfrequency(freq);
			_application_vars_frequency = freq;
			HAL_Delay(_application_vars_sweep_delay);
		}
}

void application_function_sampleAndSend(void){
    //uint32_t loopCounter = 1;

    char buffer[150];

/*    for(int i=0; i<500; i++){
    	loopCounter *= (10);
    	snprintf(buffer, 150, "%ld\r\n", loopCounter);
    	//uart_transmit(buffer);
    	application_sendUSBString(buffer);
    	HAL_Delay(50);
    	if(i%30 == 0){
    		loopCounter = 1;
    	}
    }*/

    uint32_t packetnumber = 1;


	// buffer wave amplitude
	//uint16_t buffer_wa = _application_vars_waveamplitude;
	// send start frequency, stop frequency, interval
	snprintf(buffer, 150, "%ld;%ld\r\n", packetnumber++, _application_vars_sweep_frequencystart);
	//uart_transmit(buffer);
	application_sendUSBString(buffer);
	HAL_Delay(20);
	snprintf(buffer, 150, "%ld;%ld\r\n", packetnumber++, _application_vars_sweep_frequencystop);
	//uart_transmit(buffer);
	application_sendUSBString(buffer);
	HAL_Delay(20);
	snprintf(buffer, 150, "%ld;%ld\r\n", packetnumber++, _application_vars_sweep_frequencyincrement);
	//uart_transmit(buffer);
	application_sendUSBString(buffer);
	HAL_Delay(20);

	// scale from 0-3210
	uint32_t buffer_freqDifference = _application_vars_sweep_frequencystop-_application_vars_sweep_frequencystart;
	uint32_t buffer_freqSteps = buffer_freqDifference / _application_vars_sweep_frequencyincrement;
	uint32_t buffer_dacIncrements = 3210.0 / (buffer_freqSteps+1);
	uint32_t buffer_dacValue = 0;

	//application_setDAC((uint32_t)buffer_dacValue, 1);
	//application_setDAC(3210, 2);

	snprintf(buffer, 150, "Freq steps: %ld, DAC increments: %ld\r\n", buffer_freqSteps+1, buffer_dacIncrements);
	//uart_transmit(buffer);

	for(uint32_t freq = _application_vars_sweep_frequencystart; freq<=_application_vars_sweep_frequencystop; freq += _application_vars_sweep_frequencyincrement){

		// set frequency
		application_setfrequency(freq);
		// set local variable
		_application_vars_frequency = freq;

		// set DAC value
		//application_setDAC(buffer_dacValue, 1);
		//application_setDAC(3210-buffer_dacValue, 2);

		HAL_Delay(_application_vars_sweep_delay);

		// get adc channel 1
		application_getADC(1);

		// send adc channel 1
		if(_application_dbm_values == 0){
			snprintf(buffer, 150, "%ld;%d\r\n", packetnumber++, application_getVoltageConversion(uhADCxConvertedValue1_highest));
		} else {
			double int_part = 0.0;
			double frac_part = modf(application_getDBmValue(freq, uhADCxConvertedValue1_highest),&int_part);
			snprintf(buffer, 150, "%ld;%ld.%ld\r\n", packetnumber++, (long int)int_part, (long int)frac_part);
		}

		HAL_Delay(20);
		////uart_transmit(buffer);
		application_sendUSBString(buffer);

		application_getADC(2);
		// send adc channel 2
		if(_application_dbm_values == 0){
			snprintf(buffer, 150, "%ld;%d\r\n", packetnumber++, application_getVoltageConversion(uhADCxConvertedValue2_highest));
		} else {
			double int_part = 0.0;
			double frac_part = modf(application_getDBmValue(freq, uhADCxConvertedValue2_highest),&int_part);
			snprintf(buffer, 150, "%ld;%ld.%ld\r\n", packetnumber++, (long int)int_part, (long int)frac_part);
		}

		HAL_Delay(20);
		////uart_transmit(buffer);
		application_sendUSBString(buffer);

		// increment DAC values
		buffer_dacValue += buffer_dacIncrements;
	}

	//_application_vars_waveamplitude = buffer_wa;
	//application_setDAC(buffer_wa, 1);
	//application_setDAC(buffer_wa, 2);
	HAL_Delay(20);
	snprintf(buffer, 150, "%ld;done\r\n", packetnumber++);
	//uart_transmit(buffer);
	application_sendUSBString(buffer);
}

/*	SPECIAL COMMANDS	*/
void application_selectSpecial(application_commands_special_list command){
	//uart_transmit("Special command: ");
	//uart_transmitDec(command);
	//uart_transmit("\r\n");

	switch(command){
		case application_commands_special_Escape:
				// escape!!
				application_wrongcommand();
			break;
		case application_commands_special_Reboot:
				// reboot the processor
				NVIC_SystemReset();
			break;
		default:
				application_wrongcommand();
			break;
	}
}

double application_getDBmValue(uint32_t frequency, uint16_t adcValue){
	double retValue = 0.0;

	uint16_t voltageValue = application_getVoltageConversion(adcValue);

	if (voltageValue > 2393) {
		voltageValue = 2393 - 264;
	} else if(voltageValue > 264){
		voltageValue -= 264;
	} else {
		voltageValue = 0;
	}

	if(frequency > 100000000){
		double lowVal = calvalues_lowfreq[voltageValue];
		double highVal = calvalues_highfreq[voltageValue];
		double diffVal = highVal - lowVal;
		uint64_t diffFreq = 1000000000 - frequency;
		double percentage = (diffFreq / 1000000000);
		double addVal = diffVal * percentage;
		retValue = lowVal + addVal;
	} else {
		retValue = calvalues_lowfreq[voltageValue];
	}

	return retValue;
}

uint16_t application_getVoltageConversion(uint16_t adcValue){
	application_getADC(3);
	return (adcValue * 1200) / uhADCxConvertedValueVREFINT_highest;
}

uint16_t calvalues_lowfreq[] = {609, 834, 895, 948, 991, 1006, 1049, 1088, 1106, 1134, 1163, 1231, 1260, 1292, 1349, 1367, 1421, 1446, 1464, 1489, 1503, 1524, 1546, 1567, 1589, 1603, 1617, 1632, 1650, 1675, 1696, 1710, 1728, 1739, 1750, 1761, 1771, 1796, 1814, 1814, 1829, 1839, 1850, 1864, 1879, 1889, 1900, 1911, 1925, 1936, 1947, 1957, 1968, 1979, 1986, 1986, 1997, 2007, 2015, 2025, 2033, 2043, 2050, 2061, 2068, 2068, 2075, 2086, 2093, 2101, 2111, 2118, 2126, 2126, 2133, 2140, 2147, 2154, 2161, 2169, 2169, 2176, 2183, 2197, 2204, 2211, 2211, 2215, 2222, 2229, 2233, 2237, 2237, 2244, 2244, 2251, 2254, 2254, 2258, 2262, 2265, 2272, 2272, 2276, 2283, 2287, 2290, 2290, 2297, 2301, 2305, 2305, 2312, 2315, 2322, 2326, 2326, 2330, 2337, 2340, 2340, 2348, 2351, 2355, 2355, 2362, 2365, 2373, 2373, 2383, 2387, 2391, 2391, 2394, 2401, 2401, 2401, 2408, 2412, 2412, 2419, 2423, 2426, 2426, 2433, 2437, 2437, 2441, 2444, 2451, 2451, 2459, 2462, 2462, 2469, 2473, 2480, 2480, 2484, 2491, 2491, 2494, 2502, 2502, 2505, 2512, 2512, 2516, 2523, 2523, 2527, 2534, 2534, 2537, 2544, 2544, 2548, 2555, 2555, 2559, 2570, 2570, 2577, 2584, 2584, 2587, 2595, 2595, 2598, 2605, 2605, 2609, 2609, 2616, 2620, 2620, 2623, 2630, 2630, 2630, 2638, 2638, 2641, 2641, 2648, 2652, 2652, 2659, 2663, 2663, 2670, 2670, 2673, 2681, 2681, 2684, 2684, 2691, 2698, 2698, 2702, 2702, 2709, 2716, 2716, 2727, 2727, 2734, 2738, 2738, 2741, 2741, 2749, 2752, 2752, 2756, 2756, 2763, 2763, 2766, 2770, 2770, 2777, 2777, 2784, 2784, 2788, 2795, 2795, 2799, 2799, 2806, 2806, 2813, 2817, 2817, 2824, 2824, 2831, 2831, 2834, 2842, 2842, 2849, 2849, 2852, 2852, 2860, 2860, 2867, 2867, 2870, 2877, 2877, 2885, 2885, 2888, 2888, 2895, 2895, 2902, 2902, 2910, 2910, 2913, 2920, 2920, 2928, 2928, 2935, 2935, 2938, 2938, 2945, 2945, 2953, 2953, 2960, 2960, 2967, 2967, 2974, 2974, 2978, 2978, 2985, 2985, 2992, 2992, 2999, 2999, 3006, 3013, 3013, 3021, 3021, 3028, 3028, 3038, 3038, 3046, 3046, 3053, 3053, 3060, 3060, 3064, 3064, 3064, 3071, 3071, 3078, 3078, 3085, 3085, 3092, 3092, 3099, 3099, 3107, 3107, 3114, 3114, 3121, 3121, 3132, 3132, 3135, 3135, 3142, 3142, 3153, 3153, 3160, 3160, 3160, 3167, 3167, 3178, 3178, 3189, 3189, 3200, 3200, 3210, 3210, 3221, 3221, 3232, 3232, 3232, 3239, 3239, 3250, 3250, 3260, 3260, 3271, 3271, 3285, 3285, 3285, 3296, 3296, 3310, 3310, 3321, 3321, 3336, 3336, 3336, 3346, 3346, 3357, 3357, 3368, 3368, 3378, 3378, 3378, 3393, 3393, 3407, 3407, 3421, 3421, 3421, 3432, 3432, 3446, 3446, 3457, 3457, 3468, 3468, 3468, 3479, 3479, 3489, 3489, 3489, 3500, 3500, 3511, 3511, 3522, 3522, 3522, 3532, 3532, 3543, 3543, 3550, 3550, 3550, 3561, 3561, 3572, 3572, 3572, 3579, 3579, 3590, 3590, 3600, 3600, 3600, 3608, 3608, 3618, 3618, 3618, 3629, 3629, 3633, 3633, 3633, 3643, 3643, 3650, 3650, 3650, 3661, 3661, 3668, 3668, 3668, 3679, 3679, 3686, 3686, 3686, 3693, 3693, 3704, 3704, 3704, 3711, 3711, 3722, 3722, 3722, 3729, 3729, 3736, 3736, 3736, 3744, 3744, 3744, 3751, 3751, 3758, 3758, 3758, 3769, 3769, 3776, 3776, 3776, 3783, 3783, 3783, 3794, 3794, 3804, 3804, 3804, 3812, 3812, 3812, 3826, 3826, 3829, 3829, 3829, 3837, 3837, 3837, 3844, 3844, 3851, 3851, 3851, 3858, 3858, 3858, 3865, 3865, 3869, 3869, 3869, 3876, 3876, 3876, 3883, 3883, 3883, 3887, 3887, 3894, 3894, 3894, 3901, 3901, 3901, 3908, 3908, 3908, 3919, 3919, 3926, 3926, 3926, 3930, 3930, 3930, 3937, 3937, 3937, 3944, 3944, 3944, 3948, 3948, 3948, 3955, 3955, 3962, 3962, 3962, 3969, 3969, 3969, 3976, 3976, 3976, 3980, 3980, 3980, 3987, 3987, 3987, 3994, 3994, 3994, 4001, 4001, 4001, 4008, 4008, 4008, 4012, 4012, 4012, 4019, 4019, 4019, 4026, 4026, 4033, 4033, 4033, 4037, 4037, 4037, 4044, 4044, 4044, 4051, 4051, 4051, 4059, 4059, 4059, 4062, 4062, 4062, 4069, 4069, 4069, 4076, 4076, 4076, 4076, 4084, 4084, 4084, 4091, 4091, 4091, 4094, 4094, 4094, 4098, 4098, 4098, 4105, 4105, 4105, 4112, 4112, 4112, 4116, 4116, 4116, 4123, 4123, 4123, 4130, 4130, 4130, 4137, 4137, 4137, 4137, 4141, 4141, 4141, 4148, 4148, 4148, 4155, 4155, 4155, 4159, 4159, 4159, 4162, 4162, 4162, 4169, 4169, 4169, 4169, 4177, 4177, 4177, 4180, 4180, 4180, 4187, 4187, 4187, 4195, 4195, 4195, 4195, 4198, 4198, 4198, 4205, 4205, 4205, 4212, 4212, 4212, 4216, 4216, 4216, 4216, 4223, 4223, 4223, 4230, 4230, 4230, 4234, 4234, 4234, 4234, 4241, 4241, 4241, 4248, 4248, 4248, 4252, 4252, 4252, 4252, 4259, 4259, 4259, 4263, 4263, 4263, 4263, 4270, 4270, 4270, 4273, 4273, 4273, 4280, 4280, 4280, 4280, 4284, 4284, 4284, 4291, 4291, 4291, 4291, 4295, 4295, 4295, 4298, 4298, 4298, 4298, 4306, 4306, 4306, 4309, 4309, 4309, 4309, 4316, 4316, 4316, 4320, 4320, 4320, 4320, 4327, 4327, 4327, 4331, 4331, 4331, 4331, 4338, 4338, 4338, 4341, 4341, 4341, 4341, 4348, 4348, 4348, 4352, 4356, 4356, 4356, 4359, 4359, 4359, 4359, 4363, 4363, 4363, 4370, 4370, 4370, 4370, 4374, 4374, 4374, 4374, 4381, 4381, 4381, 4384, 4384, 4384, 4384, 4388, 4388, 4388, 4388, 4395, 4395, 4395, 4399, 4399, 4399, 4399, 4406, 4406, 4406, 4406, 4409, 4409, 4409, 4409, 4417, 4417, 4417, 4420, 4420, 4420, 4420, 4424, 4424, 4424, 4424, 4431, 4431, 4431, 4431, 4434, 4434, 4434, 4442, 4442, 4442, 4442, 4445, 4445, 4445, 4445, 4452, 4452, 4452, 4452, 4456, 4456, 4456, 4456, 4460, 4460, 4460, 4460, 4467, 4467, 4467, 4470, 4470, 4470, 4470, 4477, 4477, 4477, 4477, 4481, 4481, 4481, 4481, 4485, 4485, 4485, 4485, 4492, 4492, 4492, 4492, 4495, 4495, 4495, 4495, 4502, 4502, 4502, 4502, 4506, 4506, 4506, 4506, 4510, 4510, 4510, 4510, 4517, 4517, 4517, 4517, 4520, 4520, 4520, 4520, 4524, 4524, 4524, 4524, 4535, 4535, 4535, 4535, 4535, 4535, 4535, 4535, 4538, 4538, 4538, 4538, 4549, 4549, 4549, 4549, 4553, 4553, 4553, 4553, 4556, 4556, 4556, 4556, 4556, 4563, 4563, 4563, 4563, 4567, 4567, 4567, 4567, 4574, 4574, 4574, 4574, 4578, 4578, 4578, 4578, 4585, 4585, 4585, 4585, 4588, 4588, 4588, 4588, 4588, 4596, 4596, 4596, 4596, 4599, 4599, 4599, 4599, 4603, 4603, 4603, 4603, 4610, 4610, 4610, 4610, 4610, 4613, 4613, 4613, 4613, 4617, 4617, 4617, 4617, 4621, 4621, 4621, 4621, 4621, 4624, 4624, 4624, 4624, 4628, 4628, 4628, 4628, 4631, 4631, 4631, 4631, 4631, 4635, 4635, 4635, 4635, 4639, 4639, 4639, 4639, 4642, 4642, 4642, 4642, 4642, 4646, 4646, 4646, 4646, 4653, 4653, 4653, 4653, 4653, 4656, 4656, 4656, 4656, 4664, 4664, 4664, 4664, 4664, 4667, 4667, 4667, 4667, 4671, 4671, 4671, 4671, 4674, 4674, 4674, 4674, 4674, 4682, 4682, 4682, 4682, 4682, 4685, 4685, 4685, 4685, 4689, 4689, 4689, 4689, 4689, 4692, 4692, 4692, 4692, 4696, 4696, 4696, 4696, 4696, 4703, 4703, 4703, 4703, 4707, 4707, 4707, 4707, 4707, 4710, 4710, 4710, 4710, 4710, 4714, 4714, 4714, 4714, 4721, 4721, 4721, 4721, 4721, 4724, 4724, 4724, 4724, 4724, 4728, 4728, 4728, 4728, 4732, 4732, 4732, 4732, 4732, 4739, 4739, 4739, 4739, 4739, 4742, 4742, 4742, 4742, 4742, 4746, 4746, 4746, 4746, 4750, 4750, 4750, 4750, 4750, 4757, 4757, 4757, 4757, 4757, 4760, 4760, 4760, 4760, 4760, 4764, 4764, 4764, 4764, 4764, 4767, 4767, 4767, 4767, 4775, 4775, 4775, 4775, 4775, 4778, 4778, 4778, 4778, 4778, 4782, 4782, 4782, 4782, 4782, 4785, 4785, 4785, 4785, 4785, 4793, 4793, 4793, 4793, 4793, 4796, 4796, 4796, 4796, 4796, 4800, 4800, 4800, 4800, 4800, 4807, 4807, 4807, 4807, 4807, 4810, 4810, 4810, 4810, 4810, 4814, 4814, 4814, 4814, 4814, 4818, 4818, 4818, 4818, 4818, 4821, 4821, 4821, 4821, 4821, 4825, 4825, 4825, 4825, 4825, 4832, 4832, 4832, 4832, 4832, 4835, 4835, 4835, 4835, 4835, 4839, 4839, 4839, 4839, 4839, 4843, 4843, 4843, 4843, 4843, 4850, 4850, 4850, 4850, 4850, 4853, 4853, 4853, 4853, 4853, 4853, 4857, 4857, 4857, 4857, 4857, 4861, 4861, 4861, 4861, 4861, 4864, 4864, 4864, 4864, 4864, 4871, 4871, 4871, 4871, 4871, 4871, 4875, 4875, 4875, 4875, 4875, 4878, 4878, 4878, 4878, 4878, 4882, 4882, 4882, 4882, 4882, 4886, 4886, 4886, 4886, 4886, 4886, 4893, 4893, 4893, 4893, 4893, 4896, 4896, 4896, 4896, 4896, 4900, 4900, 4900, 4900, 4900, 4900, 4904, 4904, 4904, 4904, 4904, 4907, 4907, 4907, 4907, 4907, 4907, 4914, 4914, 4914, 4914, 4914, 4918, 4918, 4918, 4918, 4918, 4921, 4921, 4921, 4921, 4921, 4921, 4925, 4925, 4925, 4925, 4925, 4929, 4929, 4929, 4929, 4929, 4929, 4936, 4936, 4936, 4936, 4936, 4939, 4939, 4939, 4939, 4939, 4939, 4943, 4943, 4943, 4943, 4943, 4947, 4947, 4947, 4947, 4947, 4947, 4950, 4950, 4950, 4950, 4950, 4950, 4957, 4957, 4957, 4957, 4957, 4961, 4961, 4961, 4961, 4961, 4961, 4964, 4964, 4964, 4964, 4964, 4964, 4972, 4972, 4972, 4972, 4972, 4975, 4975, 4975, 4975, 4975, 4975, 4979, 4979, 4979, 4979, 4979, 4979, 4989, 4989, 4989, 4989, 4989, 4989, 4989, 4989, 4989, 4989, 4989, 4997, 4997, 4997, 4997, 4997, 4997, 4997, 4997, 4997, 4997, 4997, 4997, 5000, 5000, 5000, 5000, 5000, 5000, 5004, 5004, 5004, 5004, 5004, 5007, 5007, 5007, 5007, 5007, 5007, 5018, 5018, 5018, 5018, 5018, 5018, 5018, 5018, 5018, 5018, 5018, 5018, 5022, 5022, 5022, 5022, 5022, 5022, 5025, 5025, 5025, 5025, 5025, 5025, 5029, 5029, 5029, 5029, 5029, 5029, 5032, 5032, 5032, 5032, 5032, 5032, 5036, 5036, 5036, 5036, 5036, 5036, 5040, 5040, 5040, 5040, 5040, 5040, 5043, 5043, 5043, 5043, 5043, 5043, 5047, 5047, 5047, 5047, 5047, 5047, 5054, 5054, 5054, 5054, 5054, 5054, 5058, 5058, 5058, 5058, 5058, 5058, 5061, 5061, 5061, 5061, 5061, 5061, 5065, 5065, 5065, 5065, 5065, 5065, 5068, 5068, 5068, 5068, 5068, 5068, 5072, 5072, 5072, 5072, 5072, 5072, 5072, 5075, 5075, 5075, 5075, 5075, 5075, 5083, 5083, 5083, 5083, 5083, 5083, 5086, 5086, 5086, 5086, 5086, 5086, 5090, 5090, 5090, 5090, 5090, 5090, 5090, 5093, 5093, 5093, 5093, 5093, 5093, 5097, 5097, 5097, 5097, 5097, 5097, 5101, 5101, 5101, 5101, 5101, 5101, 5104, 5104, 5104, 5104, 5104, 5104, 5104, 5111, 5111, 5111, 5111, 5111, 5111, 5115, 5115, 5115, 5115, 5115, 5115, 5115, 5118, 5118, 5118, 5118, 5118, 5118, 5122, 5122, 5122, 5122, 5122, 5122, 5126, 5126, 5126, 5126, 5126, 5126, 5126, 5129, 5129, 5129, 5129, 5129, 5129, 5133, 5133, 5133, 5133, 5133, 5133, 5133, 5140, 5140, 5140, 5140, 5140, 5140, 5143, 5143, 5143, 5143, 5143, 5143, 5143, 5147, 5147, 5147, 5147, 5147, 5147, 5147, 5151, 5151, 5151, 5151, 5151, 5151, 5154, 5154, 5154, 5154, 5154, 5154, 5154, 5165, 5165, 5165, 5165, 5165, 5165, 5169, 5169, 5169, 5169, 5169, 5169, 5169, 5172, 5172, 5172, 5172, 5172, 5172, 5172, 5172, 5172, 5172, 5172, 5172, 5172, 5176, 5176, 5176, 5176, 5176, 5176, 5176, 5179, 5179, 5179, 5179, 5179, 5179, 5179, 5186, 5186, 5186, 5186, 5186, 5186, 5186, 5190, 5190, 5190, 5190, 5190, 5190, 5190, 5194, 5194, 5194, 5194, 5194, 5194, 5197, 5197, 5197, 5197, 5197, 5197, 5197, 5201, 5201, 5201, 5201, 5201, 5201, 5201, 5204, 5204, 5204, 5204, 5204, 5204, 5204, 5208, 5208, 5208, 5208, 5208, 5208, 5208, 5212, 5212, 5212, 5212, 5212, 5212, 5212, 5215, 5215, 5215, 5215, 5215, 5215, 5215, 5219, 5219, 5219, 5219, 5219, 5219, 5219, 5222, 5222, 5222, 5222, 5222, 5222, 5222, 5226, 5226, 5226, 5226, 5226, 5226, 5226, 5229, 5229, 5229, 5229, 5229, 5229, 5229, 5233, 5233, 5233, 5233, 5233, 5233, 5233, 5237, 5237, 5237, 5237, 5237, 5237, 5237, 5240, 5240, 5240, 5240, 5240, 5240, 5240, 5244, 5244, 5244, 5244, 5244, 5244, 5244, 5251, 5251, 5251, 5251, 5251, 5251, 5251, 5251, 5255, 5255, 5255, 5255, 5255, 5255, 5255, 5258, 5258, 5258, 5258, 5258, 5258, 5258, 5262, 5262, 5262, 5262, 5262, 5262, 5262, 5265, 5265, 5265, 5265, 5265, 5265, 5265, 5265, 5269, 5269, 5269, 5269, 5269, 5269, 5269, 5272, 5272, 5272, 5272, 5272, 5272, 5272, 5276, 5276, 5276, 5276, 5276, 5276, 5276, 5276, 5280, 5280, 5280, 5280, 5280, 5280, 5280, 5283, 5283, 5283, 5283, 5283, 5283, 5283, 5287, 5287, 5287, 5287, 5287, 5287, 5287, 5287, 5290, 5290, 5290, 5290, 5290, 5290, 5290, 5294, 5294, 5294, 5294, 5294, 5294, 5294, 5294, 5301, 5301, 5301, 5301, 5301, 5301, 5301, 5305, 5305, 5305, 5305, 5305, 5305, 5305, 5305, 5308, 5308, 5308, 5308, 5308, 5308, 5308, 5312, 5312, 5312, 5312, 5312, 5312, 5312, 5312, 5315, 5315, 5315, 5315, 5315, 5315, 5315, 5315, 5319, 5319, 5319, 5319, 5319, 5319, 5319, 5323, 5323, 5323, 5323, 5323, 5323, 5323, 5323, 5326, 5326, 5326, 5326, 5326, 5326, 5326, 5326, 5330, 5330, 5330, 5330, 5330, 5330, 5330, 5333, 5333, 5333, 5333, 5333, 5333, 5333, 5333, 5337, 5337, 5337, 5337, 5337, 5337, 5337, 5337, 5340, 5340, 5340, 5340, 5340, 5340, 5340, 5340, 5344, 5344, 5344, 5344, 5344, 5344, 5344, 5344, 5348, 5348, 5348, 5348, 5348, 5348, 5348, 5351, 5351, 5351, 5351, 5351, 5351, 5351, 5351, 5358, 5358, 5358, 5358, 5358, 5358, 5358, 5358, 5358, 5358, 5358, 5358, 5358, 5358, 5358, 5358, 5366, 5366, 5366, 5366, 5366, 5366, 5366, 5366, 5369, 5369, 5369, 5369, 5369, 5369, 5369, 5369, 5373, 5373, 5373, 5373, 5373, 5373, 5373, 5373, 5376, 5376, 5376, 5376, 5376, 5376, 5376, 5376, 5380, 5380, 5380, 5380, 5380, 5380, 5380, 5380, 5383, 5383, 5383, 5383, 5383, 5383, 5383, 5383, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5391, 5391, 5391, 5391, 5391, 5391, 5391, 5391, 5391};

uint16_t calvalues_highfreq[] = {609, 834, 895, 1041, 1106, 1192, 1342, 1378, 1424, 1492, 1539, 1574, 1614, 1657, 1689, 1743, 1768, 1789, 1818, 1871, 1896, 1918, 1943, 1964, 1986, 2014, 2025, 2054, 2061, 2086, 2104, 2118, 2136, 2150, 2150, 2165, 2179, 2197, 2211, 2226, 2233, 2243, 2251, 2265, 2276, 2294, 2308, 2319, 2333, 2344, 2354, 2365, 2376, 2376, 2387, 2397, 2408, 2419, 2426, 2437, 2447, 2455, 2465, 2465, 2472, 2483, 2490, 2498, 2508, 2515, 2523, 2523, 2530, 2537, 2544, 2551, 2558, 2566, 2573, 2573, 2580, 2587, 2598, 2605, 2608, 2608, 2616, 2623, 2630, 2637, 2644, 2644, 2648, 2655, 2662, 2669, 2669, 2673, 2680, 2687, 2691, 2691, 2698, 2702, 2709, 2712, 2712, 2719, 2723, 2730, 2734, 2734, 2741, 2745, 2748, 2748, 2755, 2759, 2762, 2762, 2766, 2773, 2784, 2784, 2787, 2791, 2795, 2795, 2798, 2802, 2805, 2805, 2809, 2820, 2820, 2820, 2823, 2827, 2830, 2830, 2834, 2838, 2838, 2841, 2848, 2852, 2852, 2856, 2863, 2863, 2866, 2870, 2873, 2873, 2881, 2888, 2888, 2891, 2895, 2895, 2902, 2906, 2906, 2909, 2913, 2916, 2916, 2924, 2927, 2927, 2931, 2938, 2938, 2945, 2949, 2949, 2956, 2959, 2959, 2963, 2974, 2974, 2974, 2974, 2977, 2988, 2988, 2992, 2995, 2995, 3002, 3002, 3002, 3010, 3013, 3013, 3017, 3017, 3031, 3035, 3035, 3042, 3045, 3045, 3049, 3049, 3056, 3056, 3056, 3063, 3067, 3067, 3070, 3070, 3074, 3078, 3078, 3085, 3085, 3088, 3095, 3095, 3099, 3099, 3106, 3113, 3113, 3117, 3117, 3124, 3128, 3128, 3131, 3131, 3138, 3146, 3146, 3149, 3149, 3156, 3156, 3160, 3167, 3167, 3174, 3174, 3178, 3178, 3185, 3189, 3189, 3196, 3196, 3203, 3203, 3206, 3214, 3214, 3221, 3221, 3224, 3224, 3231, 3231, 3239, 3242, 3242, 3249, 3249, 3257, 3257, 3260, 3260, 3267, 3267, 3274, 3282, 3282, 3285, 3285, 3292, 3292, 3300, 3300, 3307, 3307, 3310, 3310, 3317, 3317, 3325, 3332, 3332, 3339, 3339, 3346, 3346, 3350, 3350, 3357, 3357, 3364, 3364, 3371, 3371, 3378, 3378, 3385, 3385, 3393, 3393, 3400, 3400, 3407, 3407, 3414, 3414, 3421, 3421, 3432, 3432, 3436, 3436, 3443, 3443, 3446, 3446, 3453, 3453, 3461, 3461, 3468, 3468, 3482, 3482, 3489, 3489, 3500, 3500, 3507, 3507, 3514, 3514, 3521, 3521, 3529, 3529, 3539, 3539, 3539, 3546, 3546, 3554, 3554, 3564, 3564, 3572, 3572, 3582, 3582, 3593, 3593, 3604, 3604, 3611, 3611, 3611, 3622, 3622, 3632, 3632, 3640, 3640, 3650, 3650, 3661, 3661, 3661, 3668, 3668, 3679, 3679, 3690, 3690, 3697, 3697, 3708, 3708, 3708, 3718, 3718, 3725, 3725, 3736, 3736, 3743, 3743, 3743, 3750, 3750, 3761, 3761, 3768, 3768, 3768, 3779, 3779, 3786, 3786, 3797, 3797, 3808, 3811, 3811, 3818, 3818, 3829, 3829, 3840, 3844, 3844, 3847, 3847, 3854, 3854, 3854, 3861, 3861, 3872, 3872, 3876, 3876, 3876, 3883, 3883, 3894, 3894, 3901, 3904, 3904, 3908, 3908, 3915, 3915, 3915, 3922, 3922, 3929, 3929, 3929, 3937, 3937, 3944, 3944, 3944, 3954, 3954, 3962, 3962, 3962, 3969, 3969, 3976, 3976, 3983, 3983, 3983, 3990, 3990, 3990, 4001, 4001, 4008, 4008, 4008, 4015, 4015, 4022, 4022, 4022, 4030, 4030, 4033, 4033, 4033, 4040, 4040, 4048, 4048, 4048, 4055, 4055, 4055, 4062, 4062, 4069, 4069, 4069, 4076, 4076, 4083, 4083, 4083, 4091, 4091, 4091, 4098, 4098, 4105, 4105, 4105, 4112, 4112, 4112, 4126, 4126, 4133, 4133, 4133, 4137, 4137, 4137, 4144, 4144, 4151, 4151, 4151, 4155, 4155, 4155, 4162, 4162, 4169, 4169, 4169, 4173, 4173, 4173, 4176, 4176, 4176, 4187, 4187, 4191, 4191, 4191, 4198, 4198, 4198, 4205, 4205, 4205, 4212, 4212, 4212, 4219, 4219, 4227, 4227, 4227, 4234, 4234, 4234, 4237, 4237, 4237, 4244, 4244, 4244, 4252, 4252, 4252, 4255, 4255, 4255, 4262, 4262, 4269, 4269, 4269, 4277, 4277, 4277, 4280, 4280, 4280, 4287, 4287, 4287, 4295, 4295, 4295, 4298, 4298, 4298, 4309, 4309, 4309, 4316, 4316, 4316, 4327, 4327, 4327, 4334, 4334, 4334, 4341, 4341, 4341, 4348, 4348, 4348, 4352, 4352, 4352, 4359, 4359, 4359, 4366, 4366, 4366, 4370, 4370, 4370, 4377, 4377, 4377, 4384, 4384, 4384, 4388, 4388, 4388, 4391, 4391, 4391, 4398, 4398, 4398, 4398, 4398, 4398, 4406, 4406, 4406, 4409, 4409, 4409, 4409, 4416, 4416, 4416, 4423, 4423, 4423, 4427, 4427, 4427, 4434, 4434, 4434, 4438, 4438, 4438, 4445, 4445, 4445, 4445, 4452, 4452, 4452, 4456, 4456, 4456, 4463, 4463, 4463, 4466, 4466, 4466, 4474, 4474, 4474, 4474, 4481, 4481, 4481, 4484, 4484, 4484, 4491, 4491, 4491, 4491, 4499, 4499, 4499, 4502, 4502, 4502, 4509, 4509, 4509, 4516, 4516, 4516, 4516, 4520, 4520, 4520, 4531, 4531, 4531, 4534, 4534, 4534, 4534, 4538, 4538, 4538, 4542, 4542, 4542, 4542, 4549, 4549, 4549, 4552, 4552, 4552, 4563, 4563, 4563, 4563, 4570, 4570, 4570, 4574, 4574, 4574, 4574, 4581, 4581, 4581, 4585, 4585, 4585, 4585, 4588, 4588, 4588, 4595, 4595, 4595, 4595, 4595, 4595, 4595, 4602, 4602, 4602, 4602, 4606, 4606, 4606, 4613, 4613, 4613, 4613, 4617, 4617, 4617, 4624, 4624, 4624, 4624, 4627, 4627, 4627, 4635, 4635, 4635, 4635, 4638, 4638, 4638, 4638, 4642, 4642, 4642, 4649, 4649, 4649, 4649, 4653, 4653, 4653, 4660, 4660, 4660, 4660, 4663, 4663, 4663, 4663, 4670, 4670, 4670, 4674, 4674, 4674, 4674, 4681, 4681, 4681, 4681, 4685, 4685, 4685, 4692, 4692, 4692, 4692, 4696, 4696, 4696, 4696, 4699, 4699, 4699, 4699, 4706, 4706, 4706, 4710, 4710, 4710, 4710, 4717, 4717, 4717, 4717, 4721, 4721, 4721, 4721, 4724, 4724, 4724, 4724, 4731, 4731, 4731, 4735, 4735, 4735, 4735, 4742, 4742, 4742, 4742, 4746, 4746, 4746, 4746, 4749, 4749, 4749, 4749, 4756, 4756, 4756, 4756, 4760, 4760, 4760, 4760, 4767, 4767, 4767, 4767, 4771, 4771, 4771, 4771, 4774, 4774, 4774, 4774, 4781, 4781, 4781, 4785, 4785, 4785, 4785, 4789, 4789, 4789, 4789, 4796, 4796, 4796, 4796, 4799, 4799, 4799, 4799, 4807, 4807, 4807, 4807, 4810, 4810, 4810, 4810, 4810, 4814, 4814, 4814, 4814, 4821, 4821, 4821, 4821, 4824, 4824, 4824, 4824, 4828, 4828, 4828, 4828, 4835, 4835, 4835, 4835, 4839, 4839, 4839, 4839, 4842, 4842, 4842, 4842, 4846, 4846, 4846, 4846, 4849, 4849, 4849, 4849, 4849, 4857, 4857, 4857, 4857, 4860, 4860, 4860, 4860, 4867, 4867, 4867, 4867, 4871, 4871, 4871, 4871, 4875, 4875, 4875, 4875, 4875, 4882, 4882, 4882, 4882, 4885, 4885, 4885, 4885, 4889, 4889, 4889, 4889, 4892, 4892, 4892, 4892, 4892, 4900, 4900, 4900, 4900, 4903, 4903, 4903, 4903, 4907, 4907, 4907, 4907, 4907, 4910, 4910, 4910, 4910, 4914, 4914, 4914, 4914, 4921, 4921, 4921, 4921, 4921, 4925, 4925, 4925, 4925, 4935, 4935, 4935, 4935, 4935, 4935, 4935, 4935, 4935, 4939, 4939, 4939, 4939, 4939, 4943, 4943, 4943, 4943, 4953, 4953, 4953, 4953, 4953, 4953, 4953, 4953, 4953, 4957, 4957, 4957, 4957, 4957, 4960, 4960, 4960, 4960, 4964, 4964, 4964, 4964, 4964, 4975, 4975, 4975, 4975, 4975, 4975, 4975, 4975, 4975, 4978, 4978, 4978, 4978, 4982, 4982, 4982, 4982, 4982, 4986, 4986, 4986, 4986, 4986, 4989, 4989, 4989, 4989, 4996, 4996, 4996, 4996, 4996, 5000, 5000, 5000, 5000, 5003, 5003, 5003, 5003, 5003, 5007, 5007, 5007, 5007, 5007, 5011, 5011, 5011, 5011, 5011, 5014, 5014, 5014, 5014, 5021, 5021, 5021, 5021, 5021, 5025, 5025, 5025, 5025, 5025, 5032, 5032, 5032, 5032, 5032, 5036, 5036, 5036, 5036, 5039, 5039, 5039, 5039, 5039, 5043, 5043, 5043, 5043, 5043, 5046, 5046, 5046, 5046, 5046, 5050, 5050, 5050, 5050, 5050, 5054, 5054, 5054, 5054, 5054, 5057, 5057, 5057, 5057, 5057, 5061, 5061, 5061, 5061, 5064, 5064, 5064, 5064, 5064, 5072, 5072, 5072, 5072, 5072, 5075, 5075, 5075, 5075, 5075, 5079, 5079, 5079, 5079, 5079, 5082, 5082, 5082, 5082, 5082, 5086, 5086, 5086, 5086, 5086, 5089, 5089, 5089, 5089, 5089, 5093, 5093, 5093, 5093, 5093, 5097, 5097, 5097, 5097, 5097, 5104, 5104, 5104, 5104, 5104, 5104, 5107, 5107, 5107, 5107, 5107, 5111, 5111, 5111, 5111, 5111, 5114, 5114, 5114, 5114, 5114, 5118, 5118, 5118, 5118, 5118, 5122, 5122, 5122, 5122, 5122, 5125, 5125, 5125, 5125, 5125, 5129, 5129, 5129, 5129, 5129, 5129, 5132, 5132, 5132, 5132, 5132, 5140, 5140, 5140, 5140, 5140, 5143, 5143, 5143, 5143, 5143, 5147, 5147, 5147, 5147, 5147, 5147, 5150, 5150, 5150, 5150, 5150, 5154, 5154, 5154, 5154, 5154, 5157, 5157, 5157, 5157, 5157, 5157, 5161, 5161, 5161, 5161, 5161, 5165, 5165, 5165, 5165, 5165, 5168, 5168, 5168, 5168, 5168, 5168, 5172, 5172, 5172, 5172, 5172, 5175, 5175, 5175, 5175, 5175, 5175, 5186, 5186, 5186, 5186, 5186, 5190, 5190, 5190, 5190, 5190, 5193, 5193, 5193, 5193, 5193, 5193, 5197, 5197, 5197, 5197, 5197, 5200, 5200, 5200, 5200, 5200, 5200, 5200, 5200, 5200, 5200, 5200, 5200, 5208, 5208, 5208, 5208, 5208, 5208, 5208, 5208, 5208, 5208, 5208, 5211, 5211, 5211, 5211, 5211, 5215, 5215, 5215, 5215, 5215, 5215, 5218, 5218, 5218, 5218, 5218, 5218, 5222, 5222, 5222, 5222, 5222, 5226, 5226, 5226, 5226, 5226, 5226, 5229, 5229, 5229, 5229, 5229, 5229, 5233, 5233, 5233, 5233, 5233, 5236, 5236, 5236, 5236, 5236, 5236, 5240, 5240, 5240, 5240, 5240, 5240, 5243, 5243, 5243, 5243, 5243, 5243, 5247, 5247, 5247, 5247, 5247, 5251, 5251, 5251, 5251, 5251, 5251, 5254, 5254, 5254, 5254, 5254, 5254, 5258, 5258, 5258, 5258, 5258, 5258, 5261, 5261, 5261, 5261, 5261, 5261, 5265, 5265, 5265, 5265, 5265, 5265, 5265, 5265, 5265, 5265, 5265, 5265, 5265, 5265, 5265, 5265, 5265, 5269, 5269, 5269, 5269, 5269, 5269, 5272, 5272, 5272, 5272, 5272, 5272, 5276, 5276, 5276, 5276, 5276, 5276, 5279, 5279, 5279, 5279, 5279, 5279, 5283, 5283, 5283, 5283, 5283, 5283, 5290, 5290, 5290, 5290, 5290, 5290, 5290, 5290, 5290, 5290, 5290, 5290, 5297, 5297, 5297, 5297, 5297, 5297, 5297, 5301, 5301, 5301, 5301, 5301, 5301, 5304, 5304, 5304, 5304, 5304, 5304, 5308, 5308, 5308, 5308, 5308, 5308, 5312, 5312, 5312, 5312, 5312, 5312, 5315, 5315, 5315, 5315, 5315, 5315, 5319, 5319, 5319, 5319, 5319, 5319, 5319, 5322, 5322, 5322, 5322, 5322, 5322, 5326, 5326, 5326, 5326, 5326, 5326, 5329, 5329, 5329, 5329, 5329, 5329, 5333, 5333, 5333, 5333, 5333, 5333, 5333, 5337, 5337, 5337, 5337, 5337, 5337, 5337, 5337, 5337, 5337, 5337, 5337, 5340, 5340, 5340, 5340, 5340, 5340, 5340, 5344, 5344, 5344, 5344, 5344, 5344, 5347, 5347, 5347, 5347, 5347, 5347, 5347, 5351, 5351, 5351, 5351, 5351, 5351, 5354, 5354, 5354, 5354, 5354, 5354, 5354, 5358, 5358, 5358, 5358, 5358, 5358, 5362, 5362, 5362, 5362, 5362, 5362, 5362, 5365, 5365, 5365, 5365, 5365, 5365, 5365, 5365, 5365, 5365, 5365, 5365, 5365, 5369, 5369, 5369, 5369, 5369, 5369, 5372, 5372, 5372, 5372, 5372, 5372, 5372, 5376, 5376, 5376, 5376, 5376, 5376, 5380, 5380, 5380, 5380, 5380, 5380, 5380, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5387, 5394, 5394, 5394, 5394, 5394, 5394, 5394, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397, 5397};
