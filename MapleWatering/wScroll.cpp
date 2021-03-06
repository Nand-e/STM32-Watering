
#include "wScroll.h"
#include "TFT.h"

#define MINPRESSURE		 10      // for touch screen sensitivity
#define MAXPRESSURE		 1000
#define UNPRESSEDLIMIT   50

// ScrollBar***************************************************************************************
#define pageW 10

//*************************************************************************************************
ScrollBar::ScrollBar(uint16_t x1, uint16_t y1, uint8_t w, uint8_t min1, uint8_t max1) :
x(x1), y(y1), width(w), min0 (min1), max0 (max1) ,
pressedR(false), pressedL(false),
opressedR(true), opressedL(true)
{
	value = 0;
	oldvalue = 10;
}
//*************************************************************************************************
#define size 28
void ScrollBar::update(uint16_t x1, uint16_t y1, uint16_t z) {
	bool press = false;
	if (z > MINPRESSURE && z < MAXPRESSURE) press = true;



	if (press) {
		if (x < x1 && x1 < (x + size) && y < y1 && y1 < (y + size)) {
			pressedL = true;
		  if ( millis() - lastpressed > 50 ){   // need 50 ms to upsate value     
         lastpressed = millis();
         updateValue();
      }
		}
		uint16_t v = width + pageW + size + x;
		if (( v ) < x1 && x1 < (v+size)  && y < y1 && y1 < (y + size)) 
		{
			pressedR = true;
      if ( millis() - lastpressed > 50 ){   // need 50 ms to upsate value     
			   lastpressed = millis();
         updateValue();
			}
		}
	}

	if (millis() - lastpressed > 50) {
		pressedR = false;
		pressedL = false;
	}

	if (pressedR != opressedR || pressedL != opressedL ) { 	// some buttons state changed										
		reDrawButtons();
		opressedR = pressedR;
		opressedL = pressedL;
	
		//if (handler != 0) handler->callBack1(pressed, ID);
		return;
	}
	//if (pressed && handler != 0)  handler->callBack2(pressed, ID);     // continouse pressing 
}



//*************************************************************************************************
void ScrollBar::setValue(uint8_t v) {
	value = v;
	updateValue();
}
/*************************************************************************************************
void ScrollBar::setDisplay(Adafruit_GFX* tft) {
	ScrollBar::tft = tft;
}*/

//*************************************************************************************************

void ScrollBar::reDrawButtons() {
	theme->drawBox(tft, x, y, size, size, pressedL);
	uint16_t color = theme->FB1;
	if (pressedL) color = theme->BRIGHT;
	tft->fillTriangle(x + 6, y + size / 2, x + 20, y + 4, x + 20, y + 24, color);

	theme->drawBox(tft, x + size + width + pageW, y, size, size, pressedR);
	color = theme->FB1;
	if (pressedR) color = theme->BRIGHT;
	uint16_t x1 = x + size + width + pageW;
	tft->fillTriangle(x1 + 20, y + size / 2, x1 + 6, y + 4, x1 + 6, y + 24, color);
}

void ScrollBar::reDraw() {	
	if (tft == 0) return;
	tft->fillRect (  x + size  , y + 2, width + pageW, 22, tft->Color565(100, 100, 200));
	reDrawButtons();
	oldvalue = value - 1;
	updateValue();	
}

void ScrollBar::updateValue() {	
	if (pressedL && value > min0 )  value--;
	if (pressedR && value < max0 )  value++; 
	if (oldvalue != value){
		if (tft == 0) return;
		uint8_t v1 = map(oldvalue, min0 , max0, 0, width);
		//drawBox(tft, x + size + v1, y + 2, 10, 20, false);
		tft->fillRect(x + size + v1, y + 2, 10, 22, tft->color565(100, 100, 200));
		v1 = map(value, min0, max0, 0, width);
		theme->drawBox(tft, x + size + v1, y + 2, 9, 21, false);
		//tft->fillRoundRect(x + size + v1, y + 2, 10, 20, 3, tft->color565(100, 200, 200));
		oldvalue = value;
	}
}



