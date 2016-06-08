#include "WateringSetup.h"
#include "measure.h"
#include "Bitmaps.h"

extern measure baseState;

chanel::chanel() {
	threshold = 0;
	timeS     = 0;
	timeBan   = 0;
}

WateringSetup::WateringSetup(StateMachine * m, Adafruit_TFTLCD * tft1) :
	State( m ) ,
	tft( tft1 ) ,
	scroll1(10,  50, 190, Water),
    scroll2(10,  100, 190, Clock),
    scroll3(10,  150, 190, TimeBan),
	ch1 ( 65,5,50,30,8,false, 0, "ch1"),
	ch2 ( 135, 5, 50, 30,9, false, 0, "ch2"),
	ch3 ( 205, 5, 50, 30,10, false, 0, "ch3"),
	back( 255, 200, 60, 35, 12, false, 0, "back")
{
	scroll1.setDisplay(tft);	
	back.setDisplay(tft);
	back.setHandler(this);
	ch1.setHandler(this);
	ch2.setHandler(this);
	ch3.setHandler(this);
	ch1.setColors(0xffff, 0x00ee);
	ch2.setColors(0xffff, 0x00ee);
	ch3.setColors(0xffff, 0x00ee);
	back.setColors(0xffff, 0x00ee);
	actualChanel = &c1;
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
	back.update (x, y, z);
	ch1.update  (x, y, z);
	ch2.update  (x, y, z);
	ch3.update  (x, y, z);
}

void WateringSetup::callBack1(bool pressed, uint8_t id) {
	if (pressed) {
		if (id == 12) {
			machine->TransitionTo(&baseState);
			return;
		}

		actualChanel->threshold = scroll1.getValue();
		actualChanel->timeS     = scroll2.getValue();
		actualChanel->timeBan   = scroll3.getValue();
		
		if (id == 8) {
			actualChanel = &c1;		
		}
		if (id == 9) {
			actualChanel = &c2;
		}
		if (id == 10) {
			actualChanel = &c3;
		}
		scroll1.setValue(actualChanel->threshold);
		scroll2.setValue(actualChanel->timeS);
		scroll3.setValue(actualChanel->timeBan);
	}	
}

void WateringSetup::exit() {}

WateringSetup::~WateringSetup()
{

}
