#pragma once

#include "State.h"
#include "FS.h"
#include "TFT.h"
#include "TFTBUTTON1.h"

class measure : public State, public ButtonHandler
{
public:
	measure(StateMachine * m, Adafruit_TFTLCD * tft);
	void update(uint16_t x, uint16_t y, uint8_t z);
	void enter();
	void exit();

	int ringMeter(int value, int vmin, int vmax, int x, int y, int r, char *units, byte scheme);
	unsigned int rainbow(uint8_t value);

	//~measure();
private:
	Adafruit_TFTLCD * tft;	
	Button1 b1;
	//Button1 b2;
	void callBack1(bool pressed, uint8_t id);


};
