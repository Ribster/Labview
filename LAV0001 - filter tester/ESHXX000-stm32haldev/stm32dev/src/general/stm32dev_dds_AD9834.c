/*
 * AD9834.c
 *
 *  Created on: 5-okt.-2015
 *      Author: Robbe Van Assche
 */

#include "stm32dev_dds_AD9834.h"

// local pin settings
static GPIO_TypeDef* _bank_data;
static uint8_t _pin_data;
static bool _pin_data_init = false;

static GPIO_TypeDef* _bank_clock;
static uint8_t _pin_clock;
static bool _pin_clock_init = false;

static GPIO_TypeDef* _bank_ss;
static uint8_t _pin_ss;
static bool _pin_ss_init = false;

// local DDS configuration
uint64_t _ad9834_baseclock = 50000000;
uint64_t _ad9834_maxFrequency = 50000000;
uint64_t _ad9834_setclock[2] = {0,0};
float _ad9834_setphase[2] = {0.0,0.0};
static bool _ad9834_triangle = false;

// internal variables
static bool _ad9834_initialized = false;

static uint16_t _ad9834_sendbuffer[2] = {0x0000, 0x0000};
static uint16_t _ad9834_controlregister = 0x00;


// STATIC FUNCTIONS

// conversion routines for the conversion to register values
static uint32_t ad9834_getFREQRegisterValue(uint32_t frequency);
static uint32_t ad9834_getPHASRegisterValue(float phase);

// for altering the internal variables
static void ad9834_setBufferFrequency(ad9834_registers_prefix_list selection, uint32_t frequency);
static void ad9834_setBufferPhase(ad9834_registers_prefix_list selection, float phase);


void ad9834_initialize(void){
	// pins need to be initialized
	if(!_pin_data_init){
		return;
	}
	if(!_pin_clock_init){
		return;
	}
	if(!_pin_ss_init){
		return;
	}

	// set the DDS as initialized, if done later the control register will not be sent
	_ad9834_initialized = true;

	// clear the control register
	_ad9834_controlregister = 0x00;

	// do a reset
		// select the mode where the whole 28 bit register is written in 2 writes
	ad9834_setControlBit(ad9834_registers_control_B28, true);
		// set the chip in reset
	ad9834_setControlBit(ad9834_registers_control_RESET, true);
		// send the control register
	ad9834_sendControlRegister();

	// set frequency for bank 0
		// initialize the phase with the default value
	ad9834_setFrequency(ad9834_registers_prefix_FREQ0, _ad9834_setclock[0]);
		// send the frequency to the DDS
	ad9834_sendFrequency(ad9834_registers_prefix_FREQ0);

	// set phase for bank 0
		// initialize the phase with the default value
	ad9834_setPhase(ad9834_registers_prefix_PHASE0, _ad9834_setphase[0]);
		// send the phase to the DDS
	ad9834_sendPhase(ad9834_registers_prefix_PHASE0);

	// did not initialized the bank 1 parameter to the DDS

	// disable reset
	ad9834_setControlBit(ad9834_registers_control_RESET, false);
		// send control register
	ad9834_sendControlRegister();

	// this is the test pattern for the DDS according to the application note
/*	ad9834_sendPacket(0x2100);
	ad9834_sendPacket(0x50C7);
	ad9834_sendPacket(0x4000);
	ad9834_sendPacket(0xC000);
	ad9834_sendPacket(0x2000);*/

}

void ad9834_deinitialize(void){
	// deinitialize the DDS

	ad9834_deinitPin_clock();
	ad9834_deinitPin_data();
	ad9834_deinitPin_ss();

	_ad9834_initialized = false;
}

void ad9834_initPin_data(GPIO_TypeDef* bank_data, uint8_t pin_data){
	// initialize the data pin

	_bank_data = bank_data;
	_pin_data = pin_data;
	stm32dev_gpio_initPinOutputPP(_bank_data, _pin_data);
	// set to reset state
	stm32dev_gpio_setPinState(_bank_data, _pin_data, AD9834_RESETSTATE_DATA);
	_pin_data_init = true;
}

void ad9834_initPin_clock(GPIO_TypeDef* bank_clock, uint8_t pin_clock){
	// initialize the clock pin

	_bank_clock = bank_clock;
	_pin_clock = pin_clock;
	stm32dev_gpio_initPinOutputPP(_bank_clock, _pin_clock);
	// set to reset state
	stm32dev_gpio_setPinState(_bank_clock, _pin_clock, AD9834_RESETSTATE_CLOCK);
	_pin_clock_init = true;
}

void ad9834_initPin_ss(GPIO_TypeDef* bank_ss, uint8_t pin_ss){
	// initialize the chip select pin

	_bank_ss = bank_ss;
	_pin_ss = pin_ss;
	stm32dev_gpio_initPinOutputPP(_bank_ss, _pin_ss);
	// set to reset state
	stm32dev_gpio_setPinState(_bank_ss, _pin_ss, AD9834_RESETSTATE_SS);
	_pin_ss_init = true;
}

void ad9834_deinitPin_data(){
	// deinitialize an already initialized pin
	if(_pin_data_init){
		stm32dev_gpio_deinitPin(_bank_data, _pin_data);
		_pin_data_init = false;
	}
}
void ad9834_deinitPin_clock(){
	// deinitialize an already initialized pin
	if(_pin_clock_init){
		stm32dev_gpio_deinitPin(_bank_clock, _pin_clock);
		_pin_clock_init = false;
	}
}
void ad9834_deinitPin_ss(){
	// deinitialize an already initialized pin
	if(_pin_ss_init){
		stm32dev_gpio_deinitPin(_bank_ss, _pin_ss);
		_pin_ss_init = false;
	}
}

/*	COMMUNICATION LAYER	*/
void ad9834_sendBuffer(uint8_t size){
	// check if the DDS is initialized
	if(_ad9834_initialized){
		// send the first buffer
		ad9834_sendData(&_ad9834_sendbuffer[0]);
		if(size == 2){
			// send the second buffer
			ad9834_sendData(&_ad9834_sendbuffer[1]);
		}
	}
}

void ad9834_sendData(uint16_t* pdata){
	// set the clock high
	stm32dev_gpio_setPinState(_bank_clock, _pin_clock, true);

	// chip select low
	stm32dev_gpio_setPinState(_bank_ss, _pin_ss, false);

	// little delay
	HAL_Delay(1);

	// loop over the bits.
	// MSB first
	for(uint8_t i = 0; i<16; i++){
		stm32dev_gpio_setPinState(_bank_data, _pin_data, *pdata & (1<<(15-i)));
		stm32dev_gpio_setPinState(_bank_clock, _pin_clock, true);
		stm32dev_gpio_setPinState(_bank_clock, _pin_clock, false);
	}

	// chip select high
	stm32dev_gpio_setPinState(_bank_ss, _pin_ss, true);
}

void ad9834_sendPacket(uint16_t data){
	// wrapper function for taking a register address

	ad9834_sendData(&data);
}

void ad9834_sendControlRegister(void){
	// copy the control register buffer to the output buffer and start transmitting

	memcpy(_ad9834_sendbuffer, &_ad9834_controlregister, sizeof(uint16_t));
	ad9834_sendBuffer(1);
}

void ad9834_sendFrequency(ad9834_registers_prefix_list freqSelection){
	// load the buffer with the frequency values and transmit

	ad9834_sendControlRegister();
	if(freqSelection == ad9834_registers_prefix_FREQ0){
		// send the first frequency
		ad9834_setBufferFrequency(freqSelection, _ad9834_setclock[0]);
	} else {
		// send the second frequency
		ad9834_setBufferFrequency(ad9834_registers_prefix_FREQ1, _ad9834_setclock[1]);
	}
	ad9834_sendBuffer(2);
}

void ad9834_sendPhase(ad9834_registers_prefix_list phaseSelection){
	// load the buffer with the phase values and transmit

	ad9834_sendControlRegister();
	if(phaseSelection == ad9834_registers_prefix_PHASE0){
		// send the first frequency
		ad9834_setBufferPhase(phaseSelection, _ad9834_setphase[0]);
	} else {
		// send the second frequency
		ad9834_setBufferPhase(ad9834_registers_prefix_PHASE1, _ad9834_setphase[1]);
	}
	// push the data out
	ad9834_sendBuffer(1);
}

void ad9834_sendReset(void){
	// reset the DDS

	ad9834_setControlBit(ad9834_registers_control_RESET, true);
	ad9834_sendControlRegister();

	ad9834_setControlBit(ad9834_registers_control_RESET, false);
	ad9834_sendControlRegister();
}

void ad9834_sendSleep1(bool newVal){
	// Internal MCLK is disabled, DAC stays at the same value

	ad9834_setControlBit(ad9834_registers_control_SLEEP1, newVal);
	ad9834_sendControlRegister();
}

void ad9834_sendSleep12(bool newVal){
	// power down the on chip DAC

	ad9834_setControlBit(ad9834_registers_control_SLEEP12, newVal);
	ad9834_sendControlRegister();
}

void ad9834_sendSIGNBITEN(bool newVal){
	// set the DDS, if it is in sign enable mode, for the type of data on the sign bit out

	ad9834_setControlBit(ad9834_registers_control_OPBITEN, newVal);
	ad9834_sendControlRegister();
}

void ad9834_sendTriangle(bool newVal){
	// set the DDS for a triangle output

	ad9834_setControlBit(ad9834_registers_control_MODE, newVal);
	ad9834_sendControlRegister();
	_ad9834_triangle = newVal;
}

/*	CONTROL LAYER	*/
void ad9834_setControlBit(ad9834_registers_control_list bitSelection, bool newValue){
	// set specific bit of the local storage variable controlregister
	if(newValue){
		_ad9834_controlregister |= (1<<bitSelection);
	} else {
		_ad9834_controlregister &= ~(1<<bitSelection);
	}
}

static uint32_t ad9834_getFREQRegisterValue(uint32_t frequency){
	// convert the wanted frequency in register values.
	// first calculate the granularity and then multiply by the frequency

	uint64_t tempVal = (uint64_t)frequency * (uint64_t)0x10000000;
	uint32_t returnval = (tempVal / _ad9834_baseclock);

	return returnval;
}

static uint32_t ad9834_getPHASRegisterValue(float phase){
	// convert the phase variable to a register value

	if(phase>360){
		phase = 360;
	}
	uint32_t tempVal = phase * 0xFFF;
	return (tempVal / 360);
}

static void ad9834_setBufferFrequency(ad9834_registers_prefix_list selection, uint32_t frequency){
	// do not allow the application to go over the max frequency
	if(frequency > _ad9834_maxFrequency){
		return;
	}

	// get register value
	uint32_t registerVal = ad9834_getFREQRegisterValue(frequency);
	// set the prefix for the buffers
	_ad9834_sendbuffer[0] = selection;
	_ad9834_sendbuffer[1] = selection;
	// move data to the buffers
	_ad9834_sendbuffer[0] |= (registerVal & 0x3FFF);			// take the LSB's of 14-bit
	_ad9834_sendbuffer[1] |= ( (registerVal & 0xFFFC000) >> 14);	// take the MSB's of 14-bit
}

static void ad9834_setBufferPhase(ad9834_registers_prefix_list selection, float phase){
	// get register value
	uint32_t registerVal = ad9834_getPHASRegisterValue(phase);
	// set the prefix for the buffer
	_ad9834_sendbuffer[0] = selection;
	// move data to the buffer
	_ad9834_sendbuffer[0] |= (registerVal & 0xFFF);			// take the LSB's of 12-bit
}
void ad9834_setFrequency(ad9834_registers_prefix_list freqSelection, uint64_t frequency){
	// set the local storage variable with the frequency
	if(freqSelection == ad9834_registers_prefix_FREQ0){
		_ad9834_setclock[0] = frequency;
	} else {
		_ad9834_setclock[1] = frequency;
	}
}

void ad9834_setPhase(ad9834_registers_prefix_list phaseSelection, float phase){
	// set the local storage variable with the phase
	if(phaseSelection == ad9834_registers_prefix_PHASE0){
		_ad9834_setphase[0] = phase;
	} else {
		_ad9834_setphase[1] = phase;
	}
}

/*	APPLICATION LAYER	*/
uint64_t ad9834_getBaseClock(void){
	// getting the local variable base clock
	return _ad9834_baseclock;
}

void ad9834_setBaseClock(uint64_t newVal){
	// setting the local variable base clock
	_ad9834_baseclock = newVal;
}

uint64_t ad9834_getMaxClock(void){
	// getting the local variable max frequency
	return _ad9834_maxFrequency;
}

void ad9834_setMaxClock(uint64_t newVal){
	// setting the local variable max frequency
	_ad9834_maxFrequency = newVal;
}
