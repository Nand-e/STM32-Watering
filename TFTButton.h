#ifndef TFTBUTTON
#define TFTBUTTON

#include <stdint.h>
#include "TFT.h"

#define MINPRESSURE		 10      // for touch screen sensitivity
#define MAXPRESSURE		 1000
#define UNPRESSEDLIMIT   50

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define RAD 5


class ButtonHandler {
public:
  virtual void callBack1 ( bool pressed, uint8_t id ) {};
  virtual void callBack2 ( bool pressed, uint8_t id ) {};
  
};

class Button {
   
public:
    Button ();
	Button(uint16_t x0, uint16_t y0, uint16_t w0, uint16_t h0, uint8_t id, bool mirrored = false, uint16_t backC = 0, char * text1 = 0);
	void setDisplay(Adafruit_TFTLCD * tft);
	void set( uint16_t x0, uint16_t y0, uint16_t w0, uint16_t h0, uint8_t id, bool mirrored = false, uint16_t backC=0);   
	void setColors(uint16_t color1, uint16_t backC);
    void update (  uint16_t x, uint16_t y , uint16_t z ) ;
    void setHandler ( ButtonHandler * handler1 ) {   handler = handler1;  }
	virtual void updateGraphic();  
protected:
   void updateButtonState ( uint16_t x, uint16_t y, bool press );
   uint16_t x1;   uint16_t y1; 
   uint8_t w;     uint8_t h;  
   ButtonHandler * handler;
   char * text;
   bool pressed;  bool mirrored;
   long lastpressed;
   uint8_t   ID;
   uint16_t  backColor;
   uint16_t  color;
   
   static Adafruit_TFTLCD * tft;
};


#endif

