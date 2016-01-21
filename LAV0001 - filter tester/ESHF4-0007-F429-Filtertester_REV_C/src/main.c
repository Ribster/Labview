/**
  ******************************************************************************
  * @file    GPIO/GPIO_EXTI/Src/main.c 
  * @author  MCD Application Team
  * @version V1.2.2
  * @date    01-July-2015
  * @brief   This example describes how to configure and use GPIOs through 
  *          the STM32F4xx HAL API.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup GPIO_EXTI
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t aShowTime[50] = {0};
uint8_t aShowDate[50] = {0};
/* RTC handler declaration */
RTC_HandleTypeDef RtcHandle;
UART_HandleTypeDef UartHandle;
/* ADC handler declaration */
ADC_HandleTypeDef    AdcHandle1;
ADC_ChannelConfTypeDef sADCConfig1;
ADC_ChannelConfTypeDef sADCConfig2;
DAC_HandleTypeDef    DacHandle;
static DAC_ChannelConfTypeDef sDACConfig;
uint8_t channelSampling = 0;
volatile bool channelSamplingEnabled = false;

/* Variable used to get converted value */
__IO uint16_t uhADCxConvertedValue1 = 0;
__IO uint16_t uhADCxConvertedValue1_highest = 0;
__IO uint16_t uhADCxConvertedValue2 = 0;
__IO uint16_t uhADCxConvertedValue2_highest = 0;
volatile uint16_t uhADCxConvertedValueVREFINT_highest = 0;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);
static void EXTILine0_Config(void);
volatile uint8_t app_enable;

void uart_transmit(char* str);
void uart_transmitLen(char* str, int len);
void uart_transmitDec(uint32_t dec);

static void RTC_CalendarConfig(void);
static void RTC_CalendarShow(uint8_t* showtime, uint8_t* showdate);

volatile bool doSweep = false;
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)

{
 /* This sample code shows how to use STM32F4xx GPIO HAL API to toggle PD12, PD13,
    PD14, and PD14 IOs (connected to LED4, LED3, LED5 and LED6 on STM32F401C-DISCO board (MB1115B)) 
    in an infinite loop.
    To proceed, 3 steps are required: */

  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
     */
	app_enable = ~(~0);

  HAL_Init();

  /* Configure the system clock to 168 MHz */
  SystemClock_Config();

  /* Configure LED3, LED4, LED5 and LED6 */
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED5);
  BSP_LED_Init(LED6);
  BSP_LED_Init(LED7);
  
  /* Configure EXTI Line0 (connected to PA0 pin) in interrupt mode */
  EXTILine0_Config();




  /*##-1- Configure the UART peripheral ######################################*/
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART1 configured as follow:
      - Word Length = 8 Bits
      - Stop Bit = One Stop bit
      - Parity = None
      - BaudRate = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */
  UartHandle.Instance          = EVAL_COM1;

  UartHandle.Init.BaudRate     = 230400;
  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits     = UART_STOPBITS_1;
  UartHandle.Init.Parity       = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode         = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    Error_Handler();
  }

    uart_transmit("Testing UART @ 230400 baud\r\n");


    /*##-1- Configure the RTC peripheral #######################################*/
    RtcHandle.Instance = RTC;

    /* Configure RTC prescaler and RTC data registers */
    /* RTC configured as follow:
        - Hour Format    = Format 24
        - Asynch Prediv  = Value according to source clock
        - Synch Prediv   = Value according to source clock
        - OutPut         = Output Disable
        - OutPutPolarity = High Polarity
        - OutPutType     = Open Drain */
    RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
    RtcHandle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
    RtcHandle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
    RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
    RtcHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    RtcHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

    if(HAL_RTC_Init(&RtcHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler();
    }



    /*##-2- Check if Data stored in BackUp register0: No Need to reconfigure RTC#*/
    /* Read the BackUp Register 0 Data */
    if(HAL_RTCEx_BKUPRead(&RtcHandle, RTC_BKP_DR0) != 0x32F2)
    {
      /* Configure RTC Calendar */
      RTC_CalendarConfig();
    }
    else
    {
    	RTC_CalendarConfig();
      /* Check if the Power On Reset flag is set */
      if(__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST) != RESET)
      {
        /* Power on reset occured: Turn LED2 on */
    	  uart_transmit("[RTC]\tPower on reset flag is set\r\n");
      }
      /* Check if Pin Reset flag is set */
      if(__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST) != RESET)
      {
        /* External reset occured: Turn LED4 on */
    	  uart_transmit("[RTC]\tPin reset flag is set\r\n");
      }

      /* Clear Reset Flag */
      __HAL_RCC_CLEAR_RESET_FLAGS();
    }


    uart_transmit("[INIT]\tRTC initialized\r\n");







    /*	INITIALIZE THE APPLICATION	*/
    application_init();





    uart_transmit("[USB]\tInit: ");
    /* Init Device Library */
    uart_transmitDec(USBD_Init(&USBD_Device, &VCP_Desc, 0));
    uart_transmit("\r\n");

    /* Add Supported Class */
    uart_transmit("[USB]\tClass register: ");
    uart_transmitDec(USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS));
    uart_transmit("\r\n");

    /* Add CDC Interface Class */
    uart_transmit("[USB]\tInterface CDC: ");
    uart_transmitDec(USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops));
    uart_transmit("\r\n");

    /* Start Device Process */
    uart_transmit("[USB]\tStart Device: ");
    uart_transmitDec(USBD_Start(&USBD_Device));
    uart_transmit("\r\n");






    /*##-1- Configure the DAC peripheral #######################################*/
      DacHandle.Instance = DACx;

      if(HAL_DAC_Init(&DacHandle) != HAL_OK)
      {
        /* Initialization Error */
        Error_Handler();
      }

      /*##-2- Configure DAC channel1 #############################################*/
      sDACConfig.DAC_Trigger = DAC_TRIGGER_NONE;

      sDACConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;

      if(HAL_DAC_ConfigChannel(&DacHandle, &sDACConfig, DACx_CHANNEL1) != HAL_OK)
      {
        /* Channel configuration Error */
        Error_Handler();
      }
      if(HAL_DAC_ConfigChannel(&DacHandle, &sDACConfig, DACx_CHANNEL2) != HAL_OK)
      {
        /* Channel configuration Error */
        Error_Handler();
      }

      /*##-3- Set DAC Channel1 DHR register ######################################*/

      HAL_DAC_SetValue(&DacHandle, DACx_CHANNEL1, DAC_ALIGN_12B_R, 0x0);

      /*##-4- Enable DAC Channel1 ################################################*/
      if(HAL_DAC_Start(&DacHandle, DACx_CHANNEL1) != HAL_OK)
      {
        /* Start Error */
        Error_Handler();
      }

      HAL_DAC_SetValue(&DacHandle, DACx_CHANNEL2, DAC_ALIGN_12B_R, 0x0);

      /*##-4- Enable DAC Channel1 ################################################*/
      if(HAL_DAC_Start(&DacHandle, DACx_CHANNEL2) != HAL_OK)
      {
        /* Start Error */
        Error_Handler();
      }


      application_setDAC(1500, 1);
      application_setDAC(2500, 2);

      uart_transmit("[INIT]\tDAC initialized\r\n");






    // ADC
    /*##-1- Configure the ADC peripheral #######################################*/
    AdcHandle1.Instance          = ADCx1;

    AdcHandle1.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV2;
    AdcHandle1.Init.Resolution            = ADC_RESOLUTION_12B;
    AdcHandle1.Init.ScanConvMode          = DISABLE;
    AdcHandle1.Init.ContinuousConvMode    = ENABLE;
    AdcHandle1.Init.DiscontinuousConvMode = DISABLE;
    AdcHandle1.Init.NbrOfDiscConversion   = 0;
    AdcHandle1.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
    AdcHandle1.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;
    AdcHandle1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    AdcHandle1.Init.NbrOfConversion       = 1;
    AdcHandle1.Init.DMAContinuousRequests = ENABLE;
    AdcHandle1.Init.EOCSelection          = DISABLE;


    if(HAL_ADC_Init(&AdcHandle1) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler();
    }




	//application_getADC(1);
	//application_getADC(2);

    char buffer[150];
    snprintf(buffer, 150, "%d Channel 1\r\n", uhADCxConvertedValue1);
    uart_transmit(buffer);


    snprintf(buffer, 150, "%d Channel 2\r\n", uhADCxConvertedValue2);
    uart_transmit(buffer);





    uint32_t loopCounter = 1;

/*    for(int i=0; i<200; i++){
    	loopCounter *= (10);
    	snprintf(buffer, 150, "%ld\r\n", loopCounter);
    	uart_transmit(buffer);
    	application_sendUSBString(buffer);
    	HAL_Delay(50);
    	if(i%30 == 0){
    		loopCounter = 1;
    	}
    }*/


  /* Infinite loop */
  while (1)
  {
	    loopCounter++;

	    if(doSweep == true){
	    	BSP_LED_On(LED3);
	    	application_function_sampleAndSend();
	    	BSP_LED_Off(LED3);
	    	doSweep = false;
	    }

  }
}


void uart_transmit(char* str){
    if(HAL_UART_Transmit(&UartHandle, (uint8_t*)str, strlen(str), 50)!= HAL_OK)
    {
      Error_Handler();
    }
}

void uart_transmitLen(char* str, int len){
    if(HAL_UART_Transmit(&UartHandle, (uint8_t*)str, len, 50)!= HAL_OK)
    {
      Error_Handler();
    }
}

void uart_transmitDec(uint32_t dec){
	char* tmp = stm32dev_general_getDec(dec);

	uart_transmit(tmp);
}


/**
  * @brief  Configure the current time and date.
  * @param  None
  * @retval None
  */
static void RTC_CalendarConfig(void)
{
  RTC_DateTypeDef sdatestructure;
  RTC_TimeTypeDef stimestructure;

  /*##-1- Configure the Date #################################################*/
  /* Set Date: Tuesday February 18th 2014 */
  sdatestructure.Year = 0x15;
  sdatestructure.Month = RTC_MONTH_OCTOBER;
  sdatestructure.Date = 0x21;
  sdatestructure.WeekDay = RTC_WEEKDAY_WEDNESDAY;

  if(HAL_RTC_SetDate(&RtcHandle,&sdatestructure,RTC_FORMAT_BCD) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /*##-2- Configure the Time #################################################*/
  /* Set Time: 02:00:00 */
  stimestructure.Hours = 0x02;
  stimestructure.Minutes = 0x00;
  stimestructure.Seconds = 0x00;
  stimestructure.TimeFormat = RTC_HOURFORMAT12_AM;
  stimestructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  stimestructure.StoreOperation = RTC_STOREOPERATION_RESET;

  if(HAL_RTC_SetTime(&RtcHandle,&stimestructure,RTC_FORMAT_BCD) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /*##-3- Writes a data in a RTC Backup data Register0 #######################*/
  HAL_RTCEx_BKUPWrite(&RtcHandle,RTC_BKP_DR0,0x32F2);
}

/**
  * @brief  Display the current time and date.
  * @param  showtime : pointer to buffer
  * @param  showdate : pointer to buffer
  * @retval None
  */
static void RTC_CalendarShow(uint8_t* showtime, uint8_t* showdate)
{
  RTC_DateTypeDef sdatestructureget;
  RTC_TimeTypeDef stimestructureget;

  /* Get the RTC current Time */
  HAL_RTC_GetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);
  /* Display time Format : hh:mm:ss */
  sprintf((char*)showtime,"%02d:%02d:%02d",stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);
  /* Display date Format : mm-dd-yy */
  sprintf((char*)showdate,"%02d-%02d-%02d",sdatestructureget.Month, sdatestructureget.Date, 2000 + sdatestructureget.Year);
}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 168000000
  *            HCLK(Hz)                       = 168000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 336
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
	  RCC_ClkInitTypeDef RCC_ClkInitStruct;
	  RCC_OscInitTypeDef RCC_OscInitStruct;

	  // Enable Power Control clock
	  __PWR_CLK_ENABLE();

	  // The voltage scaling allows optimizing the power consumption when the
	  // device is clocked below the maximum system frequency, to update the
	  // voltage scaling value regarding system frequency refer to product
	  // datasheet.
	  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  // Enable HSE Oscillator and activate PLL with HSE as source
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

  // This assumes the HSE_VALUE is a multiple of 1MHz. If this is not
  // your case, you have to recompute these PLL constants.
  RCC_OscInitStruct.PLL.PLLM = (HSE_VALUE/1000000u);
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
  // clocks dividers
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
      | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

/**
  * @brief  Configures EXTI Line0 (connected to PA0 pin) in interrupt mode
  * @param  None
  * @retval None
  */
static void EXTILine0_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  KEY_BUTTON_GPIO_CLK_ENABLE();
  
  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Pin = KEY_BUTTON_PIN;
  HAL_GPIO_Init(KEY_BUTTON_GPIO_PORT, &GPIO_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(KEY_BUTTON_EXTI_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(KEY_BUTTON_EXTI_IRQn);
}

/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == KEY_BUTTON_PIN)
  {
	  app_enable = ~app_enable;
  }
}

/**
  * @brief  Conversion complete callback in non blocking mode
  * @param  AdcHandle : AdcHandle handle
  * @note   This example shows a simple way to report end of conversion, and
  *         you can add your own implementation.
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
	if(channelSamplingEnabled == true){
		if(channelSampling == 1){
			if(uhADCxConvertedValue1 > uhADCxConvertedValue1_highest) uhADCxConvertedValue1_highest = uhADCxConvertedValue1;
		} else if (channelSampling == 2){
			if(uhADCxConvertedValue1 > uhADCxConvertedValue2_highest) uhADCxConvertedValue2_highest = uhADCxConvertedValue1;
		} else if (channelSampling == 3){
			if(uhADCxConvertedValue1 > uhADCxConvertedValueVREFINT_highest) uhADCxConvertedValueVREFINT_highest = uhADCxConvertedValue1;
		}

		_application_adc_samples_count++;
		if( (channelSampling == 1) || (channelSampling == 2) ){
			if(_application_adc_samples_count > _application_adc_samples) {
				channelSamplingEnabled = false;
				application_stopADC();
			}
		} else {
			if(_application_adc_samples_count > 10) {
				channelSamplingEnabled = false;
				application_stopADC();
			}
		}



	}
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED5 on */
	uart_transmit("An error has occured \r\n");
  while(1)
  {
  }
}
