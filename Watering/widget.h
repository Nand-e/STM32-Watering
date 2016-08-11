#pragma once

#include "Adafruit_GFX.h"

struct Theme {
	#define DARK    0x10A2
	#define LIGHTER 0x4228
	#define LIGHT   0x94b2 
	#define WHITE   0xEF5D	
	void drawBox(Adafruit_GFX * tft, uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, bool pushed);
};

class Widget
{
public:
	Widget() {};
	//~widget();	
	static void setDisplay(Adafruit_GFX * tft);
	virtual void update(uint16_t x, uint16_t y, uint16_t z) = 0;
	virtual void reDraw() = 0;	
	static Theme * theme;
protected:
	static Adafruit_GFX* tft;

};


