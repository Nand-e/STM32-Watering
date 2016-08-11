#include "widget.h"

Theme::Theme() {
	BRIGHT  = 0xEF5D;
	FILL1   = 0x94b2;
	FILL2   = 0x000;	
	FT1		 = 0xEF5D;
	FT2     = 0x0000;
	FB1     = 0x10A2;
	FB2		= 0x5422;
	BACK    = FILL1;
}

void Theme::drawBox(Adafruit_GFX * tft, uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, bool pushed, bool onlyframe) {
	if (!pushed) {
		tft->drawLine(x1, y1, x1 + w - 1, y1, BRIGHT);
		tft->drawLine(x1, y1, x1, y1 + h,     BRIGHT);

		tft->drawLine(x1 + w - 1, y1 + 1, x1 + w - 1, y1 + h - 1, FB2); // |
		tft->drawLine(x1 + 1, y1 + h - 1, x1 + w - 2, y1 + h - 1, FB2);  // -

		tft->drawLine(x1 + w, y1, x1 + w, y1 + h, FB1);     // |		
		tft->drawLine(x1, y1 + h, x1 + w, y1 + h, FB1);   // -
		if ( !onlyframe )	tft->fillRect(x1 + 1, y1 + 1, w - 2, h - 2, FILL1);
	}
	else {
		tft->drawLine(x1, y1, x1 + w - 1, y1, FB1);
		tft->drawLine(x1, y1, x1, y1 + h,     FB1);

		tft->drawLine(x1 + 1, y1 + 1, x1 + 1, y1 + h - 1, FB2); // |
		tft->drawLine(x1 + 1, y1 + 1, x1 + w - 2, y1 + 1, FB2);  // -

		tft->drawLine(x1 + w, y1, x1 + w, y1 + h, BRIGHT);     // |		
		tft->drawLine(x1, y1 + h, x1 + w, y1 + h, BRIGHT);   // -

		if (!onlyframe) tft->fillRect(x1 + 2, y1 + 2, w - 2, h - 2, FILL1);

	}
}

Theme2::Theme2() {
	FB1     = 0x3333;
	FILL2   = 0x427f;
	FILL1   = 0x94ff;
	BRIGHT  = 0xEF5D;
	BACK    = FILL1;
}

void Theme2::drawBox(Adafruit_GFX * tft, uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, bool pushed, bool onlyframe) {
	if (!pushed) {
		tft->drawRoundRect(x1, y1, w, h, 3, BRIGHT);
		tft->drawRoundRect(x1 + 1, y1 + 1, w - 1, h - 1, 3, FB1);
		tft->fillRoundRect(x1 + 1, y1 + 1, w - 2, h / 2 + 1, 3, FILL1 );
		tft->fillRect     (x1 + 1, y1 + h /2, w - 2, 3, FILL2);
		tft->fillRoundRect(x1 + 1, y1 + h / 2, w - 2, h / 2-1, 3, FILL2);

	}
	else { // pushed
		tft->drawRoundRect(x1, y1, w, h, 3, BRIGHT );
		tft->drawRoundRect(x1, y1, w - 2, h - 2, 3, FB1);   
		tft->fillRoundRect(x1 + 1, y1 + 1, w - 2, h / 2 + 1, 3, FILL2);
		tft->fillRect     (x1 + 1, y1 + h /2, w - 2, 3, FILL1);
		tft->fillRoundRect(x1 + 1, y1 + h / 2, w - 2, h / 2-1, 3, FILL1 );
	}
}


Theme3::Theme3() {
	BRIGHT = 0xEF5D;
	FILL1  = 0x94b2;
	FILL2  = 0x84a2;;
	FT1    = 0xeeee;
	FT2    = 0x0000;
	FB1    = 0x10A2;
	FB2    = 0x5422;
	BACK   = FILL1;
}



/**********************************************************************/ 
void Widget::setDisplay(Adafruit_GFX * tft1) { tft =tft1 ; }
Adafruit_GFX * Widget::tft;
Theme        * Widget::theme;

