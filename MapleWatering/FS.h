#ifndef FSMACHINE
#define FSMACHINE

#include <Arduino.h>
#include "Adafruit_GFX.h"
#include <EEPROM.h>

#include "ChartData.h"
#include "State.h"

#define CHANELSADDRES 1000

//#include "DataStore.h"


class  chanel {
public:	
	chanel();
	uint8_t threshold;
	uint8_t timeS;
	uint8_t timeBan;
	void update( uint8_t v);
	void switchTo ( bool v);
	bool switched;
	bool banned;	
	unsigned long lasttime;
};


class StateMachine {
public:
	StateMachine(State * starts, Adafruit_GFX & tft1);
	void update(uint16_t x, uint16_t y, uint8_t z);
	void TransitionTo(State * next);
	unsigned long  getTimeIn() { return (millis() - stateTime); }
	bool saveToEEPROM();		  	// Save Chanel information to eeprom
	bool LoadFromEEPROM();			// Load Chanel information from eeprom
	void updatePump();
	chanel c1, c2, c3;
	uint8_t screen;

private:
	State * current;
	unsigned long stateTime;
	//DataStore<uint8_t> store;
	Adafruit_GFX & tft;
	unsigned long lastPush;
	bool screenActive;

};

#endif
