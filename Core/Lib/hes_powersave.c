#include "hes_powersave.h"


int PowerSave(void) {

  int powerSave = 0 ; 
	
	 if (InOn() == 0)
	 {
		 // DONE SIGNAL -> turn off power
		 OutDone1(1); //Start Powersave part 1 // PB4 - DONE

		 OutDone2(0); //Start Powersave part 2 // PB3 - DRV
		 powerSave = 1;
		 HAL_Delay(100);
	}

  return powerSave ;
}





//int PowerSave(void) {

//  int powerSave ; 

//  OutDone1(0);

//  powerSave = 1;

//  if (InOn() == 1) {
//  } else {
//    powerSave = 0;
//  }
//	if (InSOS() == 1) {
//  } else {
//    powerSave = 0;
//  }

//  //powerSave = 0; // !!!!
//  if (powerSave == 1) {
//    OutDone2(0);
//    //HAL_Delay(1);
//    OutDone1(1);
//    //HAL_Delay(1);
//    OutDone1(0);
//  } else {
//    OutDone1(0);
//    OutDone2(1);
//  }
//  return powerSave ;
//}
