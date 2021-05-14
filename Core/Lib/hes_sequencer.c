#include "hes_sequencer.h"

void InitTaskState(uint32_t Tab[], uint32_t nbDelay) {

  Tab[0] = 1; // On / Off
  Tab[1] = nbDelay; // NbDelay
  Tab[2] = 1; // currentState
  Tab[3] = 0; // previousState
  Tab[4] = 0; // currentDelay
}

int TaskState(uint32_t Tab[]) {

  // doOn          <= Tab[0];
  // nbDelay       <= Tab[1];
  // currentState  <= Tab[2]; // init : 1
  // previousState <= Tab[3]; // init : 0
  // delayGo       <= Tab[4]; // init : 0

  uint32_t millis;
  int state = 0;

  if (Tab[0] == 1) 
	{ // if doOn
    millis = HAL_GetTick();
    if (Tab[2] == Tab[3]) 
		{                                 // if (previousState == currentState)
      if ((millis - Tab[4]) >= Tab[((size_t)(Tab[2] + 4))]) //  if ( (millis - delayGo) >= Tab[currentState + 4] )
      {
        state = Tab[2];      // state = currentState
        Tab[2] = Tab[2] + 1; // currentState = currentState + 1
        if (Tab[2] > Tab[1]) // if (currentState > nbDelay )
        {
          Tab[2] = 1; // currentState  = 1 ;
          Tab[3] = 0; // previousState = 0 ;
        }
      }
    } 
		else 
		{
      Tab[4] = millis; // delayGo  <= millis
      Tab[3] = Tab[2]; // previousState <= currentState
    }
  }
  return state;
}
