#include "FS.h"

EEPROMClass EEPROM;

//#define Debug 


// Hardwer PIN defines 
	#define S1PIN 12
	#define S2PIN 13
	#define S3PIN 14
	#define SCREEN 4
//-------------------------------------------------------------------



//-------------------------------------------------------------------
chanel::chanel() {
	threshold = 0;
	timeS = 0;
	timeBan = 0;
	switched = false;	
	lasttime = 1000 * 60 * 60 * 0;  // millis * secund  * minute  * hour
}

void chanel::update( uint8_t value ) {
	unsigned long v = this->timeS * 100;
	if (switched) {
		v = this->timeS * 100;
		if ((millis() - lasttime) > v) {			// the water period experied ???
			switched = false;
			lasttime = millis();
			return;
		}
		#ifdef Debug 
		Serial.print("Lt:");
		Serial.print(millis() - lasttime);
		Serial.print(" vt:");
		Serial.println(v);
		#endif
	}  //switched == true

	unsigned long bantime = this->timeBan * 100;
	banned = true;
	if (!switched) {
		#ifdef Debug  
		Serial.print("Bt:");
		Serial.print( ( millis() - lasttime ) / 1000 );
		Serial.print(" vt:");
		Serial.print( bantime );
		Serial.print("| value:");
		Serial.print( value );
		Serial.print(" thres:");
		Serial.println( this->threshold );       
		#endif 
		if (millis() - lasttime > bantime) {   // time ban experied ?????
			banned = false;
			if (value < this->threshold) {
				switched = true;
				lasttime = millis();
			}
		}
	} // switched == false

}
void chanel::switchTo ( bool v) {
	switched = v;
	lasttime = millis();
}

//-----------------------------------------------------------------
StateMachine::StateMachine(State * starts, Adafruit_GFX & tft1)  :
	tft(tft1)
{
	current = starts;
	stateTime = 0;
	lastPush = 0;
	screen = 140;
	screenActive = true;
	EEPROM.PageBase0 = 0x801F000;
	EEPROM.PageBase1 = 0x801F800;
	EEPROM.PageSize = 0x400;
	pinMode(S1PIN, OUTPUT);
	pinMode(S2PIN, OUTPUT);
	pinMode(S3PIN, OUTPUT);
}

void StateMachine::updatePump() {
	digitalWrite(S1PIN, c1.switched);
	digitalWrite(S2PIN, c2.switched);
	digitalWrite(S3PIN, c3.switched);
}

void StateMachine::update(uint16_t x, uint16_t y, uint8_t z) {
	if (current != 0) { current->update(x, y, z); }
	
	updatePump();

	// sreen light handling 
	if (z > 200) { lastPush = millis();	}	
	if (screenActive && (millis() - lastPush > 20000)) {
		if (screen > 30) { screen--; }
		else { screenActive = false; }
	}

	if (screenActive == false && (millis() - lastPush < 2000)) {
		if (screen < 255) { screen++; }
		else { screenActive = true; }
	}

	analogWrite(SCREEN, screen);
	//
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
	Serial.println(" Save to EEPROMprom!");
	EEPROM.write(CHANELSADDRES    , c1.threshold);
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
	c1.threshold  = EEPROM.read(CHANELSADDRES);
	c1.timeS      = EEPROM.read(CHANELSADDRES + 1);
	c1.timeBan    = EEPROM.read(CHANELSADDRES + 2);

	c2.threshold  = EEPROM.read(CHANELSADDRES + 3);
	c2.timeS      = EEPROM.read(CHANELSADDRES + 4);
	c2.timeBan    = EEPROM.read(CHANELSADDRES + 5);

	c3.threshold  = EEPROM.read(CHANELSADDRES + 6);
	c3.timeS      = EEPROM.read(CHANELSADDRES + 7);
	c3.timeBan    = EEPROM.read(CHANELSADDRES + 8);
}
