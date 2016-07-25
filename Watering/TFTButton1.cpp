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
void Button1::updateGraphic() {
	if (tft==0) return;
	if (pressed) {
		if (mirrored) tft->fillTriangle(x1 + 22, y1+4, x1 + 22, y1 + 28, x1+4, y1 + 16, 0x55ee);
		else  tft->fillTriangle(x1, y1+4, x1, y1 + 28, x1 + 18, y1 + 16, 0x55ee);		
		//(( Adafruit_TFTLCD * ) tft)->drawBMP2( x1, y1, ( uint16_t * ) Arrow,22,32, mirrored, 0b0110000110001100, backColor);
	} else {
		if (mirrored) tft->fillTriangle(x1 + 22, y1 + 4, x1 + 22, y1 + 28, x1+4, y1 + 16, 0xffee);
		else  tft->fillTriangle(x1, y1 + 4, x1, y1 + 28, x1 + 18, y1 + 16, 0xffee);
	}
}

