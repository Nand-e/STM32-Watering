#pragma once

#include "Adafruit_GFX.h"

class BarGraph
{
public:
	BarGraph(Adafruit_GFX * tft1, uint16_t x, uint16_t y, uint8_t w );
	//~BarGraph();
	void reDraw();
	void setValue(uint8_t v );
	void setThreshold(uint8_t th);
private:
	Adafruit_GFX * tft;
	uint8_t oldValue;
	uint16_t x, y;
	uint8_t w;
	uint8_t thres, oldthres;
};

