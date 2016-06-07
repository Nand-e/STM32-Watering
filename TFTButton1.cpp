#include <Arduino.h>

#include "TFTButton1.h"
#include "TFT.h"


/**************************************************************************************************************/
Button1::Button1() {
	handler = 0;
}

/*Construct Button in x,y coordinate **************************************************************************/
Button1::Button1(uint16_t x0, uint16_t y0, uint16_t w0, uint16_t h0, uint8_t id, bool mirrored1, uint16_t color) :
Button(x0, y0, w0, h0, id, mirrored1, color)
{ };


/*
**********************************************************************************/
void Button1::updateGraphic() {
	if (tft == 0) return;
	
	if (pressed) {
		tft->drawRoundRect( x1,  y1, w, h, RAD, WHITE );
		tft->fillRoundRect( x1 + 2, y1+2, w - 4, h -4, RAD, BLACK );
		tft->fillRoundRect( x1 + 4, y1+4, w - 8, h -8, RAD, WHITE );
		tft->drawRoundRect ( x1 + 4,  y1 + 4, w -8 , h - 8, RAD , WHITE );   

		//   tft.setCursor( x1 + 28, y1 +  16);
		//   tft.setTextColor( 0x84FF );
		//   tft.setTextSize(4);
		//  tft.println( sign);

	}
	else {
		tft->fillRoundRect( x1 + 2, y1+2, w - 4, h -4, RAD, BLACK );
		tft->drawRoundRect ( x1,  y1, w, h, RAD , WHITE );
		tft->drawRoundRect ( x1 + 2,  y1 + 2, w -4 , h - 4, RAD , WHITE );

	//	tft->setCursor( x1 + 28, y1 + 16 );     
	//	tft->setTextColor( 0b1011110111110111  );       
	//	tft->setTextSize(4);
	//  tft.print( sign );     
	    
	}
}
