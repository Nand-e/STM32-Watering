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

void BarGraph::setThreshold(uint8_t th) {
	thres = th;
	if (thres != oldthres) {
		updateGraphic();
	}
}

void BarGraph::setValue(uint8_t newValue) {
	if (oldValue != newValue ) {
		oldValue = newValue;
		updateGraphic();
	}
}

void BarGraph::updateGraphic() {
	if (tft == 0) return;
	
	//if (thres != oldthres) {
	uint8_t v = map(oldthres, 0, 255, 0, w);
	tft->fillTriangle(x + v- 5, y - 10, x + v + 5, y - 10,
			x + v, y, 0x0000);	
	v = map(thres, 0, 255, 0, w);
	tft->fillTriangle(x + v - 5, y - 10, x + v + 5, y - 10,
			x + v, y, 0x0eee);
		
	oldthres = thres;
	//}
	tft->drawRoundRect(x - 2, y - 2, w + 4, 24, 3, 0xffff);
	v = map(oldValue, 0, 255, 0, w);
	tft->fillRect( x, y, v, 20, 0xEEEE);
	tft->fillRect( x + v, y, w - oldValue, 20, 0x0eee);
}
