
#include  "ChartData.h"


ChartData::ChartData(Adafruit_GFX & tft1, uint8_t x1, uint8_t y1) :
	tft(tft1),
	x0(x1), y0(y1)
{};
/**********************************************************************************/
void ChartData::setData(uint8_t index, uint8_t dat, bool w1, bool b1,
													bool w2, bool b2,
													bool w3, bool b3) {
	/*for (uint8_t i = 1; i < 10; i++) {
		data[(index + i) % 200] = 0;
		}*/
	data[index] = dat;
	data2[index] = w1 ? 1 : 0 | b1 ? 2 : 0;
	data2[index] |= w2 ? 4 : 0 | b2 ? 8: 0;
	data2[index] |= w3 ? 16 : 0 | b3 ? 32 : 0;
	draw(index);
}
/**********************************************************************************/
uint8_t ChartData::getData(uint8_t index)  {
	//index %= 200;	    
//	w1  = b1 = false;
//	if (data2[index] & 1) w1 = true;
//	if (data2[index] & 2) b1 = true;	
	return  data[index];
}
/************************************************************************************/
void ChartData::draw(uint8_t index) {
	static uint8_t arr[6] = { 1, 2, 4, 8, 16, 32 };
	
	bool watering = false, ban = false;
	for (uint8_t x = index; x < index + 1; x++) {

		uint8_t d = data[x];
		uint16_t color = 0x0000;
		//if (x == index) color = 0xff0f;
#define HCHART 86
#define HC1    90

		tft.drawLine(x0 + x, y0, x0 + x, y0 + HCHART, color);
		tft.drawPixel(x0 + x, y0 + 80 - d, 0xff0f);
		
		for (uint8_t i = 0; i < 3; i++) {			
			// watering / chanel
			color = 0x0000;
			if (data2[x] & arr[i * 2]) color = tft.color565(0, 255, 0);
			uint8_t yv = y0 + HC1 + i * 7;
			tft.drawLine(x0 + x, yv, x0 + x, yv+1, color);
			// ban / chanel
			color = 0x0000;
			if (data2[x] & arr[i * 2 +1])	color = tft.color565(255, 0, 0);
			yv = y0 + HC1 + 3  + i * 7;
			tft.drawLine(x0 + x, yv, x0 + x, yv + 1, color);
		}










	}
}