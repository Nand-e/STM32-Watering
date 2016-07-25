

#ifndef STATE
#define STATE

#include <Arduino.h>

class StateMachine;

class State {

public:
  State ( StateMachine * st = 0 ) {
    machine = st;
  }
  virtual void update (uint16_t x, uint16_t y, uint8_t z) = 0;
  virtual void enter  () = 0;
  virtual void exit   () = 0;

  StateMachine * machine;
  
};

#endif 
