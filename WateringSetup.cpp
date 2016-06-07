#include "WateringSetup.h"
#include "measure.h"
#include "Bitmaps.h"

extern measure baseState;

WateringSetup::WateringSetup(StateMachine * m, Adafruit_TFTLCD * tft1) :
	State( m ) ,
	tft( tft1 ) ,
	scroll1(10,  50, 190, Water),
    scroll2(10,  100, 190, Clock),
    scroll3(10,  150, 190, TimeBan),
	ch1 ( 65,5,50,30,8),
	ch2 ( 135, 5, 50, 30,9),
	ch3 ( 205, 5, 50, 30,10),
	back( 260, 200, 60, 35, 12)
{
	scroll1.setDisplay(tft);	
	back.setDisplay(tft);
	back.setHandler(this);
}

void WateringSetup::enter() {
	tft->fillRect(0, 0, 320, 240, tft->color565(0, 100, 50) );
	tft->drawRoundRect(0, 0, 320, 240, 3, 0xfefe);
	ch1.updateGraphic();
	ch2.updateGraphic();
	ch3.updateGraphic();
	scroll1.updateGraphic();
	scroll2.updateGraphic();
	scroll3.updateGraphic();
	back.updateGraphic();
	ch1.updateGraphic();
	Serial.println("Enter Setup");
}

void WateringSetup::update(uint16_t x, uint16_t y, uint8_t z) {
	scroll1.update(x, y, z);
	scroll2.update(x, y, z);
	scroll3.update(x, y, z);
	back.update(x, y, z);
}

void WateringSetup::callBack1(bool pressed, uint8_t id) {
	if (pressed) {
		machine->TransitionTo(&baseState);
	}
}

void WateringSetup::exit() {}

WateringSetup::~WateringSetup()
{

}
