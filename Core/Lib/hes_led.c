#include "hes_led.h"

void LedOff(int TabGen[]) {

	if(TabGen[LOCK_I2C1] == 0) // I2C available
	{	
		TabGen[LOCK_I2C1] = 1; // I2C locked for interrupt on TIM7

  uint8_t buffer[3];

  OutLedWu(1);

  buffer[0] = 0x20;
  buffer[1] = 0x40;
  buffer[2] = 0x60;
	//HAL_Delay(1);
  HAL_I2C_Master_Transmit(&LED_I2C_PORT,0x9A, buffer, 3,10);

  buffer[0] = 0x80;
  buffer[1] = 0xA0;
  buffer[2] = 0xC0;
		
	HAL_Delay(1);

  HAL_I2C_Master_Transmit(&LED_I2C_PORT,0x9A, buffer, 3,10);
	//HAL_Delay(1);
  OutLedWu(0);
		
		TabGen[LOCK_I2C1] = 0; 
	}
}

void LedOn(int red, int green, int blue, int TabGen[]) 
{

	if(TabGen[LOCK_I2C1] == 0) // I2C available
	{	

		
	TabGen[LOCK_I2C1] = 1; // I2C locked for interrupt on TIM7
		
  uint8_t buffer[3];
	
	OutLedWu(1);


    buffer[0] = 0x20;
    buffer[1] = 0x40;
    buffer[2] = 0x60;


  buffer[0] = buffer[0] + ((uint8_t)(red / 8));
  buffer[1] = buffer[1] + ((uint8_t)(green / 8));
  buffer[2] = buffer[2] + ((uint8_t)(blue / 8));
		//HAL_Delay(1);
  HAL_I2C_Master_Transmit(&LED_I2C_PORT,0x9A , buffer, 3,10);
		//HAL_Delay(1);
		TabGen[LOCK_I2C1] = 0; // I2C locked for interrupt on TIM7
	}
  //HAL_I2C_Master_Transmit(&hi2c1,0x47<<1,0x01,1,10);
}