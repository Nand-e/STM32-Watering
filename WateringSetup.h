#pragma once


#include "State.h"
#include "FS.h"
#include "TFT.h"
#include "TFTBUTTON.h"
#include "Scroll.h"


struct chanel {
	chanel();
	uint8_t threshold;
	uint8_t timeS;
	uint8_t timeBan;
};

class WateringSetup : public State, ButtonHandler
{
public:

	~WateringSetup();
	WateringSetup (StateMachine * m, Adafruit_TFTLCD * tft);

	void update(uint16_t x, uint16_t y, uint8_t z);
	void enter();
	void exit();
	// ~
private:
	Adafruit_TFTLCD * tft;
	Button   ch1;
	Button   ch2;
	Button   ch3;
	Button   back;
	ScrollBar scroll1;
	ScrollBar scroll2;
	ScrollBar scroll3;	
	void callBack1(bool pressed, uint8_t id);
	chanel c1, c2, c3;
	chanel * actualChanel;
};

