#include "BarGraph.h"


BarGraph::BarGraph( Adafruit_GFX * tft1, uint16_t x1, uint16_t y1, uint8_t w1 ) :
  tft(tft1), 
  x(x1),
  y(y1),
  w(w1)
{
	oldValue = 0;
	thres = oldthres + 10;
}

void BarGraph::setValue(uint8_t newValue, uint8_t th) {
	thres = th;
	if (oldValue != newValue || thres != oldthres) {
		oldValue = newValue;
		updateGraphic();
	}
}

void BarGraph::updateGraphic() {
	if (tft == 0) return;
	
	if (thres != oldthres) {
		tft->fillTriangle(x + oldthres - 5, y - 10, x + oldthres + 5, y - 10,
			x + oldthres, y, 0x0000);		
		tft->fillTriangle(x + thres - 5, y - 10, x + thres + 5, y - 10,
			x + thres, y, 0x0eee);
		oldthres = thres;
	}
	tft->drawRoundRect(x - 2, y - 2, w + 4, 24, 3, 0xffff);
	tft->fillRect( x, y, oldValue, 20, 0xEEEE);
	tft->fillRect( x + oldValue, y, w - oldValue, 20, 0x0eee);
}
