/*
 * alt0068_A.h
 *
 *  Created on: 23-jul.-2015
 *      Author: Robbe
 */

#ifndef STM32DEV_BOARDS_ALT0068_A_H_
#define STM32DEV_BOARDS_ALT0068_A_H_

#if defined(stm32dev_alt0068_A)

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

typedef enum
{
  LED4 = 0,
  LED3 = 1,
  LED5 = 2,
  LED6 = 3,
  LED7 = 4
} Led_TypeDef;


typedef enum
{
  BUTTON_KEY = 0,
} Button_TypeDef;

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;


/**
 * @brief COM Types Definition
 */
typedef enum
{
  COM1 = 0
}COM_TypeDef;



/** @addtogroup STM32F4_DISCOVERY_LOW_LEVEL_LED
  * @{
  */
#define LEDn                             5

#define LED4_PIN                         GPIO_PIN_12
#define LED4_GPIO_PORT                   GPIOD
#define LED4_GPIO_CLK_ENABLE()           __GPIOD_CLK_ENABLE()
#define LED4_GPIO_CLK_DISABLE()          __GPIOD_CLK_DISABLE()

#define LED3_PIN                         GPIO_PIN_13
#define LED3_GPIO_PORT                   GPIOD
#define LED3_GPIO_CLK_ENABLE()           __GPIOD_CLK_ENABLE()
#define LED3_GPIO_CLK_DISABLE()          __GPIOD_CLK_DISABLE()

#define LED5_PIN                         GPIO_PIN_14
#define LED5_GPIO_PORT                   GPIOD
#define LED5_GPIO_CLK_ENABLE()           __GPIOD_CLK_ENABLE()
#define LED5_GPIO_CLK_DISABLE()          __GPIOD_CLK_DISABLE()

#define LED6_PIN                         GPIO_PIN_15
#define LED6_GPIO_PORT                   GPIOD
#define LED6_GPIO_CLK_ENABLE()           __GPIOD_CLK_ENABLE()
#define LED6_GPIO_CLK_DISABLE()          __GPIOD_CLK_DISABLE()

#define LED7_PIN                         GPIO_PIN_11
#define LED7_GPIO_PORT                   GPIOD
#define LED7_GPIO_CLK_ENABLE()           __GPIOD_CLK_ENABLE()
#define LED7_GPIO_CLK_DISABLE()          __GPIOD_CLK_DISABLE()

#define LEDx_GPIO_CLK_ENABLE(__INDEX__) do{if((__INDEX__) == LED4) LED4_GPIO_CLK_ENABLE(); else \
                                           if((__INDEX__) == LED3) LED3_GPIO_CLK_ENABLE(); else \
                                           if((__INDEX__) == LED5) LED5_GPIO_CLK_ENABLE(); else \
                                           if((__INDEX__) == LED6) LED6_GPIO_CLK_ENABLE(); else \
                                           if((__INDEX__) == LED7) LED7_GPIO_CLK_ENABLE(); \
                                           }while(0)

#define LEDx_GPIO_CLK_DISABLE(__INDEX__) do{if((__INDEX__) == LED4) LED4_GPIO_CLK_DISABLE(); else \
                                            if((__INDEX__) == LED3) LED3_GPIO_CLK_DISABLE(); else \
                                            if((__INDEX__) == LED5) LED5_GPIO_CLK_DISABLE(); else \
                                            if((__INDEX__) == LED6) LED6_GPIO_CLK_DISABLE(); else \
                                            if((__INDEX__) == LED7) LED7_GPIO_CLK_DISABLE(); \
                                            }while(0)


/**
  * @}
  */

/** @addtogroup STM32F4_DISCOVERY_LOW_LEVEL_BUTTON
  * @{
  */
#define BUTTONn                          1

/**
 * @brief Wakeup push-button
 */
#define KEY_BUTTON_PIN                GPIO_PIN_10
#define KEY_BUTTON_GPIO_PORT          GPIOD
#define KEY_BUTTON_GPIO_CLK_ENABLE()  __GPIOD_CLK_ENABLE()
#define KEY_BUTTON_GPIO_CLK_DISABLE() __GPIOD_CLK_DISABLE()
#define KEY_BUTTON_EXTI_IRQn          EXTI15_10_IRQn

#define BUTTONx_GPIO_CLK_ENABLE(__INDEX__)    do{if((__INDEX__) == 0) KEY_BUTTON_GPIO_CLK_ENABLE(); \
                                                }while(0)

#define BUTTONx_GPIO_CLK_DISABLE(__INDEX__)    do{if((__INDEX__) == 0) KEY_BUTTON_GPIO_CLK_DISABLE(); \
                                                 }while(0)




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
#define EVAL_COM1_TX_AF                 GPIO_AF7_USART2

#define EVAL_COM1_RX_PIN                GPIO_PIN_3
#define EVAL_COM1_RX_GPIO_PORT          GPIOA
#define EVAL_COM1_RX_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define EVAL_COM1_RX_GPIO_CLK_DISABLE() __HAL_RCC_GPIOA_CLK_DISABLE()
#define EVAL_COM1_RX_AF                 GPIO_AF7_USART2

#define EVAL_COM1_IRQn                  USART2_IRQn

#define COMx_CLK_ENABLE(__COM__)        do { if((__COM__) == COM1) EVAL_COM1_CLK_ENABLE();} while(0)
#define COMx_CLK_DISABLE(__COM__)       (((__COM__) == COM1) ? EVAL_COM1_CLK_DISABLE() : 0)

#define COMx_TX_GPIO_CLK_ENABLE(__COM__) do { if((__COM__) == COM1) EVAL_COM1_TX_GPIO_CLK_ENABLE();} while(0)
#define COMx_TX_GPIO_CLK_DISABLE(__COM__) (((__COM__) == COM1) ? EVAL_COM1_TX_GPIO_CLK_DISABLE() : 0)

#define COMx_RX_GPIO_CLK_ENABLE(__COM__) do { if((__COM__) == COM1) EVAL_COM1_RX_GPIO_CLK_ENABLE();} while(0)
#define COMx_RX_GPIO_CLK_DISABLE(__COM__) (((__COM__) == COM1) ? EVAL_COM1_RX_GPIO_CLK_DISABLE() : 0)






void     BSP_LED_Init(Led_TypeDef Led);
void     BSP_LED_On(Led_TypeDef Led);
void     BSP_LED_Off(Led_TypeDef Led);
void     BSP_LED_Toggle(Led_TypeDef Led);
void     BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef Mode);
uint32_t BSP_PB_GetState(Button_TypeDef Button);


#if defined(HAL_UART_MODULE_ENABLED)
void              BSP_COM_Init(COM_TypeDef COM, UART_HandleTypeDef* huart);
#endif /* HAL_UART_MODULE_ENABLED */




#endif // #if defined(stm32dev_alt0068_A)




#endif /* STM32DEV_BOARDS_ALT0068_A_H_ */
