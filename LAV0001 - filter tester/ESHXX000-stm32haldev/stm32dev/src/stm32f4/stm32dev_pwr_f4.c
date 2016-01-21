/*
 * stm32dev_pwr_f4.c
 *
 *  Created on: 20-okt.-2015
 *      Author: Robbe Van Assche
 */

#include "stm32dev_pwr_f4.h"

bool stm32dev_pwr_getBackupProtectionEnabled(void){
	return ( (PWR->CR & 1<<8) == 1<<8 );
}

void stm32dev_pwr_setBackupProtectionEnabled(bool newVal){
	if(newVal){
		PWR->CR &= ~(1<<8);
	} else {
		PWR->CR |= (1<<8);
	}
}
