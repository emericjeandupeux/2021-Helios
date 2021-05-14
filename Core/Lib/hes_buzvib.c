#include "hes_buzvib.h"

void PowerBuzVib(uint32_t Delay)
{
	OutBuzOn();
	OutMotorWu(1);
	HAL_Delay(Delay);
	OutBuzOff();
	OutMotorWu(0);
}

void PowerBuz(uint32_t Delay)
{
	OutBuzOn();
	HAL_Delay(Delay);
	OutBuzOff();
}

void PowerVib(uint32_t Delay)
{
	OutMotorWu(1);
	HAL_Delay(Delay);
	OutMotorWu(0);
}