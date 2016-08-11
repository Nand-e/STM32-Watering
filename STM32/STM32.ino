

#include "Adafruit_ST7735.h" // Hardware-specific library

#include <SPI.h>
#include "EEPROM.h"


#define TFT_RST    8  
#define TFT_DC     9
#define TFT_CS     10

float sineWave(int phase);
unsigned int rainbow(byte value);
int ringMeter(int value, int vmin, int vmax, int x, int y, int r, char *units, byte scheme);

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


float p = 3.1415926;

void setup1(void) {
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








int ledPin =  13;    // LED connected to digital pin 13
const char HELP_MSG[] = "Press :\r\n" \
      " 0 display configuration\r\n" \
      " 1 set configuration to 0x801F000 / 0x801F800 / 0x400 (RB MCU)\r\n" \
      " 2 set configuration to 0x801F000 / 0x801F800 / 0x800 (ZE/RE MCU)\r\n" \
      " 3 write/read variable\r\n" \
      " 4 increment address\r\n" \
      " 5 display pages top/bottom\r\n" \
      " 6 initialize EEPROM\r\n" \
      " 7 format EEPROM\r\n";
uint16 DataWrite = 0;
uint16 AddressWrite = 0x10;

void setup()
{
  setup1();
  
  // initialize the digital pin as an output:
  pinMode(ledPin, OUTPUT);
        Serial.begin(115200);
  Serial.print(HELP_MSG);

}

void loop()
{
  uint16 Status;
  uint16 Data;

  while (Serial.available())
  {
    char cmd = (char)Serial.read();
    Serial.println(cmd);
    if (cmd == '0')
    {
      DisplayConfig();
    }
    else if (cmd == '1')
    {
      EEPROM.PageBase0 = 0x801F000;
      EEPROM.PageBase1 = 0x801F800;
      EEPROM.PageSize  = 0x400;
      DisplayConfig();
    }
    else if (cmd == '2')
    {
      EEPROM.PageBase0 = 0x801F000;
      EEPROM.PageBase1 = 0x801F800;
      EEPROM.PageSize  = 0x800;
      DisplayConfig();
    }
    else if (cmd == '3')
    {
      Status = EEPROM.write(AddressWrite, DataWrite);
      Serial.print("EEPROM.write(0x");
      Serial.print(AddressWrite, HEX);
      Serial.print(", 0x");
      Serial.print(DataWrite, HEX);
      Serial.print(") : Status : ");
      Serial.println(Status, HEX);

      Status = EEPROM.read(AddressWrite, &Data);
      Serial.print("EEPROM.read(0x");
      Serial.print(AddressWrite, HEX);
      Serial.print(", &..) = 0x");
      Serial.print(Data, HEX);
      Serial.print(" : Status : ");
      Serial.println(Status, HEX);

      ++DataWrite;
    }
    else if (cmd == '4')
    {
      ++AddressWrite;
    }
    else if (cmd == '5')
    {
      DisplayPages(0x20);
      DisplayPagesEnd(0x20);
    }
    else if (cmd == '6')
    {
      Status = EEPROM.init();
      Serial.print("EEPROM.init() : ");
      Serial.println(Status, HEX);
      Serial.println();
    }
    else if (cmd == '7')
    {
      Status = EEPROM.format();
      Serial.print("EEPROM.format() : ");
      Serial.println(Status, HEX);
    }
    else
      Serial.print(HELP_MSG);
  }
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
}

void DisplayConfig(void)
{
  Serial.print  ("EEPROM.PageBase0 : 0x");
  Serial.println(EEPROM.PageBase0, HEX);
  Serial.print  ("EEPROM.PageBase1 : 0x");
  Serial.println(EEPROM.PageBase1, HEX);
  Serial.print  ("EEPROM.PageSize  : 0x");
  Serial.print  (EEPROM.PageSize, HEX);
  Serial.print  (" (");
  Serial.print  (EEPROM.PageSize, DEC);
  Serial.println(")");
}

void DisplayHex(uint16 value)
{
  if (value <= 0xF)
    Serial.print("000");
  else if (value <= 0xFF)
    Serial.print("00");
  else if (value <= 0xFFF)
    Serial.print("0");
  Serial.print(value, HEX);
}

void DisplayPages(uint32 endIndex)
{
  Serial.println("Page 0     Top         Page 1");

  for (uint32 idx = 0; idx < endIndex; idx += 4)
  {
    Serial.print  (EEPROM.PageBase0 + idx, HEX);
    Serial.print  (" : ");
    DisplayHex(*(uint16*)(EEPROM.PageBase0 + idx));
    Serial.print  (" ");
    DisplayHex(*(uint16*)(EEPROM.PageBase0 + idx + 2));
    Serial.print  ("    ");
    Serial.print  (EEPROM.PageBase1 + idx, HEX);
    Serial.print  (" : ");
    DisplayHex(*(uint16*)(EEPROM.PageBase1 + idx));
    Serial.print  (" ");
    DisplayHex(*(uint16*)(EEPROM.PageBase1 + idx + 2));
    Serial.println();
  }
}

void DisplayPagesEnd(uint32 endIndex)
{
  Serial.println("Page 0     Bottom      Page 1");

  for (uint32 idx = EEPROM.PageSize - endIndex; idx < EEPROM.PageSize; idx += 4)
  {
    Serial.print  (EEPROM.PageBase0 + idx, HEX);
    Serial.print  (" : ");
    DisplayHex(*(uint16*)(EEPROM.PageBase0 + idx));
    Serial.print  (" ");
    DisplayHex(*(uint16*)(EEPROM.PageBase0 + idx + 2));
    Serial.print  ("    ");
    Serial.print  (EEPROM.PageBase1 + idx, HEX);
    Serial.print  (" : ");
    DisplayHex(*(uint16*)(EEPROM.PageBase1 + idx));
    Serial.print  (" ");
    DisplayHex(*(uint16*)(EEPROM.PageBase1 + idx + 2));
    Serial.println();
  }
}










/*
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
*/
