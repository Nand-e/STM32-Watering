#include "BarGraph.h"


BarGraph::BarGraph( Adafruit_GFX * tft1, uint16_t x1, uint16_t y1, uint8_t w1 ) :
  tft(tft1), 
  x(x1),
  y(y1),
  w(w1)
{
	oldValue = 0;
}



void BarGraph::setValue(uint8_t newValue) {
	if (oldValue != newValue) {
		oldValue = newValue;
		updateGraphic();
	}
}

void BarGraph::updateGraphic() {
	if (tft == 0) return;
	tft->fillRect(x, y, oldValue, 20, 0xEEEE);
	tft->fillRect(x + oldValue, y, w - oldValue, 20, 0x0eee);
}
