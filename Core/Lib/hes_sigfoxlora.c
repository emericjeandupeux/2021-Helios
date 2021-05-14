
#include "hes_sigfoxlora.h"


extern uint8_t count_nb_join;

//##############################################################
// Nemeus module 
//##############################################################

void WakeUpNemeusLS(void) 
{
	OutLoraWu(1);
	HAL_Delay(3);
	OutLoraWu(0);
}

extern uint8_t DUAL_STATE_LS;

void RebootNemeusLS(int TabGen[]) 
{
		//SendMess("\n", NEMEUS_UART_PORT);
		SendMess("AT+GA=DIND,1,8401\n", NEMEUS_UART_PORT);
		//SendMess("AT+SF=?\n");
		//SendMess("AT+MAC=RDEVUID\n"); // DevEui
		//SendMess("AT+MAC=RAPPUID\n"); //AppEui
		//SendMess("AT+MAC=RAPPKEY\n", NEMEUS_UART_PORT); //AppKey
		HAL_Delay(2000);


}

void TurnOffAllLayers(void)
{
	SendMess("AT+RFTX=?\n", NEMEUS_UART_PORT); // Lora reception stop
	HAL_Delay(100);
	SendMess("AT+RFRX=STOP\n", NEMEUS_UART_PORT); // Lora reception stop
	HAL_Delay(100);
	SendMess("AT+SF=OFF\n", NEMEUS_UART_PORT); // Sigfox stop
	HAL_Delay(100);
	SendMess("AT+MAC=OFF\n", NEMEUS_UART_PORT); // LoraWan layer off
	HAL_Delay(100);
	SendMess("AT+RF=OFF\n", NEMEUS_UART_PORT); // Radio layer off
	HAL_Delay(100);
}

		
void PowerOffNemeus() 
{
	SendMess("AT+GA=DIND,1,880201\n", NEMEUS_UART_PORT);
}


//##############################################################
// LoraWan, to Objenious or similar
//##############################################################

// Activate the LoraWan layer
void LoraWanOn(void)
{
	if(LORAWANOK == 1)
	{
		//TurnOffAllLayers();
		SendMess("AT+MAC=SDR,SF12BW125,10,001F,0,0\n", NEMEUS_UART_PORT);  // active lorawan
		HAL_Delay(200);
		SendMess("AT+MAC=ON,3,A,1\n", NEMEUS_UART_PORT);  // active lorawan

	}
}

/* Ask to join the LoraWan network. /!\ Can't join before receiving this key/adress. It usually takes 7 - 12 minutes before getting it with Objenious /!\ */
void LoraWanAskKey(int TabGen[])
{
	if(LORAWANOK == 1)
	{
		SendMess("AT+MAC=RDEVADDR\n", NEMEUS_UART_PORT);  // demande de cle  // should wait 5s before using nemeus module
	}
}

// Send a message when you finally joined LoraWan network
void SendOnLora(void)
{
	if(LORAWANOK == 1)
	{
		HAL_Delay(1000);
		SendMess("AT+MAC=SNDBIN,000000000000,6,2,0\n", NEMEUS_UART_PORT); // should wait 5s before using nemeus module
	}
}

// Send a string of hexa using LoraWan, to objenious
void SendMessLoraWan(char buffer_lorawan[])
{
	if(LORAWANOK == 1)
	{
		char buffer_all[40];
		sprintf(buffer_all,"AT+MAC=SNDBIN,%s,3,2,0\n", buffer_lorawan);  // %s,buffersig
		SendMess(buffer_all, NEMEUS_UART_PORT);
		HAL_Delay(1000);

	}
}

//##############################################################
// Sigfox, to backend.sigfox (no private network possible)
//##############################################################

// Ask Nemeus module the current state of the Sigfox layer
void SendIdAskSF(void)
{
		if (SIGFOXOK == 1)
	{
		SendMess("AT+SF=?\n", NEMEUS_UART_PORT);
	}
}

// Turn on Sigfox layer
void SigfoxOn(void)
{
	if (SIGFOXOK == 1)
	{
		//SendMess("AT+GA= DIND,1,880201\n", NEMEUS_UART_PORT);

		SendMess("AT+SF=ON\n", NEMEUS_UART_PORT);
		HAL_Delay(1000);
	}
}

// Send a string of hexa using Sigfox
void SendMessSigfox(char buffer_sig[], int TabGen[]) 
{
	if (SIGFOXOK == 1)
	{
		char buffer_all[50];

		if (strlen(buffer_sig) < 10)
			sprintf(buffer_all,"AT+SF=SNDBIN,100000000000,0\n"); // ERROR // should wait 5s before using nemeus module
		else
			sprintf(buffer_all,"AT+SF=SNDBIN,%s,0\n", buffer_sig); // ERROR // should wait 5s before using nemeus module
		
		SendMess(buffer_all, NEMEUS_UART_PORT);		//AT+SF=SNDB / IN,1050d4f / 7499298001 / 100,0\n"
	}
}

//Message sent at startup
void SendOnMessSigfox(uint8_t b_downlink)
{
	if (SIGFOXOK == 1)
	{	
		HAL_Delay(500);
		if (b_downlink == 1)
			SendMess("AT+SF=SNDBIN,000000000000,1\n", NEMEUS_UART_PORT); // should wait 5s before using nemeus module
		else
			SendMess("AT+SF=SNDBIN,FFFFFFFFFFFF,0\n", NEMEUS_UART_PORT); // should wait 5s before using nemeus module
	}
}

//Message sent when shuting down(not used/needed?)
void SendOffMessSigfox(void) 
{
	if (SIGFOXOK == 1)
	{
		SendMess("AT+SF=SNDBIN,111111111111,0\n", NEMEUS_UART_PORT); // should wait 5s before using nemeus module
	}
}



//#####RAK811###############################################################




// RAK 811 ----- pChar1, huart1, patch antenna
void SendTestLora811(void)
{
	for (int i =0; i<3; i++)
	{
		SendMess("at+send=lorap2p:990389\n", RAK811_UART_PORT);
		HAL_Delay(500);
	}
}


void EnableLora811(void)
{
		// 115200 bauds,
	//OutLoraWu(1);

	//HAL_Delay(200);
	//SendMess("at+version\n", RAK811_UART_PORT); // 0 for LORAWAN, 1 for p2p
	HAL_Delay(200);
	SendMess("at+set_config=lora:work_mode:1\n", RAK811_UART_PORT); // 0 for LORAWAN, 1 for p2p
	HAL_Delay(200);
	SendMess("at+set_config=lorap2p:868100000:7:0:1:8:20\r\n", RAK811_UART_PORT);
	HAL_Delay(200);
	//SendMess("at+set_config=device:restart\n", RAK811_UART_PORT); // 0 for LORAWAN, 1 for p2p
	//HAL_Delay(500);


	//SendMess("at+version\n", RAK811_UART_PORT); // 0 for LORAWAN, 1 for p2p

	//SendMess("at+get_config=lora:status\n", RAK811_UART_PORT);
	//HAL_Delay(1000);
	//SendMess("at+join\n", RAK811_UART_PORT);
	//HAL_Delay(500);
}

void EnableLoraSend811(void)
{
	//EnableLora811();
	SendMess("at+set_config=lorap2p:transfer_mode:2\n", RAK811_UART_PORT);   // receiver: 1 , transfer mode :2
	HAL_Delay(200);
}


void EnableLoraReceive811(void)
{
	//EnableLora811();

	SendMess("at+set_config=lorap2p:transfer_mode:1\n", RAK811_UART_PORT);   // receiver: 1 , transfer mode :2
	HAL_Delay(200);
}

void SendMessLora811(char buffer_Lora[])
{
	char buffer_all[34];

	sprintf(buffer_all,"at+send=lorap2p:%s\n", buffer_Lora);

	for (int i = 0; i<9; i++)
	{
		SendMess(buffer_all, RAK811_UART_PORT);
		HAL_Delay(1000);
	}
}

void PingHelios_Rak811( void )
{
	EnableLoraSend811();

	SendMess("at+send=lorap2p:27111988\n", RAK811_UART_PORT);
	HAL_Delay(200);

	EnableLoraReceive811();
}







//##############################################################
// LORA P2P (point to point), private Lora network
//##############################################################

//
void SendTestLora(void)
{
	if(LORAP2POK == 1)
	{
		SendMess("AT+RF=ON\n", NEMEUS_UART_PORT);
		SendMess("AT+RFTX=SET,LORA,868100000,14,125000,7\n", NEMEUS_UART_PORT);
		SendMess("AT+RFTX=SNDBIN,000000000000,1\n", NEMEUS_UART_PORT);
	}
}

// Send a message using Lora P2P
void SendMessLora(char buffer_Lora[])
{
		if(LORAP2POK == 1)
	{
		char buffer_all[34];

		sprintf(buffer_all,"AT+RFTX=SNDBIN,%s,3\n", buffer_Lora);  //  %s,buffersig
		SendMess(buffer_all, NEMEUS_UART_PORT);
	}
}

// Activate the Lora/LoraWan listening mode to intercept messages
void ContinuousRxLora(void)
{
	if(LORAP2POK == 1)
	{
		TurnOffAllLayers();
		SendMess("AT+RFTX=SET,LORA,868100000,14,125000,7\n", NEMEUS_UART_PORT);
		SendMess("AT+RF=ON\n", NEMEUS_UART_PORT);
		SendMess("AT+RFRX=CONTRX\n", NEMEUS_UART_PORT);
	}
}


















//##############################################################
// Gathering all data in a string
//##############################################################

void BuildMessAlert(char buffer_sig[], int TabGen[], float TabFloatValue[], uint32_t TabGpsTimer[])
{  
	
	char b1;
	char b2; 
  char buffer1 ;
	int signe_value = -1 ;
	int elapsed_time_GPS = 0;
	int val1byte = 0 ;
	int val2byte = 0 ;
	int val3to7byte = 0 ;
	int val8to12byte = 0 ;
	uint8_t buffer = 0x00 ;
	char buffer_lat[5] ;
	char buffer_long[5] ;
	char buffer_lat2[5] ;
	char buffer_long2[5] ;
	char buffer_last_gps[3];
	
	if (TabFloatValue[LONGI] > 0)	{		signe_value = 1 ;	}

//sos + 0
//sos - 1
//fall + 2
//fall - 3
//batt + 4
//batt - 5
//gaz + 6
//gaz - 7
//malaise + 8
//malaise - 9



	if (TabGen[SIG_ALERT] == ALERT_SOS)
	{	if (signe_value == 1) {  b1 = '0' ;b2='0';}	else	{  b1 = '1' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_FALL)
	{	if (signe_value == 1) {  b1 = '2' ;b2='0';}	else	{  b1 = '3' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_LOWBAT)
	{	if (signe_value == 1) {  b1 = '4' ;b2='0';}	else	{  b1 = '5' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_MALAISE)
	{	if (signe_value == 1) {  b1 = '8' ;b2='0';}	else	{  b1 = '9' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_O2)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='0';}	else	{  b1 = 'A' ;b2='1';}	}
	else if (TabGen[SIG_ALERT] == ALERT_H2SVME)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='2';}	else	{  b1 = 'A' ;b2='3';}	}
	else if (TabGen[SIG_ALERT] == ALERT_H2SVLCT)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='4';}	else	{  b1 = 'A' ;b2='5';}	}
	else if (TabGen[SIG_ALERT] == ALERT_COVME)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='6';}	else	{  b1 = 'A' ;b2='7';}	}
	else if (TabGen[SIG_ALERT] == ALERT_COVLCT)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='8';}	else	{  b1 = 'A' ;b2='9';}	}
	else if (TabGen[SIG_ALERT] == ALERT_EX)
	{	if (signe_value == 1) {  b1 = 'B' ;b2='0';}	else	{  b1 = 'B' ;b2='1';}	}

	
	val2byte = TabGen[BAT_VALUE] / 10 ;
	if (val2byte > 9)
	{val2byte = 9 ;}
	if (val2byte < 0)
	{val2byte = 0 ;}

	val3to7byte = (int) (    roundf ( (float) ( fabs(TabFloatValue[LATI] * 10000)  )  ) );
	val8to12byte = (int) ( roundf ( (float) ( fabs(TabFloatValue[LONGI] * 100000)  ) )  );

	buffer = (uint8_t) ( val1byte * 16 + val2byte );


	sprintf(buffer_sig, "%c%c", b1, b2 ); 	
	//49,68,70

}


void BuildMessGPS(char buffer_sig[], int TabGen[], float TabFloatValue[], uint32_t TabGpsTimer[])
{  
	
	char b1;
	char b2; 
  char buffer1 ;
	int signe_value = -1 ;
	int elapsed_time_GPS = 0;
	int val1byte = 0 ;
	int val2byte = 0 ;
	int val3to7byte = 0 ;
	int val8to12byte = 0 ;
	uint8_t buffer = 0x00 ;
	char buffer_lat[5] ;
	char buffer_long[5] ;
	char buffer_lat2[5] ;
	char buffer_long2[5] ;
	char buffer_last_gps[3];
	
	if (TabFloatValue[LONGI] > 0)	{		signe_value = 1 ;	}

//sos + 0
//sos - 1
//fall + 2
//fall - 3
//batt + 4
//batt - 5
//gaz + 6
//gaz - 7
//malaise + 8
//malaise - 9



	if (TabGen[SIG_ALERT] == ALERT_SOS)
	{	if (signe_value == 1) {  b1 = '0' ;b2='0';}	else	{  b1 = '1' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_FALL)
	{	if (signe_value == 1) {  b1 = '2' ;b2='0';}	else	{  b1 = '3' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_LOWBAT)
	{	if (signe_value == 1) {  b1 = '4' ;b2='0';}	else	{  b1 = '5' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_MALAISE)
	{	if (signe_value == 1) {  b1 = '8' ;b2='0';}	else	{  b1 = '9' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_O2)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='0';}	else	{  b1 = 'A' ;b2='1';}	}
	else if (TabGen[SIG_ALERT] == ALERT_H2SVME)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='2';}	else	{  b1 = 'A' ;b2='3';}	}
	else if (TabGen[SIG_ALERT] == ALERT_H2SVLCT)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='4';}	else	{  b1 = 'A' ;b2='5';}	}
	else if (TabGen[SIG_ALERT] == ALERT_COVME)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='6';}	else	{  b1 = 'A' ;b2='7';}	}
	else if (TabGen[SIG_ALERT] == ALERT_COVLCT)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='8';}	else	{  b1 = 'A' ;b2='9';}	}
	else if (TabGen[SIG_ALERT] == ALERT_EX)
	{	if (signe_value == 1) {  b1 = 'B' ;b2='0';}	else	{  b1 = 'B' ;b2='1';}	}

	
	
	

	val2byte = TabGen[BAT_VALUE] / 10 ;
	if (val2byte > 9)
	{val2byte = 9 ;}
	if (val2byte < 0)
	{val2byte = 0 ;}

	val3to7byte = (int) (    roundf ( (float) ( fabs(TabFloatValue[LATI] * 10000)  )  ) );
	val8to12byte = (int) ( roundf ( (float) ( fabs(TabFloatValue[LONGI] * 100000)  ) )  );

	buffer = (uint8_t) ( val1byte * 16 + val2byte );
	elapsed_time_GPS = (int)((HAL_GetTick() - TabGpsTimer[LAST_UPDATE_GPS]) / 60000 + 1) ;
	if (TabGpsTimer[LAST_UPDATE_GPS] == 0)
		elapsed_time_GPS = 0;
	
	//elapsed_time_GPS = 8*60-1;
	if (elapsed_time_GPS > 8 * 60)  // 0x1E0  max, more than 8 hours => 0xFFF
		elapsed_time_GPS = 4095; // 0xFFF
	

	//elapsed_time_GPS = 8*60-1;
	decimal2hexa(val3to7byte, buffer_lat, 5);
	decimal2hexa(val8to12byte, buffer_long, 5);
	decimal2hexa(elapsed_time_GPS, buffer_last_gps, 3); 
	


	buffer_lat2[0] = buffer_lat[0];
	buffer_lat2[1] = buffer_lat[1];
	buffer_lat2[2] = buffer_lat[2];
	buffer_lat2[3] = buffer_lat[3];
	buffer_lat2[4] = buffer_lat[4];
	buffer_long2[0]  = buffer_long[0];
	buffer_long2[1]  = buffer_long[1];
	buffer_long2[2]  = buffer_long[2];
	buffer_long2[3]  = buffer_long[3];
	buffer_long2[4]  = buffer_long[4];



	sprintf(buffer_sig, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c1%d", //
	b1, b2,  //15
	buffer_lat2[0], buffer_lat2[1], buffer_lat2[2], buffer_lat2[3], buffer_lat2[4], 			// latitude in hexa
	buffer_long2[0], buffer_long2[1], buffer_long2[2], buffer_long2[3], buffer_long2[4],  // longitude in hexa
	buffer_last_gps[0], buffer_last_gps[1], buffer_last_gps[2], TabGen[ID_ALERT]); 													// last gps acquisition in hexa
	//49,68,70


	if(LORAWANOK == 1 && SIGFOXOK == 1)
		buffer_sig[15] = '2';

}




void FuncLoraMessNoGPS(char buffer_lora[], int TabGen[], float TabFloatValue[], uint32_t TabGpsTimer[])
{

	char b1;
	char b2;
  char buffer1 ;
	int signe_value = -1 ;
	int elapsed_time_GPS = 0;
	int val1byte = 0 ;
	int val2byte = 0 ;
	int val3to7byte = 0 ;
	int val8to12byte = 0 ;
	uint8_t buffer = 0x00 ;


	if (TabFloatValue[LONGI] > 0)	{		signe_value = 1 ;	}

//sos + 0
//sos - 1
//fall + 2
//fall - 3
//batt + 4
//batt - 5
//gaz + 6
//gaz - 7
//malaise + 8
//malaise - 9



	if (TabGen[SIG_ALERT] == ALERT_SOS)
	{	if (signe_value == 1) {  b1 = '0' ;b2='0';}	else	{  b1 = '1' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_FALL)
	{	if (signe_value == 1) {  b1 = '2' ;b2='0';}	else	{  b1 = '3' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_LOWBAT)
	{	if (signe_value == 1) {  b1 = '4' ;b2='0';}	else	{  b1 = '5' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_MALAISE)
	{	if (signe_value == 1) {  b1 = '8' ;b2='0';}	else	{  b1 = '9' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_O2)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='0';}	else	{  b1 = 'A' ;b2='1';}	}
	else if (TabGen[SIG_ALERT] == ALERT_H2SVME)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='2';}	else	{  b1 = 'A' ;b2='3';}	}
	else if (TabGen[SIG_ALERT] == ALERT_H2SVLCT)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='4';}	else	{  b1 = 'A' ;b2='5';}	}
	else if (TabGen[SIG_ALERT] == ALERT_COVME)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='6';}	else	{  b1 = 'A' ;b2='7';}	}
	else if (TabGen[SIG_ALERT] == ALERT_COVLCT)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='8';}	else	{  b1 = 'A' ;b2='9';}	}
	else if (TabGen[SIG_ALERT] == ALERT_EX)
	{	if (signe_value == 1) {  b1 = 'B' ;b2='0';}	else	{  b1 = 'B' ;b2='1';}	}


	val2byte = TabGen[BAT_VALUE] / 10 ;
	if (val2byte > 9)
	{val2byte = 9 ;}
	if (val2byte < 0)
	{val2byte = 0 ;}

	val3to7byte = (int) (    roundf ( (float) ( fabs(TabFloatValue[LATI] * 10000)  )  ) );
	val8to12byte = (int) ( roundf ( (float) ( fabs(TabFloatValue[LONGI] * 100000)  ) )  );

	buffer = (uint8_t) ( val1byte * 16 + val2byte );


	sprintf(buffer_lora, "%c%c0389", b1, b2 );
	//49,68,70

}





void BuildMessWifi(char buffer_sig[], int TabGen[], float TabFloatValue[], uint32_t TabTimer[], char macWifi[])
{  
	
	char b1;
	char b2; 
  char buffer1 ;
	int signe_value = -1 ;
	int elapsed_time_wifi = 0;
	int val1byte = 0 ;
	int val2byte = 0 ;
	int val3to7byte = 0 ;
	int val8to12byte = 0 ;
	uint8_t buffer = 0x00 ;
	char buffer_last_wifi[4];
	
	if (TabFloatValue[LONGI] > 0)	{		signe_value = 1 ;	}

//sos + 0
//sos - 1
//fall + 2
//fall - 3
//batt + 4
//batt - 5
//gaz + 6
//gaz - 7
//malaise + 8
//malaise - 9



	if (TabGen[SIG_ALERT] == ALERT_SOS)
	{	if (signe_value == 1) {  b1 = '0' ;b2='0';}	else	{  b1 = '1' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_FALL)
	{	if (signe_value == 1) {  b1 = '2' ;b2='0';}	else	{  b1 = '3' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_LOWBAT)
	{	if (signe_value == 1) {  b1 = '4' ;b2='0';}	else	{  b1 = '5' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_MALAISE)
	{	if (signe_value == 1) {  b1 = '8' ;b2='0';}	else	{  b1 = '9' ;b2='0';}	}
	else if (TabGen[SIG_ALERT] == ALERT_O2)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='0';}	else	{  b1 = 'A' ;b2='1';}	}
	else if (TabGen[SIG_ALERT] == ALERT_H2SVME)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='2';}	else	{  b1 = 'A' ;b2='3';}	}
	else if (TabGen[SIG_ALERT] == ALERT_H2SVLCT)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='4';}	else	{  b1 = 'A' ;b2='5';}	}
	else if (TabGen[SIG_ALERT] == ALERT_COVME)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='6';}	else	{  b1 = 'A' ;b2='7';}	}
	else if (TabGen[SIG_ALERT] == ALERT_COVLCT)
	{	if (signe_value == 1) {  b1 = 'A' ;b2='8';}	else	{  b1 = 'A' ;b2='9';}	}
	else if (TabGen[SIG_ALERT] == ALERT_EX)
	{	if (signe_value == 1) {  b1 = 'B' ;b2='0';}	else	{  b1 = 'B' ;b2='1';}	}



	elapsed_time_wifi = (int)((HAL_GetTick() - TabTimer[LAST_UPDATE_WIFI]) / 60000 + 1) ;
	if (TabTimer[LAST_UPDATE_WIFI] == 0)
		elapsed_time_wifi = 0;
	
	//elapsed_time_GPS = 8*60-1;
	if (elapsed_time_wifi > 8 * 60)  // 0x1E0  max, more than 8 hours => 0xFFF
		elapsed_time_wifi = 4095; // 0xFFF
	

	//elapsed_time_GPS = 8*60-1;

	decimal2hexa(elapsed_time_wifi, buffer_last_wifi, 3); 
	char bufferMac[13];

	uint8_t j = 0;
	//MAC[2] == ':' && MAC[5] == ':' && MAC[8] == ':' && MAC[11] == ':' && MAC[14] == ':'
	for (int i = 0;  i < 12 ; i++) // mac without ':'
	{
		if (macWifi[j] == ':')
			j++;
		bufferMac[i] = macWifi[j++];
	}
	bufferMac[12] = 0;
	
	char buff[40] = {0};
	
	sprintf(buff, "%c%c%s%c%c%c2%.2d",	b1, b2, bufferMac, buffer_last_wifi[0],buffer_last_wifi[1],buffer_last_wifi[2], TabGen[ID_ALERT]);
	
	sprintf(buffer_sig, "%s", buff); 													// last gps acquisition in hexa
	//49,68,70

}



//##############################################################
// Misc
//##############################################################



void SendMess(char *char_in, UART_HandleTypeDef huart)
{
	uint32_t Timeout_local = 1000;
	//HAL_UART_Transmit(&NEMEUS_UART_PORT,((uint8_t *)char_in),sizeof(*char_in)-1,Timeout_local  );
	
	HAL_UART_Transmit(&huart,((uint8_t *)char_in),strlen(char_in),Timeout_local  );
}

void SendMessWifi(char *char_in) 
{
	uint32_t Timeout_local = 10;
	//HAL_UART_Transmit(&NEMEUS_UART_PORT,((uint8_t *)char_in),sizeof(*char_in)-1,Timeout_local  );
	
	HAL_UART_Transmit(&huart1,((uint8_t *)char_in),strlen(char_in),Timeout_local  );
}


void decimal2hexa(unsigned int decimal,char hexa[],unsigned int size_char)
{
   static char const hexaset[] = "0123456789ABCDEF";
   //unsigned int quotient = decimal;
   unsigned int size = size_char;
	
	for(unsigned int i=0;i<size_char;i++)
	{
		hexa[i] = '0';
	}

	do
	{
		 size--;
		 hexa[size] = hexaset[decimal % 16];
		 decimal /= 16;
	}
	while(decimal != 0);
}
