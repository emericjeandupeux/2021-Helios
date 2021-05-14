/**
  ******************************************************************************
  * @file           : capteurs.c
  * @brief          : fichier pour l'ecran
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 Hestiam.
  * All rights reserved.</center></h2>
	*
	* for more informations about u8g2 library
	* https://github.com/olikraus/u8g2/wiki/u8g2setupc#using-dynamically-allocated-page-buffers
	*
	* help using :
	* https://elastic-notes.blogspot.com/2018/10/u8g2-library-usage-with-stm32-mcu.html
	* http://someonehappyau.blogspot.com/2019/07/stm32u8g2i2coled.html
	*
	* Git :
	* https://github.com/olikraus/u8g2
	*
	*
	*
  ******************************************************************************
  */
#include "hes_include_stm32.h"
#include "dco_display.h"

//#include "string.h"


char str_taux_H2S[] = "H2S ";
char str_taux_O2[] =  "O2  ";
char str_taux_CO[] =  "CO  ";
char str_taux_EX[] =  "EX  ";

uint8_t show_RSSI = 0;

uint8_t blink_soundLevel = 1;
/*
* Permet de faire l'initialisation  de l'�cran au d�marrage
*/
void display_Init(uint8_t b_display_msg) {
	//u8g2_Setup_sh1106_i2c_128x64_noname_1(&u8g2, U8G2_R0, u8x8_byte_hw_i2c, u8x8_gpio_and_delay);
	u8g2_Setup_ssd1306_i2c_128x32_univision_1(&u8g2, U8G2_R0, u8x8_byte_hw_i2c, u8x8_gpio_and_delay);
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);
	u8g2_ClearDisplay(&u8g2);
	if(b_display_msg)
		display_Chargement_perso();
	u8g2_FirstPage(&u8g2);  // EJ : test bug ecran clear
}

void display_InitBis() 
{
	//u8g2_Setup_sh1106_i2c_128x64_noname_1(&u8g2, U8G2_R0, u8x8_byte_hw_i2c, u8x8_gpio_and_delay);
	u8g2_Setup_ssd1306_i2c_128x32_univision_1(&u8g2, U8G2_R0, u8x8_byte_hw_i2c, u8x8_gpio_and_delay);
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);
	u8g2_ClearDisplay(&u8g2);
}

extern uint8_t IMU_nodata;
extern uint32_t gaz1_level_mean;
extern uint32_t gaz2_level_mean;
extern uint32_t gaz1_ppm;
extern uint32_t gaz2_ppm;
extern uint32_t TabTimer[];
extern uint8_t BiGaz_ON;
extern uint8_t GAZ_THRESHOLD_ALERT;

/*
* Fonction permettant d'afficher les taux des differents gaz et niveau sonore
* ainsi que les etats des alertes, du GPS , du reseau et de la batterie
*/
void display_dco(float TabFloatValue[],int TabAlert[],int TabGen[], uint32_t TabTimer[], char name[], char * msg1, char * msg2, char *msg3, char *msg4) 
	{

	char str_ppm[] = " PPM";
	char poucent[] = " %";
	char vme[]		 = " VME";
	char manque[]		 = " <<";
	char explo[]		 = " >>";
	char vlct[] 	 = " VLCT";
	char db[] 		 = " dB";
	char str_H2S [30] = {0};
	char str_O2 [30]	= {0};
	char str_CO [30]	= {0};
	char str_EX [30]	= {0};

	char str_son[6] = {0};

	// H2S
	strcat(str_H2S, str_taux_H2S);
	strcat(str_H2S, msg1);
	strcat(str_H2S, str_ppm);
	if (TabAlert[ALERT_H2SVLCT] == 1)
	{
		strcat(str_H2S, vlct);
	}
	else if (TabAlert[ALERT_H2SVME] == 1)
	{
		strcat(str_H2S, vme);
	}
	// O2 clignotement
	strcat(str_O2, str_taux_O2);
	strcat(str_O2, msg2);
	strcat(str_O2, poucent);
	if (TabAlert[ALERT_O2] == 1)
	{
		strcat(str_O2, manque);
	}


	//CO pas afficher
	strcat(str_CO, str_taux_CO);
	strcat(str_CO, msg3);
	strcat(str_CO, str_ppm);
	if (TabAlert[ALERT_COVLCT] == 1) {
		strcat(str_CO, vlct);
	}
	else if (TabAlert[ALERT_COVME] ==+ 1) {
		strcat(str_CO, vme);
	}

	// EX
	strcat(str_EX, str_taux_EX);
	
	strcat(str_EX, msg4);
	strcat(str_EX, poucent);
	if (TabAlert[ALERT_EX] == 1) {
		strcat(str_EX, explo);
	}

	 son = ((uint8_t) TabFloatValue[DB_VALUE])+10;
	
	sprintf(str_son, "%i", son);
	strcat(str_son, db);

	

		u8g2_FirstPage(&u8g2);   
	
	do {
		
			char str_display[18];
			u8g2_SetFont(&u8g2, u8g2_font_5x8_tr);
			if(IMU_nodata == 100)
			{
				u8g2_DrawStr(&u8g2, 45, 8, "!IMU!");
			}






//		if(WIFI == 1)  // display MAC of the closest Wifi on the screen
//			display_Wifi(TabGen, name);

		if (LORAP2POK == 1)
			RepeaterLinkStatus(TabGen);

		if(SIGFOXOK == 1 || LORAWANOK == 1)
		{
//			if(SIGFOXOK == 1 && LORAWANOK == 1)
//				NetworkStatus(TabGen);
			
			if (HAL_GetTick() - TabTimer[ACK_TIMER] <= SEC_ONOFF_SCREEN * 1000 && TabTimer[ACK_TIMER] != 0)
			{
				//NetworkStatus(TabGen);
				show_RSSI = 1;
			}
			else
				show_RSSI = 0;
		}
		//display_son(son);
		if(GPSOK == 1 && show_RSSI == 0)
			display_GPS_status(status_GPS, TabTimer, TabGen);

		if(BATTERYOK == 1 && SUEZ == 0)
			display_BatteryLvl(batteryLevel, 108, 0);
		u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr);
			
		//u8g2_DrawStr(&u8g2, 20, 16, str_son);
		if (BOX4GAZ == 1)
		{
			u8g2_DrawStr(&u8g2, 2, 27, str_H2S);
			u8g2_DrawStr(&u8g2, 2, 36, str_O2);
			u8g2_DrawStr(&u8g2, 2, 45, str_CO);
			u8g2_DrawStr(&u8g2, 2, 54, str_EX);
		}
		else 
		if (SUEZ == 1)
		{
			u8g2_DrawStr(&u8g2, 2, 17, str_H2S);
		}
		display_Alerte(TabGen, alerte);
	} while (u8g2_NextPage(&u8g2));
	//blink_soundLevel = !blink_soundLevel;
}

void ClearScreen(void)
{
	u8g2_ClearBuffer(&u8g2);
}

/*
* Pour debugger uniquement permet dafficher deux valeurs et un text
*/
void display_Print_PPM(char *title, float value, float tension) 
{
	char valueToString[10];
	char tensionToString[10];
	sprintf(valueToString, "%f", value);
	sprintf(tensionToString, "%f", tension);
	u8g2_FirstPage(&u8g2);
	do {
		//u8g2_SetFont(&u8g2, u8g2_font_ncenB14_tr);
		u8g2_SetFont(&u8g2, u8g2_font_u8glib_4_tf);
		u8g2_DrawStr(&u8g2, 0, 15, title);
		u8g2_DrawStr(&u8g2, 0, 30, valueToString);
		u8g2_DrawStr(&u8g2, 0, 45, tensionToString);
	} while (u8g2_NextPage(&u8g2));
}

/*
* Permet de changer l'icon du niveau sonore
*/
void display_son(uint8_t db) 
{
	if (db < 80) 
	{
		u8g2_DrawXBM(&u8g2, 3, 5, son60_width, son60_height, (uint8_t *)son60_bits);
	}
	if ( db >= 80 && db < 120)
	{
		u8g2_DrawXBM(&u8g2, 3, 5, son80_width, son80_height, (uint8_t *)son80_bits);
	}
	if (db >= 120) {
		u8g2_DrawXBM(&u8g2, 3, 5, son120_width, son120_height, (uint8_t *)son120_bits);
	}

}
/*
* Warning animation
*/
void display_warning(uint8_t nb) {
	for (int i = 0; i < nb; i++) {
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 32, 0, warning_width, warning_height, (uint8_t *) warning_bits);
		} while (u8g2_NextPage(&u8g2));
		HAL_Delay(500);
		u8g2_ClearDisplay(&u8g2);
		HAL_Delay(200);
	}
}

/*
* Permet d'afficher l'etat du GPS
*/
void display_GPS_status(uint8_t status, uint32_t TabGpsTimer[], int TabGen[]) 
{
	uint32_t last_update = 0 ;
	char str_display[12];
	char str_last[8];
	char nb_sat[2];
	
//	TabGpsTimer[LAST_UPDATE_GPS] = HAL_GetTick() - 8 *60 * 1000 *59 ;
	
	if(TabGen[GPS_ON] == 1)
	{
		sprintf(nb_sat, "%d", TabGen[NB_SATT_FOUND]);
		
//				if (TabGen[NB_SATT_FOUND] >= 8)
//					strcat(str_last, "++");  // concatenation
//				else if (TabGen[NB_SATT_FOUND] >= 5)
//					strcat(str_last, "+");  // concatenation

	}
	else 
		strcpy(nb_sat, ".");  // concatenation
	
	//u8g2_SetFont(&u8g2, u8g2_font_5x8_tr);	
	//u8g2_DrawStr(&u8g2, 60, 8, nb_sat); 		// Display elasped time since last good GPS position
	
	if (TabGpsTimer[LAST_UPDATE_GPS] <= 0) // never got location
		last_update = 0;
	else // last update seems valid, display time on screen
	{
		// display time when location acquired
		last_update = (HAL_GetTick() - TabGpsTimer[LAST_UPDATE_GPS]) / 60000 + 1 ; //    / 60000
	
		if(last_update > (8 * 60))
		{
			strcpy(str_last, "++"); // copy
		}
		else
		{
			if( last_update >= 60)
			{
				sprintf(str_last, "%u", last_update / 60);
				strcat(str_last, "h");  // concatenation
			}
			else
			{
				sprintf(str_last, "%u", last_update);
				strcat(str_last, "min");  // concatenation
			}
			//strcat(str_last, nb_sat);  // concatenation
		}
		//u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr);	
		u8g2_SetFont(&u8g2, u8g2_font_5x8_tr);	
		sprintf(str_display, "GPS:");
		strcat(str_display, str_last);
		u8g2_DrawStr(&u8g2, 0, 8, str_display); // Display elasped time since last good GPS position
	}
			
	
//	u8g2_SetFont(&u8g2,u8g2_font_t0_11_tr); // fonctionne
	if (last_update > 0 && last_update <= 1)  // (status)
	{
		u8g2_DrawXBM(&u8g2, 90, 0, gps_on_width, gps_on_height, (uint8_t *)gps_on_bits);
	}
	else 
	{
		u8g2_DrawXBM(&u8g2, 90, 0, gps_off_width, gps_off_height, (uint8_t *)gps_off_bits);
	}
}


void display_Wifi (int TabGen[], char name[])
{
	if(WIFI == 1)
	{
		if(name[0] != 'N' && name[1] != 'o' && name[2] != 'N' && name[3] != 'a' && name[4] != 'm' && name[5] != 'e')
		{
			char str_display[18];
			u8g2_SetFont(&u8g2, u8g2_font_5x8_tr);	
			sprintf(str_display, "%s", name);
			u8g2_DrawStr(&u8g2, 0, 10, str_display); 
		}	
	}
}

extern uint8_t DUAL_STATE_LS;

void NetworkStatus(int TabGen[])
{

	if (LORAWANOK == 1 && SIGFOXOK == 1)
	{

		if(TabGen[LORAWAN_RSSI] == 0 || TabGen[SIGFOX_RSSI] == 0)
		{
			char str_display[18];
			u8g2_SetFont(&u8g2, u8g2_font_5x8_tr);

			if(DUAL_STATE_LS == ACK_LORA_PENDING)
			{
				sprintf(str_display, "LW-W");//: %ddB", TabGen[LORAWAN_RSSI]);
				u8g2_DrawStr(&u8g2, 1, 8, str_display);
			}
			else if(DUAL_STATE_LS == SF_DELAY_ON)
			{
				sprintf(str_display, "SF-D");//: %ddB", TabGen[LORAWAN_RSSI]);
				u8g2_DrawStr(&u8g2, 1, 8, str_display);
			}
			else if(DUAL_STATE_LS == ACK_SF_PENDING)
			{
				sprintf(str_display, "SF-W");//: %ddB", TabGen[LORAWAN_RSSI]);
				u8g2_DrawStr(&u8g2, 1, 8, str_display);
			}
			else if(DUAL_STATE_LS == NO_ACK_SF_RETRY)
			{
				sprintf(str_display, "SF-R");//: %ddB", TabGen[LORAWAN_RSSI]);
				u8g2_DrawStr(&u8g2, 1, 8, str_display);
			}
			else if(DUAL_STATE_LS == ACK_SF_PENDING_2)
			{
				sprintf(str_display, "SF-W2");//: %ddB", TabGen[LORAWAN_RSSI]);
				u8g2_DrawStr(&u8g2, 1, 8, str_display);
			}
			else if(TabGen[LORAWAN_STATE] == LW_WAIT_JOIN)
			{
				sprintf(str_display, "LW-J-W");//: %ddB", TabGen[LORAWAN_RSSI]);
				u8g2_DrawStr(&u8g2, 1, 8, str_display);
			}
			else if(TabGen[LORAWAN_STATE] == LW_JOIN_OK)
			{
				sprintf(str_display, "LW-J");//: %ddB", TabGen[LORAWAN_RSSI]);
				u8g2_DrawStr(&u8g2, 1, 8, str_display);
			}
		}
	}



	int posXmes = 2, posYmes = 8;
	if (SIGFOXOK == 1 && TabGen[SIGFOX_RSSI] != 0)
	{
		char str_display[18];
		u8g2_SetFont(&u8g2, u8g2_font_5x8_tr);	
		sprintf(str_display, "RSSI: %ddB", TabGen[SIGFOX_RSSI]);
		//u8g2_DrawStr(&u8g2, 1, 8, str_display);

	}
	
		if (LORAWANOK == 1 && TabGen[LORAWAN_RSSI] != 0 )
	{
		char str_display[18];
		u8g2_SetFont(&u8g2, u8g2_font_5x8_tr);	
		sprintf(str_display, "LW: %ddB", TabGen[LORAWAN_RSSI]);
		//u8g2_DrawStr(&u8g2, 1, 8, str_display);

	}

}

void RepeaterLinkStatus(int TabGen[])
{
		char str_display[18];
		u8g2_SetFont(&u8g2, u8g2_font_5x8_tr);
		if (TabGen[STATUS_REP] == 1)
		{


			display_BatteryLvl(TabGen[BATT_REP]*20, 0, 0);
			sprintf(str_display, "Rep(-%d)",TabGen[REP_RSSI]);
			//sprintf(str_display, TabG);
			u8g2_DrawStr(&u8g2, 24, 11, str_display);

			if (TabGen[GPS_REP] == 1)  // (status)
			{
				u8g2_DrawXBM(&u8g2, 90, 0, gps_on_width, gps_on_height, (uint8_t *)gps_on_bits);
			}
			else
			{
				u8g2_DrawXBM(&u8g2, 90, 0, gps_off_width, gps_off_height, (uint8_t *)gps_off_bits);
			}

		}
		else
		{
			sprintf(str_display, "Rep.   Lien KO");
			u8g2_DrawStr(&u8g2, 2, 11, str_display);
		}


}


/*
* Permet d'afficher l'etat du reseau
*/
void display_network_status(uint8_t status, uint8_t posXmes, uint8_t posYmes)
{
	if (status == 1)
	{
		u8g2_DrawXBM(&u8g2, posXmes, posYmes, reseau_1_width, reseau_1_height, (uint8_t *)reseau_1_bits);
	}
	else
	{
		u8g2_DrawXBM(&u8g2, posXmes, posYmes, reseau_0_width, reseau_0_height, (uint8_t *)reseau_0_bits);
	}
}

/*
* Fonction permettant d'afficher un chargement au demarrage
*/
void display_Chargement(void) {
	if (DISPLAYCHARGHES == 1)
	{
			for (int i = 0; i < 2; i++) {
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, hestiam_width, hestiam_height, (uint8_t *)hestiam_bits);
		} while (u8g2_NextPage(&u8g2));
		HAL_Delay(50);
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, hestiam1_width, hestiam1_height, (uint8_t *)hestiam1_bits);
		} while (u8g2_NextPage(&u8g2));
		HAL_Delay(50);
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, hestiam2_width, hestiam2_height, (uint8_t *)hestiam2_bits);
		} while (u8g2_NextPage(&u8g2));
		HAL_Delay(50);
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, hestiam3_width, hestiam3_height, (uint8_t *)hestiam3_bits);
		} while (u8g2_NextPage(&u8g2));
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, hestiam2_width, hestiam2_height, (uint8_t *)hestiam2_bits);
		} while (u8g2_NextPage(&u8g2));
		HAL_Delay(50);
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, hestiam1_width, hestiam1_height, (uint8_t *)hestiam1_bits);
		} while (u8g2_NextPage(&u8g2));
		HAL_Delay(50);
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, hestiam_width, hestiam_height, (uint8_t *)hestiam_bits);
		} while (u8g2_NextPage(&u8g2));
		HAL_Delay(500);
	}
	}
	else
	{
	for (int i = 0; i < 2; i++) {
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, regaz_width, regaz_height, (uint8_t *)regaz_bits);
		} while (u8g2_NextPage(&u8g2));
		HAL_Delay(50);
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, regaz1_width, regaz1_height, (uint8_t *)regaz1_bits);
		} while (u8g2_NextPage(&u8g2));
		HAL_Delay(50);
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, regaz2_width, regaz2_height, (uint8_t *)regaz2_bits);
		} while (u8g2_NextPage(&u8g2));
		HAL_Delay(50);
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, regaz3_width, regaz3_height, (uint8_t *)regaz3_bits);
		} while (u8g2_NextPage(&u8g2));
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, regaz2_width, regaz2_height, (uint8_t *)regaz2_bits);
		} while (u8g2_NextPage(&u8g2));
		HAL_Delay(50);
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, regaz1_width, regaz1_height, (uint8_t *)regaz1_bits);
		} while (u8g2_NextPage(&u8g2));
		HAL_Delay(50);
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, regaz_width, regaz_height, (uint8_t *)regaz_bits);
		} while (u8g2_NextPage(&u8g2));
		HAL_Delay(500);
	}
}
}


void display_Chargement_perso(void) 
{
	
	char name_start[20] = "HELIOS";
	if (SUEZ == 1)
		strcpy(name_start, "SUEZ");
	if (BOX4GAZ == 1)
		strcpy(name_start, "REGAZ");
	
//	#ifdef debug
//	strcat(name_start, "_debug");
//	#endif
//	
//	#ifdef debug_sound_vibration
//	strcat(name_start, "_debug2");
//	#endif
	
//u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr);	
	u8g2_FirstPage(&u8g2);
	u8g2_SetFont(&u8g2, u8g2_font_7x14_tr);	

	do 
	{
		u8g2_DrawStr(&u8g2, 50, 20, name_start);
		
	}while (u8g2_NextPage(&u8g2));


	//HAL_Delay(3000);
	
//	if (moving == 1)
//	{
//			for (int i = 0; i < 2; i++) 
//		{
//		u8g2_FirstPage(&u8g2);
//		do {
//			u8g2_DrawXBM(&u8g2, 0, 0, hestiam_width, hestiam_height, (uint8_t *)hestiam_bits);
//		} while (u8g2_NextPage(&u8g2));
//		HAL_Delay(50);
//		u8g2_FirstPage(&u8g2);
//		do {
//			u8g2_DrawXBM(&u8g2, 0, 0, hestiam1_width, hestiam1_height, (uint8_t *)hestiam1_bits);
//		} while (u8g2_NextPage(&u8g2));
//		HAL_Delay(50);
//		u8g2_FirstPage(&u8g2);
//		do {
//			u8g2_DrawXBM(&u8g2, 0, 0, hestiam2_width, hestiam2_height, (uint8_t *)hestiam2_bits);
//		} while (u8g2_NextPage(&u8g2));
//		HAL_Delay(50);
//		u8g2_FirstPage(&u8g2);
//		do {
//			u8g2_DrawXBM(&u8g2, 0, 0, hestiam3_width, hestiam3_height, (uint8_t *)hestiam3_bits);
//		} while (u8g2_NextPage(&u8g2));
//		u8g2_FirstPage(&u8g2);
//		do {
//			u8g2_DrawXBM(&u8g2, 0, 0, hestiam2_width, hestiam2_height, (uint8_t *)hestiam2_bits);
//		} while (u8g2_NextPage(&u8g2));
//		HAL_Delay(50);
//		u8g2_FirstPage(&u8g2);
//		do {
//			u8g2_DrawXBM(&u8g2, 0, 0, hestiam1_width, hestiam1_height, (uint8_t *)hestiam1_bits);
//		} while (u8g2_NextPage(&u8g2));
//		HAL_Delay(50);
//		u8g2_FirstPage(&u8g2);
//		do {
//			u8g2_DrawXBM(&u8g2, 0, 0, hestiam_width, hestiam_height, (uint8_t *)hestiam_bits);
//		} while (u8g2_NextPage(&u8g2));
//		HAL_Delay(500);
//		}
//	
//	}
}



void display_AlerteDanger(int TabGen[], uint32_t TabAlertAll[], int type_warning) {

if (	TabGen[TYPE_ALERT] != NONE_ALERT ) 
{
	u8g2_FirstPage(&u8g2);
	do 
	{
		if (type_warning == 0) 
		{
			u8g2_DrawXBM(&u8g2, 5, 0, warning1_width, warning1_height, (uint8_t *)warning1_bits); // blinking warning sign step 1
		}
		else 
		{
			u8g2_DrawXBM(&u8g2, 5, 0, warning2_width, warning2_height, (uint8_t *)warning2_bits);  // blinking warning sign step 2
		}
		
		u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr ); 
		char timerChar[3];
		unsigned int timer = (SIGDURATION * 1000 + 500) -  (HAL_GetTick() - TabAlertAll[ALL_TIM_1]);
		timer = timer / 1000;
		sprintf(timerChar, "%u", timer);
		int posXmes = 45, posYmes = 0;
		
		u8g2_DrawStr(&u8g2, posXmes, 13, "ALERTE");
		u8g2_DrawStr(&u8g2, 80, 25, timerChar);
		
		if (TabGen[TYPE_ALERT] == ALERT_FALL) 
		{
			u8g2_DrawStr(&u8g2, posXmes, 13, "ALERTE CHUTE");
			//u8g2_DrawStr(&u8g2, 100, 13, "CHUTE");
		}
		if (TabGen[TYPE_ALERT] == ALERT_SOS) 
		{
			u8g2_DrawStr(&u8g2, posXmes, 13, "ALERTE SOS");
			//u8g2_DrawStr(&u8g2, 100, 13, "SOS");
		}
		if (TabGen[TYPE_ALERT] == ALERT_MALAISE) 
		{
			u8g2_DrawStr(&u8g2, posXmes, 13, "ALERTE MALAISE");
			//u8g2_DrawStr(&u8g2, 100, 13, "MALAISE");
		}
		if (TabGen[TYPE_ALERT] == ALERT_SONO) 
		{
				u8g2_DrawStr(&u8g2, posXmes, 13, "ALERTE SON");
				//u8g2_DrawStr(&u8g2, 100, 13, "SON");
		}
		if (TabGen[TYPE_ALERT] == ALERT_H2SVME) 
		{
				u8g2_DrawStr(&u8g2, 50, 13, "H2S");
				//u8g2_DrawStr(&u8g2, 100, 30, "VME");
		}
		if (TabGen[TYPE_ALERT] == ALERT_H2SVLCT) 
		{
				u8g2_DrawStr(&u8g2, 50, 13, "H2S");
				u8g2_DrawStr(&u8g2, 100, 30, "VLCT");
		}
		if (TabGen[TYPE_ALERT] == ALERT_O2) 
		{
				u8g2_DrawStr(&u8g2, 50, 13, "MANQUE");
				u8g2_DrawStr(&u8g2, 100, 30, "O2");
		}
		if (TabGen[TYPE_ALERT] == ALERT_COVME) 
		{
				u8g2_DrawStr(&u8g2, 50, 13, "CO");
				u8g2_DrawStr(&u8g2, 100, 30, "VME");
		}
		if (TabGen[TYPE_ALERT] == ALERT_COVLCT) 
		{
					u8g2_DrawStr(&u8g2, 50, 13, "CO");
					u8g2_DrawStr(&u8g2, 100, 30, "VLCT");
		}
		if (TabGen[TYPE_ALERT] == ALERT_EX) 
		{
					u8g2_DrawStr(&u8g2, 50, 13, "RISQUE");
					u8g2_DrawStr(&u8g2, 100, 30, "EX");
		}
	} while (u8g2_NextPage(&u8g2));
}
}



void display_SendMess(void) {
	u8g2_FirstPage(&u8g2);
	do {
		u8g2_DrawXBM(&u8g2, 5, 0, warning1_width, warning1_height, (uint8_t *)warning1_bits);
		u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr );
			u8g2_DrawStr(&u8g2, 50, 13, "ENVOI");
			u8g2_DrawStr(&u8g2, 50, 30, "ALERTE");
	} while (u8g2_NextPage(&u8g2));
}


void display_AlerteGaz(uint8_t gaz, int type_warning) {
}



extern uint8_t Calibration_Time_Over;

/*
* Permet d'afficher une alerte
*/
void display_Alerte(int TabGen[], uint8_t type_alerte) 
{
	u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr);
	char str_display[25];


	if (GPSOK == 1)
	{
		if(show_RSSI == 1)
		{
			if (LORAWANOK == 1 && SIGFOXOK == 1)
			{
				u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr);

				if(TabGen[SIGFOX_RSSI] != 0)
				{
					sprintf(str_display, "SIGFOX OK (%ddB)", TabGen[SIGFOX_RSSI]);
					u8g2_DrawStr(&u8g2, 0, 20, str_display);
				}

				if(TabGen[LORAWAN_RSSI] != 0)
				{
					sprintf(str_display, "LORA   OK (%ddB)", TabGen[LORAWAN_RSSI]);
					u8g2_DrawStr(&u8g2, 0, 30, str_display);
				}

				if(TabGen[LORAWAN_STATE] == LW_JOIN_OK )
				{
					sprintf(str_display, "LORA   OK ");//(%ddB)", TabGen[SIGFOX_RSSI]);
					u8g2_DrawStr(&u8g2, 0, 30, str_display);
				}

				//u8g2_SetFont(&u8g2, u8g2_font_5x8_tr);
				//sprintf(str_display, "position (RSSI%ddB)", TabGen[SIGFOX_RSSI]);
				//u8g2_DrawStr(&u8g2, 1, 8, str_display);
				//u8g2_DrawStr(&u8g2, 0, 30, str_display);
			}
			else
			if(SIGFOXOK == 1)
			{
				u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr);

				u8g2_DrawStr(&u8g2, 0, 20, "Reseau ok a cette");
				char str_display[25];
				//u8g2_SetFont(&u8g2, u8g2_font_5x8_tr);
				sprintf(str_display, "position (RSSI%ddB)", TabGen[SIGFOX_RSSI]);
				//u8g2_DrawStr(&u8g2, 1, 8, str_display);
				u8g2_DrawStr(&u8g2, 0, 30, str_display);
			}

		}
		else if (TabGen[CHARGEC] == 1)
		{
			char str_display[25];
			u8g2_DrawStr(&u8g2, 1, 30, "Alertes desactivees");
			sprintf(str_display, "En charge...");//: %ddB", TabGen[LORAWAN_RSSI]);
			u8g2_DrawStr(&u8g2, 1, 18, str_display);
		}
		else
		{
			if(TabGen[BAT_VALUE] < 15 && TabGen[BAT_VALUE] > 5 && (HAL_GetTick() - TabTimer[TIMER_LOW_BAT]) < 10 * 1000)
			{
				u8g2_DrawStr(&u8g2, 2, 30, "Batterie faible");
			}
			else if(TabGen[BAT_VALUE] < 5  && (HAL_GetTick() - TabTimer[TIMER_LOW_BAT]) < 10 * 1000)
			{
				u8g2_DrawStr(&u8g2, 2, 30, "Batterie tres faible");
			}
			else if (BiGaz_ON == 1)
			{

				if (GAZ_THRESHOLD_ALERT == 1)
					sprintf(str_display, "CO  : %4u ppm - GAZ!", gaz1_ppm);
				else
		#ifdef debug_sound_vibration
					sprintf(str_display, "CO  : %4u ppm %4u", gaz1_ppm, gaz1_level_mean);
		#endif
		#ifndef debug_sound_vibration
				if(Calibration_Time_Over == 0)
					sprintf(str_display, "CO  : calibration", gaz1_ppm);
				else
					sprintf(str_display, "CO  : %4u ppm", gaz1_ppm);
		#endif

				u8g2_DrawStr(&u8g2, 0, 20, str_display);

				if (GAZ_THRESHOLD_ALERT == 2)
					sprintf(str_display, "H2S : %4u ppm - GAZ!", gaz2_ppm);
				else
		#ifdef debug_sound_vibration
					sprintf(str_display, "H2S : %4u ppm %4u", gaz2_ppm, gaz2_level_mean);
		#endif
		#ifndef debug_sound_vibration
				if(Calibration_Time_Over == 0)
					sprintf(str_display, "H2S : calibration", gaz2_ppm);
				else
					sprintf(str_display, "H2S : %4u ppm", gaz2_ppm);
		#endif
				u8g2_DrawStr(&u8g2, 0, 30, str_display);

			}
			else
			{
				if (TabGen[STATUT_GPS] == 1)
					u8g2_DrawStr(&u8g2, 2, 30, "Protection active");

				else if (TabGen[GPS_ON] == 1 || TabGen[FORCE_GPS] == 1 )
					u8g2_DrawStr(&u8g2, 2, 30, "Recherche GPS...");

				else if (	TabGen[GPS_ON] == 0 &&	TabGen[GPS_ON_PREVIOUS] == 0 )
					u8g2_DrawStr(&u8g2, 2, 30, "GPS OFF");
				else
					u8g2_DrawStr(&u8g2, 2, 30, "NONE");
			}
		}
	}
//	else if (SUEZ == 1)
//	{
//		char buff[30] = "";
//
//		sprintf(buff, "Distance: %5d cm", TabGen[DECA1004_DIST]);
//
//		//u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr);
//		u8g2_DrawStr(&u8g2, 2, 32, buff);
//		//u8g2_NextPage(&u8g2);
//
//		//u8g2_DrawStr(&u8g2, 2, 30, "Distance: ");
//	}
	else if(TabGen[STATUS_REP] == 0 && LORAP2POK == 1)
	{
		u8g2_DrawStr(&u8g2, 2, 30, "Pas de repeteur");
	}
	else
	{
		if (TabGen[RSSI_REP] == 666 && LORAP2POK == 1)
		{

			u8g2_DrawStr(&u8g2, 2, 30, "Pas de couverture SF.");
			//display_network_status(0, 70, 0);
		}
		else if(show_RSSI == 1)
		{
			u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr);

			u8g2_DrawStr(&u8g2, 0, 20, "Reseau ok a cette");
			char str_display[25];
			//u8g2_SetFont(&u8g2, u8g2_font_5x8_tr);
			sprintf(str_display, "position (RSSI%ddB)", TabGen[SIGFOX_RSSI]);
			//u8g2_DrawStr(&u8g2, 1, 8, str_display);
			u8g2_DrawStr(&u8g2, 0, 30, str_display);
		}
		else if (TabGen[CHARGEC] == 1)
		{
			u8g2_DrawStr(&u8g2, 2, 30, "Alertes desactivees");
		}
		else if(TabGen[RSSI_REP] != 0 || TabGen[SIGFOX_RSSI] != 0 || TabGen[LORAWAN_RSSI] != 0 )
		{
			u8g2_DrawStr(&u8g2, 2, 30, "Protection active");
			if(TabGen[RSSI_REP] != 0)
				display_network_status(1, 70, 0);
		}
		else
		{
			u8g2_DrawStr(&u8g2, 2, 30, "En attente de reseau");
		}

	}
}



void display_wait(uint8_t step) {
	switch (step) {
	case 1:
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, loading1_width, loading1_height, (uint8_t *)loading1_bits);
			u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr );
			u8g2_DrawStr(&u8g2, 45, 12, "Extinction");
			u8g2_DrawStr(&u8g2, 50, 28, "dans 3 s");
		} while (u8g2_NextPage(&u8g2));
		break;
	case 2:
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, loading2_width, loading2_height, (uint8_t *)loading2_bits);
			u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr );
			u8g2_DrawStr(&u8g2, 45, 12, "Extinction");
			u8g2_DrawStr(&u8g2, 50, 28, "dans 3 s");
		} while (u8g2_NextPage(&u8g2));
		break;

	case 3 :
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, loading3_width, loading3_height, (uint8_t *)loading3_bits);
			u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr );
			u8g2_DrawStr(&u8g2, 45, 12, "Extinction");
			u8g2_DrawStr(&u8g2, 50, 28, "dans 2 s");
		} while (u8g2_NextPage(&u8g2));
		break;
			case 4 :
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, loading4_width, loading4_height, (uint8_t *)loading4_bits);
			u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr );
			u8g2_DrawStr(&u8g2, 45, 12, "Extinction");
			u8g2_DrawStr(&u8g2, 50, 28, "dans 2 s");
		} while (u8g2_NextPage(&u8g2));
		break;

	case 5:
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, loading5_width, loading5_height, (uint8_t *)loading5_bits);
			u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr );
			u8g2_DrawStr(&u8g2, 45, 12, "Extinction");
			u8g2_DrawStr(&u8g2, 50, 28, "dans 1 s");
		} while (u8g2_NextPage(&u8g2));
		break;
		case 6:
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, loading6_width, loading6_height, (uint8_t *)loading6_bits);
			u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr );
			u8g2_DrawStr(&u8g2, 45, 12, "Extinction");
			u8g2_DrawStr(&u8g2, 50, 28, "dans 1 s");
		} while (u8g2_NextPage(&u8g2));
		break;

	case 7:
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, loading7_width, loading7_height, (uint8_t *)loading7_bits);
			u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr );
			u8g2_DrawStr(&u8g2, 40, 20, "Extinction");
		} while (u8g2_NextPage(&u8g2));
		break;
		
	case 8:
		u8g2_FirstPage(&u8g2);
		do {
			u8g2_DrawXBM(&u8g2, 0, 0, loading8_width, loading8_height, (uint8_t *)loading8_bits);
			u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr );
			u8g2_DrawStr(&u8g2, 40, 20, "Extinction");
		} while (u8g2_NextPage(&u8g2));
		break;
	}
}

/*
* Fonction permettant d'afficher un message basique
*/
void display_Print(char *msg) {
	u8g2_FirstPage(&u8g2);
	do {
		u8g2_SetFont(&u8g2, u8g2_font_ncenB14_tr);
		u8g2_DrawStr(&u8g2, 0, 15, msg);
	} while (u8g2_NextPage(&u8g2));
}

/*
* fonction pour u8g2
*/
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
	/* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
	/* add extra byte for the i2c address */
	static uint8_t buffer[34];
	static uint8_t buf_idx;
	uint8_t *data;
	switch (msg)  {
	case U8X8_MSG_BYTE_SEND:
		data = (uint8_t *)arg_ptr;
		while ( arg_int > 0 )
		{
			buffer[buf_idx++] = *data;
			data++;
			arg_int--;
		}
		break;

	case U8X8_MSG_BYTE_INIT:
		/* add your custom code to init i2c subsystem */
		break;

	case U8X8_MSG_BYTE_SET_DC:
		/* ignored for i2c */
		break;

	case U8X8_MSG_BYTE_START_TRANSFER:
		buf_idx = 0;
		break;

	case U8X8_MSG_BYTE_END_TRANSFER:
		HAL_I2C_Master_Transmit(&BIGOLED_I2C_PORT, (0x78), (uint8_t *)buffer, buf_idx, 1000);
		break;

	default:
		return 0;
	}
	return 1;
}

/*
* Fonction pour u8g2
*/
uint8_t u8x8_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr) {
	switch (msg) {
	case U8X8_MSG_GPIO_AND_DELAY_INIT:
		HAL_Delay(1);
		break;

	case U8X8_MSG_DELAY_MILLI:
		HAL_Delay(arg_int);
		break;

	case U8X8_MSG_DELAY_I2C:
		// delayUs(arg_int);
		break;

	case U8X8_MSG_GPIO_I2C_CLOCK:
		// arg_int=0: Output low at I2C clock pin
		// arg_int=1: Input dir with pullup high for I2C clock pin
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, arg_int);
		break;

	case U8X8_MSG_GPIO_I2C_DATA:
		// arg_int=0: Output low at I2C data pin
		// arg_int=1: Input dir with pullup high for I2C data pin
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, arg_int);
		break;

	default:
		u8x8_SetGPIOResult(u8x8, 1);      // default return value
		break;

	}
	return 1;
}

/*
* Fonction permettant d'afficher un image par rapport au niveau sonore
*/
void display_Print_Sound_Level(uint8_t choice) {
	u8g2_ClearDisplay(&u8g2);
	switch (choice) {
	case STAGE1 :
		do {
			u8g2_DrawXBM(&u8g2, 32, 0, stage1_width, stage1_height, (uint8_t *)stage1_bits);
		} while (u8g2_NextPage(&u8g2));
		break;
	case STAGE2:
		do {
			u8g2_DrawXBM(&u8g2, 32, 0, stage2_width, stage2_height, (uint8_t *)stage2_bits);
		} while (u8g2_NextPage(&u8g2));
		break;
	case STAGE3 :
		do {
			u8g2_DrawXBM(&u8g2, 32, 0, stage3_width, stage3_height, (uint8_t *)stage3_bits);
		} while (u8g2_NextPage(&u8g2));
		break;
	case STAGE4 :
		do {
			u8g2_DrawXBM(&u8g2, 32, 0, stage4_width, stage4_height, (uint8_t *)stage4_bits);
		} while (u8g2_NextPage(&u8g2));
		break;
	}
}

/*
* Permet d'afficher un message et effacer l'ecran
*/
void display_Print_UART(char *msg, uint8_t xpos, uint8_t ypos, uint8_t sizePolice) {
	u8g2_FirstPage(&u8g2);
	do {

		// pour les polices -> https://github.com/olikraus/u8g2/wiki/fntlistall
		// prendre uniquement les tr

		switch (sizePolice) {
		case 4:
			u8g2_SetFont(&u8g2, u8g2_font_u8glib_4_tr); // fonctionne
			break;
		case 6:
			u8g2_SetFont(&u8g2, u8g2_font_5x8_tr); // fonctionne
			break;
		case 8:
			u8g2_SetFont(&u8g2, u8g2_font_t0_11_tr); //fonctionne
			break;
		case 10 :
			u8g2_SetFont(&u8g2, u8g2_font_7x14_tr); // fonctionne
			break;
		case 12 :
			u8g2_SetFont(&u8g2, u8g2_font_helvB12_tr ); // fonctionne
			break;
		case 14 :
			u8g2_SetFont(&u8g2, u8g2_font_helvB14_tr ); // fonctionne
			break;
		case 16:
			u8g2_SetFont(&u8g2, u8g2_font_crox5t_tr);
			break;
		default :
			u8g2_SetFont(&u8g2, u8g2_font_ncenB14_tr);
			break;
		}
		u8g2_DrawStr(&u8g2, xpos, ypos, msg);
	} while (u8g2_NextPage(&u8g2));
	HAL_Delay(1000);
}

/*
* Permet d'afficher le niveau de batterie
*/
void display_BatteryLvl(uint8_t lvl, uint8_t posXmes, uint8_t posYmes)
{

	if ( lvl <= 10) 
	{
		u8g2_DrawXBM(&u8g2, posXmes, 0, bat_0_width, bat_0_height, (uint8_t *)bat_0_bits);
	}
	else
	if (lvl > 10 && lvl < 30) 
	{
		u8g2_DrawXBM(&u8g2, posXmes, 0, bat_20_width, bat_20_height, (uint8_t *)bat_20_bits);
	}
	else
	if ( lvl >= 30 && lvl < 50) 
	{
		u8g2_DrawXBM(&u8g2, posXmes, 0, bat_40_width, bat_40_height, (uint8_t *)bat_40_bits);
	}
	else
	if (lvl >= 50 && lvl < 70) 
	{
		u8g2_DrawXBM(&u8g2, posXmes, 0, bat_60_width, bat_60_height, (uint8_t *)bat_60_bits);
	}
	else
	if (lvl >= 70 && lvl < 90) {
		u8g2_DrawXBM(&u8g2, posXmes, 0, bat_80_width, bat_80_height, (uint8_t *)bat_80_bits);
	}
	else
	if (lvl >= 90 && lvl <= 100)
	{
		
		u8g2_DrawXBM(&u8g2, posXmes, 0, bat_100_width, bat_100_height, (uint8_t *)bat_100_bits);
	}
	else
	{
		u8g2_DrawXBM(&u8g2, posXmes, 0, BattertyError_width, BattertyError_height, (uint8_t *)BattertyError_bits);
	}
}
