
#ifndef SCROLLBAR
#define SCROLLBAR

#include "TFTButton1.h"

class ScrollBar :public ButtonHandler {
public:
  ScrollBar   ( uint16_t x, uint16_t y, uint8_t w, const uint16_t  * bitmap = 0 );
  void update ( uint16_t x, uint16_t y, uint16_t z );
  void updateGraphic ();
  void setValue (uint8_t v);
  uint8_t getValue() { return value; }
  void callBack1 (bool, uint8_t);
  void callBack2 (bool, uint8_t );
  void setDisplay(Adafruit_GFX * tft);
protected:
  Button1 b1, b2;  
  ButtonHandler handler;
  uint8_t width;
  uint16_t x,y;
  uint8_t value, oldvalue;
  uint8_t bitmapH, ArrowW;
  uint8_t bitmapW;
  const uint16_t * bitmap;

  static Adafruit_GFX * tft;
};

#endif
