#include "FS.h"
#include <EEPROM\src\EEPROM.h>

void chanel::update( uint8_t value ) {
	if (switched) {
		unsigned long v = this->timeS * 1000;
		if ((millis() - lasttime) > v) {			// the water period experied ???
			switched = false;
			lasttime = millis();
			return;
		}
	}
	unsigned long v = this->timeBan * 1000;
	banned = true;
	if (!switched && ( millis() - lasttime >  v )) {
		banned = false;
		if (value < this->threshold) {
			switched = true;
			lasttime = millis();
		}
	}

}
void chanel::switchTo ( bool v) {
	switched = v;
	lasttime = millis();

}

//-----------------------------------------------------------------
void StateMachine::update(uint16_t x, uint16_t y, uint8_t z) {
	if (current != 0) {
		current->update(x, y, z);
	}
}
//-----------------------------------------------------------------
void StateMachine::TransitionTo(State * next) {
	if (next != 0) {
		if (current)  current->exit();
		current = next;
		current->enter();
		stateTime = millis();
	}
}
//------------------------------------------------------------------
bool StateMachine::saveToEEPROM() {
	Serial.println(" Save to EEprom!");
	EEPROM.write(CHANELSADDRES, c1.threshold);
	EEPROM.write(CHANELSADDRES + 1, c1.timeS);
	EEPROM.write(CHANELSADDRES + 2, c1.timeBan);

	EEPROM.write(CHANELSADDRES + 3, c2.threshold);
	EEPROM.write(CHANELSADDRES + 4, c2.timeS);
	EEPROM.write(CHANELSADDRES + 5, c2.timeBan);

	EEPROM.write(CHANELSADDRES + 6, c3.threshold);
	EEPROM.write(CHANELSADDRES + 7, c3.timeS);
	EEPROM.write(CHANELSADDRES + 8, c3.timeBan);
}
//---------------------------------------------------------------------
bool StateMachine::LoadFromEEPROM() {
	Serial.println(" Load from EEprom!");
	c1.threshold = EEPROM.read(CHANELSADDRES);
	c1.timeS = EEPROM.read(CHANELSADDRES + 1);
	c1.timeBan = EEPROM.read(CHANELSADDRES + 2);
	//Serial.println(c1.timeBan);
	c2.threshold = EEPROM.read(CHANELSADDRES + 3);
	c2.timeS = EEPROM.read(CHANELSADDRES + 4);
	c2.timeBan = EEPROM.read(CHANELSADDRES + 5);

	c3.threshold = EEPROM.read(CHANELSADDRES + 6);
	c3.timeS = EEPROM.read(CHANELSADDRES + 7);
	c3.timeBan = EEPROM.read(CHANELSADDRES + 8);
}
