

#include "TFTButton.h"
#include "TFT.h"
#include <Arduino.h>

// static varible definitions
Adafruit_TFTLCD * Button::tft;

/**************************************************************************************************************/
Button::Button() {
	handler = 0;
}

/*Construct Button in x,y coordinate **************************************************************************/
Button::Button ( uint16_t x0, uint16_t y0, uint16_t w0, uint16_t h0, uint8_t id, bool mirrored1, uint16_t color, char * text1) :
x1(x0), y1(y0), w(w0), h(h0), backColor(color), text( text1 )
{
    pressed     = false;
    mirrored    = mirrored1;
    lastpressed = millis();
    handler = 0;    
	ID = id;

}
/**************************************************************************************************************/
void Button::set( uint16_t x0, uint16_t y0, uint16_t w0, uint16_t h0, uint8_t id, bool mirrored1, uint16_t color) {
  x1 = x0; y1 = y0;
  w  = w0;  h = h0;
  pressed = true;
  mirrored = mirrored1;
  ID = id;
  backColor = color;
  color = 0xeeee;
}

//****************************************************************************************************************
void Button::setColors(uint16_t c1, uint16_t bc) {
	color = c1;
	backColor = bc;
}

/****************************************************************************************************************/
void Button::setDisplay(Adafruit_TFTLCD * tft) {
	Button::tft = tft;
}

/* Call in every loop on every Button ****************************************************************************/
void Button::update(uint16_t x, uint16_t y, uint16_t z) {
	bool press = false;	
	if (z > MINPRESSURE && z < MAXPRESSURE) press = true;	
	updateButtonState(x, y, press);
}
/*  
 ***********************************************************************************/
void Button::updateButtonState ( uint16_t x, uint16_t y, bool press ) {
    bool oldpressed = pressed;
	if (press) {
		if (x > x1 && x < (x1 + w) && y > y1 && y < (y1 + h)) {
			pressed = true;
			lastpressed = millis();
		}
	}

	if (millis() - lastpressed > 200) pressed = false;

	if (oldpressed != pressed) {										// Button changed
		updateGraphic();
		if (handler != 0) handler->callBack1(pressed, ID);
		return;
	}
	if (pressed && handler != 0)  handler->callBack2(pressed, ID);     // continouse pressing 
} 

/*  
 **********************************************************************************/
void Button::updateGraphic ( ) {
    if (tft == 0) return;
	if (pressed) {
		tft->drawRoundRect(x1, y1, w, h, RAD, color);
		tft->fillRoundRect(x1 + 2, y1 + 2, w - 4, h - 4, RAD, backColor);
		tft->fillRoundRect(x1 + 4, y1 + 4, w - 8, h - 8, RAD, color);
		tft->drawRoundRect(x1 + 4, y1 + 4, w - 8, h - 8, RAD, color);
		if (text != 0) {
			tft->setCursor(x1 + 15, y1+10 );
			tft->setTextColor(backColor);
			tft->setTextSize(1);
			tft->println(text);
		}
	}
	else {
		tft->fillRoundRect(x1 + 2, y1 + 2, w - 4, h - 4, RAD, backColor);
		tft->drawRoundRect(x1, y1, w, h, RAD, color);
		tft->drawRoundRect(x1 + 2, y1 + 2, w - 4, h - 4, RAD, color);
		if (text != 0) {
			tft->setCursor(x1 + 15 , y1+10);
			tft->setTextColor(color);
			tft->setTextSize(1);
			tft->print(text);
		}
	}
}
