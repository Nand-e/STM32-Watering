
#include <Adafruit_GFX.h>    // Core graphics library
#include "Adafruit_ST7735.h" // Hardware-specific library
#include "rainbow.h"
#include <SPI.h>

#define TFT_RST    8  
#define TFT_DC     9
#define TFT_CS     10

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!

#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5

// Color definitions
#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F


float p = 3.1415926;

void setup(void) {
  Serial.begin(9600);
  Serial.print("Hello! ST7735 TFT Test");

  tft.initR(INITR_GREENTAB);   // initialize a ST7735S chip, black tab
  tft.fillRect (0,0,128,160, 0x000f );
  tft.setRotation (1);
}

uint16_t d = 0;
uint16_t a1avg[10];
uint16_t a2avg[10];
uint8_t counter = 0;
void loop() {

  a1avg[counter] = analogRead ( D3 ) / 2;
  a2avg[counter] = analogRead ( D11 ) / 2;
  counter++;
  counter%=10;
  uint16_t a1=0;
  uint16_t a2=0;
  for ( int i =0; i < 10; i++ ) {
    a1 += a1avg[i];
    a2 += a2avg[i];
  }
  a1 /= 10;
  a2 /= 10;
  
   d += 5; if (d >= 360) d = 0;

    // Set the the position, gap between meters, and inner radius of the meters
    int xpos = 3, ypos = 5, gap = 4, radius = 24;

    // Test with Sine wave function, normally reading will be from a sensor
    uint16_t reading = 250 + 250 * sineWave(d+0);
    xpos = gap + ringMeter(a1, 0, 255, xpos, ypos, radius, "mA", GREEN2RED); // Draw analogue meter

    reading = 20 + 30 * sineWave(d+60);
    xpos = gap + ringMeter(a2, 0, 255, xpos, ypos, radius, "degC", GREEN2RED); // Draw analogue meter

    reading = 50 + 50 * sineWave(d + 120);
    ringMeter(reading, 0, 100, xpos, ypos, radius, "%RH",GREEN2RED); // Draw analogue meter
   delay( 50 );

}

