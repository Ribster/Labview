/*
 * stm32dev_rcc.c
 *
 *  Created on: 23-jul.-2015
 *      Author: Robbe Van Assche
 */
#include "stm32dev_rcc_f4.h"

void stm32dev_rcc_enableClock(GPIO_TypeDef* gpioBank){
	// ENABLE CLOCK

	if(gpioBank == GPIOA){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	} else if(gpioBank == GPIOB){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	} else if(gpioBank == GPIOC){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	} else if(gpioBank == GPIOD){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	} else if(gpioBank == GPIOE){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	} else if(gpioBank == GPIOF){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
	} else if(gpioBank == GPIOG){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	} else if(gpioBank == GPIOH){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
	} else if(gpioBank == GPIOI){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
	}
#ifdef GPIOJ
	else if(gpioBank == GPIOJ){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;
	}
#endif
#ifdef GPIOK
	else if(gpioBank == GPIOK){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;
	}
#endif

}

void stm32dev_rcc_disableClock(GPIO_TypeDef* gpioBank){
	if(gpioBank == GPIOA){
		RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOAEN);
	} else if(gpioBank == GPIOB){
		RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOBEN);
	} else if(gpioBank == GPIOC){
		RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOCEN);
	} else if(gpioBank == GPIOD){
		RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIODEN);
	} else if(gpioBank == GPIOE){
		RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOEEN);
	} else if(gpioBank == GPIOF){
		RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOFEN);
	} else if(gpioBank == GPIOG){
		RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOGEN);
	} else if(gpioBank == GPIOH){
		RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOHEN);
	} else if(gpioBank == GPIOI){
		RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOIEN);
	}
#ifdef GPIOJ
	else if(gpioBank == GPIOJ){
		RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOJEN);
	}
#endif
#ifdef GPIOK
	else if(gpioBank == GPIOK){
		RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOKEN);
	}
#endif
}

void stm32dev_rcc_setClock(GPIO_TypeDef* gpioBank, bool newVal){
	if(newVal){
		stm32dev_rcc_enableClock(gpioBank);
	} else {
		stm32dev_rcc_disableClock(gpioBank);
	}
}

void stm32dev_rcc_setClockPWR(bool newVal){
	if(newVal){
		RCC->APB1ENR |= (1<<28);
	} else {
		RCC->APB1ENR &= ~(1<<28);
	}
}

void stm32dev_rcc_setRTCClockEnabled(bool newVal){
	if(newVal){
		RCC->BDCR |= (1<<15);
	} else {
		RCC->BDCR &= ~(1<<15);
	}
}

void stm32dev_rcc_setRTCClock(stm32dev_rcc_RTCClock_list newVal){
	uint32_t temp = RCC->BDCR;
	temp &= ~(0x3 << 8);
	temp |= (newVal << 8);

	// force backup register reset
	/* RTC Clock selection can be changed only if the Backup Domain is reset */
	stm32dev_rcc_setBackupDomainReset(true);
	stm32dev_rcc_setBackupDomainReset(false);

	RCC->BDCR = temp;
}

void stm32dev_rcc_setRTCLSEBypass(bool newVal){
	if(newVal){
		RCC->BDCR |= (1<<2);
	} else {
		RCC->BDCR &= ~(1<<2);
	}
}

void stm32dev_rcc_setRTCLSEEnabled(bool newVal){
	if(newVal){
		RCC->BDCR |= (1<<0);
	} else {
		RCC->BDCR &= ~(1<<0);
	}
}

void stm32dev_rcc_setRTCLSIEnabled(bool newVal){
	if(newVal){
		RCC->CSR |= (1<<0);
	} else {
		RCC->CSR &= ~(1<<0);
	}
}

void stm32dev_rcc_setBackupDomainReset(bool newVal){
	if(newVal){
		RCC->BDCR |= (1<<16);
	} else {
		RCC->BDCR &= ~(1<<16);
	}
}

bool stm32dev_rcc_getRTCClockEnabled(void){
	return ((RCC->BDCR & (1<<15)) == (1<<15));
}

stm32dev_rcc_RTCClock_list stm32dev_rcc_getRTCClock(void){
	uint32_t temp = (RCC->BDCR >> 8);
	return (stm32dev_rcc_RTCClock_list)(temp & 0x3);
}

bool stm32dev_rcc_getRTCLSEBypassed(void){
	return ((RCC->BDCR & (1<<2)) == (1<<2));
}

bool stm32dev_rcc_getRTCLSEReady(void){
	return ((RCC->BDCR & (1<<1)) == (1<<1));
}

bool stm32dev_rcc_getRTCLSEEnabled(void){
	return ((RCC->BDCR & (1<<0)) == (1<<0));
}

bool stm32dev_rcc_getRTCLSIReady(void){
	return ((RCC->CSR & (1<<1)) == (1<<1));
}

bool stm32dev_rcc_getRTCLSIEnabled(void){
	return ((RCC->CSR & (1<<0)) == (1<<0));
}

bool stm32dev_rcc_getBackupDomainReset(void){
	return ((RCC->BDCR & (1<<16)) == (1<<16));
}

bool stm32dev_rcc_getClockPWR(void){
	return ((RCC->APB1ENR & (1<<28)) == (1<<28));
}

uint32_t stm32dev_rcc_getSystemClock(void){
	SystemCoreClockUpdate();
	return SystemCoreClock;
}

uint32_t stm32dev_rcc_getPCLK1Clock(void){
	return 0;
}
uint32_t stm32dev_rcc_getPCLK2Clock(void){
	return 0;
}
