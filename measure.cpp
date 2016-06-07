#include "measure.h"


measure::measure (StateMachine * m, Adafruit_TFTLCD * tft1) :
	State(m),
	tft( tft1),
	b1( 0, 200, 50, 35, 5),
	b2( 100, 200, 50, 35 ,6)
{	
	b1.setDisplay(tft);
	b1.setHandler(this);
	b2.setHandler(this);
}

void measure::enter() {
	b1.updateGraphic();
	b2.updateGraphic();
}

void measure::exit() {}

void measure::update(uint16_t x, uint16_t y, uint8_t z) {
	b1.update(x, y, z);
	b2.update(x, y, z);
}

void measure::callBack1(bool pressed, uint8_t) {
	tft->fillRect(0, 0, 100, 100, 0xf0f0);
}
