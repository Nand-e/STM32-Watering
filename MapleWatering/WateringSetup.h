#pragma once


#include "State.h"
#include "FS.h"
#include "TFT.h"

#include "wButton.h"
#include "wScroll.h"
#include "WHolder.h"


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
	WHolder holder;
	Adafruit_TFTLCD * tft;
	Button   ch1Button;
	Button   ch2Button;
	Button   ch3Button;
	Button   back;
	Button   save;
	Button   style1;
	Button   style2;
  Button   style3;

	ScrollBar scroll1;
	ScrollBar scroll2;
	ScrollBar scroll3;	
	void callBack1(bool pressed, uint8_t id);	

	chanel * actualChanel;
};

