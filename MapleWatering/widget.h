#pragma once

#include "Adafruit_GFX.h"

class Theme {
public:
	Theme();

	uint16_t BRIGHT;// = 0xeeee;
	uint16_t FILL1; // = 0x94b2;
	uint16_t FILL2; // = 0x000;
	uint16_t FT1;   // = 0xeeee;
	uint16_t FT2;   // = 0x0000;
	uint16_t FB1;   // = 0x10A2;
	uint16_t FB2;   // = 0x5422;
	uint16_t BACK;  //

	virtual void drawBox(Adafruit_GFX * tft, uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, bool pushed, bool onlyframe = false );
	virtual void drawBox2(Adafruit_GFX * tft, uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, bool pushed, bool onlyframe = false) {};
};

class Theme2 : public  Theme{
public:
	Theme2();
	virtual void drawBox (Adafruit_GFX * tft, uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, bool pushed, bool onlyframe = false);
	virtual void drawBox2(Adafruit_GFX * tft, uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, bool pushed, bool onlyframe = false) {};
};

class Theme3 : public  Theme2
{
  public:
    Theme3();  
};


//-------------------------------------------------------------------------------------------------------------------------------------------
class ButtonHandler;
class Widget
{
public:
	Widget() {};
	//~widget();	
	static void setDisplay(Adafruit_GFX * tft);
	virtual void update(uint16_t x, uint16_t y, uint16_t z) {}; // = 0;
	virtual void reDraw() {}; // = 0;
  virtual void setHandler ( ButtonHandler * handler ) {};
	static Theme * theme;
protected:
	static Adafruit_GFX* tft;

};


