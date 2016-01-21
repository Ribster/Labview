/*
 * stm32dev_general.c
 *
 *  Created on: 26-jul.-2015
 *      Author: Robbe
 */

#include "stm32dev_general.h"
#include <stdint.h>
#include <string.h>

void
stm32dev_general_convertToCapital(char* str){
	for(uint8_t tmp_iterator=0; tmp_iterator<strlen(str); tmp_iterator++){
		if( (str[tmp_iterator] <= 'z') || (str[tmp_iterator] >= 'a') ){
			str[tmp_iterator] += ('A' - 'a');
		}
	}
}
// convert base 2 to base 10 ASCII
char*
stm32dev_general_getDec(uint64_t dec){
	  static char str[16];
	  char *s = str + sizeof(str);
	  *--s = 0;
	  do
	  {
	    *--s = '0' + (char)(dec % 10);
	    dec /= 10;
	  }
	  while(dec);
	  return(s);
}
char*
stm32dev_general_getDecSigned(int64_t dec){
	  static char str[16];
	  char *s = str + sizeof(str);
	  // convert 2's complement to unsigned
	  uint64_t b;
	  if(dec <= -1){
		  b = (~dec)+1;
	  } else {
		  b = dec;
	  }
	  *--s = 0;
	  do
	  {
	    *--s = '0' + (char)(b % 10);
	    b /= 10;
	  }
	  while(b);
	  if(dec <= -1){
		  // negative
		  *--s = '-';
	  }
	  return(s);
}

uint32_t
stm32dev_general_getDecfromBCD(uint32_t bcd){
	uint32_t retVal = 0;
	for(uint8_t i=0; i<8; i++){
		retVal += ((bcd >> (i*4)) & 0xF) * pow(10,i);
	}
	return retVal;
}

uint32_t
stm32dev_general_getBCDfromDec(uint16_t dec){
	return (dec) ? ((stm32dev_general_getBCDfromDec( dec / 10 ) << 4) + (dec % 10)) : 0;
}

