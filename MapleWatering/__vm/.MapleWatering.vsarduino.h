/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Maple Mini, Platform=STM32F1, Package=Ardunio_STM32
*/

#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
#define DEBUG_LEVEL DEBUG_NONE
#define BOARD_maple_mini
#define VECT_TAB_ADDR 0x8005000
#define ERROR_LED_PORT GPIOB
#define ERROR_LED_PIN 1
#define F_CPU 72000000L
#define ARDUINO 10609
#define ARDUINO_MAPLE_MINI
#define ARDUINO_ARCH_STM32F1
#define MCU_STM32F103CB
#define SERIAL_USB
#define __STM32F1__
#define __cplusplus 201103L
#define GCC_VERSION 40803
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__


#define __ICCARM__
#define __ASM
#define __INLINE
#define __builtin_va_list void
//#define _GNU_SOURCE 
//#define __GNUC__ 0
//#undef  __ICCARM__
//#define __GNU__

typedef long Pio;
typedef long Efc;
typedef long Adc;
typedef long Pwm;
typedef long Rtc;
typedef long Rtt;
typedef long pRtc;
typedef long Spi;
typedef long spi;
typedef long Ssc;
//typedef long p_scc;
typedef long Tc;
//typedef long pTc;
typedef long Twi;
typedef long Wdt;
//typedef long pTwi;
typedef long Usart;
typedef long Pdc;
typedef long Rstc;

extern const int ADC_MR_TRGEN_DIS = 0;
extern const int ADC_MR_TRGSEL_ADC_TRIG0 = 0;
extern const int ADC_MR_TRGSEL_Pos = 0;

extern const int ADC_MR_TRGSEL_Msk = 0;
extern const int ADC_MR_TRGEN = 0;
extern const int ADC_TRIG_TIO_CH_0 = 0;
extern const int ADC_MR_TRGSEL_ADC_TRIG1 = 0;
extern const int ADC_TRIG_TIO_CH_1 = 0;
extern const int ADC_MR_TRGSEL_ADC_TRIG2 = 0;
extern const int ADC_MR_TRGSEL_ADC_TRIG3 = 0;

#define __ARMCC_VERSION 400678
#define __attribute__(noinline)

#define prog_void
#define PGM_VOID_P int


            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}



#include <arduino.h>
#include <pins_arduino.h> 
#include <variant.h> 
#undef F
#define F(string_literal) ((const PROGMEM char *)(string_literal))
#undef PSTR
#define PSTR(string_literal) ((const PROGMEM char *)(string_literal))
#undef cli
#define cli()
#define pgm_read_byte(address_short)
#define pgm_read_word(address_short)
#define pgm_read_word2(address_short)
#define digitalPinToPort(P)
#define digitalPinToBitMask(P) 
#define digitalPinToTimer(P)
#define analogInPinToBit(P)
#define portOutputRegister(P)
#define portInputRegister(P)
#define portModeRegister(P)
#include <..\MapleWatering\MapleWatering.ino>
#include <..\MapleWatering\Adafruit_GFX.cpp>
#include <..\MapleWatering\Adafruit_GFX.h>
#include <..\MapleWatering\BarGraph.cpp>
#include <..\MapleWatering\BarGraph.h>
#include <..\MapleWatering\Bitmaps.cpp>
#include <..\MapleWatering\Bitmaps.h>
#include <..\MapleWatering\ChartData.cpp>
#include <..\MapleWatering\ChartData.h>
#include <..\MapleWatering\DataStore.cpp>
#include <..\MapleWatering\DataStore.h>
#include <..\MapleWatering\FS.cpp>
#include <..\MapleWatering\FS.h>
#include <..\MapleWatering\State.h>
#include <..\MapleWatering\TFT.cpp>
#include <..\MapleWatering\TFT.h>
#include <..\MapleWatering\TouchScreen.cpp>
#include <..\MapleWatering\TouchScreen.h>
#include <..\MapleWatering\WHolder.cpp>
#include <..\MapleWatering\WHolder.h>
#include <..\MapleWatering\WateringSetup.cpp>
#include <..\MapleWatering\WateringSetup.h>
#include <..\MapleWatering\glcdfont.c>
#include <..\MapleWatering\measure.cpp>
#include <..\MapleWatering\measure.h>
#include <..\MapleWatering\pin_magic.h>
#include <..\MapleWatering\pin_magic_MAPLEMINI.h>
#include <..\MapleWatering\pin_magic_UNO.h>
#include <..\MapleWatering\registers.h>
#include <..\MapleWatering\wButton.cpp>
#include <..\MapleWatering\wButton.h>
#include <..\MapleWatering\wScroll.cpp>
#include <..\MapleWatering\wScroll.h>
#include <..\MapleWatering\widget.cpp>
#include <..\MapleWatering\widget.h>
#endif