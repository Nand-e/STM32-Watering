#include <TouchScreen.h>

#include "TFT.h"
#include "TFTButton.h"
#include "Bitmaps.h"
#include "Scroll.h"


#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define TS_MINX 200
#define TS_MAXX 910
#define TS_MINY 195
#define TS_MAXY 950

//***************** Global definition

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen     ts = TouchScreen(XP, YP, XM, YM, 300);

#define MAXBUTTONS 4
Button          * Buttons[MAXBUTTONS];


// ScrollBar***************************************************************************************
#define BACK  0b0011100011100111

//*************************************************************************************************
void ScrollBar::update( uint16_t x, uint16_t y, uint16_t z ) {
  b1.update( x,y,z );
  b2.update( x,y,z );
}
//*************************************************************************************************
void ScrollBar::updateGraphic () {
  b1.updateGraphic();
  b2.updateGraphic();
  
  tft.fillRoundRect( x-2 , y-2, width + bitmapW*2 + ArrowW + 10, bitmapH +4, 2, BACK );
 
  tft.drawRoundRect( x-2 , y-2, width + bitmapW*2 + ArrowW + 10, bitmapH +4, 2, tft.color565 ( 150,150, 150 ) );
  tft.drawLine     ( x + bitmapW+2 , y-1, x + bitmapW+2, y + bitmapH +1, tft.color565 ( 150,150, 150 ) );
  tft.fillRect     ( x + ArrowW +bitmapW+ 6 , y +2, width  , 28, tft.color565 ( 100, 100, 200 ) );
  callBack1(true, 1);
  if ( bitmap != 0) {
    tft.drawBMP2     ( x, y, bitmap, 32,32, false, 0, BACK );
  }
}
//*************************************************************************************************
ScrollBar::ScrollBar( uint16_t x1, uint16_t y1, uint8_t w, const uint16_t * bmp) :
  x(x1), y(y1) , width(w) 
{
  b1.setHandler ( this);
  b2.setHandler ( this);
  value = 0;
  bitmapH = 32;
  bitmapW = 32;
  ArrowW   = 22;
  bitmap = bmp;
  b1.set ( x + bitmapW +4,  y, 32,32, 0, true, BACK );
  b2.set ( x + ArrowW +bitmapW+ width+ 8,y, 32,32, 1, false ,BACK);
}

void ScrollBar::callBack1 ( bool pressed, uint8_t ID ) {
  if ( pressed ) {
    uint8_t oldv = value;
    switch ( ID ) {
      case 0:   value--; break;
      case 1:   value++; break; 
    }
    value %= width;
    if ( oldv != value )       
    {
     tft.fillRect ( x +bitmapW + ArrowW + 6 + oldv, y+2 , 10, 28, tft.color565 ( 100, 100, 200 ));
     tft.fillRoundRect ( x +bitmapW + ArrowW + 6 + value, y+2, 10, 28, 3, tft.color565 ( 100, 200, 200 ) );
    }  
  } 
}


ScrollBar scroll ( 30,20, 170, Water );
ScrollBar scroll2 ( 30,70, 170, Clock );
ScrollBar scroll3 ( 30,120, 170, TimeBan );
 
/* Setup ******************************************************************************************/
void setup(void) {

  Serial.begin (9600);
  Serial.println ( "Watering system start!");
  tft.reset();  
  uint16_t identifier = tft.readID();
  Serial.println ( identifier );
  tft.begin(identifier); 
  tft.setRotation ( 1);
  tft.fillScreen(tft.color565( 0,100, 50 ));
  pinMode(13, OUTPUT);

  scroll.updateGraphic();
  scroll2.updateGraphic();
  scroll3.updateGraphic();
}






void loop()
{


  
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  TSPoint p2;
  digitalWrite(13, LOW);

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  //pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //pinMode(YM, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {

   p2.y = map(p.x, TS_MINX, TS_MAXX,0, 240 );   
   p2.x = map(p.y, TS_MAXY, TS_MINY, 0, 320 );    
   
    //tft.fillCircle ( p2.x, p2.y , 2, 0xf000 );
    
   /* Serial.print ( p.x );
    Serial.print ( " , " );
    Serial.println ( p.y );*/
  } 
  

 
  scroll.update ( p2.x, p2.y, p.z );  
  scroll2.update ( p2.x, p2.y, p.z );
  scroll3.update ( p2.x, p2.y, p.z );


 

  
}

