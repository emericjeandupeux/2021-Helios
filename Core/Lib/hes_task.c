#include "hes_task.h"

extern uint32_t AskJoinTimeLoraWan;

void TaskClearScreen(void)
{
	ClearScreen();
}

void TaskBigScreen(uint32_t Tab[], int TabAlert[], int TabGen[],
		float TabFloatValue[], uint32_t TabGpsTimer[], uint32_t TabAlertAll[],
		char name[])
{
	char str_h2S[10];
	char str_o2[10];
	char str_co[10];
	char str_ex[10];

	if (TabGen[SCREENSTATE] == 1)
	{
		switch (TaskState(Tab))
		{
		case 1:
			if (TabGen[TYPE_ALERT] == NONE_ALERT)
			{
				// Normal display
				if (BOX4GAZ)
				{
					sprintf(str_h2S, "%.1f", TabFloatValue[H2S_VALUE]);
					sprintf(str_o2, "%.1f", TabFloatValue[O2_VALUE]);
					sprintf(str_co, "%.1f", TabFloatValue[CO_VALUE]);
					sprintf(str_ex, "%.1f", TabFloatValue[EX_VALUE]);
				}
				else if (SUEZ)
					sprintf(str_h2S, "%.1f", TabFloatValue[H2S_VALUE]);

				status_GPS = (uint8_t) TabGen[STATUT_GPS];

				batteryLevel = (uint8_t) TabGen[BAT_VALUE];
				display_dco(TabFloatValue, TabAlert, TabGen, TabGpsTimer, name,
						str_h2S, str_o2, str_co, str_ex);

			}
			break;
		case 2:
			if (TabGen[TYPE_ALERT] != NONE_ALERT)
			{
				display_AlerteDanger(TabGen, TabAlertAll, 0);
			}
			break;
		case 3:
			if (TabGen[TYPE_ALERT] != NONE_ALERT)
			{
				display_AlerteDanger(TabGen, TabAlertAll, 1);
			}
			break;
		}
	}

}

void TaskLedBlinking(uint32_t Tab[], int TabGen[])
{
	if (TabGen[CHARGEC] == 1)
	{
		if (TabGen[BAT_VALUE] >= 100)
			LedOn(0, 100, 0, TabGen);
		else
			LedOn(100, 0, 0, TabGen);
	}
	else
	{
		switch (TaskState(Tab))
		{
		case 1:

			LedOn(TabGen[LEDR0], TabGen[LEDV0], TabGen[LEDB0], TabGen);
			break;

		case 2:

			LedOn(TabGen[LEDR], TabGen[LEDV], TabGen[LEDB], TabGen);
			break;

		default:
			break;
		}
	}
}

void TaskUpdateUpperLed(uint32_t Tab[], int TabGen[])
{

	switch (TaskState(Tab))
	{
	case 1:
		if (((TabGen[CHARGEC] == 1) || (TabGen[EOC] == 1))
				&& (TabGen[BAT_VALUE] < 100))
		{
			if (BOX4GAZ == 0)
			{
				TabGen[LEDR] = 50;
				TabGen[LEDV] = 0;
				TabGen[LEDB] = 0;
				TabGen[LEDR0] = 50;
				TabGen[LEDV0] = 0;
				TabGen[LEDB0] = 0;
			}
			else
			{
				TabGen[LEDR] = 250;
				TabGen[LEDV] = 0;
				TabGen[LEDB] = 0;
				TabGen[LEDR0] = 250;
				TabGen[LEDV0] = 0;
				TabGen[LEDB0] = 0;
			}
		}

		if (((TabGen[CHARGEC] == 1) || (TabGen[EOC] == 1))
				&& (TabGen[BAT_VALUE] == 100))
		{
			if (BOX4GAZ == 0)
			{
				TabGen[LEDR] = 0;
				TabGen[LEDV] = 50;
				TabGen[LEDB] = 0;
				TabGen[LEDR0] = 0;
				TabGen[LEDV0] = 50;
				TabGen[LEDB0] = 0;
			}
			else
			{
				TabGen[LEDR] = 0;
				TabGen[LEDV] = 250;
				TabGen[LEDB] = 0;
				TabGen[LEDR0] = 0;
				TabGen[LEDV0] = 250;
				TabGen[LEDB0] = 0;
			}
		}

		if ((TabGen[CHARGEC] == 0) && (TabGen[EOC] == 0))
		{
			if ((TabGen[BAT_VALUE] >= 50))
			{
				if (BOX4GAZ == 0)
				{
					TabGen[LEDR] = 0;
					TabGen[LEDV] = 50;
					TabGen[LEDB] = 0;
					TabGen[LEDR0] = 0;
					TabGen[LEDV0] = 0;
					TabGen[LEDB0] = 0;
				}
				else
				{
					TabGen[LEDR] = 0;
					TabGen[LEDV] = 250;
					TabGen[LEDB] = 0;
					TabGen[LEDR0] = 0;
					TabGen[LEDV0] = 0;
					TabGen[LEDB0] = 0;
				}
			}
			if ((TabGen[BAT_VALUE] < 50) && (TabGen[BAT_VALUE] >= 20))
			{
				if (BOX4GAZ == 0)
				{
					TabGen[LEDR] = 127;
					TabGen[LEDV] = 10;
					TabGen[LEDB] = 0;
					TabGen[LEDR0] = 0;
					TabGen[LEDV0] = 0;
					TabGen[LEDB0] = 0;
				}
				else
				{
					TabGen[LEDR] = 250;
					TabGen[LEDV] = 30;
					TabGen[LEDB] = 0;
					TabGen[LEDR0] = 0;
					TabGen[LEDV0] = 0;
					TabGen[LEDB0] = 0;
				}
			}
			if (TabGen[BAT_VALUE] < 20)
			{
				if (BOX4GAZ == 0)
				{
					TabGen[LEDR] = 100;
					TabGen[LEDV] = 0;
					TabGen[LEDB] = 0;
					TabGen[LEDR0] = 0;
					TabGen[LEDV0] = 0;
					TabGen[LEDB0] = 0;
				}
				else
				{
					TabGen[LEDR] = 250;
					TabGen[LEDV] = 0;
					TabGen[LEDB] = 0;
					TabGen[LEDR0] = 0;
					TabGen[LEDV0] = 0;
					TabGen[LEDB0] = 0;
				}
			}
		}

		break;

	default:
		break;
	}
}

//void TaskCharger(uint32_t Tab[], int TabGen[]) 
//{
//	int bmsEOC = 0;
//	int bmsCharge = 0;

//	switch (TaskState(Tab)) 
//	{
//	case 1:

//		if(TabGen[LOCK_I2C1] == 0) // I2C available
//	{	
//		TabGen[LOCK_I2C1] = 1; // I2C locked for interrupt on TIM7
//		
//		// by GPIO Input
//		//*bmsEOC_out = InEOC();
//		//*bmsCharge_out = InCHG();

//		// by I2C
//		chargerRead(&bmsEOC, &bmsCharge, TabGen);
//		TabGen[EOC] = bmsEOC;
//		TabGen[CHARGEC] = bmsCharge;
//		
//		TabGen[LOCK_I2C1] = 0;
//	}

//		break;
//	
//	default:
//		break;
//	}
//}

void TaskCharger(int TabGen[])
{
	int bmsEOC = 0;
	int bmsCharge = 0;

	// by GPIO Input
	//*bmsEOC_out = InEOC();
	//*bmsCharge_out = InCHG();

	// by I2C

	if (TabGen[LOCK_I2C1] == 0) // I2C available
	{
		TabGen[LOCK_I2C1] = 1; // I2C locked for interrupt on TIM7

		//HAL_Delay(1);
		chargerRead(&bmsEOC, &bmsCharge, TabGen);
		//HAL_Delay(1);

		TabGen[LOCK_I2C1] = 0;
	}

	TabGen[EOC]		= bmsEOC;
	TabGen[CHARGEC] = bmsCharge;

}

//void TaskReadBat(uint32_t Tab[], int TabGen[]) 
//{
//	int percent ;

//	switch (TaskState(Tab)) 
//	{
//	case 1:
//		ReadBat(&percent, 1, 1, TabGen);
//		TabGen[BAT_VALUE] = percent ;
//		break;

//	default:
//		break;
//	} 
//}

void TaskReadBat(int TabGen[])
{
	int percent;

	ReadBat(&percent, 1, 1, TabGen);
	TabGen[BAT_VALUE] = percent;
}

extern uint32_t low_bat_shutdown;

void TaskExtButton(int TabGen[])
{

	int i = 0;
	int butOn = 1;

	if ((TabGen[NS_ON] > 30 || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT)) // >3s
	{
		PowerVib(100);

//		ScreenMessExt3s();
		display_wait(1);

		i = 0;
		while ((i < 50)
				&& (butOn == 1 || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT))
		{
			HAL_Delay(10);
			if ((InOn() == 1))
			{
				butOn = 1;
			}
			else
			{
				butOn = 0;
			}
			i = i + 1;
		}
		if (butOn == 1 || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT)
		{
			//ScreenMessExt2s();
			display_wait(2);

		}
		i = 0;
		while ((i < 50)
				&& (butOn || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT))
		{
			HAL_Delay(10);
			if ((InOn() == 1))
			{
				butOn = 1;
			}
			else
			{
				butOn = 0;
			}
			i = i + 1;
		}
		if (butOn == 1 || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT)
		{
			//ScreenMessExt1s();
			display_wait(3);
		}
		i = 0;
		while ((i < 50)
				&& (butOn == 1 || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT))
		{
			HAL_Delay(10);
			if ((InOn() == 1))
			{
				butOn = 1;
			}
			else
			{
				butOn = 0;
			}
			i = i + 1;
		}
		if (butOn == 1 || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT)
		{
			//ScreenMessExt1s();
			display_wait(4);
		}
		i = 0;
		while ((i < 50)
				&& (butOn == 1 || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT))
		{
			HAL_Delay(10);
			if ((InOn() == 1))
			{
				butOn = 1;
			}
			else
			{
				butOn = 0;
			}
			i = i + 1;
		}
		if (butOn == 1 || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT)
		{
			//ScreenMessExt1s();
			display_wait(5);
		}
		i = 0;
		while ((i < 50)
				&& (butOn == 1 || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT))
		{
			HAL_Delay(10);
			if ((InOn() == 1))
			{
				butOn = 1;
			}
			else
			{
				butOn = 0;
			}
			i = i + 1;
		}
		if (butOn == 1 || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT)
		{
			//ScreenMessExt1s();
			display_wait(6);
		}
		i = 0;
		while ((i < 50)
				&& (butOn == 1 || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT))
		{
			HAL_Delay(10);
			if ((InOn() == 1))
			{
				butOn = 1;
			}
			else
			{
				butOn = 0;
			}
			i = i + 1;
		}
		if (butOn == 1 || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT)
		{
			//ScreenMessExt1s();
			display_wait(7);
		}
		i = 0;
		while ((i < 50)
				&& (butOn == 1 || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT))
		{
			HAL_Delay(10);
			//if ( (InOn() == 1) )
			//{
			//butOn = 1;
			//}
			//else
			//{
			//butOn = 0;
			//}
			i = i + 1;
			butOn = 1; // Even if you stop pressing the ON/OFF button, device will turn off while showing "Extinction"
		}
		if (butOn == 1 || low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT)
		{
			//ScreenMessExtOnly();
			display_wait(8);

			PowerVib(100);
			HAL_Delay(500);
			LedOff(TabGen);
			//ScreenMessEmpty();
			display_Print("");
			//HAL_Delay(2000);
			TabGen[STOPDEVICE] = 1;

			//      OutDoneVer(0);
			//  HAL_Delay(1);
			//  OutDone(1);
			//  HAL_Delay(1);
			//  OutDone(0);
			//  HAL_Delay(1000);
			HAL_Delay(2000);
			OutDone1(1); //Start Powersave part 1
			OutDone2(0); //Start Powersave part 2
			//powerSave = 1;
			HAL_Delay(1000);
		}
	}
}

void TaskFallTest(int TabAlert[], int TabGen[])
{

	int fallBrutal = 0;

	if ((TabGen[FALL_DELAY] == 0) && (TabAlert[ALERT_FALL] == 0)
			&& (TabAlert[ALERT_MALAISE] == 0))
	{
		if (TabGen[FALL_COND_3] == 1)
		{
			TabGen[FALL_COND_3] = 0;
			uint8_t z = 0;
			z = test_chute(ar_full, y_full);
//			for ( int k = 0; k < 400 ; k++) // on teste si on a un grand pic qui va caract�riser surement une chute pas besoin de v�rifier l'angle
//			{
//				if (ar_full[k] > NBECHBRUTALFALL)
//				{fallBrutal = 1;}
//			}
			if (z == 1)
			{
				TabGen[FALL_DELAY] = 1;
			}
		}
		if (TabGen[FALL_COND_4] == 1)
		{
			uint8_t z = 0;
			z = test_chute(arr, yy);
//			for ( int k = 0; k < 400 ; k++) // on teste si on a un grand pic qui va caract�riser surement une chute pas besoin de v�rifier l'angle
//			{
//				if (arr[k] > NBECHBRUTALFALL)
//				{fallBrutal = 1;}
//			}
			//z= test_chute(ar_full,y_full);
			if (z == 1)
			{
				TabGen[FALL_DELAY] = 1;
			}
			TabGen[FALL_COND_4] = 0;
		}
		if (fallBrutal == 1)
		{
			fallBrutal = 0;
			TabAlert[ALERT_FALL] = 1;
			TabGen[FALL_UP_DELAY] = 0;
			TabGen[FALL_DELAY] = 0;
		}
	}

	if ((TabGen[FALL_DELAY] == 1) && (TabAlert[ALERT_FALL] == 0))
	{
		if (TabGen[FALL_UP_DELAY] == 1)
		{
			TabAlert[ALERT_FALL] = 1;
			TabGen[FALL_UP_DELAY] = 0;
			TabGen[FALL_DELAY] = 0;
		}
	}

}

void TaskAlertAll(int TabAlert[], int TabGen[], uint32_t TabAlertAll[],
		float TabFloatValue[]) // int *sosRelach, uint32_t *OnLength, uint32_t *On_nb_sample, int *sigSend, char lcd_buf1[], char lcd_buf2[], uint32_t  *nS_malaise, uint32_t  *nS_immo, uint32_t  *nS_fall, int *h2sAlerte, int *COAlerte, int *sos, int *fallmalaise, int *send_mess, uint32_t *SOS_nb_sample, uint32_t *alert_t0, uint32_t *alert_duration, uint32_t *sosLength, int *malaise, int *fall, int *alert_on, int *alert_on_previous, int *gps_on, int *buz_on, int *ledAlert)
{

// for 	int TabAlert[]

//#define ALERT_FALL    0
//#define ALERT_MALAISE 1
//#define ALERT_IMMO    2
//#define ALERT_SOS     3
//#define ALERT_EXVME   4
//#define ALERT_O2VME   5
//#define ALERT_COVME   6
//#define ALERT_H2SVME  7
//#define ALERT_EXVLCT  8
//#define ALERT_O2VLCT  9
//#define ALERT_COVLCT  10
//#define ALERT_H2SVLCT 11
//#define ALERT_SONO    12
//#define ALERT_COL     13
//#define ALERT_DIST    14

//#define NB_ALERT    14
//#define NB_GAZ_BEG    4
//#define NB_GAZ_END    11

//uint8_t charuart[11];
	uint32_t millis2;

	millis2 = HAL_GetTick();

//char bufferSig[30];

	if (TabGen[ALERT_ON] == 0)
	{
		if (TabAlert[ALERT_SOS] == 1)
		{
			TabGen[TYPE_ALERT] = ALERT_SOS;
		}
		else if (TabAlert[ALERT_FALL] == 1
				&& ((HAL_GetTick() - TabAlertAll[ALL_TIM_3]) > NB_MS_REALERTGAZ))
		{
			TabGen[TYPE_ALERT] = ALERT_FALL;
			TabAlertAll[ALL_TIM_3] = millis2;
		}
		else if (TabAlert[ALERT_MALAISE] == 1
				&& ((HAL_GetTick() - TabAlertAll[ALL_TIM_3]) > NB_MS_REALERTGAZ))
		{
			TabGen[TYPE_ALERT] = ALERT_MALAISE;
			TabAlertAll[ALL_TIM_3] = millis2;
		}
		else if ((TabAlert[ALERT_EX] == 1)
				&& ((HAL_GetTick() - TabAlertAll[ALL_TIM_3]) > NB_MS_REALERTGAZ))
		{
			TabGen[TYPE_ALERT] = ALERT_EX;
			TabAlertAll[ALL_TIM_3] = millis2;
		}
		else if ((TabAlert[ALERT_O2] == 1)
				&& ((HAL_GetTick() - TabAlertAll[ALL_TIM_3]) > NB_MS_REALERTGAZ))
		{
			TabGen[TYPE_ALERT] = ALERT_O2;
			TabAlertAll[ALL_TIM_3] = millis2;
		}
		else if ((TabAlert[ALERT_COVME] == 1)
				&& ((HAL_GetTick() - TabAlertAll[ALL_TIM_3]) > NB_MS_REALERTGAZ))
		{
			TabGen[TYPE_ALERT] = ALERT_COVME;
			TabAlertAll[ALL_TIM_3] = millis2;
		}
		else if ((TabAlert[ALERT_H2SVME] == 1)
				&& ((HAL_GetTick() - TabAlertAll[ALL_TIM_3]) > NB_MS_REALERTGAZ))
		{
			TabGen[TYPE_ALERT] = ALERT_H2SVME;
			TabAlertAll[ALL_TIM_3] = millis2;
		}
		else if ((TabAlert[ALERT_COVLCT] == 1)
				&& ((HAL_GetTick() - TabAlertAll[ALL_TIM_3]) > NB_MS_REALERTGAZ))
		{
			TabGen[TYPE_ALERT] = ALERT_COVLCT;
			TabAlertAll[ALL_TIM_3] = millis2;
		}
		else if ((TabAlert[ALERT_H2SVLCT] == 1)
				&& ((HAL_GetTick() - TabAlertAll[ALL_TIM_3]) > NB_MS_REALERTGAZ))
		{
			TabGen[TYPE_ALERT] = ALERT_H2SVLCT;
			TabAlertAll[ALL_TIM_3] = millis2;
		}
		else if (TabAlert[ALERT_SONO] == 1)
		{
			TabGen[TYPE_ALERT] = ALERT_SONO;
		}
		else if (TabAlert[ALERT_COL] == 1)
		{
			TabGen[TYPE_ALERT] = ALERT_COL;
		}
		else if (TabAlert[ALERT_DIST] == 1)
		{
			TabGen[TYPE_ALERT] = ALERT_DIST;
		}
		else if (TabAlert[ALERT_LOWBAT] == 1)
		{
			TabGen[TYPE_ALERT] = ALERT_LOWBAT;
		}
		else
		{
			TabGen[TYPE_ALERT] = NONE_ALERT;
		}
	}

	if ((TabGen[TYPE_ALERT] != NONE_ALERT) && (TabGen[ALERT_ON] == 0))
	{
		TabAlertAll[ALL_TIM_1] = HAL_GetTick(); // beg. timer
		TabGen[ALERT_ON] = 1;
		TabGen[GPS_ON] = 1;
		// Big Led Blinking (major)
		if ((TabAlert[ALERT_FALL] == 1) || (TabAlert[ALERT_MALAISE] == 1)
				|| (TabAlert[ALERT_SOS] == 1) || (TabAlert[ALERT_EX] == 1)
				|| (TabAlert[ALERT_O2] == 1) || (TabAlert[ALERT_COVLCT] == 1)
				|| (TabAlert[ALERT_H2SVLCT] == 1) || (TabAlert[ALERT_COL] == 1)
				|| (TabAlert[ALERT_DIST])) // Big Alert
		{
			TabGen[BUZ_ON_FAST] = 1;
			TabGen[LED_ON_FAST] = 1;
			TabGen[VIB_ON_FAST] = 1;

			HAL_UART_Transmit(&huart1, (uint8_t*) "A050B010C1D",
					sizeof((uint8_t*) "A050B010C1D") - 1, 500);

		}
		else if ((TabAlert[ALERT_COVME] == 1) || (TabAlert[ALERT_H2SVME] == 1)
				|| (TabAlert[ALERT_SONO] == 1) || (TabAlert[ALERT_LOWBAT]))
		{
			TabGen[BUZ_ON_SLOW] = 1;
			TabGen[LED_ON_SLOW] = 1;
			TabGen[VIB_ON_SLOW] = 1;

			HAL_UART_Transmit(&huart1, (uint8_t*) "A050B010C1D",
					sizeof((uint8_t*) "A050B010C1D") - 1, 500);

		}

	}

	for (int i_fct = 0; i_fct < NB_ALERT; i_fct++) // clear all alert
	{
		TabAlert[i_fct] = 0;
	}

	if (TabGen[ALERT_ON] == 1)  // if Alert Actually
	{
		if (TabGen[SOS_PUSH_LONG] == 1) // if long punch on SOS or ON/off button
		{
			TabGen[ALERT_ON] = 0;     // clear alert
			TabGen[NS_MALAISE] = 0;
			TabGen[NS_IMMO] = 0;
			TabGen[SOS_PUSH_LONG] = 0;  // clear push button
			TabGen[TYPE_ALERT] = NONE_ALERT;

			HAL_UART_Transmit(&huart1, (uint8_t*) "A000B000C0D",sizeof((uint8_t*) "A050B010C1D") - 1, 500); // A periodicité, B fréquence, C on/off

			TabAlertAll[ALL_TIM_3] = HAL_GetTick();

			TabFloatValue[O2_VALUE] = 21;
			TabFloatValue[CO_VALUE] = 0;
			TabFloatValue[EX_VALUE] = 0;
			TabFloatValue[H2S_VALUE] = 0;
			TabFloatValue[DB_VALUE] = 0;

		}

		if ((HAL_GetTick() - TabAlertAll[ALL_TIM_1]) > (SIGDURATION * 1000)) // if timer to cancel alert is over
		{
			TabGen[NS_MALAISE] = 0;
			TabGen[ALERT_PENDING] = 1;

			if (SIGFOXOK == 1)
			{

				TabGen[SIGFOX_SEND] = 1;   // send sigfox mess
			}
			if (LORAWANOK == 1)
			{
				if (SIGFOXOK == 0)
					TabGen[LORA_SEND] = 1; // send lora mess
				else
				{
					TabGen[DUAL_SEND] = 1;
					TabGen[SIGFOX_SEND] = 0;
				}
				//TabGen[SIGFOX_SEND] = 0;

			}
			if (LORAP2POK == 1)
			{
				TabGen[LORAP2P_SEND] = 1; // send lora mess
			}

			TabGen[SIG_ALERT] = TabGen[TYPE_ALERT];

			TabGen[NS_IMMO] = 0;
			TabGen[ALERT_ON] = 0;     // clear alert
			TabGen[SOS_PUSH_LONG] = 0;  // clear push button
			TabGen[TYPE_ALERT] = NONE_ALERT;

			HAL_UART_Transmit(&huart1, (uint8_t*) "A000B000C0D",
					sizeof((uint8_t*) "A050B010C1D") - 1, 500);

			TabAlertAll[ALL_TIM_3] = HAL_GetTick();
		}
	}

}

extern uint8_t REBOOT_FROM_WATCHDOG;

void TaskOnScreen(int TabGen[], uint32_t *Timer_screen)
{

//	if ( (TabGen[RE_ON_SCREEN] == 1 ) || (TabGen[TYPE_ALERT] != NONE_ALERT) )
//	{
//		TabGen[RE_ON_SCREEN] = 0 ;
//		TabGen[SCREENSTATEON] = 1 ;
//		*Timer_screen = HAL_GetTick() - 1 ;
//	}

//	if   ( (HAL_GetTick() - *Timer_screen ) >  (SEC_ONOFF_SCREEN * 1000)  )
//	{
//		ScreenOff();
//		TabGen[SCREENSTATE] = 0;
//		TabGen[SCREENSTATEON] = 0 ;
//	}
//	
//	if ((TabGen[SCREENSTATEON] == 1) && (TabGen[SCREENSTATE] == 0)) {
//		ScreenOn();
//		display_InitBis();
//		TabGen[SCREENSTATE] = 1;
//		TabGen[SCREENSTATEON] = 0 ;
//	}

	if ((TabGen[RE_ON_SCREEN] == 1) || (TabGen[TYPE_ALERT] != NONE_ALERT))
	{

		TabGen[RE_ON_SCREEN] = 0;
		*Timer_screen = HAL_GetTick() - 1;
		if (TabGen[SCREENSTATE] == 0)
		{
			ScreenOn();
			display_InitBis();
			TabGen[SCREENSTATE] = 1;
		}
	}

	if ((HAL_GetTick() - *Timer_screen) > (SEC_ONOFF_SCREEN * 1000))
	{

		ScreenOff();
		//HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFI);  // Enter stop mode for test only
		TabGen[SCREENSTATE] = 0;
	}
}

void TaskGPS(uint8_t RxI[], int TabGen[], uint32_t TabGpsTimer[],
		float TabFloatValue[])
{

	float lati = 0;
	float longi = 0;

	if (GPSOK == 1) // GPS IS ENABLED
	{
		if (TabGen[GPS_ON] == 1)
		{
//			if ((RxI[0] == '$') && (RxI[1] == 'G') && (RxI[2] == 'N') && (RxI[3] == 'G') && (RxI[4] == 'G') && (RxI[5] == 'A'))
//			{

			if ((RxI[6] == ',') && (RxI[16] == ',') && (RxI[27] == ',')
					&& (RxI[29] == ',') && (RxI[41] == ',') && (RxI[43] == ','))
			{
				lati = ((RxI[17] - 48) * 10 + (RxI[18] - 48))
						+ ((RxI[19] - 48) * pow(10, 6)
								+ (RxI[20] - 48) * pow(10, 5)
								+ (RxI[22] - 48) * pow(10, 4)
								+ (RxI[23] - 48) * pow(10, 3)
								+ (RxI[24] - 48) * pow(10, 2)
								+ (RxI[25] - 48) * 10 + RxI[26] - 48) * 0.00001
								/ 60;
				longi = ((RxI[30] - 48) * pow(10, 2) + (RxI[31] - 48) * 10
						+ (RxI[32] - 48))
						+ ((RxI[33] - 48) * pow(10, 6)
								+ (RxI[34] - 48) * pow(10, 5)
								+ (RxI[36] - 48) * pow(10, 4)
								+ (RxI[37] - 48) * pow(10, 3)
								+ (RxI[38] - 48) * pow(10, 2)
								+ (RxI[39] - 48) * 10 + RxI[40] - 48) * 0.00001
								/ 60;
				if (RxI[28] == 'S')
				{
					lati = -lati;
				}
				if (RxI[42] == 'W')
				{
					longi = -longi;
				}
				if ((lati > 35) && (lati < 60) && (longi > -10) && (longi < 10)) // France
				{
					//					h = (RxI[7]  - 48)*10 + (RxI[8]  - 48);
					//					m = (RxI[9]  - 48)*10 + (RxI[10]  - 48);
					int sat = 0;

					if (RxI[46] >= '0' && RxI[46] <= '9' && RxI[47] >= '0'
							&& RxI[47] <= '9')
						TabGen[NB_SATT_FOUND] = (RxI[46] - '0') * 10 + RxI[47]
								- '0';
					//if (TabGen[NB_SATT_FOUND] > 10) TabGen[GPS_ON] =0;

					TabGpsTimer[LAST_UPDATE_GPS] = HAL_GetTick();

					//						char * token = strtok((char*)RxI, ",");   // not working yet, nmea gga sentence empty on satelites field at start?
					//						int cnt = 0;
					//					 // loop through the string to extract all other tokens
					//						do
					//						{
					//							token = strtok(NULL, ",");
					//							//printf( " %s\n", token ); //printing each token
					//							cnt++;
					//						}while(cnt <= 6);
					//						*last_update = (token[0] - 48)*10 + (token[1] - 48);//(RxI[46] -48)*10 + RxI[47] - 48;
					//						if (*last_update > 12 )
					//								*last_update = 13;

					TabFloatValue[LATI] = lati;
					TabFloatValue[LONGI] = longi;
					TabGen[STATUT_GPS] = 1;
					// get time from GPS or last time you got data

					if (TabGen[GPS_GOOD] == 0)
					{
						TabGpsTimer[GPS_FIRST_START] = HAL_GetTick();//- (GPSDURA * 60 * 1000) + (GPSSTOP * 60 * 1000) ;  //LAST CHANGE 18h10-07/10
						TabGen[GPS_GOOD] = 1;
						TabGen[GPS_DURATION] = 1;
					}
				}
			}
			//	}
		}
	}
}

void TaskSendMessage(int TabGen[], float TabFloatValue[], uint32_t TabTimer[],
		char WifiName[])
{
	if (RAK811 == 1)
	{
		TaskSendLoraNoGPS(TabGen, TabFloatValue, TabTimer);
	}
	else
	{
		TaskSendSigfox(TabGen, TabFloatValue, TabTimer, WifiName);
		TaskSendLora(TabGen, TabFloatValue, TabTimer);
	}
}

// LoraWan to Objenious
void TaskSendLoraWan(int TabGen[], float TabFloatValue[],
		uint32_t TabGpsTimer[])
{
	char bufferLoraWan[32];

	if ((LORAWANOK == 1) && (TabGen[LORA_SEND] == 1))
	{
		TabGen[RE_ON_SCREEN] = 1;
		TabGen[LORA_SEND] = 0;

		display_SendMess();

		OutBuzOff();
		OutMotorWu(0);
		LedOn(0, 0, 0, TabGen);

		srand(HAL_GetTick());
		TabGen[ID_ALERT] = rand() % 99;

		BuildMessGPS(bufferLoraWan, TabGen, TabFloatValue, TabGpsTimer);
		SendMessLoraWan(bufferLoraWan);
	}
}

extern IWDG_HandleTypeDef hiwdg;

//Sigfox to antenna
void TaskSendSigfox(int TabGen[], float TabFloatValue[], uint32_t TabTimer[],
		char WifiName[])
{
	char bufferSig[40];

	if ((SIGFOXOK == 1) && (TabGen[SIGFOX_SEND] == 1))
	{
		HAL_IWDG_Refresh(&hiwdg);
		RebootNemeusLS(TabGen); // Override duty cycle limitation, must wait 9 min before sending another message

		TabGen[RE_ON_SCREEN] = 1;

		display_SendMess();
		SigfoxOn();

		OutBuzOff();
		OutMotorWu(0);
		LedOn(0, 0, 0, TabGen);
		if (WIFI == 1)
			BuildMessWifi(bufferSig, TabGen, TabFloatValue, TabTimer, WifiName);
		else
			BuildMessGPS(bufferSig, TabGen, TabFloatValue, TabTimer);

		HAL_IWDG_Refresh(&hiwdg);

		SendMessSigfox(bufferSig, TabGen);

		HAL_Delay(5000);
		HAL_IWDG_Refresh(&hiwdg);
		HAL_Delay(5000);
		HAL_IWDG_Refresh(&hiwdg);

		TabGen[SIGFOX_SEND] = 0;
		TabGen[LORA_SEND] = 0;
		TabGen[ID_ALERT] = 0;
		TabGen[ALERT_PENDING] = 0;
		RebootNemeusLS(TabGen);
		SigfoxOn();
	}
}

//Sigfox to antenna
void TaskSendDUAL(int TabGen[], float TabFloatValue[], uint32_t TabTimer[],
		char WifiName[])
{
	char bufferDual[40];

	if (TabGen[DUAL_SEND] == 1)
	{
		srand(HAL_GetTick());
		TabGen[ID_ALERT] = (rand() % 98) + 1;
		display_SendMess();
		TabGen[RE_ON_SCREEN] = 1;
		OutBuzOff();
		OutMotorWu(0);
		LedOn(0, 0, 0, TabGen);
		if (WIFI == 1)
			BuildMessWifi(bufferDual, TabGen, TabFloatValue, TabTimer,
					WifiName);
		else
			BuildMessGPS(bufferDual, TabGen, TabFloatValue, TabTimer);

		SendMessLoraWan(bufferDual);
		RebootNemeusLS(TabGen);
		HAL_Delay(5000);

		HAL_IWDG_Refresh(&hiwdg);
		HAL_Delay(5000);

		HAL_IWDG_Refresh(&hiwdg);

		RebootNemeusLS(TabGen); // Override duty cycle limitation, must wait 9 min before sending another message
		SigfoxOn();

		HAL_IWDG_Refresh(&hiwdg);
		SendMessSigfox(bufferDual, TabGen);

		HAL_Delay(5000);
		HAL_IWDG_Refresh(&hiwdg);
		HAL_Delay(5000);
		HAL_IWDG_Refresh(&hiwdg);

		TabGen[DUAL_SEND] = 0;
		TabGen[ID_ALERT] = 0;
		TabGen[ALERT_PENDING] = 0;
		RebootNemeusLS(TabGen);
		SigfoxOn();
		LoraWanOn();
	}
}

//Lora private network
void TaskSendLora(int TabGen[], float TabFloatValue[], uint32_t TabGpsTimer[])
{
	char bufferLora[32];

	if ((LORAP2POK == 1) && (TabGen[LORA_SEND] == 1) && SUEZ == 0)
	{
		TabGen[RE_ON_SCREEN] = 1;
		TabGen[LORA_SEND] = 0;
		display_SendMess();
		//WakeUpNemeusLS();
		//RebootNemeusLS();
		OutBuzOff();
		OutMotorWu(0);
		LedOn(0, 0, 0, TabGen);
		//LoraWanOn();

		BuildMessAlert(bufferLora, TabGen, TabFloatValue, TabGpsTimer); // No GPS data in the message
		SendMessLora(bufferLora);

	}
}

void TaskButtonManager(int TabGen[], int TabAlert[])
{
	//if (TabGen[I_READ_BUTTON] == 10)  // button management
	//{
	if (InOn() == 1)
	{
		if (TabGen[ALERT_ON] == 0) // EJ : button on to update GPS
		{
			TabGen[FORCE_GPS] = 1;
//					TabGen[STATUT_GPS] = 0 ;
//					TabGen[GPS_GOOD] = 0 ;
		}

		TabGen[RE_ON_SCREEN] = 1;
		TabGen[ON_ON] = 1;
		TabGen[NS_ON]++;
		if (TabGen[NS_ON] > (ON_TOUCH * 100))
		{
			if (TabGen[ALERT_ON] == 1)
			{
				TabGen[SOS_PUSH_LONG] = 1;
				TabGen[NS_MALAISE] = 0;
			}
			TabGen[NS_SOS] = 0;
		}
	}
	else
	{
		TabGen[ON_ON] = 0;
		TabGen[NS_ON] = 0;
	}

	if (InSOS() == 1)
	{
		TabGen[FORCE_GPS] = 1;

		TabGen[RE_ON_SCREEN] = 1;
		TabGen[SOS_ON] = 1;
		TabGen[NS_SOS]++;
		if (TabGen[NS_SOS] > (SOS_TOUCH))
		{
			if (TabGen[ALERT_ON] == 1 && TabGen[SOS_RELEACH] == 1)
			{
				TabGen[SOS_PUSH_LONG] = 1;
				TabGen[NS_MALAISE] = 0;
				TabGen[NS_SOS] = 0;
			}

			if (TabGen[NS_SOS] > (SOS_TOUCH * 100))
			{
				if (TabGen[ALERT_ON] == 0)
				{

					TabAlert[ALERT_SOS] = 1;
					TabGen[NS_SOS] = 0;
					TabGen[SOS_RELEACH] = 0;

				}
			}
		}

//			TabGen[RE_ON_SCREEN] = 1 ;
//			TabGen[SOS_ON] = 1;
//			TabGen[NS_SOS]++ ;
//			if (TabGen[NS_SOS] > (SOS_TOUCH * 10))
//			{
//				if (TabGen[ALERT_ON] == 0)
//				{
//				TabAlert[ALERT_SOS] = 1 ;
//				}
//				if (TabGen[ALERT_ON] == 1)
//				{
//					TabGen[SOS_PUSH_LONG] = 1 ;
//					TabGen[NS_MALAISE] = 0 ;
//				}
//				TabGen[NS_SOS] = 0 ;
//			}
	}
	else
	{
		TabGen[SOS_RELEACH] = 1;
		TabGen[SOS_ON] = 0;
		TabGen[NS_SOS] = 0;
	}
	TabGen[I_READ_BUTTON] = 0;

	if ((TabGen[ON_ON] == 1) || (TabGen[SOS_ON] == 1))
	{

		if (TabGen[CHARGEC] == 0)
			LedOn(50, 0, 0, TabGen);

		if (TabGen[CHARGEC] == 1 && (TabGen[ON_ON] == 1))
			LedOn(50, 0, 0, TabGen);
	}
	else
	{
		if (TabGen[CHARGEC] == 0)
			LedOn(0, 0, 0, TabGen);
	}

	/*}
	 else
	 {
	 TabGen[I_READ_BUTTON]++ ;
	 }*/

}

void TaskAlertManager(int TabGen[], int *i_led)
{
	if (TabGen[ALERT_ON] == 1) // if there is an alert
	{
		if ((TabGen[BUZ_ON_FAST] == 1) && (TabGen[LED_ON_FAST] == 1)
				&& (TabGen[VIB_ON_FAST] == 1)) // fast vibration, blinking, and noise mode
		{
			if (*i_led == 1)
			{
				LedOn(250, 200, 200, TabGen); // turn led on

#ifndef debug_sound_vibration
				OutBuzOn();			// buzzer on  // EJ : stop sound for debug
				OutMotorWu(1);				// vibration on
#endif
			}
			if (*i_led == 10)   // after 100 ms
			{
				LedOn(0, 0, 0, TabGen); // turn led off
				OutBuzOff();		// buzzer off
				OutMotorWu(0);	// vibration on
			}
			if (*i_led == 100) // every 1 sec
			{
				*i_led = 0;     // restart
			}
			(*i_led)++;
		}
		else if ((TabGen[BUZ_ON_SLOW] == 1) && (TabGen[LED_ON_SLOW] == 1)
				&& (TabGen[VIB_ON_SLOW] == 1)) // slow vibration, blinking, and noise mode
		{
			if (*i_led == 1)
			{
				LedOn(250, 200, 200, TabGen); // turn led on
				OutBuzOn();						// buzzer on
				OutMotorWu(1);				// vibration on
			}
			if (*i_led == 10) 		// after 100 ms
			{
				LedOn(0, 0, 0, TabGen); 	// turn led off
				OutBuzOff();			// buzzer off
				OutMotorWu(0);		// vibration off
			}
			if (*i_led == 1000) 	// every 10 sec
			{
				*i_led = 0; 			// restart
			}
			(*i_led)++;
		}
	}
	if ((TabGen[ALERT_ON_PREVIOUS] == 1) && (TabGen[ALERT_ON] == 0))
	{
		LedOn(0, 0, 0, TabGen);
		OutBuzOff();
		OutMotorWu(0);
		TabGen[ALERT_ON_PREVIOUS] = 0;

		TabGen[FALL_IND_1] = 0;
		TabGen[FALL_IND_2] = 0;
		TabGen[FALL_COND_1] = 0;
		TabGen[FALL_COND_2] = 1;
		TabGen[FALL_COND_3] = 0;
		TabGen[FALL_COND_4] = 0;

	}

	if ((TabGen[ALERT_ON_PREVIOUS] == 0) && (TabGen[ALERT_ON] == 1))
	{
		TabGen[ALERT_ON_PREVIOUS] = 1;

		TabGen[FALL_IND_1] = 0;
		TabGen[FALL_IND_2] = 0;
		TabGen[FALL_COND_1] = 0;
		TabGen[FALL_COND_2] = 1;
		TabGen[FALL_COND_3] = 0;
		TabGen[FALL_COND_4] = 0;
	}
}

void TaskFallManager(uint16_t ar[], uint8_t y[], uint16_t accres, uint8_t accy,
		int TabGen[])
{
	uint16_t i_full;

	if (TabGen[FALL_IND_1] < 200 && TabGen[FALL_COND_2])
	{ // teste2 est initialis� en true ce if s'execute une seule fois pour remplie les 200 premiers elements du tableau
		ar[TabGen[FALL_IND_1]] = accres;
		y[TabGen[FALL_IND_1]] = accy;
		TabGen[FALL_IND_1]++;
	}

	if ((TabGen[FALL_IND_1] == 200) && (TabGen[FALL_COND_2]))
	{ // lorsque les 2OO premieres elements sont remplis dans le 1er tableau la valeur de test2 sera false donc le 1er if ne devient plus activ�
		TabGen[FALL_COND_1] = 1; //la variable test va nous permettre de savoir que les 200 premiers element du tableau sont bien remplis
		TabGen[FALL_COND_2] = 0;
	}

	// notez bien que les 2 tableaux sont d�phas� dans le temps par 2s.
	if (TabGen[FALL_COND_1] && 200 <= TabGen[FALL_IND_1]
			&& TabGen[FALL_IND_1] <= 399 && 0 <= TabGen[FALL_IND_2]
			&& TabGen[FALL_IND_2] <= 199)
	{ // cette �tape permet de remplir les deux tableaux � la fois et avec la m�me valeur pour avoir des valeurs en temps r�el
		ar[TabGen[FALL_IND_1]] = accres;
		y[TabGen[FALL_IND_1]] = accy;
		arr[TabGen[FALL_IND_2]] = ar[TabGen[FALL_IND_1]];
		yy[TabGen[FALL_IND_2]] = y[TabGen[FALL_IND_1]];
		TabGen[FALL_IND_2]++;
		TabGen[FALL_IND_1]++;
		if (TabGen[FALL_IND_1] == 400)
		{
			for (i_full = 0; i_full < 400; i_full++)
			{
				ar_full[i_full] = ar[i_full];
				y_full[i_full] = y[i_full];
			}
			TabGen[FALL_IND_1] = 0;
			TabGen[FALL_COND_3] = 1;
		}
	}

	if (TabGen[FALL_COND_1] && 0 <= TabGen[FALL_IND_1]
			&& TabGen[FALL_IND_1] <= 199 && 200 <= TabGen[FALL_IND_2]
			&& TabGen[FALL_IND_2] <= 399)
	{ //	cette �tape permet de remplir les deux tableaux � la fois et avec la m�me valeur pour avoir des valeurs en temps r�el
		arr[TabGen[FALL_IND_2]] = accres;
		yy[TabGen[FALL_IND_2]] = accy;
		ar[TabGen[FALL_IND_1]] = arr[TabGen[FALL_IND_2]];
		y[TabGen[FALL_IND_1]] = yy[TabGen[FALL_IND_2]];
		TabGen[FALL_IND_2]++;
		TabGen[FALL_IND_1]++;
		if (TabGen[FALL_IND_2] == 400)
		{
			for (i_full = 0; i_full < 400; i_full++)
			{
				ar_full[i_full] = arr[i_full];
				y_full[i_full] = yy[i_full];
			}
			TabGen[FALL_IND_2] = 0;
			TabGen[FALL_COND_4] = 1;
		}
	}
}

void TaskSendLoraNoGPS(int TabGen[], float TabFloatValue[],
		uint32_t TabGpsTimer[])
{
	char bufferLora[32];

	if ((LORAP2POK == 1) && (TabGen[LORAP2P_SEND] == 1) && SUEZ == 0)
	{
		TabGen[RE_ON_SCREEN] = 1;
		TabGen[LORAP2P_SEND] = 0;
		display_SendMess();
		//WakeUpNemeusLS();
		//RebootNemeusLS();
		OutBuzOff();

		OutMotorWu(0);
		LedOn(0, 0, 0, TabGen);
		//LoraOn();
		FuncLoraMessNoGPS(bufferLora, TabGen, TabFloatValue, TabGpsTimer);

		if (RAK811 == 1)
		{
			OutDwmRst(0);
			OutDwmRst(1);

			HAL_Delay(500);

			EnableLoraSend811();

			EnableLoraSend811();
			SendMessLora811(bufferLora);
			EnableLoraReceive811();
		}
		else
		{
			SendMessLora(bufferLora);
			ContinuousRxLora();
		}
	}
}

extern uint8_t Rx_datagps[MAXITGPS];
extern uint8_t Rx_Nemeus[MAXITNEMEUS];
extern uint8_t Rx_WIFI[MAXITWIFI];
extern uint8_t Rx_data1004[MAX_1004];

extern char msg_Lora[];
extern int distCnt;

char Name[30];
char MAC[18]; // 17
uint8_t nbcomma = 0;

extern uint8_t GA_Nem;
extern uint8_t ping_rep_ok;
extern uint8_t Rx_bufferNemeus[];
extern uint8_t Rx_bufferRAK811[];
extern uint8_t Rx_RAK811[];
extern int TabGen[];
extern uint32_t TabTimer[];
extern int TabAlert[];
extern uint32_t TabAlertAll[];
extern uint32_t millis;
extern uint32_t time_network_rep;
extern uint8_t network_state;
extern uint8_t DUAL_STATE_LS;

void Task_Read_Nemeus(void)
{
// SIGFOX
	if ((Rx_bufferNemeus[0] == '+') && (Rx_bufferNemeus[1] == 'S')
			&& (Rx_bufferNemeus[2] == 'F') && (Rx_bufferNemeus[3] == ':')
			&& (Rx_bufferNemeus[4] == ' '))
	{
		if ( //
		(Rx_bufferNemeus[5] == 'S') && (Rx_bufferNemeus[6] == 'N')
				&& (Rx_bufferNemeus[7] == 'D'))
		{
			//TabGen[SIGFOX_STATE] = 10;
		}

		if ( //
		(Rx_bufferNemeus[5] == 'R') && (Rx_bufferNemeus[6] == 'C')
				&& (Rx_bufferNemeus[7] == 'V') && (Rx_bufferNemeus[8] == 'B')
				&& (Rx_bufferNemeus[9] == 'I') && (Rx_bufferNemeus[10] == 'N'))
		{
			if (  //
			(Rx_bufferNemeus[12] == '1') && (Rx_bufferNemeus[13] == '2')
					&& (Rx_bufferNemeus[14] == '3')
					&& (Rx_bufferNemeus[15] == '4'))
			{
				uint8_t nbcomma = 0;
				uint8_t nbchar = 0;

				while (nbcomma < 2 && nbchar <= MAXITNEMEUS)
				{
					if (Rx_bufferNemeus[nbchar] == ',')
						nbcomma++;
					nbchar++;
				}

				if (Rx_bufferNemeus[nbchar] == '-') // RSSI AVAILABLE
				{
#ifndef debug_sound_vibration
					PowerBuzVib(100);
#endif
#ifdef debug_sound_vibration
					PowerVib(100);
#endif

					if (DUAL_STATE_LS == ACK_SF_PENDING)
					{
						//SendOnMessSigfox(1);
						TabTimer[ACK_TIMER] = HAL_GetTick();
						TabGen[RE_ON_SCREEN] = 1;
						DUAL_STATE_LS = NO_ACK_PENDING;

					}

					if (DUAL_STATE_LS == ACK_SF_PENDING_2)
					{
						TabTimer[ACK_TIMER] = HAL_GetTick();
						TabGen[RE_ON_SCREEN] = 1;
						DUAL_STATE_LS = NO_ACK_PENDING;
						LoraWanOn();
					}

					//RebootNemeusLS(TabGen);

					if (Rx_bufferNemeus[nbchar + 3] == '.') // 2 digit => -XX.XX
					{
						TabGen[SIGFOX_RSSI] = -(Rx_bufferNemeus[nbchar + 1]
								- '0') * 10
								+ (Rx_bufferNemeus[nbchar + 2] - '0');
					}
					else // 3 digits => -XXX.XX
					{
						TabGen[SIGFOX_RSSI] = -((Rx_bufferNemeus[nbchar + 1]
								- '0') * 100
								+ (Rx_bufferNemeus[nbchar + 2] - '0') * 10
								+ (Rx_bufferNemeus[nbchar + 3] - '0'));

						if (TabGen[SIGFOX_RSSI] <= -150
								&& TabGen[SIGFOX_RSSI] >= -10)
						{
							TabGen[SIGFOX_RSSI] = 0; // if RSSI is not between -10 and -150 dB, value is considered false
						}
					}
				}
			}
		}
	}

	// LORA (Orange or Objenious)
	if ((Rx_bufferNemeus[0] == '+') && (Rx_bufferNemeus[1] == 'M')
			&& (Rx_bufferNemeus[2] == 'A') && (Rx_bufferNemeus[3] == 'C')
			&& (Rx_bufferNemeus[4] == ':'))
	{
		if ((Rx_bufferNemeus[6] == 'R') && (Rx_bufferNemeus[7] == 'D')
				&& (Rx_bufferNemeus[8] == 'E') && (Rx_bufferNemeus[9] == 'V')
				&& (Rx_bufferNemeus[10] == 'A') && (Rx_bufferNemeus[11] == 'D'))
		{
			if (  //
			(Rx_bufferNemeus[15] != '0') || (Rx_bufferNemeus[16] != '0')
					|| (Rx_bufferNemeus[17] != '0')
					|| (Rx_bufferNemeus[18] != '0')
					|| (Rx_bufferNemeus[19] != '0')
					|| (Rx_bufferNemeus[20] != '0')
					|| (Rx_bufferNemeus[21] != '0')
					|| (Rx_bufferNemeus[22] != '0'))
			{
				// --'UN'SOLICITED ANSWER, JOIN OK
				if (TabGen[LORAWAN_STATE] == LW_WAIT_JOIN)
				{
					HAL_Delay(500);
					SendOnLora();

#ifndef debug_sound_vibration
					PowerBuzVib(100);
#endif
#ifdef debug_sound_vibration
					PowerVib(100);
#endif
					AskJoinTimeLoraWan = HAL_GetTick();

					TabTimer[ACK_TIMER] = HAL_GetTick();
					TabGen[RE_ON_SCREEN] = 1;
					TabGen[LORAWAN_STATE] = LW_JOIN_OK;
					DUAL_STATE_LS = ACK_LORA_PENDING;
				}

			}
		}

		if ((Rx_bufferNemeus[14] == ',' && Rx_bufferNemeus[6] != 'R')
				|| GA_Nem == 1)
		{
			if (  //
			(Rx_bufferNemeus[6] != '0') || (Rx_bufferNemeus[7] != '0')
					|| (Rx_bufferNemeus[8] != '0')
					|| (Rx_bufferNemeus[9] != '0')
					|| (Rx_bufferNemeus[10] != '0')
					|| (Rx_bufferNemeus[11] != '0')
					|| (Rx_bufferNemeus[12] != '0')
					|| (Rx_bufferNemeus[13] != '0'))
			{
				// SOLICITED ANSWER, JOIN OK
				if (TabGen[LORAWAN_STATE] == LW_WAIT_JOIN)
				{
					HAL_Delay(500);
					SendOnLora();

					AskJoinTimeLoraWan = HAL_GetTick();

#ifndef debug_sound_vibration
					PowerBuzVib(100);
#endif
#ifdef debug_sound_vibration
					PowerVib(100);
#endif

					TabTimer[ACK_TIMER] = HAL_GetTick();
					TabGen[RE_ON_SCREEN] = 1;
					TabGen[LORAWAN_STATE] = LW_JOIN_OK;
					DUAL_STATE_LS = ACK_LORA_PENDING;
				}
			}
		}

		if ( //
		(Rx_bufferNemeus[6] == 'R') && (Rx_bufferNemeus[7] == 'C')
				&& (Rx_bufferNemeus[8] == 'V') && (Rx_bufferNemeus[9] == 'B')
				&& (Rx_bufferNemeus[10] == 'I') && (Rx_bufferNemeus[11] == 'N'))
		{

			uint8_t nbcomma = 0;
			uint8_t nbchar = 0;
			uint8_t pending_downlink = 0;

			// PARSING ',' to look for RSSI
			while (nbcomma < 4 && nbchar <= MAXITNEMEUS)
			{
				if (Rx_bufferNemeus[nbchar] == ',')
					nbcomma++;
				if (nbcomma == 2)
					if (nbchar + 1 == 't')
						pending_downlink = 1; // not use, never true

				nbchar++;
			}

			// TESTING LORA SUCCESSFUL, TIME TO TEST SIGFOX
			if (DUAL_STATE_LS == ACK_LORA_PENDING)
			{
				for (int i_fct = 0; i_fct < MAXITNEMEUS; i_fct++)
				{
					Rx_Nemeus[i_fct] = 0;
				}

				DUAL_STATE_LS = SF_DELAY_ON;
				AskJoinTimeLoraWan = HAL_GetTick();

			}

			// IF THERE IS A '-' IT MEANS THE MESSAGE IS RECEIVED FROM AN ANTENNA
			if (Rx_bufferNemeus[nbchar] == '-')	//if (Rx_Nemeus[22] == '-')
			{

//					if(TabGen[ALERT_PENDING] == 1)
//					{
//						TabGen[ALERT_PENDING] = 0;
//						TabGen[SIGFOX_SEND] = 0;
//						TabGen[ALERT_PENDING] = 0;
//					}

				if (TabGen[LORAWAN_RSSI] == 0)
				{
#ifndef debug_sound_vibration
					PowerBuzVib(100);
#endif
#ifdef debug_sound_vibration
					PowerVib(100);
#endif

					TabTimer[ACK_TIMER] = HAL_GetTick();
					TabGen[RE_ON_SCREEN] = 1;
				}

				if (Rx_bufferNemeus[nbchar + 3] == '.') // 2 digit => -XX.XX
				{
					TabGen[LORAWAN_RSSI] = -(Rx_bufferNemeus[nbchar + 1] - '0')
							* 10 + (Rx_bufferNemeus[nbchar + 2] - '0');
				}
				else // 3 digits => -XXX.XX
				{
					TabGen[LORAWAN_RSSI] = -((Rx_bufferNemeus[nbchar + 1] - '0')
							* 100 + (Rx_bufferNemeus[nbchar + 2] - '0') * 10
							+ (Rx_bufferNemeus[nbchar + 3] - '0'));

					if (TabGen[LORAWAN_RSSI] <= -150
							&& TabGen[LORAWAN_RSSI] >= -10)
					{
						TabGen[LORAWAN_RSSI] = 0; // if RSSI is not between -10 and -150 dB, value is considered false
					}
				}

			} // NO RSSI, LORA DOWNLINK NOT RECEIVED
//				else if(SIGFOXOK == 1 && TabGen[ALERT_PENDING] == 1)
//				{// MAC COMMAND RECEIVED  ### +MAC: RDEVADDR, no minus, no ack // WORKING
//
//					TabGen[SIGFOX_SEND] = 1;
//				}
		}
	}

	// CLEAR DMA BUFFER
	for (int i_fct = 0; i_fct < MAXITNEMEUS; i_fct++)
	{
		Rx_Nemeus[i_fct] = 0;
		Rx_bufferNemeus[i_fct] = 0;
	}
}

void Task_Read_Incoming_Rak()
{
	//at+recv=-34,6,4:27111988
	uint8_t nbchar = 0;
	uint8_t offset = 0;
	uint8_t lenght_rx_rak = 23;
	if (strlen(Rx_bufferRAK811) >= lenght_rx_rak)
	{
		if ((Rx_bufferRAK811[0] == 'a') && (Rx_bufferRAK811[1] == 't')
				&& (Rx_bufferRAK811[2] == '+') && (Rx_bufferRAK811[3] == 'r')
				&& (Rx_bufferRAK811[4] == 'e') && (Rx_bufferRAK811[5] == 'c')
				&& (Rx_bufferRAK811[6] == 'v') && (Rx_bufferRAK811[7] == '='))
		{
			if (Rx_bufferRAK811[12] == ',')
			{
				offset++;
				lenght_rx_rak++;
			}
			uint8_t nbcolon = 0;
			while (nbcolon < 1 && nbchar <= lenght_rx_rak)
			{
				if (Rx_bufferRAK811[nbchar] == ':')
					nbcolon++;

				nbchar++;
			}
			sprintf(msg_Lora, "%c%c%c%c%c%c%c%c%c%c", Rx_bufferRAK811[nbchar],
					Rx_bufferRAK811[nbchar + 1], Rx_bufferRAK811[nbchar + 2],
					Rx_bufferRAK811[nbchar + 3], Rx_bufferRAK811[nbchar + 4],
					Rx_bufferRAK811[nbchar + 5], Rx_bufferRAK811[nbchar + 6],
					Rx_bufferRAK811[nbchar + 7], Rx_bufferRAK811[nbchar + 8],
					Rx_bufferRAK811[nbchar + 9]);

			if (msg_Lora[0] == '3' && msg_Lora[1] == '3' && msg_Lora[2] == '1'
					&& msg_Lora[3] == '1' && msg_Lora[4] == '1'
					&& msg_Lora[5] == '9')
			{
				uint8_t buff[3] =
				{ 0 };
				buff[0] = Rx_bufferRAK811[9];
				buff[1] = Rx_bufferRAK811[10];
				buff[2] = Rx_bufferRAK811[11];

				if (buff[1] == ',') //RSSI 1 digits
				{
					TabGen[REP_RSSI] = (Rx_bufferRAK811[9] - '0');
				}
				else if (buff[2] == ',') //RSSI 2 digits
				{
					TabGen[REP_RSSI] = (Rx_bufferRAK811[9] - '0') * 10
							+ (Rx_bufferRAK811[10] - '0');
				}
				else // RSSI 3 digits
				{
					TabGen[REP_RSSI] = (Rx_bufferRAK811[9] - '0') * 100
							+ (Rx_bufferRAK811[10] - '0') * 10
							+ (Rx_bufferRAK811[11] - '0');
				}

				ping_rep_ok = 1;

				if (msg_Lora[8] == 'F' && msg_Lora[9] == 'F')
				{
					// no SIFGOX COVERAGE
					TabGen[RSSI_REP] = 666;
				}
				else
				{

					uint16_t rssi_rep = (uint16_t) (msg_Lora[9] - '0') * 10;
					rssi_rep += (uint16_t) (msg_Lora[8] - '0') * 100;

					TabGen[RSSI_REP] = rssi_rep; // check if format is ok from value to char in repet
				}
				//{
				//AT+RFTX=SNDBIN,27111988,1
				//at+recv=-10,6,4:27111988, at+recv=-{1-140},{SNR},4:{111988

				TabGen[BATT_REP] = msg_Lora[6] - '0';
				TabGen[GPS_REP] = msg_Lora[7] - '0';

				//}
			}
		}
		for (int i_fct = 0; i_fct < MAXITRAK; i_fct++)
		{
			Rx_RAK811[i_fct] = 0;
			Rx_bufferRAK811[i_fct] = 0;
		}
	}
}

void Repeater_Link_Management(void)
{
	if (ping_rep_ok == 1)
	{
		network_state = 0;
		ping_rep_ok = 0;
		//PowerVib(100);
		TabGen[STATUS_REP] = 1;
		time_network_rep = HAL_GetTick();
		millis = time_network_rep;
	}
	if (TabGen[STATUS_REP] == 1)
	{
		if ((network_state == 0)
				&& ((millis - time_network_rep)
						> (TIME_BETWEEN_PING * 1 * 1000 + 1000)))
		{
			network_state = 1;
#ifdef debug_sound_vibration
			PowerVib(100);
#endif

#ifndef debug_sound_vibration
			PowerBuzVib(100);
#endif
			//ContinuousRxLora();
		}

		if ((network_state == 1)
				&& ((millis - time_network_rep)
						> (TIME_BETWEEN_PING * 2 * 1000 + 1000)))
		{
			network_state = 2;

#ifdef debug_sound_vibration
			PowerVib(100);
			HAL_Delay(200);
			PowerVib(100);
#endif

#ifndef debug_sound_vibration
			PowerBuzVib(100);
			HAL_Delay(200);
			PowerBuzVib(100);
#endif
		}

		if ((network_state == 2)
				&& ((millis - time_network_rep)
						> (TIME_BETWEEN_PING * 3 * 1000 + 1000)))
		{
			network_state = 3;
#ifdef debug_sound_vibration
			PowerVib(100);
			HAL_Delay(200);
			PowerVib(100);
			HAL_Delay(200);
			PowerVib(100);
#endif

#ifndef debug_sound_vibration
			PowerBuzVib(100);
			HAL_Delay(200);
			PowerBuzVib(100);
			HAL_Delay(200);
			PowerBuzVib(100);
#endif
			TabGen[STATUS_REP] = 0;
		}
	}
}

extern uint8_t batt_20;
extern uint8_t batt_15;
extern uint8_t batt_10;
extern uint8_t batt_5;
extern uint32_t low_bat_shutdown;
extern volatile uint8_t Flag[];
extern uint8_t USB_In_Event;
extern float TabFloatValue[];

void Battery_Charger_Management(void)
{
	if (Flag[F_CHARGER] == 1)
	{
		Flag[F_CHARGER] = 0;
		TaskCharger(TabGen);
		if (TabGen[CHARGEC] == 0)
		{
			if (USB_In_Event == 1)
			{
				USB_In_Event = 0;
				TabGen[RE_ON_SCREEN] = 1;
				PowerVib(50);

				TabGen[ALERT_ON] = 0; // clear alert
				TabGen[NS_MALAISE] = 0;
				TabGen[NS_IMMO] = 0;
				for (uint8_t i = 0; i < NB_ALERT; i++)
					TabAlert[i] = 0;
				TabGen[TYPE_ALERT] = NONE_ALERT;
			}
		}
		if (TabGen[CHARGEC] == 1)
		{
			if (USB_In_Event == 0)
			{
				USB_In_Event = 1;
				TabGen[RE_ON_SCREEN] = 1;
				PowerVib(50);
			}
			TabGen[ALERT_ON] = 0; // clear alert
			TabGen[NS_MALAISE] = 0;
			TabGen[NS_IMMO] = 0;
			for (uint8_t i = 0; i < NB_ALERT; i++)
				TabAlert[i] = 0;
			TabGen[TYPE_ALERT] = NONE_ALERT;
			TaskAlertAll(TabAlert, TabGen, TabAlertAll, TabFloatValue);
		}
	}

#ifndef debug_sound_vibration
	if (Flag[F_BATTERY] == 1)
	{
		Flag[F_BATTERY] = 0;
		TaskReadBat(TabGen);
		// Battery level between 15 - 20, do nothing
		if (TabGen[BAT_VALUE] > 15 && TabGen[BAT_VALUE] < 20)
		{
			batt_20 = 1; //
			batt_15 = 0;
			batt_10 = 0;
			batt_5 = 0;
		}
		// Battery level between 10 - 15. If the battery was previously above 15 => vibration and buzzer because battery level is decreasing
		if (TabGen[BAT_VALUE] > 10 && TabGen[BAT_VALUE] < 15)
		{
			if (batt_20 == 1)
			{
				PowerBuzVib(100);
				LedOn(250, 0, 0, TabGen);
				HAL_Delay(50);
				PowerBuzVib(100);
				TabGen[RE_ON_SCREEN] = 1;
				TabTimer[TIMER_LOW_BAT] = HAL_GetTick();
			}
			batt_20 = 0;
			batt_15 = 1; //
			batt_10 = 0;
			batt_5 = 0;
		}
		// Battery level between 5 - 10. If the battery was previously above 10 => vibration and buzzer because battery level is decreasing
		if (TabGen[BAT_VALUE] > 5 && TabGen[BAT_VALUE] < 10)
		{
			if (batt_15 == 1)
			{
				PowerBuzVib(100);
				LedOn(250, 0, 0, TabGen);
				HAL_Delay(50);
				PowerBuzVib(100);
				TabGen[RE_ON_SCREEN] = 1;
				TabTimer[TIMER_LOW_BAT] = HAL_GetTick();
			}
			batt_20 = 0;
			batt_15 = 0;
			batt_10 = 1; //
			batt_5 = 0;
		}
		// Battery level between 0 - 5. If the battery was previously above 5 => vibration and buzzer because battery level is decreasing
		if (TabGen[BAT_VALUE] < 5)
		{
			if (batt_10 == 1)
			{
				PowerBuzVib(100);
				LedOn(250, 0, 0, TabGen);
				HAL_Delay(50);
				PowerBuzVib(100);
				TabGen[RE_ON_SCREEN] = 1;
				TabTimer[TIMER_LOW_BAT] = HAL_GetTick();
			}
			batt_20 = 0;
			batt_15 = 0;
			batt_10 = 0;
			batt_5 = 1; //
			if (TabGen[CHARGEC] == 0)
			{
				low_bat_shutdown++;
			}
			else
				low_bat_shutdown = 0;
		}
	}
	if (TabGen[BAT_VALUE] == 255)
	{
		if (TabGen[CHARGEC] == 0)
		{
			low_bat_shutdown++;
		}
		else
			low_bat_shutdown = 0;

		if (low_bat_shutdown > TIME_BEFORE_SHUTDOWN_LOWBAT - 10)
			TabGen[RE_ON_SCREEN] = 1;
	}

#endif
}

void GPS_Management(void)
{
	if (TabGen[FORCE_GPS] == 1)
	{
		TabGen[GPS_ON] = 1;
		TabGen[FORCE_GPS] = 0;
	}

	// STEP 1
	if ((TabGen[GPS_ON] == 1) && (TabGen[GPS_ON_PREVIOUS] == 0)) // IF GPS MUST BE ON BUT WASN'T ALREADY
	{
		// GPS is on, first start.
		TabGen[GPS_ON_PREVIOUS] = 1;
		TabTimer[GPS_FIRST_START] = millis;
		GpsStart();
		TabGen[GPS_GOOD] = 0;
		if (millis - TabTimer[LAST_UPDATE_GPS] > 10 * 60 * 1000 || TabTimer[LAST_UPDATE_GPS] == 0)
			TabGen[GPS_DURATION] = 10;
	}

	// STEP 2
	if ((TabGen[GPS_ON] == 1) && (TabGen[GPS_ON_PREVIOUS] == 1)) // IF GPS IS ON ALREADY
	{
		if ((millis - TabTimer[GPS_FIRST_START]) > (TabGen[GPS_DURATION] * 60 * 1000)) // in minutes
		{
			TabGen[GPS_ON] = 0;
			TabGen[GPS_ON_PREVIOUS] = 0;
			TabTimer[GPS_REPEAT_START] = millis;
			GpsStop();
		}
	}

	// STEP 3
	if ((TabGen[GPS_ON] == 0) && (TabGen[GPS_ON_PREVIOUS] == 0))
	{
		// GPS is not on => turn it on
		if ((millis - TabTimer[GPS_REPEAT_START]) > (GPSREPEAT * 60 * 1000)) // in minutes
		{
			TabGen[GPS_ON] = 1;
		}
	}
}

extern uint8_t nb_parametre;
extern uint8_t received_data[64];
extern struct config_data c1;
void Task_USB_Configuration(void)
{
	uint8_t len = sizeof(received_data);
	uint8_t count = 0;

	if (len > 0)
	{
		while ((received_data[count] != 'r') && (received_data[count] != 'w')
				&& (count < len))
		{
			count++;
		}
		if ((received_data[count] == 'r') && (received_data[count + 1] == 'e')
				&& (received_data[count + 2] == 'a')
				&& (received_data[count + 3] == 'd'))
		{
			uint8_t buffer[] = "ID SIGFOX + Vbat";
			uint8_t send_buffer2[nb_parametre];
			uint8_t send_buffer3[64];
			CDC_Transmit_FS(buffer, sizeof(buffer));
			memset(received_data, 0, len);
			vibration_LBL(1, 0, 200);
			ee_init();
			ee_read(0, sizeof(send_buffer2), send_buffer2);
			sprintf(send_buffer3,
					"CONFIG,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d",
					send_buffer2[0], send_buffer2[1], send_buffer2[2],
					send_buffer2[3], send_buffer2[4], send_buffer2[5],
					send_buffer2[6], send_buffer2[7], send_buffer2[8],
					send_buffer2[9], send_buffer2[10], send_buffer2[11],
					send_buffer2[12], send_buffer2[13], send_buffer2[14]);
			CDC_Transmit_FS(send_buffer3, strlen(send_buffer3));
		}
		else if ((received_data[count] == 'w')
				&& (received_data[count + 1] == 'r')
				&& (received_data[count + 2] == 'i')
				&& (received_data[count + 3] == 't')
				&& (received_data[count + 4] == 'e'))
		{
			vibration_LBL(1, 0, 200);
			unsigned char *config_data_received;
			int tabint[nb_parametre];
			uint8_t send_buffer[64];
			unsigned char i = 0;
			config_data_received = strtok(received_data, ",");
			while (config_data_received != NULL)
			{
				unsigned char tabtemp2[nb_parametre];
				sprintf(tabtemp2, "%s", config_data_received);
				tabint[i] = atoi(tabtemp2);
				config_data_received = strtok(NULL, ",");
				i++;
			}
			c1.tps_immo = tabint[1];
			c1.tps_PerteDeVerticalite = tabint[2];
			c1.tps_GPS_ON = tabint[3];
			c1.tps_GPS_OFF = tabint[4];
			c1.tps_Alarme = tabint[5];
			c1.chute_Actif = tabint[6];
			c1.malaise_Actif = tabint[7];
			c1.com_sigfox = tabint[8];
			c1.com_LoRa = tabint[9];
			c1.GPS_Actif = tabint[10];
			c1.Immo_Actif = tabint[11];
			c1.Verti_Actif = tabint[12];
			c1.Sensibilite_chute = tabint[13];
			c1.tps_chute = tabint[14];
			c1.Angle = tabint[15];
			uint8_t buffer[] = "config ok";
			CDC_Transmit_FS(buffer, sizeof(buffer));
			memset(received_data, 0, len);

			//eeprom
			ee_init();
			uint8_t d[] =
			{ c1.tps_immo, c1.tps_PerteDeVerticalite, c1.tps_GPS_ON,
					c1.tps_GPS_OFF, c1.tps_Alarme, c1.chute_Actif,
					c1.malaise_Actif, c1.com_sigfox, c1.com_LoRa, c1.GPS_Actif,
					c1.Immo_Actif, c1.Verti_Actif, c1.Sensibilite_chute,
					c1.tps_chute, c1.Angle};
			uint8_t dr[sizeof(d)];
			ee_read(0, sizeof(d), dr);
			if ((c1.tps_immo != dr[0]) || (c1.tps_PerteDeVerticalite != dr[1])
					|| (c1.tps_GPS_ON != dr[2]) || (c1.tps_GPS_OFF != dr[3])
					|| (c1.tps_Alarme != dr[4]) || (c1.chute_Actif != dr[5])
					|| (c1.malaise_Actif != dr[6]) || (c1.com_sigfox != dr[7])
					|| (c1.com_LoRa != dr[8]) || (c1.GPS_Actif != dr[9])
					|| (c1.Immo_Actif != dr[10]) || (c1.Verti_Actif != dr[11])
					|| (c1.Sensibilite_chute != dr[12])
					|| (c1.tps_chute != dr[13]) || (c1.Angle != dr[14]))
			{
				ee_writeToRam(0, sizeof(d), d);
				ee_commit();
				vibration_LBL(2, 200, 200);
			}
			ee_read(0, sizeof(d), dr);
			sprintf(send_buffer,
					"CONFIG,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d",
					dr[0], dr[1], dr[2], dr[3], dr[4], dr[5], dr[6], dr[7],
					dr[8], dr[9], dr[10], dr[11], dr[12], dr[13], dr[14]);
			CDC_Transmit_FS(send_buffer, strlen(send_buffer));
		}
	}
}

void TaskReadGaz(uint32_t Tab[], float *gazFloatLevel, float *COFloatLevel, float h2sOffset, float h2sfactor,ADC_HandleTypeDef *hadc1) {

  uint32_t h2sLevel32;
  int i_max = 50;

  switch (TaskState(Tab)) {
  case 1:
    OutCmdGaz(1);
    HAL_Delay(1);
    *gazFloatLevel = 0;
    for (int i = 0; i < i_max; ++i) {
      HAL_ADC_Start(hadc1);
      HAL_ADC_PollForConversion(hadc1, 1);
      h2sLevel32 = HAL_ADC_GetValue(hadc1);
      HAL_ADC_Stop(hadc1);
      *gazFloatLevel = ((float)h2sLevel32) + *gazFloatLevel;
    }
    *gazFloatLevel = h2sfactor * (((*gazFloatLevel / i_max) * 3.3 / 4096) / 0.0297);
    *gazFloatLevel = *gazFloatLevel - h2sOffset;

   *gazFloatLevel = (*gazFloatLevel) * 1.66667 ;  //for B7E9 without blank protection
   // *h2sFloatLevel = (*h2sFloatLevel) * 1.412 ;  //for 25AE with blank protection
		*COFloatLevel = 0 ;
    break;
  default:
    break;
  }
}



extern ADC_HandleTypeDef hadc1;
extern uint8_t BiGaz_ON;
extern uint8_t count_gaz ;
extern uint16_t gaz1_level[NB_SAMPLES_GAZ];
extern uint16_t gaz2_level[NB_SAMPLES_GAZ];
extern uint32_t gaz1_level_mean ;
extern uint32_t gaz1_ppm ;
extern uint32_t gaz2_level_mean ;
extern uint32_t gaz2_ppm ;
extern uint8_t gaz_alert_phase ;
extern uint8_t Calibration_Time_Over ;
extern uint32_t last_vib ;

uint8_t GAZ_THRESHOLD_ALERT ;

void Task_Gaz()
{
	if (BiGaz_ON == 1 && TabGen[ALERT_ON] == 0 && TabGen[SIGFOX_SEND] == 0)
	{
		uint32_t time = HAL_GetTick();
		if (time > 20000)
			Calibration_Time_Over = 1;

		if (time % 500 == 0)
		{

			ADC_ChannelConfTypeDef sConfig = {0};

			// CHANNEL 5 ALONE OK, CO VOUT1, RIGHT SENSOR, ADC_G1
			sConfig.Channel = ADC_CHANNEL_5;
			sConfig.Rank = 1;
			sConfig.SamplingTime = ADC_SAMPLETIME_247CYCLES_5;
			sConfig.SingleDiff = ADC_SINGLE_ENDED;
			sConfig.OffsetNumber = ADC_OFFSET_NONE;
			sConfig.Offset = 0;

			if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
			{
				Error_Handler();
			}

			if (HAL_ADC_Start(&hadc1) != HAL_OK)
			{
				Error_Handler();
			}

			if (HAL_ADC_PollForConversion(&hadc1, 100) != HAL_OK)
			{
				Error_Handler();
			}

			uint16_t gaz_12bit = 0;
			gaz_12bit = HAL_ADC_GetValue(&hadc1);

			HAL_ADC_Stop(&hadc1);

			gaz1_level[count_gaz] = gaz_12bit ;//((double)gaz_12bit * 3.3)/4096;

			gaz1_level_mean = 0;
			for (uint8_t i = 0; i < NB_SAMPLES_GAZ; i++)
				gaz1_level_mean +=  (uint32_t)gaz1_level[i];

			gaz1_level_mean = (uint32_t) ((double)gaz1_level_mean / NB_SAMPLES_GAZ) ;
			gaz1_ppm = (uint32_t)((double)gaz1_level_mean * 3.3);
			//gaz1_level_mean = ((double) gaz1_level_mean * 3.3)/4095;



			// CHANNEL 9 ALONE OK, H2S VOUT2, LEFT SENSOR, ADC_G3
			sConfig.Channel = ADC_CHANNEL_9;
			sConfig.Rank = 1;
			sConfig.SamplingTime = ADC_SAMPLETIME_247CYCLES_5;
			sConfig.SingleDiff = ADC_SINGLE_ENDED;
			sConfig.OffsetNumber = ADC_OFFSET_NONE;
			sConfig.Offset = 0;

			if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
			{
				Error_Handler();
			}

			if (HAL_ADC_Start(&hadc1) != HAL_OK)
			{
				Error_Handler();
			}

			if (HAL_ADC_PollForConversion(&hadc1, 100) != HAL_OK)
			{
				Error_Handler();
			}

			gaz_12bit = 0;
			gaz_12bit = HAL_ADC_GetValue(&hadc1);

			HAL_ADC_Stop(&hadc1);

			gaz2_level[count_gaz] = gaz_12bit ;//((double)gaz_12bit * 3.3)/4096;

			gaz2_level_mean = 0;
			for (uint8_t i = 0; i < NB_SAMPLES_GAZ; i++)
				gaz2_level_mean +=  (uint32_t) gaz2_level[i];

			gaz2_level_mean = (uint32_t) ((double)gaz2_level_mean / NB_SAMPLES_GAZ) ;
			gaz2_ppm = (uint32_t)((double)(25 * gaz2_level_mean)/1600.0);
			//gaz2_level_mean = ((double) gaz2_level_mean * 3.3)/4095;
			//gaz2_level = gaz_12bit; //((double)gaz_12bit * 3.3)/4096;

			if (count_gaz < NB_SAMPLES_GAZ)
				count_gaz++;
			else
				count_gaz = 0;

		}


		uint8_t VLEP_CO = 100;
		uint8_t VLEP_H2S = 10;

		if (gaz1_ppm > VLEP_CO || gaz2_ppm > VLEP_H2S && Calibration_Time_Over == 1)
		{
			if (gaz1_ppm > VLEP_CO )
				GAZ_THRESHOLD_ALERT = 1;
			else if (gaz2_ppm > VLEP_H2S)
				GAZ_THRESHOLD_ALERT = 2;
			else
				GAZ_THRESHOLD_ALERT = 0;

			if (time - last_vib > 1000 && gaz_alert_phase == 0)
			{
				gaz_alert_phase = 1;
				LedOn(250, 250, 250, TabGen);


				OutBuzOn();
				PowerVib(80);
				OutBuzOff();

				//LedOn(0, 0, 0, TabGen);
				last_vib = HAL_GetTick();
			}
			else if (time - last_vib > 100 && gaz_alert_phase == 1)
			{
				gaz_alert_phase = 2;

			}
			else if (time - last_vib > 150 && gaz_alert_phase == 2)
			{
				gaz_alert_phase = 0;

				OutBuzOn();
				PowerVib(80);
				OutBuzOff();

				LedOn(0, 0, 0, TabGen);
			}



		}
		else
			GAZ_THRESHOLD_ALERT = 0;
	}
}




