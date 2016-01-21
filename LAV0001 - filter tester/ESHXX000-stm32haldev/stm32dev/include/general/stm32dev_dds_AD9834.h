/*
 * AD9834.h
 *
 *  Created on: 5-okt.-2015
 *      Author: Robbe
 */

#ifndef STM32DEV_INCLUDE_GENERAL_AD9834_H_
#define STM32DEV_INCLUDE_GENERAL_AD9834_H_

#include "stm32dev_boards.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>

// PINS FROM IC
/*
ANALOG SIGNAL AND REFERENCE
1			FS ADJUST		Full-Scale Adjust Control. A resistor (RSET) is connected between this pin and AGND. This determines the magnitude of the full-scale DAC current. The relationship between RSET and the full-scale current is as follows: IOUT FULL SCALE = 18 × FSADJUST/RSET FSADJUST = 1.15 V nominal, RSET = 6.8 kΩ typical.
2			REFOUT			Voltage Reference Output. The AD9834 has an internal 1.20 V reference that is made available at this pin.
3			COMP			DAC Bias Pin. This pin is used for decoupling the DAC bias voltage.
17			VIN				Input to Comparator. The comparator can be used to generate a square wave from the sinusoidal DAC output. The DAC output should be filtered appropriately before being applied to the comparator to improve jitter. When Bit OPBITEN and Bit SIGN/PIB in the control register are set to 1, the comparator input is connected to VIN.
19,20		IOUT, IOUTB		Current Output. This is a high impedance current source. A load resistor of nominally 200 Ω should be connected between IOUT and AGND. IOUTB should preferably be tied through an external load resistor of 200 Ω to AGND, but it can be tied directly to AGND. A 20 pF capacitor to AGND is also recommended to prevent clock feedthrough.

POWER SUPPLY
4			AVDD			Positive Power Supply for the Analog Section. AVDD can have a value from 2.3 V to 5.5 V. A 0.1 μF decoupling capacitor should be connected between AVDD and AGND.
5			DVDD			Positive Power Supply for the Digital Section. DVDD can have a value from 2.3 V to 5.5 V. A 0.1 μF decoupling capacitor should be connected between DVDD and DGND.
6			CAP/2V5			The digital circuitry operates from a 2.5 V power supply. This 2.5 V is generated from DVDD using an on-board regulator (when DVDD exceeds 2.7 V). The regulator requires a decoupling capacitor of typically 100 nF that is connected from CAP/2.5 V to DGND. If DVDD is equal to or less than 2.7 V, CAP/2.5 V should be shorted to DVDD.
7			DGND			Digital Ground.
18			AGND			Analog Ground.

DIGITAL INTERFACE AND CONTROL
8			MCLK			Digital Clock Input. DDS output frequencies are expressed as a binary fraction of the frequency of MCLK. The output frequency accuracy and phase noise are determined by this clock.
9			FSELECT			Frequency Select Input. FSELECT controls which frequency register, FREQ0 or FREQ1, is used in the phase accumulator. The frequency register to be used can be selected using Pin FSELECT or Bit FSEL. When Bit FSEL is used to select the frequency register, the FSELECT pin should be tied to CMOS high or low.
10			PSELECT			Phase Select Input. PSELECT controls which phase register, PHASE0 or PHASE1, is added to the phase accumulator output. The phase register to be used can be selected using Pin PSELECT or Bit PSEL. When the phase registers are being controlled by Bit PSEL, the PSELECT pin should be tied to CMOS high or low.

-------------------
11			RESET			Active High Digital Input. RESET resets appropriate internal registers to zero; this corresponds to an analog output of midscale. RESET does not affect any of the addressable registers.
12			SLEEP			Active High Digital Input. When this pin is high, the DAC is powered down. This pin has the same function as Control Bit SLEEP12.
13			SDATA			Serial Data Input. The 16-bit serial data-word is applied to this input.
14			SCLK			Serial Clock Input. Data is clocked into the AD9834 on each falling SCLK edge.
15			FSYNC			Active Low Control Input. This is the frame synchronization signal for the input data. When FSYNC is taken low, the internal logic is informed that a new word is being loaded into the device.
-------------------

16			SIGN BIT OUT	Logic Output. The comparator output is available on this pin or, alternatively, the MSB from the NCO can be output on this pin. Setting Bit OPBITEN in the control register to 1 enables this output pin. Bit SIGN/PIB determines whether the comparator output or the MSB from the NCO is output on the pin.
*/

/*	WRITEPREFIXES	*/
typedef enum ad9834_registers_prefix_list{
	ad9834_registers_prefix_command 		=	(0x00<<14),
	ad9834_registers_prefix_FREQ0 			=	(0x01<<14),
	ad9834_registers_prefix_FREQ1 			=	(0x02<<14),
	ad9834_registers_prefix_PHASE0			 =	(0x06<<13),
	ad9834_registers_prefix_PHASE1			 =	(0x07<<13)
}ad9834_registers_prefix_list;

typedef enum ad9834_registers_control_list{
	ad9834_registers_control_B28			=	13,		// 1 for 28bit in 2 writes, 0 for 1 write 14bit (HLB)
	ad9834_registers_control_HLB			=	12,		// 1 for 14bit MSBs, 0 for 14bit LSBs
	ad9834_registers_control_FSEL			=	11,		// 0 -> FREQ0, 1 -> FREQ1
	ad9834_registers_control_PSEL			=	10,		// 0 -> PHASE0, 1-> PHASE1
	ad9834_registers_control_PINSW			=	9,		// set to 0 for software - 1 for hardware
	ad9834_registers_control_RESET			=	8,		// 1 for reset, 0 for disable reset
	ad9834_registers_control_SLEEP1			=	7,		// 1 internal MCLK is disabled DAC stays at it's present value
	ad9834_registers_control_SLEEP12		=	6,		// 1 power down the on-chip DAC
	ad9834_registers_control_OPBITEN		=	5,		// 1 enables the SIGN BIT OUT pin
	ad9834_registers_control_SIGNPIB		=	4,		// 1 comparator, 0 direct MSB or MSB/2 data
	ad9834_registers_control_DIV2			=	3,		// 1 no divide, 0 divide by 2
	ad9834_registers_control_MODE			=	1		// 1 SIN rom is bypassed (triangle), 0 sinus output
}ad9834_registers_control_list;

/*	RESET STATES	*/
#define AD9834_RESETSTATE_DATA 		false
#define AD9834_RESETSTATE_CLOCK 	false
#define AD9834_RESETSTATE_SS 		true

/*	CONSTANTS	*/
#define AD9834_NUMBEROFBITS	28

/*	INITIALIZATIONS	*/
void ad9834_initialize(void);
void ad9834_deinitialize(void);

void ad9834_initPin_data(GPIO_TypeDef* bank_data, uint8_t pin_data);
void ad9834_initPin_clock(GPIO_TypeDef* bank_clock, uint8_t pin_clock);
void ad9834_initPin_ss(GPIO_TypeDef* bank_ss, uint8_t pin_ss);

void ad9834_deinitPin_data();
void ad9834_deinitPin_clock();
void ad9834_deinitPin_ss();

/*	COMMUNICATION LAYER	*/
void ad9834_sendBuffer(uint8_t size);
void ad9834_sendData(uint16_t* pdata);
void ad9834_sendPacket(uint16_t data);
void ad9834_sendControlRegister(void);
void ad9834_sendFrequency(ad9834_registers_prefix_list freqSelection);
void ad9834_sendPhase(ad9834_registers_prefix_list phaseSelection);
void ad9834_sendReset(void);
void ad9834_sendSleep1(bool newVal);
void ad9834_sendSleep12(bool newVal);
void ad9834_sendSIGNBITEN(bool newVal);
void ad9834_sendTriangle(bool newVal);

/*	CONTROL LAYER	*/
void ad9834_setControlBit(ad9834_registers_control_list bitSelection, bool newValue);

void ad9834_setFrequency(ad9834_registers_prefix_list freqSelection, uint64_t frequency);
void ad9834_setPhase(ad9834_registers_prefix_list phaseSelection, float phase);

/*	APPLICATION LAYER	*/
uint64_t ad9834_getBaseClock(void);
void ad9834_setBaseClock(uint64_t newVal);
uint64_t ad9834_getMaxClock(void);
void ad9834_setMaxClock(uint64_t newVal);


#endif /* STM32DEV_INCLUDE_GENERAL_AD9834_H_ */
