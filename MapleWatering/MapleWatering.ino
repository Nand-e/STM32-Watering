#include "TouchScreen.h"

#include "TFT.h"
#include "FS.h"				// final state machine class

#include "widget.h"
#include "measure.h"
#include "WateringSetup.h"


#define XM 3  // A2 on UNO
#define YP 8  // A3 on UNO

#define YM 20 //  9
#define XP 21 //  8

#define LCD_RD   19 // A0
#define LCD_WR   18 // A1
#define LCD_CD   3  // A2 on UNO  // shared XM
#define LCD_CS   8  // A3 on UNO  // shared YP
#define LCD_RESET 15 // A4 

Adafruit_TFTLCD tft  (LCD_RD, LCD_WR , LCD_CD  , LCD_CS , LCD_RESET);
TouchScreen     ts = TouchScreen(XP, YP, XM, YM, 0);

//******** State Machine and states
StateMachine  machine   ( 0 , tft );
measure       baseState ( &machine, &tft);
WateringSetup setupState( &machine, &tft);

Theme theme1;
Theme2 theme2;
Theme3 theme3;

 
/* Setup ******************************************************************************************/
void setup(void) {

  Serial.begin (9600);
  Serial.println ( "Watering start!");
  tft.reset();
  uint16_t identifier = tft.readID();
  Serial.println ( identifier );
  tft.begin(identifier); 
  tft.setRotation (3);
  
  Widget::theme = & theme2;				// init widget
  Widget::setDisplay(&tft);  

  machine.TransitionTo(&baseState);
}


#define TS_MINY 5800
#define TS_MAXY 600

#define TS_MINX 550
#define TS_MAXX 5500


void loop()
{  

  TSPoint p1, p2;  
  p1 = ts.getPoint();
 
 
  pinMode(XM, OUTPUT);  // They are shared pins
  pinMode(YP, OUTPUT);
  pinMode(YM, OUTPUT);  // They are shared pins
  pinMode(XP, OUTPUT);
 
  if (p1.z > 400 && p1.z < 2000) {
     p2.y = map(p1.x, TS_MINX, TS_MAXX,0, 240 );      
     p2.x = map(p1.y, TS_MINY, TS_MAXY, 0, 320 );      
     
   //  tft.drawPixel( p2.x, p2.y ,  0xf000 );
   //  Serial.print   ( "x:" );
   //  Serial.print   ( p1.x );
   //  Serial.print   ( " , y:" );
   //  Serial.print  ( p1.y );
   //  Serial.print   ( " , z:" );
   //  Serial.println  ( p1.z );
   }  
   machine.update( p2.x, p2.y , p1.z );
}

