/*
 * alt0065_A.h
 *
 *  Created on: 23-jul.-2015
 *      Author: Robbe
 */

#ifndef STM32DEV_BOARDS_ALT0065_A_H_
#define STM32DEV_BOARDS_ALT0065_A_H_

#if defined(stm32dev_alt0065_A)

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"


/**
 * @brief LED Types Definition
 */
typedef enum
{
  LED3 = 0,
  LED4 = 1,
  LED5 = 2,
  LED6 = 3,
  /* Color led aliases */
  LED_RED    = LED3,
  LED_ORANGE = LED4,
  LED_GREEN  = LED5,
  LED_BLUE   = LED6
}Led_TypeDef;


/**
 * @brief COM Types Definition
 */
typedef enum
{
  COM1 = 0
}COM_TypeDef;


/* LEDs
 *
 *
 */
#define LEDn                             4

#define LED3_PIN                         GPIO_PIN_3
#define LED3_GPIO_PORT                   GPIOB
#define LED3_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define LED3_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()

#define LED4_PIN                         GPIO_PIN_4
#define LED4_GPIO_PORT                   GPIOB
#define LED4_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define LED4_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()

#define LED5_PIN                         GPIO_PIN_5
#define LED5_GPIO_PORT                   GPIOB
#define LED5_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define LED5_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()

#define LED6_PIN                         GPIO_PIN_6
#define LED6_GPIO_PORT                   GPIOB
#define LED6_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define LED6_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()

#define LEDx_GPIO_CLK_ENABLE(__LED__) do { if((__LED__) == LED3) LED3_GPIO_CLK_ENABLE(); else \
                                           if((__LED__) == LED4) LED4_GPIO_CLK_ENABLE(); else \
                                           if((__LED__) == LED5) LED5_GPIO_CLK_ENABLE(); else \
                                           if((__LED__) == LED6) LED6_GPIO_CLK_ENABLE();} while(0)

#define LEDx_GPIO_CLK_DISABLE(__LED__)  (((__LED__) == LED3) ? LED3_GPIO_CLK_DISABLE() :\
                                         ((__LED__) == LED4) ? LED4_GPIO_CLK_DISABLE() :\
                                         ((__LED__) == LED5) ? LED5_GPIO_CLK_DISABLE() : \
                                         ((__LED__) == LED6) ? LED6_GPIO_CLK_DISABLE() : 0 )

/* COMMUNICATION - UART
 *
 *
 */
#define COMn                            1

/**
 * @brief Definition for COM port1, connected to USART2
 */
#define EVAL_COM1                       USART2
#define EVAL_COM1_CLK_ENABLE()          __HAL_RCC_USART2_CLK_ENABLE()
#define EVAL_COM1_CLK_DISABLE()         __HAL_RCC_USART2_CLK_DISABLE()
#define EVAL_COM1_FORCE_RESET()         __HAL_RCC_USART2_FORCE_RESET()
#define EVAL_COM1_RELEASE_RESET()       __HAL_RCC_USART2_RELEASE_RESET()

#define EVAL_COM1_TX_PIN                GPIO_PIN_2
#define EVAL_COM1_TX_GPIO_PORT          GPIOA
#define EVAL_COM1_TX_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define EVAL_COM1_TX_GPIO_CLK_DISABLE() __HAL_RCC_GPIOA_CLK_DISABLE()
#define EVAL_COM1_TX_AF                 GPIO_AF1_USART2

#define EVAL_COM1_RX_PIN                GPIO_PIN_3
#define EVAL_COM1_RX_GPIO_PORT          GPIOA
#define EVAL_COM1_RX_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define EVAL_COM1_RX_GPIO_CLK_DISABLE() __HAL_RCC_GPIOA_CLK_DISABLE()
#define EVAL_COM1_RX_AF                 GPIO_AF1_USART2

#define EVAL_COM1_IRQn                  USART2_IRQn

#define COMx_CLK_ENABLE(__COM__)        do { if((__COM__) == COM1) EVAL_COM1_CLK_ENABLE();} while(0)
#define COMx_CLK_DISABLE(__COM__)       (((__COM__) == COM1) ? EVAL_COM1_CLK_DISABLE() : 0)

#define COMx_TX_GPIO_CLK_ENABLE(__COM__) do { if((__COM__) == COM1) EVAL_COM1_TX_GPIO_CLK_ENABLE();} while(0)
#define COMx_TX_GPIO_CLK_DISABLE(__COM__) (((__COM__) == COM1) ? EVAL_COM1_TX_GPIO_CLK_DISABLE() : 0)

#define COMx_RX_GPIO_CLK_ENABLE(__COM__) do { if((__COM__) == COM1) EVAL_COM1_RX_GPIO_CLK_ENABLE();} while(0)
#define COMx_RX_GPIO_CLK_DISABLE(__COM__) (((__COM__) == COM1) ? EVAL_COM1_RX_GPIO_CLK_DISABLE() : 0)



/* function prototypes
 *
 *
 */
void     BSP_LED_Init(Led_TypeDef Led);
void     BSP_LED_On(Led_TypeDef Led);
void     BSP_LED_Off(Led_TypeDef Led);
void     BSP_LED_Toggle(Led_TypeDef Led);

#if defined(HAL_UART_MODULE_ENABLED)
void              BSP_COM_Init(COM_TypeDef COM, UART_HandleTypeDef* huart);
#endif /* HAL_UART_MODULE_ENABLED */

#endif // #if defined(stm32dev_alt0065_A)


#endif /* STM32DEV_BOARDS_ALT0065_A_H_ */
