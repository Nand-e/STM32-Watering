#include <Arduino.h>

#include "TFTButton1.h"
#include "Adafruit_GFX.h"
#include "TFT.h"

/**************************************************************************************************************/
Button1::Button1() {
	handler = 0;
}

/*Construct Button in x,y coordinate **************************************************************************/
Button1::Button1(uint16_t x0, uint16_t y0, uint16_t w0, uint16_t h0, uint8_t id, bool mirrored1, uint16_t color) :
	Button(x0, y0, w0, h0, id, mirrored1, color)
{ };


//**************************************************************************************************************
void Button1::reDraw() {

}

