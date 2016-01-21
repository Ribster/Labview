/*
 * AD9851.h
 *
 *  Created on: 5-okt.-2015
 *      Author: Robbe
 */

#ifndef STM32DEV_INCLUDE_GENERAL_AD9851_H_
#define STM32DEV_INCLUDE_GENERAL_AD9851_H_

// PINS FROM IC
/*PIN NO 				MNEMONIC 		DESCRIPTION
4 to 1, 28 to 25 	D0 to D7		8-Bit Data Input. This is the 8-bit data port for iteratively loading the 32-bit frequency and the 8-bit phase/ control word. D7 = MSB; D0 = LSB. D7 (Pin 25) also serves as the input pin for the 40-bit serial data-word.
5 					PGND			6x REFCLK Multiplier Ground Connection.
6					PVCC			6x REFCLK Multiplier Positive Supply Voltage Pin.
7					W_CLK			Word Load Clock. Rising edge loads the parallel or serial frequency/phase/control words asynchronously into the 40-bit input register.
8 					FQ_UD			Frequency Update. A rising edge asynchronously transfers the contents of the 40-bit input register to be acted upon by the DDS core. FQ_UD should be issued when the contents of the input register are known to contain only valid, allowable data.
9 					REFCLOCK		Reference Clock Input. CMOS/TTL-level pulse train, direct or via the 6x REFCLK Multiplier. In direct mode, this is also the SYSTEM CLOCK. If the 6 REFCLK Multiplier is engaged, then the output of the multiplier is the SYSTEM CLOCK. The rising edge of the SYSTEM CLOCK initiates operations.
10,19				AGND			Analog Ground.The ground return for the analog circuitry (DAC and Comparator).
11,18				AVDD 			Positive supply voltage for analog circuitry (DAC and Comparator, Pin 18) and bandgap voltage reference, Pin 11.
12					RSET 			The DAC’s external RSET connection—nominally a 3.92 kohm resistor to ground for 10 mA out.This sets the DAC full-scale output current available from IOUT and IOUTB. RSET = 39.93/IOUT.
13					VOUTN			Voltage Output Negative.The comparator’s complementary CMOS logic level output.
14					VOUTP			Voltage Output Positive.The comparator’s true CMOS logic level output.
15					VINN			Voltage Input Negative.The comparator’s inverting input.
16 					VINP			Voltage Input Positive.The comparator’s noninverting input.
17					DACBP			DAC Bypass Connection.This is the DAC voltage reference bypass connection normally NC (NO CONNECT) for optimum SFDR performance.
20 					IOUTB			The complementary DAC output with same characteristics as IOUT except that IOUTB = (full-scale output–IOUT). Output load should equal that of IOUT for best SFDR performance.
21					IOUT 			The true output of the balanced DAC. Current is sourcing and requires current-to-voltage conversion, usually a resistor or transformer referenced to GND. IOUT = (full-scale output–IOUTB).
22					RESET 			Master Reset pin; active high; clears DDS accumulator and phase offset register to achieve 0 Hz and 0° output phase. Sets programming to parallel mode and disengages the 6x REFCLK Multiplier. Reset does not clear the 40-bit input register. On power-up, asserting RESET should be the first priority before pro- gramming commences.
23					DVDD			Positive supply voltage pin for digital circuitry.
24 					DGND			Digital Ground.The ground return pin for the digital circuitry.*/


#endif /* STM32DEV_INCLUDE_GENERAL_AD9851_H_ */
