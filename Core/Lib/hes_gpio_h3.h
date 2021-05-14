#include "hes_include_stm32.h"
#include "main.h"

extern TIM_HandleTypeDef htim16;

extern TIM_HandleTypeDef BUZ_TIM_PORT;
	
#define BUZ_TIM_PORT htim16

// function :  set output * to 1 (param. : 1) or to 0  (param. : 0)

// function :  set output OuChaIsel to 1 (param. : 1) or to 0  (param. : 0)
void OuChaIsel(int outputValue);

// function :  set output OutDone1 to 1 (param. : 1) or to 0  (param. : 0)
void OutDone1(int outputValue);

// function :  set output OuDone2 to 1 (param. : 1) or to 0  (param. : 0)
void OutDone2(int outputValue);

// function :  set output OutDwmRst to 1 (param. : 1) or to 0  (param. : 0)
void OutDwmRst(int outputValue);

// function :  set output OutDwmWu to 1 (param. : 1) or to 0  (param. : 0)
void OutDwmWu(int outputValue);

// function :  set output OutOledWu to 1 (param. : 1) or to 0  (param. : 0)
void OutOledWu(int outputValue);

// function :  set output OutLoraWu to 1 (param. : 1) or to 0  (param. : 0)
void OutLoraWu(int outputValue);

// function :  set output OutGpsRst to 1 (param. : 1) or to 0  (param. : 0)
void OutGpsRst(int outputValue);

// function :  set output OutLedWu to 1 (param. : 1) or to 0  (param. : 0)
void OutLedWu(int outputValue);

// function :  set output OutGazWu to 1 (param. : 1) or to 0  (param. : 0)
void OutGazWu(int outputValue);

// function :  set output OutBuzWu to 1 (param. : 1) or to 0  (param. : 0)
void OutBuzWu(int outputValue);

// function :  set output OutMotorWu to 1 (param. : 1) or to 0  (param. : 0)
void OutMotorWu(int outputValue);

// function :  set output OutOledRst to 1 (param. : 1) or to 0  (param. : 0)
void OutOledRst(int outputValue);

// function :  read binary value of input * (param. : 1 for high value or param. : 0 for low value)
// Note : SOS and B button are reversed

// function :  read binary value of input InA (param. : 1 for high value or param. : 0 for low value)
int InOn(void);

// function :  read binary value of input InSOS (param. : 1 for high value or param. : 0 for low value)
int InSOS(void);

// function : start Buzzer 
void OutBuzOn();

// function : stop Buzzer 
void OutBuzOff();
