
#include "Scroll.h"
#include "TFT.h"

Adafruit_TFTLCD *ScrollBar::tft;

// ScrollBar***************************************************************************************
#define BACK  0b0011100011100111


//*************************************************************************************************
ScrollBar::ScrollBar(uint16_t x1, uint16_t y1, uint8_t w, const uint16_t * bmp) :
x(x1), y(y1), width(w)
{
	b1.setDisplay(tft);
	b1.setHandler(this);
	b2.setHandler(this);
	value = 0;
	bitmapH = 32;	bitmapW = 32;
	ArrowW = 22;
	bitmap = bmp;
	b1.set(x + bitmapW + 4, y, 32, 32, 0, true, BACK);
	b2.set(x + ArrowW + bitmapW + width + 8 + 10, y, 32, 32, 1, false, BACK);

}
//*************************************************************************************************
void ScrollBar::update(uint16_t x, uint16_t y, uint16_t z) {
	b1.update(x, y, z);
	b2.update(x, y, z);

}
//*************************************************************************************************
void ScrollBar::setDisplay(Adafruit_TFTLCD* tft) {
	ScrollBar::tft = tft;
}

//*************************************************************************************************
void ScrollBar::updateGraphic() {
	if (tft == 0) return;
	tft->fillRoundRect(x - 2, y - 2, width + bitmapW * 2 + ArrowW + 10, bitmapH + 4, 2, BACK);
	tft->drawRoundRect(x - 2, y - 2, width + bitmapW * 2 + ArrowW + 10, bitmapH + 4, 2, tft->color565(150, 150, 150));
	tft->drawLine(x + bitmapW + 2, y - 1, x + bitmapW + 2, y + bitmapH + 1, tft->color565(150, 150, 150));
	tft->fillRect(x + ArrowW + bitmapW + 6, y + 2, width, 28, tft->color565(100, 100, 200));
	callBack1(true, 1);
	if (bitmap != 0) {
		tft->drawBMP2(x, y, bitmap, 32, 32, false, 0, BACK);
	}
	callBack2(true, 0 );
	b1.updateGraphic();
	b2.updateGraphic();
	
}

//*************************************************************************************************
void ScrollBar::callBack1(bool pressed, uint8_t ID) {};
void ScrollBar::callBack2(bool pressed, uint8_t ID) {
	if (pressed) {
		uint8_t oldv = value;
		switch (ID) {
		case 0:   value--; break;
		case 1:   value++; break;
		}
		value %= width;
		if (oldv != value)
		{
			if (tft == 0) return;
			tft->fillRect(x + bitmapW + ArrowW + 6 + oldv, y + 2, 10, 28, tft->color565(100, 100, 200));
			tft->fillRoundRect(x + bitmapW + ArrowW + 6 + value, y + 2, 10, 28, 3, tft->color565(100, 200, 200));
		}
	}
}

