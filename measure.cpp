#include "measure.h"
#include "WateringSetup.h"


#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5

extern WateringSetup setupState;

measure::measure(StateMachine * m, Adafruit_TFTLCD * tft1) :
State(m),
tft(tft1),
b1(5, 200, 60, 35, 18, false, 0, "Setup"),
bg1(tft1, 30, 20, 200),
bg2(tft1, 30, 60, 200),
bg3(tft1, 30, 100, 200)
	//b2( 100, 200, 50, 35 ,6)
{	
	b1.setDisplay(tft);
	b1.setHandler(this);
	b1.setColors(0xffff, 0x00ee);
	//b2.setHandler(this);
}

void measure::enter() {
	tft->fillRect(0, 0, 320, 240, tft->color565(100, 0, 100));
	tft->drawRoundRect(0, 0, 320, 240, 3, 0xfefe);
	b1.updateGraphic();
	Serial.println("Measuring Mode");
	//b2.updateGraphic();
}

void measure::exit() {}

void measure::update(uint16_t x, uint16_t y, uint8_t z) {
	
//	b2.update(x, y, z);
	
	static uint8_t d = 0;
	static uint8_t c = 0;
	
	d++; 
	if (d >= 5) {
		d = 0;
		c++;
		c %= 100;
		tft->setTextSize(4);
		tft->setCursor(150, 150);
		tft->fillRect(150, 150, 50, 50, tft->color565(100, 0, 100));
		tft->print(c);

	}
	bg1.setValue(c, 40);
	bg2.setValue(c, 60);
	bg3.setValue(c, 200 - c);
	// Set the the position, gap between meters, and inner radius of the meters
	int xpos = 3, ypos = 5, gap = 4, radius = 50;
	// xpos = gap + ringMeter(d, 0, 255, xpos, ypos, radius, "mA", GREEN2RED); // Draw analogue meter

	b1.update(x, y, z);
}

void measure::callBack1(bool pressed, uint8_t) {
	//tft->fillRect(0, 0, 100, 100, 0xf0f0);
	if (pressed) {
		machine->TransitionTo(&setupState);
	}
}

int measure::ringMeter(int value, int vmin, int vmax, int x, int y, int r, char *units, byte scheme)
{
	// Minimum value of r is about 52 before value text intrudes on ring
	// drawing the text first is an option

	x += r; y += r;   // Calculate coords of centre of ring
	int  w = r / 4;    // Width of outer ring is 1/4 of radius  
	int  angle = 150;  // Half the sweep angle of meter (300 degrees)
	int  text_colour = 0; // To hold the text colour
	int  v = map(value, vmin, vmax, -angle, angle); // Map the value to an angle v
	byte seg = 5; // Segments are 5 degrees wide = 60 segments for 300 degrees
	byte inc = 5; // Draw segments every 5 degrees, increase to 10 for segmented ring

	// Draw colour blocks every inc degrees
	for (int i = -angle; i < angle; i += inc) {

		// Choose colour from scheme
		int colour = 0;
		switch (scheme) {
	/*	case 0: colour = ILI9341_RED; break; // Fixed colour
		case 1: colour = ILI9341_GREEN; break; // Fixed colour
		case 2: colour = ILI9341_BLUE; break; // Fixed colour */
		case 3: colour = rainbow(map(i, -angle, angle, 0, 127)); break; // Full spectrum blue to red
		case 4: colour = rainbow(map(i, -angle, angle, 63, 127)); break; // Green to red (high temperature etc)
		case 5: colour = rainbow(map(i, -angle, angle, 127, 63)); break; // Red to green (low battery etc)
		default: colour = 0x001f; break;     // Fix colour
		}

		// Calculate pair of coordinates for segment start
		float sx = cos((i - 90) * 0.0174532925);
		float sy = sin((i - 90) * 0.0174532925);
		uint16_t x0 = sx * (r - w) + x;
		uint16_t y0 = sy * (r - w) + y;
		uint16_t x1 = sx * r + x;
		uint16_t y1 = sy * r + y;

		// Calculate pair of coordinates for segment end
		float sx2 = cos((i + seg - 90) * 0.0174532925);
		float sy2 = sin((i + seg - 90) * 0.0174532925);
		int x2 = sx2 * (r - w) + x;
		int y2 = sy2 * (r - w) + y;
		int x3 = sx2 * r + x;
		int y3 = sy2 * r + y;

		if (i < v) { // Fill in coloured segments with 2 triangles
			tft->fillTriangle(x0, y0, x1, y1, x2, y2, colour);
			tft->fillTriangle(x1, y1, x2, y2, x3, y3, colour);
			text_colour = colour; // Save the last colour drawn
		}
		else // Fill in blank segments
		{
			tft->fillTriangle(x0, y0, x1, y1, x2, y2, 0x0005);
			tft->fillTriangle(x1, y1, x2, y2, x3, y3, 0x0005);
		}
	}

	// Convert value to a string
	char buf[10];
	byte len = 4; if (value > 999) len = 5;
	dtostrf(value, len, 0, buf);
	
	// Set the text colour to default
	//tft->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
	// Uncomment next line to set the text colour to the last segment value!
	// tft.setTextColor(text_colour, ILI9341_BLACK);

	// Print value, if the meter is large then use big font 6, othewise use 4
	//if (r > 84) tft.drawCentreString(buf, x - 5, y - 20, 6); // Value in middle
	// else tft.drawCentreString(buf, x - 5, y - 20, 4); // Value in middle

	// Print units, if the meter is large then use big font 4, othewise use 2
	//tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
	//if (r > 84) tft.drawCentreString(units, x, y + 30, 4); // Units display
	// else tft.drawCentreString(units, x, y + 5, 2); // Units display

	// Calculate and return right hand side x coordinate
	return x + r;
}

// #########################################################################
// Return a 16 bit rainbow colour
// #########################################################################
unsigned int measure::rainbow(uint8_t value)
{
	// Value is expected to be in range 0-127
	// The value is converted to a spectrum colour from 0 = blue through to 127 = red

	byte red = 0; // Red is the top 5 bits of a 16 bit colour value
	byte green = 0;// Green is the middle 6 bits
	byte blue = 0; // Blue is the bottom 5 bits

	byte quadrant = value / 32;

	if (quadrant == 0) {
		blue = 31;
		green = 2 * (value % 32);
		red = 0;
	}
	if (quadrant == 1) {
		blue = 31 - (value % 32);
		green = 63;
		red = 0;
	}
	if (quadrant == 2) {
		blue = 0;
		green = 63;
		red = value % 32;
	}
	if (quadrant == 3) {
		blue = 0;
		green = 63 - 2 * (value % 32);
		red = 31;
	}
	return (blue << 11) + (green << 5) + red;
}
