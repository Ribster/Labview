/*
 * stm32dev_screen_ssd1306.c
 *
 *  Created on: 27-jul.-2015
 *      Author: Robbe
 */
#include <stm32dev_screen_ssd1306.h>


static SSD1306_OLED_t ssd1306_parameters; // stores the local variables of the ssd1306
/* SPI handler declaration */


// local prototypes
	// first initialization routine
	static void
	ssd1306_firstInit(void);

	// set Reset Pin
	inline static void
	setRST(bool newVal);

	// set DC pin
	inline static void
	setDC(bool newVal);

	// set Chip Select pin
	inline static void
	setSS(bool newVal);

	// transmit a command to the ssd1306
	inline static void
	transmitCommand(uint8_t val);

	// transmit a byte to the ssd1306
	inline static void
	transmitByte(uint8_t val);

	// transmit data via DMA
	inline static void
	transmitSingleData(uint8_t data);

	// transmit data via DMA
	inline static void
	transmitMultipleData(uint32_t datasize, uint8_t* data);

	// alter a pixel on the ssd1306
	inline static void
	ssd1306_alterPixel(uint8_t x, uint8_t y, bool newVal);

	// alter a line on the ssd1306
	inline static void
	ssd1306_alterLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool newval);

	// alter a circle on the ssd1306
	inline static void
	ssd1306_alterCircle(uint8_t x0, uint8_t y0, uint16_t radius, bool newVal);

	// alter an area on the ssd1306
	inline static void
	ssd1306_alterArea(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool newval);

	// check if the coordinate is within writing range of the screen. If not, clip the value
	inline static xypair_t
	ssd1306_adjustCoordinate(uint8_t x, uint8_t y);

// local functions
	// first initialization routine
	static void
	ssd1306_firstInit(void){
		setRST(false);
		HAL_Delay(10);
		setRST(true);
		HAL_Delay(10);
		setDC(true);
		setSS(true);

		// Steps are taken from UG-2864HMBEG01 OLED screen.
		// Reference: http://www.sunrom.com/media/files/p/648/4199_Datasheet.pdf
		// Altered the steps to squeeze in existing functions from library

		/* STEP 1 */
			// display off
			transmitCommand(SSD1306_COMMANDS_BASE_DisplayOff_1of1);

		/* STEP 2 */
			// clock divide set
			transmitCommand(SSD1306_COMMANDS_TDCONF_SetDisplayClockDivide_1of2);
			transmitCommand(0x80); // suggested ratio

		/* STEP 3 */
			// set multiplex ratio
			transmitCommand(SSD1306_COMMANDS_HCONF_SetMultiplexRatio_1of2);
			transmitCommand(0x3F);

		/* STEP 4 */
			// set display offset
			transmitCommand(SSD1306_COMMANDS_HCONF_SetDisplayOffset_1of2);
			transmitCommand(0x00);

		/* STEP 5 */
			// Set display start line
			transmitCommand(SSD1306_COMMANDS_HCONF_SetDisplayStartLine_1of1);

		/* STEP 6 */
			// set chargepump
			transmitCommand(SSD1306_COMMANDS_CHRGPMP_SetChargepumpSetting_1of2);
			if(ssd1306_parameters.externalVCC == true){
				transmitCommand(0x10);
			} else {
				transmitCommand(0x14);
			}

				/* ORIENTATION FUNCTION TAKING OVER STEP 7, 8 && Added step */
				ssd1306_setOrientation(ssd1306_parameters.viewOrientation);

//				/* STEP 7 */
//					// segment remap
//					transmitCommand(SSD1306_COMMANDS_HCONF_SetSegmentReMapCol0AsSeg0_1of1);
//
//				/* STEP 8 */
//					// Com output from high to SEG0
//					transmitCommand(SSD1306_COMMANDS_HCONF_SetComDirectionNormal_1of1);
//
//				/* STEP NOT DESCRIBED */
//				// set memory mode
//					//	A[1:0] = 00b, Horizontal Addressing Mode
//					//	A[1:0] = 01b, Vertical Addressing Mode
//					//	A[1:0] = 10b, Page Addressing Mode (RESET)
//					//	A[1:0] = 11b, Invalid
//
//					transmitCommand(SSD1306_COMMANDS_ADDRESS_SetMemoryAddressingMode_1of2);
//					transmitCommand(0x01);

		/* STEP 9 */
			// set com pins
			transmitCommand(SSD1306_COMMANDS_HCONF_SetComPinsHardwareConfig_1of2);
			transmitCommand(0x12);

		/* STEP 10 */
			// set contrast
			transmitCommand(SSD1306_COMMANDS_BASE_Contrast_1of2);
			if(ssd1306_parameters.externalVCC == true){
				transmitCommand(0x9F);
			} else {
				transmitCommand(0xCF);
			}

		/* STEP 11 */
			// set precharge
			transmitCommand(SSD1306_COMMANDS_TDCONF_SetPrechargePeriod_1of2);
			if(ssd1306_parameters.externalVCC == true){
				transmitCommand(0x22);
			} else {
				transmitCommand(0xF1);
			}

		/* STEP 12 */
			// set VCOMH deselect level
			transmitCommand(SSD1306_COMMANDS_TDCONF_SetVCOMHDeselectLevel_1of2);
			transmitCommand(0x40);

		/* STEP 13 */
			// set on and use data in RAM
			transmitCommand(SSD1306_COMMANDS_BASE_DisplayOn_IgnoreRam_1of1);
			//transmitCommand(SSD1306_COMMANDS_BASE_DisplayOn_UseRam_1of1);

		/* STEP 14 */
			// set viewmode state
			ssd1306_setViewMode(ssd1306_parameters.viewMode);

		/* STEP 15 */
			memset(ssd1306_parameters.pixBuffer, 0, ssd1306_parameters.bufferSize);

		/* STEP 16 */
			transmitCommand(SSD1306_COMMANDS_BASE_DisplayOn_1of1);
	}

	// set Reset Pin
	inline static void
	setRST(bool newVal){
		HAL_GPIO_WritePin(ssd1306_parameters.pin_RST.GPIOx, ssd1306_parameters.pin_RST.config.Pin, (newVal)?(GPIO_PIN_SET):(GPIO_PIN_RESET));
	}

	// set DC pin
	inline static void
	setDC(bool newVal){
		HAL_GPIO_WritePin(ssd1306_parameters.pin_DC.GPIOx, ssd1306_parameters.pin_DC.config.Pin, (newVal)?(GPIO_PIN_SET):(GPIO_PIN_RESET));
	}

	// set Chip Select pin
	inline static void
	setSS(bool newVal){
		HAL_GPIO_WritePin(ssd1306_parameters.pin_SS.GPIOx, ssd1306_parameters.pin_SS.config.Pin, (newVal)?(GPIO_PIN_SET):(GPIO_PIN_RESET));
	}

	// transmit a command to the ssd1306
	inline static void
	transmitCommand(uint8_t val){
		setDC(false);
		transmitSingleData(val);
	}

	// transmit a byte to the ssd1306
	inline static void
	transmitByte(uint8_t val){
		transmitSingleData(val);
	}

	// transmit data via DMA
	inline static void
	transmitSingleData(uint8_t data){
		setSS(false);
		transmitMultipleData(1, &data);
		setSS(true);

	}

	// transmit data via DMA
	inline static void
	transmitMultipleData(uint32_t datasize, uint8_t* data){
	    /*##-2- Start the Full Duplex Communication process ########################*/
	    /* While the SPI in TransmitReceive process, user can transmit data through
	       "aTxBuffer" buffer & receive data through "aRxBuffer" */
	    HAL_SPI_Transmit_DMA(ssd1306_parameters.SpiHandler, (uint8_t*)data, datasize);

	    /*##-3- Wait for the end of the transfer ###################################*/
	    /*  Before starting a new communication transfer, you need to check the current
	        state of the peripheral; if it’s busy you need to wait for the end of current
	        transfer before starting a new one.
	        For simplicity reasons, this example is just waiting till the end of the
	        transfer, but application may perform other tasks while transfer operation
	        is ongoing. */
	    while (HAL_SPI_GetState(ssd1306_parameters.SpiHandler) != HAL_SPI_STATE_READY)
	    {
	    }
	}

	// alter a pixel on the ssd1306
	inline static void
	ssd1306_alterPixel(uint8_t x, uint8_t y, bool newVal){
		xypair_t tmp = ssd1306_getScreenDimensions();
		// not writing out of bounds
		if(x>=tmp.x || y>=tmp.y){ return; }

		if( (ssd1306_parameters.viewOrientation == SSD1306_ORIENTATION_LANDSCAPE_Normal) || (ssd1306_parameters.viewOrientation == SSD1306_ORIENTATION_LANDSCAPE_UpsideDown) ){
				// From 0,0 to 0,7; 1,0 to 1,7 .... From 127,0 to 127,7
				// From 0,8 to 0,15; 1,8 to 1,15 .... From 127,8 to 127,15
				// ...
				// From 0,55 to 0,63; 1,55 to 1,63 .... From 127,55 to 127,63
				if(newVal){
					ssd1306_parameters.pixBuffer[(x) + ( (y/8) * ssd1306_parameters.pixels_width)] |= (1<< (y%8) );
	//				printf("SET LANDSCAPE x: %d, y: %d ; byte: %d ; bit: %d \r\n", x, y, (x) + ( (y/8) * ssd1306_parameters.pixels_width), y%8);
	//				delay_milli(50);
				} else {
					ssd1306_parameters.pixBuffer[(x) + ( (y/8) * ssd1306_parameters.pixels_width)] &= ~(1<< (y%8) );
	//				printf("RESET LANDSCAPE x: %d, y: %d ; byte: %d ; bit: %d \r\n", x, y, (x) + ( (y/8) * ssd1306_parameters.pixels_width), y%8);
	//				delay_milli(50);
				}
		} else if ( (ssd1306_parameters.viewOrientation == SSD1306_ORIENTATION_PORTRAIT_CW) || (ssd1306_parameters.viewOrientation == SSD1306_ORIENTATION_PORTRAIT_CCW) ){
				// From 0,0 to 63,0
				// From 0,1 to 63,1
				// ...
				// From 0,127 to 63,127
				if(newVal){
					ssd1306_parameters.pixBuffer[(x/8) + y*ssd1306_parameters.pixels_height/8] |= (1<< (x%8) );
					//printf("SET PORTRAIT x: %d, y: %d ; byte: %d ; bit: %d \r\n", x, y, (x/8) + y*ssd1306_parameters.pixels_height/8, x%8);
					//delay_milli(50);
				} else {
					ssd1306_parameters.pixBuffer[(x/8) + y*ssd1306_parameters.pixels_height/8] &= ~(1<< (x%8) );
					//printf("RESET PORTRAIT x: %d, y: %d ; byte: %d ; bit: %d \r\n", x, y, (x/8) + y*ssd1306_parameters.pixels_height/8, x%8);
					//delay_milli(50);
				}
		}
	}


	// alter a line on the ssd1306
	inline static void
	ssd1306_alterLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool newval){
		xypair_t xy0, xy1; // input normalized parameters

		// normalize values
		xy0 = ssd1306_adjustCoordinate(x0, y0);
		xy1 = ssd1306_adjustCoordinate(x1, y1);
		// get the difference

		/* Bresenham's line algorithm */
			// Reference: http://rosettacode.org/wiki/Bitmap/Bresenham's_line_algorithm
			// Altered with the struct
			int dx = abs(xy1.x-xy0.x), sx = xy0.x<xy1.x ? 1 : -1;
			int dy = abs(xy1.y-xy0.y), sy = xy0.y<xy1.y ? 1 : -1;
			int err = (dx>dy ? dx : -dy)/2, e2;

			for(;;){
			ssd1306_alterPixel(xy0.x,xy0.y, newval);
			if (xy0.x==xy1.x && xy0.y==xy1.y) break;
			e2 = err;
			if (e2 >-dx) { err -= dy; xy0.x += sx; }
			if (e2 < dy) { err += dx; xy0.y += sy; }
			}
		/* Bresenham's line algorithm */
	}

	// alter a circle on the ssd1306
	inline static void
	ssd1306_alterCircle(uint8_t x0, uint8_t y0, uint16_t radius, bool newVal){
		// reference : http://en.wikipedia.org/wiki/Midpoint_circle_algorithm
		  int x = radius;
		  int y = 0;
		  int radiusError = 1-x;

		  while(x >= y)
		  {
		    ssd1306_alterPixel( x + x0,  y + y0, newVal);
		    ssd1306_alterPixel( y + x0,  x + y0, newVal);
		    ssd1306_alterPixel(-x + x0,  y + y0, newVal);
		    ssd1306_alterPixel(-y + x0,  x + y0, newVal);
		    ssd1306_alterPixel(-x + x0, -y + y0, newVal);
		    ssd1306_alterPixel(-y + x0, -x + y0, newVal);
		    ssd1306_alterPixel( x + x0, -y + y0, newVal);
		    ssd1306_alterPixel( y + x0, -x + y0, newVal);
		    y++;
		    if (radiusError<0)
		    {
		      radiusError += 2 * y + 1;
		    }
		    else
		    {
		      x--;
		      radiusError += 2 * (y - x) + 1;
		    }
		  }
	}

	// alter an area on the ssd1306
	inline static void
	ssd1306_alterArea(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool newval){
		uint8_t xMin = MIN(x0,x1), xMax = MAX(x0,x1);
		uint8_t yMin = MIN(y0,y1), yMax = MAX(y0,y1);

		for (uint8_t x = xMin; x <= xMax; ++x) {
			for (uint8_t y = yMin; y < yMax; ++y) {
				ssd1306_alterPixel(x,y,newval);
			}
		}
	}
	inline static xypair_t
	ssd1306_adjustCoordinate(uint8_t x, uint8_t y){
		xypair_t tmp;
		if( (ssd1306_parameters.viewOrientation == SSD1306_ORIENTATION_LANDSCAPE_Normal) || (ssd1306_parameters.viewOrientation == SSD1306_ORIENTATION_LANDSCAPE_UpsideDown) ){
			if (x>=ssd1306_parameters.pixels_width){
				x = ssd1306_parameters.pixels_width-1;
			}
			if (y>=ssd1306_parameters.pixels_height) {
				y = ssd1306_parameters.pixels_height-1;
			}

		} else if ( (ssd1306_parameters.viewOrientation == SSD1306_ORIENTATION_PORTRAIT_CW) || (ssd1306_parameters.viewOrientation == SSD1306_ORIENTATION_PORTRAIT_CCW) ){
			if (x>=ssd1306_parameters.pixels_height){
				x = ssd1306_parameters.pixels_height-1;
			}
			if (y>=ssd1306_parameters.pixels_width) {
				y = ssd1306_parameters.pixels_width-1;
			}
		}
		tmp.x = x;
		tmp.y = y;
		return tmp;
	}

// global functions
	void
	ssd1306_init(
			uint8_t pixelWidth,
			uint8_t pixelHeight,
			SSD1306_VIEWMODE_t viewMode,
			SSD1306_ORIENTATION_t viewOrientation,
			uint8_t* pixBuffer,
			bool externalVCC,
			SPI_HandleTypeDef* SpiHandler){

		// sanity check on input
		if(ssd1306_parameters.pin_SCK.initialized == false) return;
		if(ssd1306_parameters.pin_MOSI.initialized == false) return;
		if(ssd1306_parameters.pin_SS.initialized == false) return;
		if(ssd1306_parameters.pin_RST.initialized == false) return;
		if(ssd1306_parameters.pin_DC.initialized == false) return;

		// set the parameters of the OLED screen
		ssd1306_parameters.pixels_height = pixelHeight;
		ssd1306_parameters.pixels_width = pixelWidth;
		ssd1306_parameters.bufferSize = ((pixelHeight*pixelWidth)/8);
		ssd1306_parameters.viewMode = viewMode;
		ssd1306_parameters.viewOrientation = viewOrientation;
		ssd1306_parameters.pixBuffer = pixBuffer;
		ssd1306_parameters.externalVCC = externalVCC;
		ssd1306_parameters.SpiHandler = SpiHandler;


		HAL_GPIO_Init(ssd1306_parameters.pin_SCK.GPIOx, &ssd1306_parameters.pin_SCK.config);
		HAL_GPIO_Init(ssd1306_parameters.pin_MOSI.GPIOx, &ssd1306_parameters.pin_MOSI.config);
		HAL_GPIO_Init(ssd1306_parameters.pin_SS.GPIOx, &ssd1306_parameters.pin_SS.config);
		HAL_GPIO_Init(ssd1306_parameters.pin_DC.GPIOx, &ssd1306_parameters.pin_DC.config);
		HAL_GPIO_Init(ssd1306_parameters.pin_RST.GPIOx, &ssd1306_parameters.pin_RST.config);

		// initialize the SPI
		HAL_SPI_Init(SpiHandler);

		// initialize routine
		ssd1306_firstInit();

	}

	void ssd1306_initPin(
			SSD1306_pins_t SSD1306_pins,
			GPIO_TypeDef* GPIOx,
			uint32_t pin,
			uint32_t mode,
			uint32_t pull,
			uint32_t speed,
			uint32_t alternate){

		// make pinpointer
		stm32dev_gpio_pinHolder_t* pPin = NULL;

		// fill pin pointer
		switch(SSD1306_pins){
			case SSD1306_pins_SCK:
				pPin = &ssd1306_parameters.pin_SCK;
				break;
			case SSD1306_pins_MOSI:
				pPin = &ssd1306_parameters.pin_MOSI;
				break;
			case SSD1306_pins_SS:
				pPin = &ssd1306_parameters.pin_SS;
				break;
			case SSD1306_pins_DC:
				pPin = &ssd1306_parameters.pin_DC;
				break;
			case SSD1306_pins_RST:
				pPin = &ssd1306_parameters.pin_RST;
				break;
		}

		// sanity check pin pointer
		if(pPin == NULL) return;

		// assign values to pin struct
		stm32dev_gpio_setPinHolderGPIO(pPin, pin, mode, pull, speed, alternate);
		stm32dev_gpio_setPinHolder(pPin, false, 0, GPIOx);
	}
	// pixel buffer
	void
	ssd1306_transmitPixelBuffer(void){
		setDC(true);
		setSS(false);

/*		SPI_Cmd(OLED_SPI, DISABLE);

		ssd1306_initializeDMA();

		dma_enableSPIRequest(OLED_DMA_TX_DMAStream, OLED_SPI, OLED_DMA_TX_DMARequest);

		SPI_Cmd(OLED_SPI, ENABLE);

		while (DMA_GetFlagStatus(OLED_DMA_TX_DMAStream, OLED_DMA_TX_TransferCompleteFlag)==RESET);

		dma_disableSPIRequest(OLED_DMA_TX_DMAStream, OLED_SPI, OLED_DMA_TX_DMARequest);

		DMA_Cmd(OLED_DMA_TX_DMAStream, DISABLE);*/

		setSS(true);
	}
	// interrupt
	void
	ssd1306_interruptHandler(void){

	}
	// testfunctions
	void
	ssd1306_pixbufferTest(void){

	}
	void
	ssd1306_lineTest(void){

	}
	void
	ssd1306_circleTest(void){

	}
	void
	ssd1306_areaTest(void){

	}
	void
	ssd1306_stringTest(void){

	}
	// general settings
	void
	ssd1306_setOn(void){
		transmitCommand(SSD1306_COMMANDS_BASE_DisplayOn_1of1);
	}
	void
	ssd1306_setOff(void){
		transmitCommand(SSD1306_COMMANDS_BASE_DisplayOff_1of1);
	}
	void
	ssd1306_setOrientation(SSD1306_ORIENTATION_t newVal){
		if( newVal == SSD1306_ORIENTATION_PORTRAIT_CW ){
			transmitCommand(SSD1306_COMMANDS_HCONF_SetSegmentReMapCol0AsSeg0_1of1);
			transmitCommand(SSD1306_COMMANDS_HCONF_SetComDirectionNormal_1of1);
			transmitCommand(SSD1306_COMMANDS_ADDRESS_SetMemoryAddressingMode_1of2);
			transmitCommand(0x01);
		} else if ( newVal == SSD1306_ORIENTATION_PORTRAIT_CCW ){
			transmitCommand(SSD1306_COMMANDS_HCONF_SetSegmentReMapCol127AsSeg0_1of1);
			transmitCommand(SSD1306_COMMANDS_HCONF_SetComDirectionInverted_1of1);
			transmitCommand(SSD1306_COMMANDS_ADDRESS_SetMemoryAddressingMode_1of2);
			transmitCommand(0x01);
		} else if ( newVal == SSD1306_ORIENTATION_LANDSCAPE_Normal ){
			transmitCommand(SSD1306_COMMANDS_HCONF_SetSegmentReMapCol127AsSeg0_1of1);
			transmitCommand(SSD1306_COMMANDS_HCONF_SetComDirectionNormal_1of1);
			transmitCommand(SSD1306_COMMANDS_ADDRESS_SetMemoryAddressingMode_1of2);
			transmitCommand(0x00);
		} else if ( newVal == SSD1306_ORIENTATION_LANDSCAPE_UpsideDown ){
			transmitCommand(SSD1306_COMMANDS_HCONF_SetSegmentReMapCol0AsSeg0_1of1);
			transmitCommand(SSD1306_COMMANDS_HCONF_SetComDirectionInverted_1of1);
			transmitCommand(SSD1306_COMMANDS_ADDRESS_SetMemoryAddressingMode_1of2);
			transmitCommand(0x00);
		}
	}
	void
	ssd1306_setViewMode(SSD1306_VIEWMODE_t newVal){
		ssd1306_parameters.viewMode = newVal;
		if(newVal == SSD1306_VIEWMODE_NORMAL){
			transmitCommand(SSD1306_COMMANDS_BASE_SetNormal_1of1);
		} else if(newVal == SSD1306_VIEWMODE_INVERTED){
			transmitCommand(SSD1306_COMMANDS_BASE_SetInverse_1of1);
		}
	}
	xypair_t
	ssd1306_getScreenDimensions(void){
		xypair_t tmp;
		if( (ssd1306_parameters.viewOrientation == SSD1306_ORIENTATION_LANDSCAPE_Normal) || (ssd1306_parameters.viewOrientation == SSD1306_ORIENTATION_LANDSCAPE_UpsideDown) ){
			tmp.x = ssd1306_parameters.pixels_width;
			tmp.y = ssd1306_parameters.pixels_height;
		} else if ( (ssd1306_parameters.viewOrientation == SSD1306_ORIENTATION_PORTRAIT_CW) || (ssd1306_parameters.viewOrientation == SSD1306_ORIENTATION_PORTRAIT_CCW) ){
			tmp.x = ssd1306_parameters.pixels_height;
			tmp.y = ssd1306_parameters.pixels_width;
		}
		return tmp;
	}
	// pixels
	bool
	ssd1306_getPixel(uint8_t x, uint8_t y){
		return true;
	}
	void
	ssd1306_setPixel(uint8_t x, uint8_t y){
		ssd1306_alterPixel(x, y, true);
	}
	void
	ssd1306_clearPixel(uint8_t x, uint8_t y){
		ssd1306_alterPixel(x, y, false);
	}
	// whole screen
	void
	ssd1306_setScreen(void){
		memset(ssd1306_parameters.pixBuffer, 0xFF, ssd1306_parameters.bufferSize);
	}
	void
	ssd1306_clearScreen(void){
		memset(ssd1306_parameters.pixBuffer, 0x00, ssd1306_parameters.bufferSize);
	}
	// lines
	void
	ssd1306_setLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
		ssd1306_alterLine(x0,y0,x1,y1, true);
	}
	void
	ssd1306_clearLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
		ssd1306_alterLine(x0,y0,x1,y1, false);
	}
	// circles
	void
	ssd1306_setCircle(uint8_t x, uint8_t y, uint16_t radius){

	}
	void
	ssd1306_clearCircle(uint8_t x, uint8_t y, uint16_t radius){

	}
	// semi-circles
	void
	ssd1306_setSemiCircle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t radius){

	}
	void
	ssd1306_setSemiCircleOutline(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t radius){

	}
	// area's
	void
	ssd1306_setOutline(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
	}
	void
	ssd1306_setOutlineRounded(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t radius){

	}
	void
	ssd1306_setArea(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
		ssd1306_alterArea(x0, y0, x1, y1, true);
	}
	void
	ssd1306_clearArea(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
		ssd1306_alterArea(x0, y0, x1, y1, false);
	}
