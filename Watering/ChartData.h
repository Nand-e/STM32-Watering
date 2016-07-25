
#include <Arduino.h>
#include "Adafruit_GFX.h"

class ChartData{
public:
	ChartData(Adafruit_GFX & tft1) :
		tft(tft1) {}; 
	
	void setData(  uint8_t index, uint8_t dat, bool watering, bool ban) {	
		for (uint8_t i = 1; i < 10; i++) {
			data[(index + i) % 200] = 0;
		}
		data[index] = dat;
		data2[index] = watering ? 1 : 0 | ban ? 2 : 0;
		draw( 60 , 100 , index );
	}

	uint8_t getData(uint8_t index, bool & watering, bool & ban)  {
		//index %= 200;	    
		watering = false; 	ban = false;
		if (data2[index] & 1 ) watering = true;
		if (data2[index] & 2 ) ban = true;		
		return  data[index];
	}	

	void draw( uint16_t x0, uint8_t y, uint8_t index) {
		bool watering = false, ban = false;
		for (uint8_t x = index; x < index+1 ; x++) {

			uint8_t d = getData(x, watering, ban);
			uint16_t color = 0x0000;
			//if (x == index) color = 0xff0f;

			tft.drawLine  ( x0 + x, y, x0 + x,  y+ 80  , color);
			tft.drawPixel  (x0 + x, y + 80 - d, 0xff0f );
			
			 color = 0x0000;
			if (ban)	color = tft.color565(255, 0, 0);
			tft.drawLine( x0 + x, y + 100, x0 + x, y + 97, color);
			// watering
			color = 0x0000;
			if (watering)	color = tft.color565(0, 255, 0);				
				tft.drawLine( x0 + x, y + 90,  x0 + x, y + 87, color);
		}
	}


	Adafruit_GFX & tft;
private:

	uint8_t  data[200];	
	uint8_t data2[200];
};