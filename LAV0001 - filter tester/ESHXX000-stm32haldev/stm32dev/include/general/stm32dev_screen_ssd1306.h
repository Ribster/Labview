/*
 * stm32dev_screen_ssd1306.h
 *
 *  Created on: 27-jul.-2015
 *      Author: Robbe
 */


#ifndef STM32HALDEV_STM32DEV_INCLUDE_GENERAL_STM32DEV_SCREEN_SSD1306_H_
#define STM32HALDEV_STM32DEV_INCLUDE_GENERAL_STM32DEV_SCREEN_SSD1306_H_

// GCC libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>




/**
 * Check which device we are working on
 */
#if !defined(stm32dev_F0) && !defined(stm32dev_F1) && !defined(stm32dev_F2) && !defined(stm32dev_F3) && !defined(stm32dev_F4) && !defined(stm32dev_F7) && !defined(stm32dev_L0) && !defined(stm32dev_L1)
#include "stm32dev_devicelib.h"
#endif


#include "stm32dev_general.h"

/**
 * include the STM32F4 HAL libraries
 */
#if defined(stm32dev_F4)
	#include "stm32f4xx_hal_dma.h"
	#include "stm32f4xx_hal_spi.h"
	#include "stm32f4xx_hal_gpio.h"
	#include "stm32f4xx_hal_rcc.h"
#endif

#ifdef stm32dev_F4
	// stm32dev libs
	#include "stm32dev_gpio_f4.h"
	#include "stm32dev_spi_f4.h"
	#include "stm32dev_dma_f4.h"
#endif

#if defined(stm32dev_F0)
#include "stm32f0xx_hal_dma.h"
#include "stm32f0xx_hal_spi.h"
#include "stm32f0xx_hal_gpio.h"
#include "stm32f0xx_hal_rcc.h"
#endif

#ifdef stm32dev_F0
	// stm32dev libs
	#include "stm32dev_gpio_f0.h"
	#include "stm32dev_spi_f0.h"
	#include "stm32dev_dma_f0.h"
	#include "stm32dev_rcc_f0.h"
#endif


typedef enum SSD1306_COMMANDS_e{
	// XXXX XXXX are masking bits
	// **** **** are don't care bits

	//	Fundamental Commands
		// 1st byte= Contrast command
		// 2nd byte= value XXXX XXXX
		SSD1306_COMMANDS_BASE_Contrast_1of2 = 0x81,
		// Output follows RAM content
		SSD1306_COMMANDS_BASE_DisplayOn_UseRam_1of1 = 0xA4,
		// Output ignores RAM content
		SSD1306_COMMANDS_BASE_DisplayOn_IgnoreRam_1of1 = 0xA5,
		// 0 in RAM, Off in Display
		SSD1306_COMMANDS_BASE_SetNormal_1of1 = 0xA6,
		// 1 in RAM, Off in Display
		SSD1306_COMMANDS_BASE_SetInverse_1of1 = 0xA7,
		SSD1306_COMMANDS_BASE_DisplayOff_1of1 = 0xAE,
		SSD1306_COMMANDS_BASE_DisplayOn_1of1 = 0xAF,

	//	Scrolling Commands
		// 1st byte= select right / left hor. scroll
		// 2nd byte= dummy byte 0x00
		// 3rd byte= define start page address ; **** *XXX
		// 4th byte= time between each scroll step; **** *XXX
		// 5th byte= end page address; **** *XXX
		// 6th byte= dummy byte; 0x00
		// 7th byte= dummy byte; 0xFF
			// Right Horizontal Scroll
			SSD1306_COMMANDS_SCROLL_RightHorizontalScroll_1of7 = 0x26,
			// Left Horizontal Scroll
			SSD1306_COMMANDS_SCROLL_LeftHorizontalScroll_1of7 = 0x27,
		// Continuous vertical & horizontal scroll setup
			SSD1306_COMMANDS_SCROLL_ContinuousVerticalAndRightScroll_1of6 = 0x29,
			SSD1306_COMMANDS_SCROLL_ContinuousVerticalAndLeftScroll_1of6 = 0x2A,
		// Deactivate Scroll
		SSD1306_COMMANDS_SCROLL_DeactivateScroll_1of1 = 0x2E,
		// Activate Scroll
		SSD1306_COMMANDS_SCROLL_ActivateScroll_1of1 = 0x2F,
		// Set Vertical Scroll Area
		SSD1306_COMMANDS_SCROLL_SetVerticalScrollArea_1of3 = 0xA3,

	//	Addressing Setting Commands
		// Set lower nibble of column start address for Page Addressing Mode; 0000 XXXX
		SSD1306_COMMANDS_ADDRESS_SetLowerColumnStartAddress_1of1 = 0x00,
		// Set higher nibble of column start address for Page Addressing Mode; 0001 XXXX
		SSD1306_COMMANDS_ADDRESS_SetHigherColumnStartAddress_1of1 = 0x10,
		// 1st byte: Set memory addressing mode
		// 2nd byte: **** **XX
			// 00: Horizontal
			// 01: Vertical
			// 10: Page Addressing Mode (RESET)
			// 11: Invalid
		SSD1306_COMMANDS_ADDRESS_SetMemoryAddressingMode_1of2 = 0x20,
		// 1st byte: Set column address
		// 2nd byte: Column start address; *XXX XXXX
		// 3rd byte: Column end address; *XXX XXXX
		SSD1306_COMMANDS_ADDRESS_SetColumnAddress_1of3 = 0x21,
		// 1st byte: Set page address
		// 2nd byte: Page start address; **** *XXX
		// 3rd byte: Page end address; **** *XXX
		SSD1306_COMMANDS_ADDRESS_SetPageAddress_1of3 = 0x22,
		// Set page start address for page addressing mode; 1011 0XXX
		SSD1306_COMMANDS_ADDRESS_SetPageStartAddress_1of1 = 0xB0,

	//	Hardware Configuration Commands	(Panel resolution && layout)
		// Set display start line; 01XX XXXX
		SSD1306_COMMANDS_HCONF_SetDisplayStartLine_1of1 = 0x40,
		// Set segment Re-map
		SSD1306_COMMANDS_HCONF_SetSegmentReMapCol0AsSeg0_1of1 = 0xA0,
		SSD1306_COMMANDS_HCONF_SetSegmentReMapCol127AsSeg0_1of1 = 0xA1,
		// 1st byte: Set Multiplex Ratio
		// 2nd byte: 16-64MUX
		SSD1306_COMMANDS_HCONF_SetMultiplexRatio_1of2 = 0xA8,
		// Set COM Output Scan Direction; 1100 *000
			// Normal Mode (RESET) scan from COM0 to COM[n-1]
			SSD1306_COMMANDS_HCONF_SetComDirectionNormal_1of1 = 0xC0,
			// Remapped mode. Rescan from COM[N-1] to COM0
			SSD1306_COMMANDS_HCONF_SetComDirectionInverted_1of1 = 0xC8,
		// 1st byte: Set Display Offset
		// 2nd byte: **XX XXXX vertical shift by COM from 0d~63d
		SSD1306_COMMANDS_HCONF_SetDisplayOffset_1of2 = 0xD3,
		// 1st byte: Set COM pins hardware config
		// 2nd byte: 00XX 0010
			//b4 == 0: sequential COM pin config
			//b4 == 1: alternative COM pin config
			//b5 == 0: disable COM left/right remap
			//b5 == 1: enable COM lef/right remap
		SSD1306_COMMANDS_HCONF_SetComPinsHardwareConfig_1of2 = 0xDA,

	//	Timing & Driving Scheme Settings
		// 1st byte: Set display clock divide ration / oscillator freq
		// 2nd byte: XXXX XXXX
			// [3:0] -> divide ratio -1
			// [7:4] -> Fosc
		SSD1306_COMMANDS_TDCONF_SetDisplayClockDivide_1of2 = 0xD5,
		// 1st byte: Set precharge period
		// 2nd byte: XXXX XXXX
			// [3:0] -> phase 1 period
			// [7:4] -> phase 2 period
		SSD1306_COMMANDS_TDCONF_SetPrechargePeriod_1of2 = 0xD9,
		// 1st byte: Set VCOMH deselect level
		// 2nd byte: 0XXX 0000
			// 000 -> 0.65 x VCC
			// 010 -> 0.77 x VCC (RESET)
			// 011 -> 0.83 x VCC
		SSD1306_COMMANDS_TDCONF_SetVCOMHDeselectLevel_1of2 = 0xDB,
		// 1st byte:
		SSD1306_COMMANDS_TDCONF_NOP_1of1 = 0xE3,

	//	Charge pump commands
		// Sequence:
			// 0x8D: charge pump setting
			// 0x14: enable charge pump
			// 0xAF: display ON
		// 1st byte: Charge pump setting
		// 2nd byte: **01 0X00
			// 0: disable charge pump (reset)
			// 1: enable charge pump during display on
		SSD1306_COMMANDS_CHRGPMP_SetChargepumpSetting_1of2 = 0x8D
} SSD1306_COMMANDS_t;

typedef enum SSD1306_VIEWMODE_t{
	SSD1306_VIEWMODE_INVERTED,
	SSD1306_VIEWMODE_NORMAL
} SSD1306_VIEWMODE_t;

typedef enum SSD1306_ORIENTATION_t{
	SSD1306_ORIENTATION_PORTRAIT_CW,
	SSD1306_ORIENTATION_PORTRAIT_CCW,
	SSD1306_ORIENTATION_LANDSCAPE_Normal,
	SSD1306_ORIENTATION_LANDSCAPE_UpsideDown
} SSD1306_ORIENTATION_t;

typedef struct SSD1306_OLED{
	uint8_t pixels_width;
	uint8_t pixels_height;
	uint32_t bufferSize;
	SSD1306_VIEWMODE_t viewMode;
	SSD1306_ORIENTATION_t viewOrientation;
	uint8_t* pixBuffer;
	bool externalVCC;
	SPI_HandleTypeDef* SpiHandler;
	stm32dev_gpio_pinHolder_t pin_SCK;
	stm32dev_gpio_pinHolder_t pin_MOSI;
	stm32dev_gpio_pinHolder_t pin_SS;
	stm32dev_gpio_pinHolder_t pin_DC;
	stm32dev_gpio_pinHolder_t pin_RST;
}SSD1306_OLED_t;

typedef enum SSD1306_pins_e{
	SSD1306_pins_SCK 		= 0,
	SSD1306_pins_MOSI 		= 1,
	SSD1306_pins_SS 		= 2,
	SSD1306_pins_DC 		= 3,
	SSD1306_pins_RST 		= 4
}SSD1306_pins_t;

// prototypes
	// initialization
	void
	ssd1306_init(
			uint8_t pixelWidth,
			uint8_t pixelHeigth,
			SSD1306_VIEWMODE_t viewMode,
			SSD1306_ORIENTATION_t viewOrientation,
			uint8_t* pixBuffer,
			bool externalVCC,
			SPI_HandleTypeDef* SpiHandler);
	void
	ssd1306_initPin(
			SSD1306_pins_t SSD1306_pins,
			GPIO_TypeDef* GPIOx,
			uint32_t pin,
			uint32_t mode,
			uint32_t pull,
			uint32_t speed,
			uint32_t alternate);
	// pixel buffer
	void
	ssd1306_transmitPixelBuffer(void);
	// interrupt
	void
	ssd1306_interruptHandler(void);
	// testfunctions
	void
	ssd1306_pixbufferTest(void);
	void
	ssd1306_lineTest(void);
	void
	ssd1306_circleTest(void);
	void
	ssd1306_areaTest(void);
	void
	ssd1306_stringTest(void);
	// general settings
	void
	ssd1306_setOn(void);
	void
	ssd1306_setOff(void);
	void
	ssd1306_setOrientation(SSD1306_ORIENTATION_t newVal);
	void
	ssd1306_setViewMode(SSD1306_VIEWMODE_t newVal);
	xypair_t
	ssd1306_getScreenDimensions(void);
	// pixels
	bool
	ssd1306_getPixel(uint8_t x, uint8_t y);
	void
	ssd1306_setPixel(uint8_t x, uint8_t y);
	void
	ssd1306_clearPixel(uint8_t x, uint8_t y);
	// whole screen
	void
	ssd1306_setScreen(void);
	void
	ssd1306_clearScreen(void);
	// lines
	void
	ssd1306_setLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
	void
	ssd1306_clearLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
	// circles
	void
	ssd1306_setCircle(uint8_t x, uint8_t y, uint16_t radius);
	void
	ssd1306_clearCircle(uint8_t x, uint8_t y, uint16_t radius);
	// semi-circles
	void
	ssd1306_setSemiCircle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t radius);
	void
	ssd1306_setSemiCircleOutline(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t radius);
	// area's
	void
	ssd1306_setOutline(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
	void
	ssd1306_setOutlineRounded(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t radius);
	void
	ssd1306_setArea(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
	void
	ssd1306_clearArea(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

#endif /* STM32HALDEV_STM32DEV_INCLUDE_GENERAL_STM32DEV_SCREEN_SSD1306_H_ */
