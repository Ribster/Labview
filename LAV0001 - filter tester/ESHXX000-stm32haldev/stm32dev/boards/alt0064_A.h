/*
 * alt0064_A.h
 *
 *  Created on: 23-jul.-2015
 *      Author: Robbe
 */

#ifndef STM32DEV_BOARDS_ALT0064_A_H_
#define STM32DEV_BOARDS_ALT0064_A_H_


#if defined(stm32dev_alt0064_A)

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/**
 * @brief LED Types Definition
 */
typedef enum
{
  LED3 = 0,
  /* Color led aliases */
  LED_GREEN  = LED3
}Led_TypeDef;

/**
 * @brief COM Types Definition
 */
typedef enum
{
  COM1 = 0
}COM_TypeDef;

#define LEDn                             1

#define LED3_PIN                         GPIO_PIN_0
#define LED3_GPIO_PORT                   GPIOF
#define LED3_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()
#define LED3_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOF_CLK_DISABLE()

#define LEDx_GPIO_CLK_ENABLE(__LED__)   do { if((__LED__) == LED3) LED3_GPIO_CLK_ENABLE();} while(0)

#define LEDx_GPIO_CLK_DISABLE(__LED__)  (((__LED__) == LED3) ? LED3_GPIO_CLK_DISABLE() : 0 )



void     BSP_LED_Init(Led_TypeDef Led);
void     BSP_LED_On(Led_TypeDef Led);
void     BSP_LED_Off(Led_TypeDef Led);
void     BSP_LED_Toggle(Led_TypeDef Led);



/* COMMUNICATION - UART
 *
 *
 */
#define COMn                            1

/**
 * @brief Definition for COM port1, connected to USART1
 */
#define EVAL_COM1                       USART1
#define EVAL_COM1_CLK_ENABLE()          __HAL_RCC_USART1_CLK_ENABLE()
#define EVAL_COM1_CLK_DISABLE()         __HAL_RCC_USART1_CLK_DISABLE()
#define EVAL_COM1_FORCE_RESET()         __HAL_RCC_USART1_FORCE_RESET()
#define EVAL_COM1_RELEASE_RESET()       __HAL_RCC_USART1_RELEASE_RESET()

#define EVAL_COM1_TX_PIN                GPIO_PIN_2
#define EVAL_COM1_TX_GPIO_PORT          GPIOA
#define EVAL_COM1_TX_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define EVAL_COM1_TX_GPIO_CLK_DISABLE() __HAL_RCC_GPIOA_CLK_DISABLE()
#define EVAL_COM1_TX_AF                 GPIO_AF1_USART1

#define EVAL_COM1_RX_PIN                GPIO_PIN_3
#define EVAL_COM1_RX_GPIO_PORT          GPIOA
#define EVAL_COM1_RX_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define EVAL_COM1_RX_GPIO_CLK_DISABLE() __HAL_RCC_GPIOA_CLK_DISABLE()
#define EVAL_COM1_RX_AF                 GPIO_AF1_USART1

#define EVAL_COM1_IRQn                  USART1_IRQn

#define COMx_CLK_ENABLE(__COM__)        do { if((__COM__) == COM1) EVAL_COM1_CLK_ENABLE();} while(0)
#define COMx_CLK_DISABLE(__COM__)       (((__COM__) == COM1) ? EVAL_COM1_CLK_DISABLE() : 0)

#define COMx_TX_GPIO_CLK_ENABLE(__COM__) do { if((__COM__) == COM1) EVAL_COM1_TX_GPIO_CLK_ENABLE();} while(0)
#define COMx_TX_GPIO_CLK_DISABLE(__COM__) (((__COM__) == COM1) ? EVAL_COM1_TX_GPIO_CLK_DISABLE() : 0)

#define COMx_RX_GPIO_CLK_ENABLE(__COM__) do { if((__COM__) == COM1) EVAL_COM1_RX_GPIO_CLK_ENABLE();} while(0)
#define COMx_RX_GPIO_CLK_DISABLE(__COM__) (((__COM__) == COM1) ? EVAL_COM1_RX_GPIO_CLK_DISABLE() : 0)


#if defined(HAL_UART_MODULE_ENABLED)
void              BSP_COM_Init(COM_TypeDef COM, UART_HandleTypeDef* huart);
#endif /* HAL_UART_MODULE_ENABLED */


#endif //#if defined(stm32dev_alt0064_A)




#endif /* STM32DEV_BOARDS_ALT0064_A_H_ */
