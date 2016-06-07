#pragma once


#include "State.h"
#include "FS.h"
#include "TFT.h"
#include "TFTBUTTON1.h"
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
	Button1   ch1;
	Button1   ch2;
	Button1   ch3;
	Button1   back;
	ScrollBar scroll1;
	ScrollBar scroll2;
	ScrollBar scroll3;	
	void callBack1(bool pressed, uint8_t id);


};

