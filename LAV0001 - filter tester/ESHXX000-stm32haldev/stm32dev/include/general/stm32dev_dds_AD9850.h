/*
 * AD9850.h
 *
 *  Created on: 5-okt.-2015
 *      Author: Robbe
 */

#ifndef STM32DEV_INCLUDE_GENERAL_AD9850_H_
#define STM32DEV_INCLUDE_GENERAL_AD9850_H_

// PINS FROM IC
/*
PIN NO				MNEMONIC		DESCRIPTION
4 to 1, 28 to 25 	D0 to D7		8-Bit Data Input. This is the 8-bit data port for iteratively loading the 32-bit frequency and the 8-bit phase/ control word. D7 = MSB; D0 = LSB. D7 (Pin 25) also serves as the input pin for the 40-bit serial data-word.
5, 24				DGND			Digital Ground. These are the ground return leads for the digital circuitry.
6, 23				DVDD			Supply Voltage Leads for Digital Circuitry.
7					W_CLK			Word Load Clock. This clock is used to load the parallel or serial frequency/phase/control words.
8					FQ_UD			Frequency Update. On the rising edge of this clock, the DDS updates to the frequency (or phase) loaded in the data input register; it then resets the pointer to Word 0.
9					CLKIN			Reference Clock Input. This may be a continuous CMOS-level pulse train or sine input biased at 1/2 V supply. The rising edge of this clock initiates operation.
10,19				AGND			Analog Ground. These leads are the ground return for the analog circuitry (DAC and comparator).
11,18				AVDD			Supply Voltage for the Analog Circuitry (DAC and Comparator).
12					RSET 			DAC’s External RSET Connection. This resistor value sets the DAC full-scale output current. For normal applications (FS IOUT = 10 mA), the value for RSET is 3.9 kΩ connected to ground. The RSET/IOUT relationship is IOUT = 32 (1.248 V/RSET).
13					QOUTB			Output Complement. This is the comparator’s complement output.
14					QOUT 			Output True. This is the comparator’s true output.
15					VINN			Inverting Voltage Input. This is the comparator’s negative input.
16					VINP			Noninverting Voltage Input. This is the comparator’s positive input.
17					DACBL (NC)		DAC Baseline. This is the DAC baseline voltage reference; this lead is internally bypassed and should normally be considered a no connect for optimum performance.
20					IOUTB			Complementary Analog Output of the DAC.
21					IOUT 			Analog Current Output of the DAC.
22					RESET 			Reset. This is the master reset function; when set high, it clears all registers (except the input register), and the DAC output goes to cosine 0 after additional clock cycles—see Figure 7.
*/


#endif /* STM32DEV_INCLUDE_GENERAL_AD9850_H_ */
