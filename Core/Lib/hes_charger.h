#include "hes_include_stm32.h"

extern I2C_HandleTypeDef hi2c1;

extern I2C_HandleTypeDef CHARGER_I2C_PORT;
	
#define CHARGER_I2C_PORT	hi2c1	
	
void chargerRead(int *bmsEOC,int *bmsCharge, int TabGen[]);

void ReadBat(int *percent, int bmsEOC, int bmsCharge, int TabGen[]);
