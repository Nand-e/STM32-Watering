#pragma once


#include "State.h"
#include "FS.h"
#include "TFT.h"
#include "TFTBUTTON.h"
#include "Scroll.h"


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
	Button   save;
	ScrollBar scroll1;
	ScrollBar scroll2;
	ScrollBar scroll3;	
	void callBack1(bool pressed, uint8_t id);

	chanel * actualChanel;
};

