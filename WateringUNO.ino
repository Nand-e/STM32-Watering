#include <TouchScreen.h>

#include "TFT.h"
#include "FS.h"				// final state machine class


#include "measure.h"
#include "WateringSetup.h"

#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define TS_MINX 200
#define TS_MAXX 910
#define TS_MINY 195
#define TS_MAXY 950

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4




Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen     ts = TouchScreen(XP, YP, XM, YM, 300);

//******** State Machine and states
StateMachine  machine;
measure       baseState( &machine, &tft);
WateringSetup setupState(&machine, &tft);

 
/* Setup ******************************************************************************************/
void setup(void) {

  Serial.begin (9600);
  Serial.println ( "Watering system start!");
  tft.reset();
  uint16_t identifier = tft.readID();
  Serial.println ( identifier );
  tft.begin(identifier); 
  tft.setRotation (1);

  pinMode(13, OUTPUT);
  
  machine.TransitionTo(&baseState);

}



enum States { NOrmal, Setup };

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

   machine.update(p2.x, p2.y, p.z);  
}

