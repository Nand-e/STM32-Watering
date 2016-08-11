
#include <Arduino.h>
#include "Adafruit_GFX.h"

class ChartData{
public:
	ChartData(Adafruit_GFX & tft1, uint8_t x1, uint8_t y1);	
	void setData(uint8_t index, uint8_t dat, bool w1, bool b1,
											 bool w2, bool b2,
											 bool w3, bool b3);

	uint8_t getData(uint8_t index);
	void draw(uint8_t index);
	Adafruit_GFX & tft;
private:
	uint8_t x0, y0;
	uint8_t  data[200];	
	uint8_t data2[200];
};