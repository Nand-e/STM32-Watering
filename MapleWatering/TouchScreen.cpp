

#include "Arduino.h"
#include "TouchScreen.h"

// increase or decrease the touchscreen oversampling. This is a little different than you make think:
// 1 is no oversampling, whatever data we get is immediately returned
// 2 is double-sampling and we only return valid data if both points are the same
// 3+ uses insert sort to get the median value.
// We found 2 is precise yet not too slow so we suggest sticking with it!

#define NUMSAMPLES 2

TSPoint::TSPoint(void) {
  x = y = 0;
}

TSPoint::TSPoint(int16_t x0, int16_t y0, int16_t z0) {
  x = x0;
  y = y0;
  z = z0;
}

bool TSPoint::operator==(TSPoint p1) {
  return  ((p1.x == x) && (p1.y == y) && (p1.z == z));
}

bool TSPoint::operator!=(TSPoint p1) {
  return  ((p1.x != x) || (p1.y != y) || (p1.z != z));
}

#if (NUMSAMPLES > 2)
static void insert_sort(int array[], uint8_t size) {
  uint8_t j;
  int save;
  
  for (int i = 1; i < size; i++) {
    save = array[i];
    for (j = i; j >= 1 && save < array[j - 1]; j--)
      array[j] = array[j - 1];
    array[j] = save; 
  }
}
#endif

TSPoint TouchScreen::getPoint(void) {
  int x, y, z;
  int samples[NUMSAMPLES];
  uint8_t i, valid;
  valid = 1;
  // delayMicroseconds(20);            // Fast ARM chips need to allow voltages to settle
  
  for (i=0; i<NUMSAMPLES; i++) {
     samples[i] = readTouchX();
  }   
/*  
#if NUMSAMPLES > 2
   insert_sort(samples, NUMSAMPLES);
#endif
*/

#if NUMSAMPLES == 2
   // Allow small amount of measurement noise, because capacitive
   // coupling to a TFT display's signals can induce some noise.
  if (samples[0] - samples[1] < -10 || samples[0] - samples[1] > 10) {
     valid = 0;
   } else {
     samples[1] = (samples[0] + samples[1]) >> 1; // average 2 samples
   }
        
#endif
   x = samples[0] + samples [1] /2;

  for (i=0; i<NUMSAMPLES; i++) {      
     samples[i] = readTouchY();
  }   
   y= samples[0] + samples [1] / 2;
  
  // Set X+ to ground
   pinMode(_xp, OUTPUT);
   //*portOutputRegister(xp_port) &= ~xp_pin;
   digitalWrite(_xp, LOW);
  
   // Set Y- to VCC
   //*portOutputRegister(ym_port) |= ym_pin;
   digitalWrite(_ym, HIGH); 
  
   // Hi-Z X- and Y+
   //*portOutputRegister(yp_port) &= ~yp_pin;
   digitalWrite(_yp, LOW);
   pinMode(_yp, INPUT); 
  
   int z1 = analogRead(_xm)/6; 
   int z2 = analogRead(_yp)/6;

   if (_rxplate != 0) {
     // now read the x 
     float rtouch;
     rtouch = z2;
     rtouch /= z1;
     rtouch -= 1;
     rtouch *= x;
     rtouch *= _rxplate ;
     rtouch /= 1024;     
     z = rtouch;
   } else {
     z = (1023-(z2-z1));
   }

   if (! valid) {
     z = 0;
   }

   return TSPoint(x, y, z);
}

TouchScreen::TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym) {
  _yp = yp;
  _xm = xm;
  _ym = ym;
  _xp = xp;
  _rxplate = 0;
  pressureThreshhold = 10;
}


TouchScreen::TouchScreen(uint8_t xp, uint8_t yp, uint8_t xm, uint8_t ym,
			 uint16_t rxplate) {
  _yp = yp;
  _xm = xm;
  _ym = ym;
  _xp = xp;
  _rxplate = rxplate;

  pressureThreshhold = 10;
}

int TouchScreen::readTouchX(void) {
   pinMode(_yp, INPUT);
   pinMode(_ym, INPUT);
   digitalWrite(_yp, LOW);
   digitalWrite(_ym, LOW);
   
   pinMode(_xp, OUTPUT);
   digitalWrite(_xp, HIGH);
   pinMode(_xm, OUTPUT);
   digitalWrite(_xm, LOW);
   
   return (analogRead(_yp));
}


int TouchScreen::readTouchY(void) {
   pinMode(_xp, INPUT);
   pinMode(_xm, INPUT);
   digitalWrite(_xp, LOW);
   digitalWrite(_xm, LOW);
   
   pinMode(_yp, OUTPUT);
   digitalWrite(_yp, HIGH);
   pinMode(_ym, OUTPUT);
   digitalWrite(_ym, LOW);
   
   return (analogRead(_xm)); 
}


uint16_t TouchScreen::pressure(void) {
  // Set X+ to ground
  pinMode(_xp, OUTPUT);
  digitalWrite(_xp, LOW);
  
  // Set Y- to VCC
  pinMode(_ym, OUTPUT);
  digitalWrite(_ym, HIGH); 
  
  // Hi-Z X- and Y+
  digitalWrite(_xm, LOW);
  pinMode(_xm, INPUT);
  digitalWrite(_yp, LOW);
  pinMode(_yp, INPUT);
  
  int z1 = analogRead(_xm); 
  int z2 = analogRead(_yp);

  if (_rxplate != 0) {
    // now read the x 
    float rtouch;
    rtouch = z2;
    rtouch /= z1;
    rtouch -= 1;
    rtouch *= readTouchX() /100;
    rtouch *= _rxplate;
    rtouch /=  40;
    
    return rtouch;
  } else {
    return (z2-z1);
  }
}
