#include "hes_include_stm32.h"
#include "hes_gpio_h3.h"

extern I2C_HandleTypeDef hi2c1;

extern I2C_HandleTypeDef LED_I2C_PORT;
	
#define LED_I2C_PORT	hi2c1	

void LedOff(int TabGen[]);

void LedOn(int red, int green, int blue, int TabGen[]);