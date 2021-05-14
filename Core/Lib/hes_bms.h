#include "hes_include_stm32.h"

extern I2C_HandleTypeDef hi2c1;

extern I2C_HandleTypeDef BMS_I2C_PORT;
	
#define BMS_I2C_PORT	hi2c1	

void ChargerSend(uint8_t *pData, uint16_t Size);

void ChargerRec(uint8_t *pData, uint16_t Size);



