#include "widget.h"

void Theme::drawBox(Adafruit_GFX * tft, uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, bool pushed) {
	if (!pushed) {
		tft->drawLine(x1, y1, x1 + w - 1, y1, WHITE);
		tft->drawLine(x1, y1, x1, y1 + h, WHITE);

		tft->drawLine(x1 + w - 1, y1 + 1, x1 + w - 1, y1 + h - 1, LIGHTER); // |
		tft->drawLine(x1 + 1, y1 + h - 1, x1 + w - 2, y1 + h - 1, LIGHTER);  // -

		tft->drawLine(x1 + w, y1, x1 + w, y1 + h, DARK);     // |		
		tft->drawLine(x1, y1 + h, x1 + w, y1 + h, DARK);   // -

		tft->fillRect(x1 + 1, y1 + 1, w - 2, h - 2, LIGHT);
	}
	else {
		tft->drawLine(x1, y1, x1 + w - 1, y1, DARK);
		tft->drawLine(x1, y1, x1, y1 + h, DARK);

		tft->drawLine(x1 + 1, y1 + 1, x1 + 1, y1 + h - 1, LIGHTER); // |
		tft->drawLine(x1 + 1, y1 + 1, x1 + w - 2, y1 + 1, LIGHTER);  // -

		tft->drawLine(x1 + w, y1, x1 + w, y1 + h, WHITE);     // |		
		tft->drawLine(x1, y1 + h, x1 + w, y1 + h, WHITE);   // -

		tft->fillRect(x1 + 2, y1 + 2, w - 2, h - 2, LIGHT);

	}
}

/**********************************************************************/ 
void Widget::setDisplay(Adafruit_GFX * tft1) { tft =tft1 ; }
Adafruit_GFX * Widget::tft;
Theme        * Widget::theme;

