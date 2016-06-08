#pragma once

#include "Adafruit_GFX.h"

class BarGraph
{
public:
	BarGraph(Adafruit_GFX * tft1, uint16_t x, uint16_t y, uint8_t w );
	//~BarGraph();
	void updateGraphic();
	void setValue(uint8_t v,  uint8_t thres = 0);
private:
	Adafruit_GFX * tft;
	uint8_t oldValue;
	uint16_t x, y;
	uint8_t w;
	uint8_t thres, oldthres;
};

