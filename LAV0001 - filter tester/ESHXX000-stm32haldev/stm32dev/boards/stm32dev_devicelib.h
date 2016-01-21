/*
 * stm32dev_devicelib.h
 *
 *  Created on: 26-jul.-2015
 *      Author: Robbe
 */

#ifndef STM32DEV_BOARDS_STM32DEV_DEVICELIB_H_
#define STM32DEV_BOARDS_STM32DEV_DEVICELIB_H_



/*	Device libraries 														*/

/* F0 ----
 *
 *
 */
#if !defined (STM32F030x6) && !defined (STM32F030x8) &&                           \
    !defined (STM32F031x6) && !defined (STM32F038xx) &&                           \
    !defined (STM32F042x6) && !defined (STM32F048xx) && !defined (STM32F070x6) && \
    !defined (STM32F051x8) && !defined (STM32F058xx) &&                           \
    !defined (STM32F071xB) && !defined (STM32F072xB) && !defined (STM32F078xx) && !defined (STM32F070xB) && \
    !defined (STM32F091xC) && !defined (STM32F098xx) && !defined (STM32F030xC)
  /* #define STM32F030x6 */  /*!< STM32F030x4, STM32F030x6 Devices (STM32F030xx microcontrollers where the Flash memory ranges between 16 and 32 Kbytes)              */
  /* #define STM32F030x8 */  /*!< STM32F030x8 Devices (STM32F030xx microcontrollers where the Flash memory is 64 Kbytes)                                              */
  /* #define STM32F031x6 */  /*!< STM32F031x4, STM32F031x6 Devices (STM32F031xx microcontrollers where the Flash memory ranges between 16 and 32 Kbytes)              */
  /* #define STM32F038xx */  /*!< STM32F038xx Devices (STM32F038xx microcontrollers where the Flash memory is 32 Kbytes)                                              */
  /* #define STM32F042x6 */  /*!< STM32F042x4, STM32F042x6 Devices (STM32F042xx microcontrollers where the Flash memory ranges between 16 and 32 Kbytes)              */
  /* #define STM32F048x6 */  /*!< STM32F048xx Devices (STM32F042xx microcontrollers where the Flash memory is 32 Kbytes)                                              */
  /* #define STM32F051x8 */  /*!< STM32F051x4, STM32F051x6, STM32F051x8 Devices (STM32F051xx microcontrollers where the Flash memory ranges between 16 and 64 Kbytes) */
  /* #define STM32F058xx */  /*!< STM32F058xx Devices (STM32F058xx microcontrollers where the Flash memory is 64 Kbytes)                                              */
  /* #define STM32F070x6 */  /*!< STM32F070x6 Devices (STM32F070x6 microcontrollers where the Flash memory ranges between 16 and 32 Kbytes)                           */
  /* #define STM32F070xB */  /*!< STM32F070xB Devices (STM32F070xB microcontrollers where the Flash memory ranges between 64 and 128 Kbytes)                          */
  /* #define STM32F071xB */  /*!< STM32F071x8, STM32F071xB Devices (STM32F071xx microcontrollers where the Flash memory ranges between 64 and 128 Kbytes)             */
  /* #define STM32F072xB */  /*!< STM32F072x8, STM32F072xB Devices (STM32F072xx microcontrollers where the Flash memory ranges between 64 and 128 Kbytes)             */
  /* #define STM32F078xx */  /*!< STM32F078xx Devices (STM32F078xx microcontrollers where the Flash memory is 128 Kbytes)                                             */
  /* #define STM32F030xC */  /*!< STM32F030xC Devices (STM32F030xC microcontrollers where the Flash memory is 256 Kbytes)                                             */
  /* #define STM32F091xC */  /*!< STM32F091xC Devices (STM32F091xx microcontrollers where the Flash memory is 256 Kbytes)                                             */
  /* #define STM32F098xx */  /*!< STM32F098xx Devices (STM32F098xx microcontrollers where the Flash memory is 256 Kbytes)                                             */
#else
	#include "stm32f0xx.h"
	#include "stm32f0xx_hal.h"
	#define stm32dev_F0
#endif

/* F1 ----
 *
 *
 */
#if !defined (STM32F100xB) && !defined (STM32F100xE) && !defined (STM32F101x6) && \
    !defined (STM32F101xB) && !defined (STM32F101xE) && !defined (STM32F101xG) && !defined (STM32F102x6) && !defined (STM32F102xB) && !defined (STM32F103x6) && \
    !defined (STM32F103xB) && !defined (STM32F103xE) && !defined (STM32F103xG) && !defined (STM32F105xC) && !defined (STM32F107xC)
  /* #define STM32F100xB  */   /*!< STM32F100C4, STM32F100R4, STM32F100C6, STM32F100R6, STM32F100C8, STM32F100R8, STM32F100V8, STM32F100CB, STM32F100RB and STM32F100VB */
  /* #define STM32F100xE */    /*!< STM32F100RC, STM32F100VC, STM32F100ZC, STM32F100RD, STM32F100VD, STM32F100ZD, STM32F100RE, STM32F100VE and STM32F100ZE */
  /* #define STM32F101x6  */   /*!< STM32F101C4, STM32F101R4, STM32F101T4, STM32F101C6, STM32F101R6 and STM32F101T6 Devices */
  /* #define STM32F101xB  */   /*!< STM32F101C8, STM32F101R8, STM32F101T8, STM32F101V8, STM32F101CB, STM32F101RB, STM32F101TB and STM32F101VB */
  /* #define STM32F101xE */    /*!< STM32F101RC, STM32F101VC, STM32F101ZC, STM32F101RD, STM32F101VD, STM32F101ZD, STM32F101RE, STM32F101VE and STM32F101ZE */
  /* #define STM32F101xG  */   /*!< STM32F101RF, STM32F101VF, STM32F101ZF, STM32F101RG, STM32F101VG and STM32F101ZG */
  /* #define STM32F102x6 */    /*!< STM32F102C4, STM32F102R4, STM32F102C6 and STM32F102R6 */
  /* #define STM32F102xB  */   /*!< STM32F102C8, STM32F102R8, STM32F102CB and STM32F102RB */
  /* #define STM32F103x6  */   /*!< STM32F103C4, STM32F103R4, STM32F103T4, STM32F103C6, STM32F103R6 and STM32F103T6 */
  /* #define STM32F103xB  */   /*!< STM32F103C8, STM32F103R8, STM32F103T8, STM32F103V8, STM32F103CB, STM32F103RB, STM32F103TB and STM32F103VB */
  /* #define STM32F103xE */    /*!< STM32F103RC, STM32F103VC, STM32F103ZC, STM32F103RD, STM32F103VD, STM32F103ZD, STM32F103RE, STM32F103VE and STM32F103ZE */
  /* #define STM32F103xG  */   /*!< STM32F103RF, STM32F103VF, STM32F103ZF, STM32F103RG, STM32F103VG and STM32F103ZG */
  /* #define STM32F105xC */    /*!< STM32F105R8, STM32F105V8, STM32F105RB, STM32F105VB, STM32F105RC and STM32F105VC */
  /* #define STM32F107xC  */   /*!< STM32F107RB, STM32F107VB, STM32F107RC and STM32F107VC */
#else
	#include "stm32f1xx.h"
	#include "stm32f1xx_hal.h"
	#define stm32dev_F1
#endif

/* F2 ----
 *
 *
 */
#if !defined (STM32F205xx) && !defined (STM32F215xx) && !defined (STM32F207xx) && !defined (STM32F217xx)

  /* #define STM32F205xx */   /*!< STM32Fxx    Devices */
  /* #define STM32F215xx */   /*!< STM32Fxx    Devices */
  /* #define STM32F207xx */   /*!< STM32Fxx    Devices */
  /* #define STM32F217xx */   /*!< STM32Fxx    Devices */
#else
	#include "stm32f2xx.h"
	#include "stm32f2xx_hal.h"
	#define stm32dev_F2
#endif


/* F3 ----
 *
 *
 */
#if !defined (STM32F301x8) && !defined (STM32F302x8) && !defined (STM32F318xx) && \
    !defined (STM32F302xC) && !defined (STM32F303xC) && !defined (STM32F358xx) && \
    !defined (STM32F303x8) && !defined (STM32F334x8) && !defined (STM32F328xx) && \
    !defined (STM32F302xE) && !defined (STM32F303xE) && !defined (STM32F398xx) && \
    !defined (STM32F373xC) && !defined (STM32F378xx)

  /* #define STM32F301x8 */   /*!< STM32F301K6, STM32F301K8, STM32F301C6, STM32F301C8,
                                   STM32F301R6 and STM32F301R8 Devices */
  /* #define STM32F302x8 */   /*!< STM32F302K6, STM32F302K8, STM32F302C6, STM32F302C8,
                                   STM32F302R6 and STM32F302R8 Devices */
  /* #define STM32F302xC */   /*!< STM32F302CB, STM32F302CC, STM32F302RB, STM32F302RC, STM32F302VB and STM32F302VC Devices */
  /* #define STM32F302xE */   /*!< STM32F302CE, STM32F302RE, and STM32F302VE Devices */
  /* #define STM32F303x8 */   /*!< STM32F303K6, STM32F303K8, STM32F303C6, STM32F303C8,
                                   STM32F303R6 and STM32F303R8 Devices */
  /* #define STM32F303xC */   /*!< STM32F303CB, STM32F303CC, STM32F303RB, STM32F303RC, STM32F303VB and STM32F303VC Devices */
  /* #define STM32F303xE */   /*!< STM32F303RE, STM32F303VE and STM32F303ZE Devices */
  /* #define STM32F373xC */   /*!< STM32F373C8, STM32F373CB, STM32F373CC, STM32F373R8, STM32F373RB, STM32F373RC,
                                   STM32F373V8, STM32F373VB and STM32F373VC Devices */
  /* #define STM32F334x8 */   /*!< STM32F334C4, STM32F334C6, STM32F334C8, STM32F334R4, STM32F334R6 and STM32F334R8 Devices */
  /* #define STM32F318xx */   /*!< STM32F318K8, STM32F318C8: STM32F301x8 with regulator off: STM32F318xx Devices */
  /* #define STM32F328xx */   /*!< STM32F328C8, STM32F328R8: STM32F334x8 with regulator off: STM32F328xx Devices */
  /* #define STM32F358xx */   /*!< STM32F358CC, STM32F358RC, STM32F358VC: STM32F303xC with regulator off: STM32F358xx Devices */
  /* #define STM32F378xx */   /*!< STM32F378CC, STM32F378RC, STM32F378VC: STM32F373xC with regulator off: STM32F378xx Devices */
  /* #define STM32F398xx */   /*!< STM32F398CE, STM32F398RE, STM32F398VE: STM32F303xE with regulator off: STM32F398xx Devices */
#else
	#include "stm32f3xx.h"
	#include "stm32f3xx_hal.h"
	#define stm32dev_F3
#endif


/* F4 ----
 *
 *
 */
#if !defined (STM32F405xx) && !defined (STM32F415xx) && !defined (STM32F407xx) && !defined (STM32F417xx) && \
    !defined (STM32F427xx) && !defined (STM32F437xx) && !defined (STM32F429xx) && !defined (STM32F439xx) && \
    !defined (STM32F401xC) && !defined (STM32F401xE) && !defined (STM32F411xE) && !defined (STM32F446xx)
  /* #define STM32F405xx */   /*!< STM32F405RG, STM32F405VG and STM32F405ZG Devices */
  /* #define STM32F415xx */   /*!< STM32F415RG, STM32F415VG and STM32F415ZG Devices */
  /* #define STM32F407xx */   /*!< STM32F407VG, STM32F407VE, STM32F407ZG, STM32F407ZE, STM32F407IG  and STM32F407IE Devices */
  /* #define STM32F417xx */   /*!< STM32F417VG, STM32F417VE, STM32F417ZG, STM32F417ZE, STM32F417IG and STM32F417IE Devices */
  /* #define STM32F427xx */   /*!< STM32F427VG, STM32F427VI, STM32F427ZG, STM32F427ZI, STM32F427IG and STM32F427II Devices */
  /* #define STM32F437xx */   /*!< STM32F437VG, STM32F437VI, STM32F437ZG, STM32F437ZI, STM32F437IG and STM32F437II Devices */
  /* #define STM32F429xx */   /*!< STM32F429VG, STM32F429VI, STM32F429ZG, STM32F429ZI, STM32F429BG, STM32F429BI, STM32F429NG,
                                   STM32F439NI, STM32F429IG  and STM32F429II Devices */
  /* #define STM32F439xx */   /*!< STM32F439VG, STM32F439VI, STM32F439ZG, STM32F439ZI, STM32F439BG, STM32F439BI, STM32F439NG,
                                   STM32F439NI, STM32F439IG and STM32F439II Devices */
  /* #define STM32F401xC */   /*!< STM32F401CB, STM32F401CC, STM32F401RB, STM32F401RC, STM32F401VB and STM32F401VC Devices */
  /* #define STM32F401xE */   /*!< STM32F401CD, STM32F401RD, STM32F401VD, STM32F401CE, STM32F401RE and STM32F401VE Devices */
  /* #define STM32F411xE */   /*!< STM32F411CD, STM32F411RD, STM32F411VD, STM32F411CE, STM32F411RE and STM32F411VE Devices */
  /* #define STM32F446xx */   /*!< STM32F446MC, STM32F446ME, STM32F446RC, STM32F446RE, STM32F446VC, STM32F446VE, STM32F446ZC,
                                   and STM32F446ZE Devices */
#else
	#include "stm32f4xx.h"
	#include "stm32f4xx_hal.h"
	#define stm32dev_F4
#endif


/* F7 ----
 *
 *
 */
#if !defined (STM32F756xx) && !defined (STM32F746xx) && !defined (STM32F745xx)
  /* #define STM32F756xx */   /*!< STM32F756VG, STM32F756ZG, STM32F756ZG, STM32F756IG, STM32F756BG,
                                   STM32F756NG Devices */
  /* #define STM32F746xx */   /*!< STM32F746VE, STM32F746VG, STM32F746ZE, STM32F746ZG, STM32F746IE, STM32F746IG,
                                   STM32F746BE, STM32F746BG, STM32F746NE, STM32F746NG Devices */
  /* #define STM32F745xx */   /*!< STM32F745VE, STM32F745VG, STM32F745ZG, STM32F745ZE, STM32F745IE, STM32F745IG Devices */
#else
	#include "stm32f7xx.h"
	#include "stm32f7xx_hal.h"
	#define stm32dev_F7
#endif


/* L0 ----
 *
 *
 */
#if !defined (STM32L051xx) && !defined (STM32L052xx) && !defined (STM32L053xx) && !defined (STM32L062xx) && \
    !defined (STM32L063xx) && !defined (STM32L061xx)
  /* #define STM32L051xx */   /*!< STM32L051K8, STM32L051C6,STM32L051C8,STM32L051R6 and STM32L051R8 Devices */
  /* #define STM32L052xx */   /*!< STM32L052K6, STM32L052K8,STM32L052C6,STM32L052C8,STM32L052R6 and STM32L052R8 Devices */
  /* #define STM32L053xx */   /*!< STM32L053C6, STM32L053C8, STM32L053R6, and STM32L053R8 Devices */
  /* #define STM32L062xx */   /*!< STM32L062K8 */
  /* #define STM32L063xx */   /*!< STM32L063C8, STM32L063R8 */
  /* #define STM32L061xx */
#else
	#include "stm32l0xx.h"
	#include "stm32l0xx_hal.h"
	#define stm32dev_L0
#endif


/* L1 ----
 *
 *
 */
#if !defined (STM32L100xB) && !defined (STM32L100xBA) && !defined (STM32L100xC) && \
    !defined (STM32L151xB) && !defined (STM32L151xBA) && !defined (STM32L151xC) && !defined (STM32L151xCA) && !defined (STM32L151xD) && !defined (STM32L151xDX) && !defined (STM32L151xE) && \
    !defined (STM32L152xB) && !defined (STM32L152xBA) && !defined (STM32L152xC) && !defined (STM32L152xCA) && !defined (STM32L152xD) && !defined (STM32L152xDX) && !defined (STM32L152xE) && \
    !defined (STM32L162xC) && !defined (STM32L162xCA) && !defined (STM32L162xD) && !defined (STM32L162xDX) && !defined (STM32L162xE)
  /* #define STM32L100xB  */   /*!< STM32L100C6, STM32L100R and STM32L100RB Devices */
  /* #define STM32L100xBA */   /*!< STM32L100C6-A, STM32L100R8-A and STM32L100RB-A Devices */
  /* #define STM32L100xC  */   /*!< STM32L100RC Devices */
  /* #define STM32L151xB  */   /*!< STM32L151C6, STM32L151R6, STM32L151C8, STM32L151R8, STM32L151V8, STM32L151CB, STM32L151RB and STM32L151VB */
  /* #define STM32L151xBA */   /*!< STM32L151C6-A, STM32L151R6-A, STM32L151C8-A, STM32L151R8-A, STM32L151V8-A, STM32L151CB-A, STM32L151RB-A and STM32L151VB-A */
  /* #define STM32L151xC  */   /*!< STM32L151CC, STM32L151UC, STM32L151RC and STM32L151VC */
  /* #define STM32L151xCA */   /*!< STM32L151RC-A, STM32L151VC-A, STM32L151QC and STM32L151ZC */
  /* #define STM32L151xD  */   /*!< STM32L151QD, STM32L151RD, STM32L151VD & STM32L151ZD */
  /* #define STM32L151xDX  */  /*!< STM32L151VD-X Devices */
  /* #define STM32L151xE  */   /*!< STM32L151QE, STM32L151RE, STM32L151VE and STM32L151ZE */
  /* #define STM32L152xB  */   /*!< STM32L152C6, STM32L152R6, STM32L152C8, STM32L152R8, STM32L152V8, STM32L152CB, STM32L152RB and STM32L152VB */
  /* #define STM32L152xBA */   /*!< STM32L152C6-A, STM32L152R6-A, STM32L152C8-A, STM32L152R8-A, STM32L152V8-A, STM32L152CB-A, STM32L152RB-A and STM32L152VB-A */
  /* #define STM32L152xC  */   /*!< STM32L152CC, STM32L152UC, STM32L152RC and STM32L152VC */
  /* #define STM32L152xCA */   /*!< STM32L152RC-A, STM32L152VC-A, STM32L152QC and STM32L152ZC */
  /* #define STM32L152xD  */   /*!< STM32L152QD, STM32L152RD, STM32L152VD and STM32L152ZD */
  /* #define STM32L152xDX  */  /*!< STM32L152VD-X Devices */
  /* #define STM32L152xE  */   /*!< STM32L152QE, STM32L152RE, STM32L152VE and STM32L152ZE */
  /* #define STM32L162xC  */   /*!< STM32L162RC and STM32L162VC */
  /* #define STM32L162xCA */   /*!< STM32L162RC-A, STM32L162VC-A, STM32L162QC and STM32L162ZC */
  /* #define STM32L162xD  */   /*!< STM32L162QD, STM32L162RD, STM32L162VD and STM32L162ZD */
  /* #define STM32L162xDX  */  /*!< STM32L162VD-X Devices */
  /* #define STM32L162xE  */   /*!< STM32L162RE, STM32L162VE and STM32L162ZE */
#else
	#include "stm32l1xx.h"
	#include "stm32l1xx_hal.h"
	#define stm32dev_L1
#endif


#endif /* STM32DEV_BOARDS_STM32DEV_DEVICELIB_H_ */
