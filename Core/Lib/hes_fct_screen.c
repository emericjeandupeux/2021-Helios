#include "hes_fct_screen.h"

void initScreen() {

	  for (int ii = 0; ii < 115; ii=ii+2) {
    ssd1306_Fill(Black);
    ssd1306_SetCursor(115 - ii, 7);
    //ssd1306_WriteString("[Hestiam]", Font_11x18, White);
		ssd1306_WriteString("[Enedis]", Font_11x18, White);
    ssd1306_UpdateScreen();
    //HAL_Delay(1);
		}

	 HAL_Delay(200);
	

  HAL_Delay(100);
  ssd1306_Fill(Black);
  ssd1306_SetCursor(0, 12);
  ssd1306_WriteString(" Helios Fir. v10.5", Font_7x10, White);
  ssd1306_UpdateScreen();
  HAL_Delay(200);

	ssd1306_Fill(Black);
  ssd1306_SetCursor(0, 12);
  ssd1306_WriteString(" Initialisation ", Font_7x10, White);
  ssd1306_UpdateScreen();	
		
}
 
void ScreenMessExt3s(void)
{
	char lcd_buf1[25];
	
			if (BOX4GAZ == 0)
		{
			ssd1306_On();
			ssd1306_Init();
			sprintf(lcd_buf1, "  Extinction 3s ");
			ssd1306_Fill(Black);
			ssd1306_SetCursor(0, 5);
			ssd1306_WriteString(lcd_buf1, Font_7x10, White);
			ssd1306_UpdateScreen();
		}
		else
		{
			uart_sendCommandExtinction(ON);
		}
}

void ScreenMessExt2s(void)
{
	char lcd_buf1[25];
	
				if (BOX4GAZ == 0)
			{
				sprintf(lcd_buf1, "  Extinction 2s ");
				ssd1306_Fill(Black);
				ssd1306_SetCursor(0, 5);
				ssd1306_WriteString(lcd_buf1, Font_7x10, White);
				ssd1306_UpdateScreen();
			}
			else
			{
     uart_sendCommandExtinction(ON);
			}
}

void ScreenMessExt1s(void)
{
	char lcd_buf1[25];
	
		if (BOX4GAZ == 0)
			{
				sprintf(lcd_buf1, "  Extinction 1s ");
				ssd1306_Fill(Black);
				ssd1306_SetCursor(0, 5);
				ssd1306_WriteString(lcd_buf1, Font_7x10, White);
				ssd1306_UpdateScreen();
			}
			else
			{
      uart_sendCommandExtinction(ON);
			}
}

void ScreenMessExtOnly(void)
{
	char lcd_buf1[25];
	
		if (BOX4GAZ == 0)
			{
				sprintf(lcd_buf1, "    Extinction ");
				ssd1306_Fill(Black);
				ssd1306_SetCursor(0, 5);
				ssd1306_WriteString(lcd_buf1, Font_7x10, White);
				ssd1306_UpdateScreen();
			}
			else
			{
      uart_sendCommandExtinction(ON);
			}
}

void ScreenMessEmpty(void)
{
	char lcd_buf1[25];
	
			if (BOX4GAZ == 0)
			{
				sprintf(lcd_buf1, "  ");
				ssd1306_Fill(Black);
				ssd1306_SetCursor(0, 5);
				ssd1306_WriteString(lcd_buf1, Font_7x10, White);
				ssd1306_UpdateScreen();
			}
			else
			{
//				sprintf(lcd_buf1, "  ");
//				uart_sendCommandDisplay(xpos, ypos, police,"  ", sizeof("  ") ) ;

			}
		}

		
		void AdcCompute(float tab_ADC [])
		{
			
			float valueEx,ValueO2,ValueCO,ValueH2S,ValueSono ;
			float GoodValueEx,GoodValueO2,GoodValueCO,GoodValueH2S,GoodValueSono ; 
			
			float sensibilite_ADC,sensibilite_EX,sensibilite_O2,sensibilite_CO,sensibilite_H2S,sensibilite_SONOMETRE ;
			
			float gain_EX,gain_O2,gain_CO,gain_H2S,gain_SONOMETRE;
			
			float p0 ;
				
			sensibilite_ADC = 3.3 / pow(2,12);
	
				sensibilite_EX = 12 *pow(10,-3); // en mV/% de methane 
	sensibilite_EX = sensibilite_EX * 10000; // en mV/ppm
	gain_EX = 1;
			
				sensibilite_O2 = 1;
	gain_O2 = 20;
			
				sensibilite_CO = 55* pow(10,-9);
	gain_CO = 82 * pow(10,4);
	
	sensibilite_H2S = 50 * pow(10,-9);
	gain_H2S = 43 * pow(10,4);
			
			
	p0 = 20; // 20µPa
	sensibilite_SONOMETRE = pow(10,-40/20); // sensiilite en V/Pa 0,01V/Pa soit 10mV/Pa
	sensibilite_SONOMETRE = sensibilite_SONOMETRE * pow(10,-6); // 0.01mV/µPA
			
			
			valueEx = (float) tab_ADC_value[CHANNEL_EX] ; 
			ValueO2 = (float)tab_ADC_value[CHANNEL_O2] ; 
			ValueCO = (float)tab_ADC_value[CHANNEL_CO] ; 
			ValueH2S = (float)tab_ADC_value[CHANNEL_H2S] ; 
			ValueSono = (float)tab_ADC_value[CHANNEL_SONOMETRE] ; 
			
			// Ex
			GoodValueEx = (((sensibilite_ADC * valueEx) - (2.85/2)) / gain_EX) * 1000; // en mV
			if ( GoodValueEx < 0){
		GoodValueEx = 0;
	}
			GoodValueEx = GoodValueEx/ sensibilite_EX; 	
	
	// O2
	GoodValueO2 = (sensibilite_ADC * ValueO2) / gain_O2;

		// CO
	GoodValueCO = (sensibilite_ADC * ValueCO) / gain_CO;
	
		// H2S
	GoodValueH2S = (sensibilite_ADC * ValueH2S) / gain_H2S;
	
			// Sono
	GoodValueSono = ((sensibilite_ADC * ValueSono) / gain_SONOMETRE) * 1000; // en mV
	GoodValueSono = GoodValueSono/sensibilite_SONOMETRE; // en uPa
	GoodValueSono =  20*log10(GoodValueSono/p0); // en dB
	
	
	tab_ADC[CHANNEL_EX] = GoodValueEx;
	tab_ADC[CHANNEL_O2] = GoodValueO2;
	tab_ADC[CHANNEL_CO] = GoodValueCO;
	tab_ADC[CHANNEL_H2S] = GoodValueH2S;
	tab_ADC[CHANNEL_SONOMETRE] = GoodValueSono;
	
}	
	

void	ComputeAlerteGaz(int TabAlert[],float TabFloatValue[])
{
if (TabFloatValue[H2S_VALUE]<TabFloatValue[TH_H2SVME]) { TabAlert[ALERT_H2SVME] = 0 ; TabAlert[ALERT_H2SVLCT] = 0 ; }
else if (TabFloatValue[H2S_VALUE]>TabFloatValue[TH_H2SVLCT]) { TabAlert[ALERT_H2SVME] = 0 ; TabAlert[ALERT_H2SVLCT] = 1 ; }	
else { TabAlert[ALERT_H2SVME] = 1 ; TabAlert[ALERT_H2SVLCT] = 0 ; }	

if (TabFloatValue[CO_VALUE]<TabFloatValue[TH_COVME]) { TabAlert[ALERT_COVME] = 0 ; TabAlert[ALERT_COVLCT] = 0 ; }
else if (TabFloatValue[CO_VALUE]>TabFloatValue[TH_COVLCT]) { TabAlert[ALERT_COVME] = 0 ; TabAlert[ALERT_COVLCT] = 1 ; }	
else { TabAlert[ALERT_COVME] = 1 ; TabAlert[ALERT_COVLCT] = 0 ; }	

if (TabFloatValue[O2_VALUE]<TabFloatValue[TH_O2]) { TabAlert[ALERT_O2] = 1;  }
else { TabAlert[ALERT_O2] = 0;  }	

if (TabFloatValue[EX_VALUE]>TabFloatValue[TH_EX]) { TabAlert[ALERT_EX] = 1;  }
else { TabAlert[ALERT_EX] = 0;  }	

}


void ComputeAdc(float TabFloatValue[],float O2Adc,float COadc,float ExAdc,float H2SAdc,float DBAdc,uint32_t TabAlertAll[],int TabGen[])
{
			
		float ValueSono ;
		float GoodValueSono ; 
		float sensibilite_ADC,sensibilite_SONOMETRE ;
		float gain_SONOMETRE;
		float p0 ;
				
	
	

float O2_msr_0  ;
float O2_msr_1  ;
float O2_aff_0  ;
float O2_aff_1  ;	

float CO_msr_0  ;	
float CO_msr_1  ;	
float CO_aff_0  ;	
float CO_aff_1  ;			
	
float EX_msr_0  ;	
float EX_msr_1  ;	
float EX_aff_0  ;	
float EX_aff_1  ;			
	
float H2S_msr_0  ;	
float H2S_msr_1  ;	
float H2S_aff_0  ;	
float H2S_aff_1  ;		
	
	
if (TabGen[BOXNUMBER] == 3) {
	  // R3
		 O2_msr_0 = 20.9 ;
		 O2_msr_1 = 18 ;
		 O2_aff_0 = 43 ;
		 O2_aff_1 = 22 ;	

		 CO_msr_0 = 0 ;
		 CO_msr_1 = 50 ;
		 CO_aff_0 = 0 ;
		 CO_aff_1 = 302 ;		
		
		 EX_msr_0 = 0 ;
		 EX_msr_1 = 2.2 ;
		 EX_aff_0 = 1776 ;
		 EX_aff_1 = 1781 ;		
		
		 H2S_msr_0 = 0 ;
		 H2S_msr_1 = 10 ;
		 H2S_aff_0 = 0 ;
		 H2S_aff_1 = 307 ;		
}	

if (TabGen[BOXNUMBER] == 1) {
		// R1	
		 O2_msr_0 = 21 ;
		 O2_msr_1 = 18 ;
		 O2_aff_0 = 105 ;
		 O2_aff_1 = 86 ;	

		 CO_msr_0 = 0 ;
		 CO_msr_1 = 50 ;
		 CO_aff_0 = 0 ;
		 CO_aff_1 = 315 ;		
		
		 EX_msr_0 = 0 ;
		 EX_msr_1 = 2.2 ;
		 EX_aff_0 = 1706 ;
		 EX_aff_1 = 1720 ;		
		
		 H2S_msr_0 = 0 ;
		 H2S_msr_1 = 10 ;
		 H2S_aff_0 = 0 ;
		 H2S_aff_1 = 245 ;	
}

if (TabGen[BOXNUMBER] == 2) {
		//R2
				 O2_msr_0 = 21 ;
		 O2_msr_1 = 18 ;
		 O2_aff_0 = 57 ;
		 O2_aff_1 = 46 ;	

		 CO_msr_0 = 0 ;
		 CO_msr_1 = 50 ;
		 CO_aff_0 = 0 ;
		 CO_aff_1 = 312 ;		
		
		 EX_msr_0 = 0 ;
		 EX_msr_1 = 2.2 ;
		 EX_aff_0 = 1733 ;
		 EX_aff_1 = 1750 ;		
		
		 H2S_msr_0 = 0 ;
		 H2S_msr_1 = 10 ;
		 H2S_aff_0 = 0 ;
		 H2S_aff_1 = 220 ;	
}
if (TabGen[BOXNUMBER] == 4) {
		//R4
				 O2_msr_0 = 21 ;
		 O2_msr_1 = 18 ;
		 O2_aff_0 = 91 ;
		 O2_aff_1 = 71 ;	

		 CO_msr_0 = 0 ;
		 CO_msr_1 = 50 ;
		 CO_aff_0 = 0 ;
		 CO_aff_1 = 275 ;		
		
		 EX_msr_0 = 0 ;
		 EX_msr_1 = 2.2 ;
		 EX_aff_0 = 1780 ;
		 EX_aff_1 = 1790 ;		
		
		 H2S_msr_0 = 0 ;
		 H2S_msr_1 = 10 ;
		 H2S_aff_0 = 0 ;
		 H2S_aff_1 = 222 ;	
}
if (TabGen[BOXNUMBER] == 5) {
		//R5
				 O2_msr_0 = 21 ;
		 O2_msr_1 = 18 ;
		 O2_aff_0 = 101 ;
		 O2_aff_1 = 82 ;	

		 CO_msr_0 = 0 ;
		 CO_msr_1 = 50 ;
		 CO_aff_0 = 0 ;
		 CO_aff_1 = 285 ;		
		
		 EX_msr_0 = 0 ;
		 EX_msr_1 = 2.2 ;
		 EX_aff_0 = 1735 ;
		 EX_aff_1 = 1755 ;		
		
		 H2S_msr_0 = 0 ;
		 H2S_msr_1 = 10 ;
		 H2S_aff_0 = 0 ;
		 H2S_aff_1 = 218 ;	
}
		


    if ((HAL_GetTick() - TabAlertAll[ALL_TIM_3] ) > NB_MS_REALERTGAZ)

{
    if (O2Adc == 0){O2Adc=51;}

    TabFloatValue[O2_A] = (O2_msr_1-O2_msr_0)/(O2_aff_1-O2_aff_0);
		TabFloatValue[O2_B] = O2_msr_1-TabFloatValue[O2_A]*O2_aff_1;

    TabFloatValue[CO_A] = (CO_msr_1-CO_msr_0)/(CO_aff_1-CO_aff_0);
		TabFloatValue[CO_B] = CO_msr_1-TabFloatValue[CO_A]*CO_aff_1;
		
		TabFloatValue[EX_A] = (EX_msr_1-EX_msr_0)/(EX_aff_1-EX_aff_0);
		TabFloatValue[EX_B] = EX_msr_1-TabFloatValue[EX_A]*EX_aff_1;
		
		TabFloatValue[H2S_A] = (H2S_msr_1-H2S_msr_0)/(H2S_aff_1-H2S_aff_0);
		TabFloatValue[H2S_B] = H2S_msr_1-TabFloatValue[H2S_A]*H2S_aff_1;

		
		TabFloatValue[O2_VALUE] = O2Adc*TabFloatValue[O2_A]+TabFloatValue[O2_B];
		TabFloatValue[CO_VALUE] = COadc*TabFloatValue[CO_A]+TabFloatValue[CO_B];
		TabFloatValue[EX_VALUE] = ExAdc*TabFloatValue[EX_A]+TabFloatValue[EX_B];
		TabFloatValue[H2S_VALUE] = H2SAdc*TabFloatValue[H2S_A]+TabFloatValue[H2S_B];
		
		if (TabFloatValue[O2_VALUE]<0) { TabFloatValue[O2_VALUE] = 0;}
		if (TabFloatValue[CO_VALUE]<0) { TabFloatValue[CO_VALUE] = 0;}
		if (TabFloatValue[EX_VALUE]<2) { TabFloatValue[EX_VALUE] = 0;}
		if (TabFloatValue[H2S_VALUE]<0) { TabFloatValue[H2S_VALUE] = 0;}
		
		
		ValueSono = DBAdc ; 
		
		sensibilite_ADC = 3.3 / pow(2,12);
			p0 = 20; // 20µPa
	sensibilite_SONOMETRE = pow(10,-40/20); // sensiilite en V/Pa 0,01V/Pa soit 10mV/Pa
	sensibilite_SONOMETRE = sensibilite_SONOMETRE * pow(10,-6); // 0.01mV/µPA
	gain_SONOMETRE = 1 ;
			// Sono
	GoodValueSono = ((sensibilite_ADC * ValueSono) / gain_SONOMETRE) * 1000; // en mV
	GoodValueSono = GoodValueSono/sensibilite_SONOMETRE; // en uPa
	GoodValueSono =  20*log10(GoodValueSono/p0); // en dB
	
	TabFloatValue[DB_VALUE] = DBAdc ;//GoodValueSono;
	}
}



void ComputeAdcH2S(float TabFloatValue[],float H2SAdc,uint32_t TabAlertAll[],int TabGen[])
{
			
float H2S_msr_0  ;	
float H2S_msr_1  ;	
float H2S_aff_0  ;	
float H2S_aff_1  ;		
	
	
if (TabGen[BOXNUMBER] == 3) 
{
	  // R3

		
		 H2S_msr_0 = 0 ;
		 H2S_msr_1 = 10 ;
		 H2S_aff_0 = 0 ;
		 H2S_aff_1 = 307 ;		
}	

if (TabGen[BOXNUMBER] == 1) 
{
		// R1	

		
		 H2S_msr_0 = 0 ;
		 H2S_msr_1 = 10 ;
		 H2S_aff_0 = 0 ;
		 H2S_aff_1 = 245 ;	
}

if (TabGen[BOXNUMBER] == 2) 
{
		//R2

		 H2S_msr_0 = 0 ;
		 H2S_msr_1 = 10 ;
		 H2S_aff_0 = 0 ;
		 H2S_aff_1 = 220 ;	
}
if (TabGen[BOXNUMBER] == 4) 
{
		//R4
		
		 H2S_msr_0 = 0 ;
		 H2S_msr_1 = 10 ;
		 H2S_aff_0 = 0 ;
		 H2S_aff_1 = 222 ;	
}
if (TabGen[BOXNUMBER] == 5) 
{
		//R5
		
		 H2S_msr_0 = 0 ;
		 H2S_msr_1 = 10 ;
		 H2S_aff_0 = 0 ;
		 H2S_aff_1 = 218 ;	
}
		


	if ((HAL_GetTick() - TabAlertAll[ALL_TIM_3] ) > NB_MS_REALERTGAZ)
	{
		TabFloatValue[H2S_A] = (H2S_msr_1-H2S_msr_0)/(H2S_aff_1-H2S_aff_0);
		TabFloatValue[H2S_B] = H2S_msr_1-TabFloatValue[H2S_A]*H2S_aff_1;

		TabFloatValue[H2S_VALUE] = H2SAdc*TabFloatValue[H2S_A]+TabFloatValue[H2S_B];
		
		if (TabFloatValue[H2S_VALUE] < 0) 
		{
		TabFloatValue[H2S_VALUE] = 0;
		}

	}
}



//		
//void MessSos(char lcd_buf1[])
//{
//		if (REGAZ == 0 )
//			{
//				sprintf(lcd_buf1, " ! Alerte SOS ! ");
//			}
//			else
//			{
//				while (ReadyGirl == 0) {};
//				uart_commandAlerte(SOS);
//				while (ReadyGirl == 0) {};
//				uart_sendCommandBlink(10, 100, ON);
//			}
//}

//void MessFall(char lcd_buf1[])
//	{
//	if (REGAZ == 0 )
//			{
//				
//				sprintf(lcd_buf1, " ! Alerte chute !  ");
//			}
//			else
//			{
//				while (ReadyGirl == 0) {};
//				uart_commandAlerte(CHUTE);
//			}
//}

//void MessMalaise(char lcd_buf1[])
//	{
//		if (REGAZ == 0 )
//			{
//				sprintf(lcd_buf1, " !Alerte malaise! ")	;
//			}
//			else
//			{
//				while (ReadyGirl == 0) {};
//				uart_commandAlerte(MALAISE);
//			}
//}

//void MessGaz(char lcd_buf1[])
//	{
//		if (REGAZ == 0 )
//			{
//				sprintf(lcd_buf1, " !Alerte malaise! ")	;
//			}
//			else
//			{
//				while (ReadyGirl == 0) {};
//				uart_commandAlerte(GAZ);
//			}
//}

//void MessSono(char lcd_buf1[]) 
//{
//	//
//}


//	

//		
//		
//		
//		
//		

//		/*			if (*h2sAlerte==1)
//		{
//		sprintf(lcd_buf1, " ! Alerte H2S ! ")	;
//		}

//						if (*COAlerte==1)
//		{
//		sprintf(lcd_buf1, " ! Alerte CO ! ")	;
//		}
//		*/

//		if (*sosLength > 2000)
//		{
//			*sos = 1 ;
		
		
		
