/*
 * stm32dev_general.h
 *
 *  Created on: 26-jul.-2015
 *      Author: Robbe
 */

#ifndef STM32DEV_INCLUDE_GENERAL_STM32DEV_GENERAL_H_
#define STM32DEV_INCLUDE_GENERAL_STM32DEV_GENERAL_H_

#include <stdio.h>
#include <math.h>

/*	Macro's																	*/
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

/*	Function prototypes														*/
void
stm32dev_general_convertToCapital(char* str);
char*
stm32dev_general_getDec(uint64_t dec);
char*
stm32dev_general_getDecSigned(int64_t dec);
uint32_t
stm32dev_general_getDecfromBCD(uint32_t bcd);
uint32_t
stm32dev_general_getBCDfromDec(uint16_t dec);

/*	Structures																*/
typedef struct xypair_t{
	uint8_t x;
	uint8_t y;
}xypair_t;

typedef struct xycorners_t{
	xypair_t topLeft;
	xypair_t topRight;
	xypair_t bottomLeft;
	xypair_t bottomRight;
}xycorners_t;

#endif /* STM32DEV_INCLUDE_GENERAL_STM32DEV_GENERAL_H_ */
