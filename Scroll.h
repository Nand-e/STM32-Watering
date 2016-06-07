
#ifndef SCROLLBAR
#define SCROLLBAR

#include "TFTButton.h"

class ScrollBar :public ButtonHandler {
public:
  ScrollBar   ( uint16_t x, uint16_t y, uint8_t w, const uint16_t  * bitmap = 0 );
  void update ( uint16_t x, uint16_t y, uint16_t z );
  void updateGraphic ();
  void callBack1 (bool, uint8_t );
  Button b1, b2;  
  ButtonHandler handler;
  uint8_t width;
  uint16_t x,y;
  uint8_t value;
  uint8_t bitmapH, ArrowW;
  uint8_t bitmapW;
  const uint16_t * bitmap;
};

#endif
