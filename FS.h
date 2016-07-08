#ifndef FSMACHINE
#define FSMACHINE

#include <Arduino.h>
#include <EEPROM\EEPROM.h>

#include "State.h"
#define CHANELSADDRES 1000

#include "DataStore.h"


struct chanel {
	chanel();
	enum State { off, on };	
	uint8_t threshold;
	uint8_t timeS;
	uint8_t timeBan;
	State state;
	long lasttime = 0;
};


class StateMachine {
  public:
  StateMachine ( State * starts= 0 ): 
  store ( 0, 50 )
  {
    current = starts;
    stateTime = 0;
  }
  void update(uint16_t x, uint16_t y, uint8_t z); 
  void TransitionTo (State * next);
  unsigned long  getTimeIn () {   return ( millis () - stateTime );  }  

  bool saveToEEPROM();		// Save Chanel information to eeprom
  bool LoadFromEEPROM();	// Load Chanel information from eeprom

  chanel c1, c2, c3;
private:
  State * current;
  unsigned long stateTime;
  DataStore<uint8_t> store;
	
};





#endif
