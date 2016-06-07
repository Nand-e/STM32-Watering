#ifndef FSMACHINE
#define FSMACHINE

#include <Arduino.h>
#include "State.h"

class StateMachine {
  public:
  StateMachine ( State * starts= 0 ){
    current = starts;
    stateTime = 0;
  }
  //-----------------------------------------------
  void update ( uint16_t x, uint16_t y, uint8_t z) {
    if ( current != 0 ) {
      current->update ( x, y, z );
    }    
  }
  //-----------------------------------------------
  void TransitionTo ( State * next) {
    if ( next !=0 ) {
      if ( current )  current->exit();
      current = next;
      current->enter ();
      stateTime = millis ();
    }
  }

  unsigned long  getTimeIn () {
    return ( millis () - stateTime );
  }

  
private:
  State * current;
  unsigned long stateTime;
};




#endif
