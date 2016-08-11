#pragma once

#include "State.h"
#include "FS.h"
#include "TFT.h"
#include "wButton.h"
#include "wScroll.h"
#include "WHolder.h"

#include "BarGraph.h"

class measure : public State, public ButtonHandler
{
public:
	measure(StateMachine * m, Adafruit_GFX * tft);
	void update(uint16_t x, uint16_t y, uint8_t z);
	void updateLed(uint16_t x, uint16_t y, bool onOff);

	void enter();
	void exit();

	int ringMeter(int value, int vmin, int vmax, int x, int y, int r, char *units, byte scheme);
	unsigned int rainbow(uint8_t value);

	//~measure();
private:
	WHolder holder;
	Button b1;
	Button b2;
	Button b3;
	Button b4;	
  ScrollBar scroll;
	//BarGraph bg1;
	//BarGraph bg2;
	//BarGraph bg3;
	void callBack2(bool pressed, uint8_t id) {}
	void callBack1(bool pressed, uint8_t id);
	Adafruit_GFX * tft;
	ChartData chart;
};


