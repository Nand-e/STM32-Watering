#include "WateringSetup.h"
#include "measure.h"
#include "Bitmaps.h"
#include "widget.h"

extern Theme theme1;
extern Theme2 theme2;
extern Theme3 theme3;

extern measure baseState;

#define SY1 80
#define SY2 120
#define SY3 160



WateringSetup::WateringSetup(StateMachine * m, Adafruit_TFTLCD * tft1) :
	State(m), tft(tft1),
	scroll1( 52, SY1, 180),
	scroll2( 52, SY2, 180 ),
	scroll3( 52, SY3, 180 ),
	ch1Button( 65,  5, SY1-20, 30, 8, false, 0, "ch1"),
	ch2Button( 135, 5, SY1-20, 30, 9, false, 0, "ch2"),
	ch3Button( 205, 5, SY1-20, 30, 10, false,0, "ch3"),
	back(255, 200, 60, 35, 12, false, 0, "Back"),
	save(180, 200, 60, 35, 13, false, 0, "Save"),
	style1(10, 200, 40, 35, 20, false, 0, "T1"),
	style2(60, 200, 40, 35, 21, false, 0, "T2"),
  style3(110, 200, 40, 35, 22, false, 0, "T3")
{
  //------
	ch1Button.setColors(0xffff, 0x50ee);
	ch2Button.setColors(0xffff, 0x50ee);
	ch3Button.setColors(0xffff, 0x50ee);
  
  back.setColors(0xffff, 0x50ee);
	save.setColors(0xffff, 0x50ee);
 
	holder.addWidget(&back , this);
	holder.addWidget(&save , this);
	holder.addWidget(&ch1Button, this);
	holder.addWidget(&ch2Button, this);
	holder.addWidget(&ch3Button, this);
  holder.addWidget(&scroll1);
  holder.addWidget(&scroll2);
  holder.addWidget(&scroll3);
	holder.addWidget(&style1 , this);
	holder.addWidget(&style2 , this);
	holder.addWidget(&style3 , this);
	
	machine->LoadFromEEPROM();	

}
//----------
void WateringSetup::enter() {

	//Widget::theme->drawBox(tft, 0, 0 , 319, 239, false);	
	//Widget::theme->drawBox(tft, 10, SY1 - 35, 300, 150, false);
  
  tft->fillRect(0, 0, 320, 240, tft->color565(100, 0, 100));
  tft->drawRoundRect(0, 0, 320, 240, 3, 0xfefe);
	
	actualChanel = &machine->c1;	
	
	tft->drawBitmap( 17, SY1 -2, Water  , 32, 32, 0x0000);
	tft->drawBitmap( 17, SY2 -2, Clock  , 32, 32, 0x0000);
	tft->drawBitmap( 17, SY3 -2, TimeBan, 32, 32, 0x0000);
	
  holder.redrawWs();
  
  scroll1.setValue(actualChanel->threshold);
  scroll2.setValue(actualChanel->timeS);
	scroll3.setValue(actualChanel->timeBan);
	callBack1(true, 8);
	//Serial.println("->Setup");
}

void WateringSetup::update(uint16_t x, uint16_t y, uint8_t z) {
	holder.updateWs(x, y, z);
}

void WateringSetup::callBack1(bool pressed, uint8_t id) {
	if (pressed) {
		if (id == 12) {
			machine->TransitionTo(&baseState);
			return;
		}

		if (id == 20) {
			Widget::theme = &theme2;
		  enter();
		  return;
		}

		if (id == 21) {
			Widget::theme = &theme1;
      enter();
      return;
		}
    if (id == 22) {
      Widget::theme = &theme3;
      enter();
      return;
    }
   
		// copy data to chanel data from scroll
		actualChanel->threshold = scroll1.getValue();
		actualChanel->timeS     = scroll2.getValue();
		actualChanel->timeBan   = scroll3.getValue();
	
		if (id == 13) {
			machine->saveToEEPROM();
			machine->TransitionTo(&baseState);
			return;
		}
		tft->setTextSize(2);
		tft->setTextColor(Widget::theme->BRIGHT);
		tft->setCursor(15, SY1-30);
		tft->fillRect(15, SY1 - 30, 45, 25, Widget::theme->BACK);
		
		if (id == 8) {
			actualChanel = & machine->c1;	
			tft->print("CH1");
		}
		if (id == 9) {
			actualChanel = & machine->c2;
			tft->print("CH2");
		}
		if (id == 10) {
			actualChanel = & machine->c3;
			tft->print("CH3");
		}
		scroll1.setValue(actualChanel->threshold);
		scroll2.setValue(actualChanel->timeS);
		scroll3.setValue(actualChanel->timeBan);
	}	
}

void WateringSetup::exit() {}

WateringSetup::~WateringSetup()
{

}
