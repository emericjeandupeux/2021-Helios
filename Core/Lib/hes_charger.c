#include "hes_charger.h"
#define LP3947_I2C 		0x47	// Battery charger
#define MAX17260_I2C	0x36 	// Battery cell Fuel Gauge

extern HAL_StatusTypeDef I2C1_OK;

//LP3947
void chargerRead(int *bmsEOC,int *bmsCharge, int TabGen[])
{

		
	uint8_t buffer = 0x00 ; 
		
	if (I2C1_OK == HAL_OK)
	{
		I2C1_OK = HAL_I2C_Mem_Read(&CHARGER_I2C_PORT, LP3947_I2C <<1, 0x01, 1, &buffer, 1, 100); // Charger
	}
	
	

	*bmsEOC    = (int) (( buffer & ( (uint8_t) 0x10) )/( (uint8_t) 0x10)); //10000
	*bmsCharge  = (int) (( buffer & ( (uint8_t) 0x08) )/( (uint8_t) 0x08)); //1000
	
//	if (I2C1_OK == HAL_OK)
//	{
//		I2C1_OK = HAL_I2C_Mem_Read(&CHARGER_I2C_PORT, LP3947_I2C <<1, 0x00, 1, &buffer, 1, 50); // Charger
//	}


}


//MAX17260
void ReadBat(int *percent, int bmsEOC, int bmsCharge, int TabGen[]) 
{
	//EOC : end of charge
	//uint8_t old_percent = *percent;
	uint8_t buffer[2];
	int battmVolt;
	int newPercent ;
	int current;
		
 
	if(TabGen[LOCK_I2C1] == 0) // I2C available
	{	
		buffer[1] = 0x00;  buffer[0] = 0x00;
		
		TabGen[LOCK_I2C1] = 1; // I2C locked for interrupt on TIM7
		//HAL_Delay(1);
		
		// 0x36 => max17260
		// 0x47 => LP3947 (to test)

		if (I2C1_OK == HAL_OK)
		{
			I2C1_OK = HAL_I2C_Mem_Read(&CHARGER_I2C_PORT, 0x36 << 1, 0x19, 1, buffer, 2, 100);
			uint32_t buff = buffer[1];
			buff = buff * 256;
			//buff += buffer[0]	;
			buff = buff / 16.0;
			battmVolt = buff * 1.25;

			if(battmVolt >= BAT_MIN)
			{
				if (battmVolt < BAT_MAX)
				{
					buff = battmVolt - BAT_MIN;
					buff = buff * 100;
					buff = buff / (BAT_MAX - BAT_MIN);

					newPercent = buff ; //+ 5; // =(95 * ((A5 - 3100) / 700) + 5)
				}
				else
				{
					newPercent = 100;
				}
			}
			else
			{
				if(battmVolt < BAT_MIN - 200)
					newPercent = 255;
				else
					newPercent = 1;
			}



			if(battmVolt  < 3800)
			{
				TabGen[LOW_BAT] = 1;
			}
			else
				TabGen[LOW_BAT] = 0;



			if ((newPercent < *percent) || (bmsEOC==1) || (bmsCharge==1) || newPercent == 255)
			{
				*percent = newPercent;
			}
		}
		else
			*percent = TabGen[BAT_VALUE];
		//HAL_Delay(1);		// bms // AvrgVoltage (mm 45s)
		
		TabGen[LOCK_I2C1] = 0;
		




		uint16_t capacity_uV = 0;
		//HAL_I2C_Mem_Read(&CHARGER_I2C_PORT, MAX17260_I2C << 1, 0x05, 1, buffer, 2, 20); // capacity measured

		capacity_uV = buffer[1] *255 + buffer[0];
		float capacity = (5 / 0.01) * capacity_uV / 1000; // capacity in mAH = (5.0uV / RSENSE) * capacity in uv / 1000

		uint16_t cycles = 0;
		//HAL_I2C_Mem_Read(&CHARGER_I2C_PORT, MAX17260_I2C << 1, 0x17, 1, buffer, 2, 20); //
		cycles = buffer[1] *255 + buffer[0];

		uint16_t percentage = 0;

		int16_t avg_current = 0;

//		//int16_t
//		if (I2C1_OK == HAL_OK)
//		{
//			I2C1_OK = HAL_I2C_Mem_Read(&CHARGER_I2C_PORT, MAX17260_I2C << 1, 0x0B, 1, buffer, 2, 100); // avg current
//		}

		uint16_t temp = 0;
		temp = buffer[1];
		temp = temp ;//& 0b01111111;
		temp = temp << 8 ;
		temp = temp + buffer[0];
		avg_current = (int16_t) temp;
		//temp = 0xcdde;
				//(uint16_t)buffer[1] << 8 + buffer[0];
		//avg_current = (int16_t)0xcdde;
		//avg_current = (int)((int8_t)buffer[1] *255 + (int8_t)buffer[0]);
		//avg_current = (((int)(buffer[1] *255 + buffer[0])*1.5625)/0.01) ;
		//TabGen[AVG_CURRENT] = buffer[1] *255 + buffer[0];
		//TabGen[AVG_CURRENT] =ke
		avg_current = avg_current*(1.5625/0.01)/1000;// * (buffer[1] *255 + buffer[0]) ;
		TabGen[AVG_CURRENT] = (int)abs(avg_current);

		//HAL_I2C_Mem_Read(&CHARGER_I2C_PORT, MAX17260_I2C << 1, 0x1C, 1, buffer, 2, 20); // min max current

		uint16_t min,max = 0;

		max = buffer[1];
		min = buffer[0];
		//temp = temp << 8 ;
		//temp = buffer[0];
				//(uint16_t)buffer[1] << 8 + buffer[0];
		avg_current = (int)min;
		//avg_current = (int)((int8_t)buffer[1] *255 + (int8_t)buffer[0]);
		//avg_current = (((int)(buffer[1] *255 + buffer[0])*1.5625)/0.01) ;
		//TabGen[AVG_CURRENT] = buffer[1] *255 + buffer[0];
		//TabGen[AVG_CURRENT] = avg_current*(0.4/0.01)/1000;// * (buffer[1] *255 + buffer[0]) ;

		uint16_t time = 0;
		//HAL_I2C_Mem_Read(&CHARGER_I2C_PORT, MAX17260_I2C << 1, 0x20, 1, buffer, 2, 100); // TTF
		time = buffer[1] * 255 + buffer[0];
		time = time /60;
		time = time /60;

		time = 0;
		//HAL_I2C_Mem_Read(&CHARGER_I2C_PORT, MAX17260_I2C << 1, 0x11, 1, buffer, 2, 100); // TTE
		time = buffer[1] *255 + buffer[0];
		time = time /60;
		time = time /60;

		//battmVolt = (float)((256 * ((float)buffer[1]) + ((float)buffer[0])) * (1.25 / 16)); //mV
		
		// New version 24/04/2019


		/*
			if (battmVolt >= 4050) {
			newPercent = 100;
		}

		if ((battmVolt >= 3650) && (battmVolt < 4050)) {
			newPercent = (int)(80 * ((battmVolt - 3650) / 400) + 20);  // =80*((A21-3650)/400)+20
		}
		if ((battmVolt >= 3100) && (battmVolt < 3650)) {
			newPercent = (int)(19 * ((battmVolt - 3100) / 550) + 1); // =19*((A7-3100)/550)+1
		}
		if (battmVolt < 3100) {
			newPercent = 1;
		}
		*/
		

	}
	
	/*if (*percent<100) 
	{	OutCmdBuzzer(1);
		HAL_Delay(100);
		OutCmdBuzzer(0);
		HAL_Delay(50);
	}*/
			
}
