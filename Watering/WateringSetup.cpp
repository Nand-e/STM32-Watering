#include "WateringSetup.h"
#include "measure.h"
#include "Bitmaps.h"

extern measure baseState;

#define BACK 0b0011000001101110

chanel::chanel() {
	threshold = 0;
	timeS     = 0;
	timeBan   = 0;
	switched = false;
	lasttime = 1000 * 60 * 60 * 24;  // perc * 60 perc * óra
}

#define SY 75
WateringSetup::WateringSetup(StateMachine * m, Adafruit_TFTLCD * tft1) :
	State(m),
	tft(tft1),
	scroll1(18, SY, 190, Water),
	scroll2(18, SY+40, 190, Clock),
	scroll3(18, SY+80, 190, TimeBan),
	ch1( 65,  5, SY-20, 30, 8, false, 0, "Ch1"),
	ch2( 135, 5, SY-20, 30, 9, false, 0, "Ch2"),
	ch3( 205, 5, SY-20, 30, 10, false,0, "Ch3"),
	back(255, 200, 60, 35, 12, false, 0, "Back"),
	save(180, 200, 60, 35, 13, false, 0, "Save")
{
	scroll1.setDisplay(tft);	
	back.setDisplay(tft);
	back.setHandler(this);
	save.setHandler(this);
	ch1.setHandler(this);
	ch2.setHandler(this);
	ch3.setHandler(this);
	

	ch1.setColors(0xffff, 0x50ee);
	ch2.setColors(0xffff, 0x50ee);
	ch3.setColors(0xffff, 0x50ee);
	back.setColors(0xffff, 0x50ee);
	save.setColors(0xffff, 0x50ee);
	
	machine->LoadFromEEPROM();	

}

void WateringSetup::enter() {
	tft->fillRect(0, 0, 320, 240, BACK);
	tft->drawRoundRect(0, 0, 320, 240, 3, 0xfefe);
	tft->drawRoundRect(10, SY -30 , 300, 150, 3, 0xfefe);
	actualChanel = &machine->c1;
	// Scrolls
	scroll1.setValue(actualChanel->threshold);
	scroll2.setValue(actualChanel->timeS);
	scroll3.setValue(actualChanel->timeBan);

	scroll1.updateGraphic();
	scroll2.updateGraphic();
	scroll3.updateGraphic();
	// Buttons
	ch1.updateGraphic();
	ch2.updateGraphic();
	ch3.updateGraphic();
	back.updateGraphic();
	save.updateGraphic();	

	callBack1(true, 8);
	Serial.println("->Setup");
}

void WateringSetup::update(uint16_t x, uint16_t y, uint8_t z) {
	scroll1.update(x, y, z);
	scroll2.update(x, y, z);
	scroll3.update(x, y, z);

	ch1.update  (x, y, z);
	ch2.update  (x, y, z);
	ch3.update  (x, y, z);

	back.update(x, y, z);
	save.update(x, y, z);
}

void WateringSetup::callBack1(bool pressed, uint8_t id) {
	if (pressed) {
		if (id == 12) {
			machine->TransitionTo(&baseState);
			return;
		}
		// copy data to chanel data from scroll
		actualChanel->threshold = scroll1.getValue();
		actualChanel->timeS     = scroll2.getValue();
		actualChanel->timeBan   = scroll3.getValue();
	
		if (id == 13) {
			machine->saveToEEPROM();
			machine->TransitionTo(&baseState);
			return;
		}
		tft->setTextSize(2);
		tft->setTextColor(0xffff);
		tft->setCursor(15, SY-30);
		tft->fillRect(15, 40, 50, 25, BACK);
		
		if (id == 8) {
			actualChanel = & machine->c1;	
			tft->print("ch1");
		}
		if (id == 9) {
			actualChanel = & machine->c2;
			tft->print("ch2");
		}
		if (id == 10) {
			actualChanel = & machine->c3;
			tft->print("ch3");
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
