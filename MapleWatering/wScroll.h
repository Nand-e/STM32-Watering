
#ifndef SCROLLBAR
#define SCROLLBAR

#include "widget.h"

class ScrollBar : public Widget {
public:
	ScrollBar(uint16_t x, uint16_t y, uint8_t w, uint8_t min1 =0, uint8_t max1 = 255 );

	//virtual void setDisplay( Adafruit_GFX * tft );
	virtual void update( uint16_t x, uint16_t y, uint16_t z );
	virtual void reDraw( );
	
	void setValue(uint8_t v);
	uint8_t getValue() { return value; }
protected:
	void reDrawButtons();
	void updateValue();	
	bool pressedL, pressedR;	
	bool opressedR, opressedL;
	long lastpressed;

	uint8_t width;   
	uint16_t x, y;
  uint8_t min0, max0;
	//ButtonHandler * handler;
	uint8_t value, oldvalue;
};

#endif
