/*
 * globals.h
 *
 *  Created on: 2-okt.-2015
 *      Author: Robbe Van Assche
 */

#ifndef INCLUDE_GLOBALS_H_
#define INCLUDE_GLOBALS_H_

#include "stm32dev_boards.h"
#include "usbd_desc.h"
#include "cdc/usbd_cdc.h"
#include "usbd_cdc_interface.h"

// global variables
UART_HandleTypeDef UartHandle;
USBD_HandleTypeDef  USBD_Device;

// global function prototypes
int8_t CDC_Itf_Receive(uint8_t* pbuf, uint32_t *Len);
void CDC_Itf_Send(uint8_t* pbuf, uint32_t Len);


#endif /* INCLUDE_GLOBALS_H_ */
