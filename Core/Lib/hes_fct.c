#include "hes_fct.h"

extern struct config_data c1;

void LedChargeIndic(int TabGen[])
{
	int bmsEOC = 0;
	int bmsCharge = 0;
	int percent = 1;

	chargerRead(&bmsEOC, &bmsCharge, TabGen);
	ReadBat(&percent, 1, 1, TabGen);

	if (percent == 0xFF)
	{
		LedOn(0, 0, 100, TabGen);
	}
	else if (((bmsCharge == 1) || (bmsEOC == 1)) && (percent < 100))
	{
		if (BOX4GAZ == 0)
		{
			LedOn(50, 0, 0, TabGen);
		}
		else
		{
			LedOn(250, 0, 0, TabGen);
		}

	}
	else if (((bmsCharge == 1) || (bmsEOC == 1)) && (percent == 100))
	{
		if (BOX4GAZ == 0)
		{
			//LedOn(0, 50, 0, TabGen);
			LedOn(0, 0, 0, TabGen);
		}
		else
		{
			LedOn(0, 250, 0, TabGen);
		}
	}
	else if ((bmsCharge == 0) && (bmsEOC == 0))
	{
		LedOn(0, 0, 0, TabGen);
	}

//	while ((bmsCharge == 1) || (bmsEOC == 1)) {chargerRead(&bmsEOC, &bmsCharge); HAL_Delay(3000);};
//	
//	
//	if ((bmsCharge == 0) &&	(bmsEOC == 0)) {		LedOn(0, 0, 0);
//	}
}

void CopyTabChar(uint8_t inTab1[], uint8_t outTab[], int size)
{
	for (int i_tab = 0; i_tab < size; i_tab++)
	{
		outTab[i_tab] = inTab1[i_tab];
	}
}

//void SearchChar(uint8_t inTab1[], uint8_t inSearchTab[],int outTabInv[], int sizeS, int size) {
//	
//	int maxInd = 30 ;
//	
//	int okS = 0 ;
//	int indTabind = 0 ;
//	int outTabInt[30]  ;
//	int i_tab_fct = 0;
//	int stop = 1 ;
//	int i_tab_ind = 0 ;

//	int indMax = 9999 ;
//	
//	int *val ;
//	
//	sizeS = sizeS-1;
//	
//	for (int i_tab = 0; i_tab < maxInd; i_tab++)
//	{
//		outTabInv[i_tab] = -1;
//	}

//	
//	

//	for (int i_tab = 0; i_tab < (size - sizeS); i_tab++)
//	{ 
//		okS = 0 ; 
//		for (int i_tabS = 0; i_tabS < sizeS; i_tabS++)
//		{
//			if (inTab1[i_tab + i_tabS] == inSearchTab[i_tabS])
//			{
//				okS++;
//			}
//		}
//		if (okS == (sizeS))
//			{
//				outTabInv[indTabind] = i_tab ;
//				indTabind++;
//				if (indTabind > maxInd)
//				{
//					indTabind == maxInd ; 
//					
//					
//				}
//			}
//	}

//	
//for(uint16_t i_tab = 0; i_tab < maxInd; i_tab++)
//	{
//		if (outTabInv[i_tab] > 0)
//		{
//			indMax = i_tab ; 
//		}
//	}
//		
//	
//if 	(indMax<9999)
//{
//	
//			for (int i_tab = 0; i_tab < maxInd; i_tab++)
//	{
//		outTabInt[i_tab] = outTabInv[i_tab];
//	}
//	
//	for(int i_tab = indMax; i_tab >=0; i_tab--)
//	{
//		outTabInv[i_tab_ind] = outTabInt[i_tab];
//		i_tab_ind++;
//	}
//}	
//	
//	
//}

void TaskAlertAcc(float angle, float accres2, int TabAlert[], int TabGen[],
		float seuil)
{
	// malaise

	if (c1.Verti_Actif == 1)
	{
		if ((angle < seuil) && (TabAlert[ALERT_MALAISE] == 0)
				&& (TabGen[FALL_UP_DELAY] == 0) && (TabAlert[ALERT_FALL] == 0))
		{
			TabGen[NS_MALAISE]++;
			if (TabGen[NS_MALAISE] >= TabGen[NMAXS_MALAISE])
			{
				TabAlert[ALERT_MALAISE] = 1;
				TabGen[NS_MALAISE] = 0;
			}
		}
		else
		{
			TabGen[NS_MALAISE] = 0;
		}
	}

	// immo

	if (c1.Immo_Actif == 1)
	{
		if (((accres2 < 1.2) && (accres2 > 0.8)) && (TabAlert[ALERT_MALAISE] == 0)
				&& (TabGen[FALL_UP_DELAY] == 0) && (TabAlert[ALERT_FALL] == 0))
		{
			TabGen[NS_IMMO]++;
			if (TabGen[NS_IMMO] >= TabGen[NMAXS_IMMO])
			{
				TabAlert[ALERT_MALAISE] = 1;
				TabGen[NS_IMMO] = 0;
			}
		}
		else
		{
			TabGen[NS_IMMO] = 0;
		}
	}

	//fall

	if (c1.chute_Actif == 1)
	{
		if ((angle < seuil) && (TabGen[FALL_DELAY] == 1)
				&& (TabAlert[ALERT_MALAISE] == 0)
				&& (TabAlert[ALERT_FALL] == 0))
		{
			TabGen[NS_FALL]++;
			if (TabGen[NS_FALL] >= TabGen[NMAXS_FALL])
			{
				TabGen[FALL_UP_DELAY] = 1;
			}

		}
		else
		{
			TabGen[FALL_UP_DELAY] = 0;
			TabGen[NS_FALL] = 0;
		}
	}
}

unsigned char bootloader(unsigned char tps_appui)
{
	while (tps_appui > 0)
	{
		if (InSOS() == 1)
		{
			vibration_LBL(1, 250, 1000);
			tps_appui--;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

extern uint8_t nb_parametre;
extern struct config_data c_default;
void default_value(void)
{
	uint8_t curent_conf[nb_parametre];
	uint8_t count2 = 0;
	ee_init();
	ee_read(0, sizeof(curent_conf), curent_conf);
	for (int i = 0; i <= sizeof(curent_conf); i++)
	{
		if (curent_conf[i] == 255)
		{
			count2++;
		}
	}
	if (count2 > 0)
	{
		c_default.tps_immo = 15;	//default value OK
		c_default.tps_PerteDeVerticalite = 10;	//default value OK
		c_default.tps_GPS_ON = 1;	//default value OK
		c_default.tps_GPS_OFF = 1;	//default value OK
		c_default.tps_Alarme = 30;	//default value OK
		c_default.chute_Actif = 1;	//default value OK
		c_default.loraP2P = 0;		//default value OK
		c_default.com_sigfox = 1;	//default value OK
		c_default.com_LoRa = 0; 	//default value OK
		c_default.GPS_Actif = 1;	//default value OK
		c_default.Immo_Actif = 1;	//default value OK
		c_default.Verti_Actif = 1;	//default value OK
		c_default.Sensibilite_chute = 0;
		c_default.tps_chute = 20;	//default value OK
		c_default.Angle = 15;
		c_default.colision_Actif = 0;
		c_default.biGaz = 0;
		uint8_t data2[] =
		{ c_default.tps_immo, c_default.tps_PerteDeVerticalite,
				c_default.tps_GPS_ON, c_default.tps_GPS_OFF,
				c_default.tps_Alarme, c_default.chute_Actif, c_default.loraP2P,
				c_default.com_sigfox, c_default.com_LoRa, c_default.GPS_Actif,
				c_default.Immo_Actif, c_default.Verti_Actif,
				c_default.Sensibilite_chute, c_default.tps_chute,
				c_default.Angle, c_default.colision_Actif, c_default.biGaz };
		ee_writeToRam(0, sizeof(data2), data2);
		ee_commit();
		vibration_LBL(2, 200, 400);
	}
}

extern uint8_t nb_flash[3];
void Load_configuration_value(void)
{
	uint8_t curent_conf2[nb_parametre];
	ee_read(0, sizeof(curent_conf2), curent_conf2);
	c1.tps_immo = curent_conf2[0];
	c1.tps_PerteDeVerticalite = curent_conf2[1];
	c1.tps_GPS_ON = curent_conf2[2];
	c1.tps_GPS_OFF = curent_conf2[3];
	c1.tps_Alarme = curent_conf2[4];
	c1.chute_Actif = curent_conf2[5];
	c1.loraP2P = curent_conf2[6];
	c1.com_sigfox = curent_conf2[7];
	c1.com_LoRa = curent_conf2[8];
	c1.GPS_Actif = curent_conf2[9];
	c1.Immo_Actif = curent_conf2[10];
	c1.Verti_Actif = curent_conf2[11];
	c1.Sensibilite_chute = curent_conf2[12];
	c1.tps_chute = curent_conf2[13];
	c1.Angle = curent_conf2[14];
	c1.colision_Actif = curent_conf2[15];
	c1.biGaz = curent_conf2[16];
}

extern unsigned char ID_Sigfox[8];
extern uint8_t Rx_Nemeus[200];
void Load_ID_Sigfox(unsigned char Ask_ID_Sigfox)
{
	if (Ask_ID_Sigfox == 1)
	{
		unsigned char i = 0;
		unsigned char count_virgule = 0;
		unsigned char len = sizeof(Rx_Nemeus);
		while (i < len)
		{
			if ((Rx_Nemeus[i] == 'N') && (Rx_Nemeus[i + 4] == 'S')
					&& (Rx_Nemeus[i + 8] == 'L'))
			{
				i = 0;
				while (i < len)
				{
					if ((Rx_Nemeus[i] == ',') && (count_virgule == 2))
					{
						for (int j = 0; j < 9; j++)
						{
							ID_Sigfox[j] = Rx_Nemeus[i + j + 1];
						}
						i = 210;
					}
					else if ((Rx_Nemeus[i] == ',') && (count_virgule != 2))
					{
						count_virgule++;
						i++;
					}
					else
						i++;
				}
			}
			else
				i++;
		}
		int value;
		char *endPtr;
		value = strtol(ID_Sigfox, &endPtr, 16);
		sprintf(ID_Sigfox, "%08X", value);
		ee_writeToRam(96, sizeof(ID_Sigfox), ID_Sigfox);
		ee_commit();
	}
	else
	{
		ee_read(96, sizeof(ID_Sigfox), ID_Sigfox);
	}
}

extern int TabGen[NB_GEN];
extern uint8_t DMA_Done;
unsigned char AskSigFox_ID(void)
{
	uint8_t curent_ID[sizeof(ID_Sigfox)];
	uint8_t count3 = 0;
	ee_read(96, sizeof(curent_ID), curent_ID);
	for (int i = 0; i <= sizeof(curent_ID); i++)
	{
		if ((curent_ID[i] == 255)
				|| ((curent_ID[i] == '0') && (curent_ID[i + 1] == '0')
						&& (curent_ID[i + 2] == '0')
						&& (curent_ID[i + 3] == '0')))
		{
			count3++;
		}
	}
	if (count3 > 0)
	{
		WakeUpNemeus_forID();
		SendIdAskSF();
		HAL_Delay(300);
		return 1;
	}
	else
	{
		return 0;
	}
}

float config_seuil(void)
{
	uint8_t sensibility = c1.Sensibilite_chute;
	if (sensibility == 0)
	{
		return 25; //Par défaut
	}
	if (sensibility != 0)
	{
		if (sensibility == 1)
		{
			return 20;	//corresponds à un Angle
		}
		if (sensibility == 2)
		{
			return 25;
		}
		if (sensibility == 3)
		{
			return 30;
		}
	}
}
