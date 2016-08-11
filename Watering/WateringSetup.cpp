#include "WateringSetup.h"
#include "measure.h"
#include "Bitmaps.h"
#include "widget.h"


extern measure baseState;

#define BACK 0b0011000001101110
#define SY1 80
#define SY2 120
#define SY3 160

chanel::chanel() {
	threshold = 0;
	timeS     = 0;
	timeBan   = 0;
	switched = false;
	lasttime = 1000 * 60 * 60 * 24;  // perc * 60 perc * óra
}


WateringSetup::WateringSetup(StateMachine * m, Adafruit_TFTLCD * tft1) :
	State(m), tft(tft1),
	scroll1( 52, SY1, 180),
	scroll2( 52, SY2, 180 ),
	scroll3( 52, SY3, 180 ),
	ch1Button( 65,  5, SY1-20, 30, 8, false, 0, "ch1"),
	ch2Button( 135, 5, SY1-20, 30, 9, false, 0, "ch2"),
	ch3Button( 205, 5, SY1-20, 30, 10, false,0, "ch3"),
	back(255, 200, 60, 35, 12, false, 0, "Back"),
	save(180, 200, 60, 35, 13, false, 0, "Save")
{

	back.setHandler(this);
	save.setHandler(this);
	ch1Button.setHandler(this);
	ch2Button.setHandler(this);
	ch3Button.setHandler(this);	

	ch1Button.setColors(0xffff, 0x50ee);
	ch2Button.setColors(0xffff, 0x50ee);
	ch3Button.setColors(0xffff, 0x50ee);

	back.setColors(0xffff, 0x50ee);
	save.setColors(0xffff, 0x50ee);
	
	machine->LoadFromEEPROM();	

}

void WateringSetup::enter() {

	//tft->fillRect(0, 0, 320, 240, BACK);
	Widget::theme->drawBox(tft, 0, 0 , 319, 239, false);
	//tft->drawRoundRect(0, 0, 320, 240, 3, 0xfefe);
	
	Widget::theme->drawBox(tft, 10, SY1 - 35, 300, 150, false);

	actualChanel = &machine->c1;	
	
	tft->drawBitmap( 17, SY1 -2 , Water, 32, 32, 0x0000);
	tft->drawBitmap( 17, SY2 -2, Clock, 32, 32, 0x0000);
	tft->drawBitmap( 17, SY3 -2, TimeBan, 32, 32, 0x0000);
	
	// Scrolls
	scroll1.reDraw();
	scroll2.reDraw();
	scroll3.reDraw();

	scroll1.setValue(actualChanel->threshold);
	scroll2.setValue(actualChanel->timeS);
	scroll3.setValue(actualChanel->timeBan);


	// Buttons
	ch1Button.reDraw();
	ch2Button.reDraw();
	ch3Button.reDraw();
	back.reDraw();
	save.reDraw();	

	callBack1(true, 8);
	Serial.println("->Setup");
}

void WateringSetup::update(uint16_t x, uint16_t y, uint8_t z) {
	scroll1.update(x, y, z);
	scroll2.update(x, y, z);
	scroll3.update(x, y, z);

	ch1Button.update  (x, y, z);
	ch2Button.update  (x, y, z);
	ch3Button.update  (x, y, z);

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
		tft->setCursor(15, SY1-30);
		tft->fillRect(15, SY1 - 30, 45, 25, LIGHT);
		
		if (id == 8) {
			actualChanel = & machine->c1;	
			tft->print("CH1");
		}
		if (id == 9) {
			actualChanel = & machine->c2;
			tft->print("CH2");
		}
		if (id == 10) {
			actualChanel = & machine->c3;
			tft->print("CH3");
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
