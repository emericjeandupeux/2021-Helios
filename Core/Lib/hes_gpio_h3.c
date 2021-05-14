
#include "hes_gpio_h3.h"

// function :  set output * to 1 (param. : 1) or to 0  (param. : 0)

// function :  set output OuChaIsel to 1 (param. : 1) or to 0  (param. : 0)
void OuChaIsel(int outputValue) {
  if (outputValue==1) {
    HAL_GPIO_WritePin(GPIOB,CHA_ISEL_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOB,CHA_ISEL_Pin, GPIO_PIN_RESET);
  }
}

// function :  set output OutDone1 to 1 (param. : 1) or to 0  (param. : 0) // PB4 - DONE
void OutDone1(int outputValue) {
  if (outputValue==1) {
    HAL_GPIO_WritePin(GPIOB,DONE_1_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOB,DONE_1_Pin, GPIO_PIN_RESET);
  }
}

// function :  set output OuDone2 to 1 (param. : 1) or to 0  (param. : 0)  // PB3 - DRV
void OutDone2(int outputValue) {
  if (outputValue==1) {
    HAL_GPIO_WritePin(GPIOB,DONE_2_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOB,DONE_2_Pin, GPIO_PIN_RESET);
  }
}

// function :  set output OutDwmRst to 1 (param. : 1) or to 0  (param. : 0)
void OutDwmRst(int outputValue) {
  if (outputValue==1) {
    HAL_GPIO_WritePin(GPIOA,DWM_RST_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOA,DWM_RST_Pin, GPIO_PIN_RESET);
  }
}

// function :  set output OutDwmWu to 1 (param. : 1) or to 0  (param. : 0)
void OutDwmWu(int outputValue) {
  if (outputValue==1) {
    HAL_GPIO_WritePin(GPIOB,DWM_WU_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOB,DWM_WU_Pin, GPIO_PIN_RESET);
  }
}

/*
// for 76 function :  set output OutOledWu to 1 (param. : 1) or to 0  (param. : 0)
void OutOledWu(int outputValue) {
  if (outputValue==1) {
    HAL_GPIO_WritePin(OLED_WU_GPIO_Port,OLED_WU_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(OLED_WU_GPIO_Port,OLED_WU_Pin, GPIO_PIN_RESET);
  }
}
*/

// for L433
// function :  set output OutOledWu to 1 (param. : 1) or to 0  (param. : 0)
void OutOledWu(int outputValue) {
  if (outputValue==1) {
    HAL_GPIO_WritePin(GPIOB,OLED_WU_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOB,OLED_WU_Pin, GPIO_PIN_RESET);
  }
}

// function :  set output OutLoraWu to 1 (param. : 1) or to 0  (param. : 0)
void OutLoraWu(int outputValue) {
  if (outputValue==1) {
    HAL_GPIO_WritePin(GPIOB,LORA_WU_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOB,LORA_WU_Pin, GPIO_PIN_RESET);
  }
}

// function :  set output OutGpsRst to 1 (param. : 1) or to 0  (param. : 0)
void OutGpsRst(int outputValue) {
  if (outputValue==1) {
    HAL_GPIO_WritePin(GPIOB,GPS_RST_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOB,GPS_RST_Pin, GPIO_PIN_RESET);
  }
}

// function :  set output OutLedWu to 1 (param. : 1) or to 0  (param. : 0)
void OutLedWu(int outputValue) {
  if (outputValue==1) {
    HAL_GPIO_WritePin(GPIOB,LED_WU_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOB,LED_WU_Pin, GPIO_PIN_RESET);
  }
}

// function :  set output OutGazWu to 1 (param. : 1) or to 0  (param. : 0)
void OutGazWu(int outputValue) {
  if (outputValue==1) {
    HAL_GPIO_WritePin(GPIOA,GAZ_WU_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOA,GAZ_WU_Pin, GPIO_PIN_RESET);
  }
}

// function :  set output OutMotorWu to 1 (param. : 1) or to 0  (param. : 0)
void OutMotorWu(int outputValue) {
	if (VIBOK==1)
	{
  if (outputValue==1) {
    HAL_GPIO_WritePin(GPIOA,MOTOR_WU_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(GPIOA,MOTOR_WU_Pin, GPIO_PIN_RESET);
  }
}
}

// function :  set output OutOledRst to 1 (param. : 1) or to 0  (param. : 0)
void OutOledRst(int outputValue) {
  if (outputValue==1) {
    HAL_GPIO_WritePin(OLED_RST_GPIO_Port,OLED_RST_Pin, GPIO_PIN_SET);
  } else {
    HAL_GPIO_WritePin(OLED_RST_GPIO_Port,OLED_RST_Pin, GPIO_PIN_RESET);
  }
}

// function :  read binary value of input * (param. : 1 for high value or param. : 0 for low value)

// function :  read binary value of input InOn (param. : 1 for high value or param. : 0 for low value)
int InOn(void) {
	int stateBP = 0 ; 
  if (((int)HAL_GPIO_ReadPin(GPIOB,BP_ON_Pin)) == 0)
	{
		stateBP = 1 ; 
	}
	return stateBP ;
}

// function :  read binary value of input InSOS (param. : 1 for high value or param. : 0 for low value)
int InSOS(void) {
	int stateBP = 0 ; 
  if (((int)HAL_GPIO_ReadPin(GPIOB,BP_SOS_Pin)) == 0)
	{
		stateBP = 1 ; 
	}
	return stateBP ;
}

// function : start Buzzer  
void OutBuzOn() {
	if (BUZOK==1){
HAL_TIM_PWM_Start(&BUZ_TIM_PORT,TIM_CHANNEL_1);
	}
}

// function : stop Buzzer 
void OutBuzOff() {
		if (BUZOK==1){
HAL_TIM_PWM_Stop(&BUZ_TIM_PORT,TIM_CHANNEL_1);
		}
}



