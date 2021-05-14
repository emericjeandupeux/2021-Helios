
#include "hes_gps.h"

void GpsStop(void) {
	
	OutGpsRst(1);
HAL_Delay(1);
	 // hexadecimal messages to stop GPS
 uint8_t stop_gps1[] = {0xB5, 0x62, 0x06, 0x04, 0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x16, 0x74};
 uint8_t stop_gps2[] = {0xB5, 0x62, 0x0A, 0x04, 0x00, 0x00, 0x0E, 0x34};
 

  HAL_UART_Transmit_IT(&GPS_UART_PORT, stop_gps1, sizeof(stop_gps1));
  HAL_Delay(20);
  HAL_UART_Transmit_IT(&GPS_UART_PORT, stop_gps2, sizeof(stop_gps2));
  HAL_Delay(20);
  //OutGpsRst(0);
}

/*Byte sequence, GLONASS Only - UBX-CFG-GNSS
size 3C (60)

B5 62
06 3E // UBX-CFG-GNSS
3C    // Size
	Ver	Ch	Ch	Nb blocks
00	00 	00 	20 	07

ID Chnls XX	En
00 08 10 00 00 00 01 01 // GPS
01 01 03 00 00 00 01 01 // SBAS
02 04 08 00 00 00 01 01 // GALILEO
03 08 10 00 00 00 01 01 // BeiDou
04 00 08 00 00 00 01 01 // IMES
05 00 03 00 00 00 01 01 // QZSS
06 08 20 00 01 00 01 01 // GLONASS
3E 89 // check
*/


void CheckSum(uint8_t tab[], uint8_t size)
{
	uint8_t CK_A = 0, CK_B = 0;
	int i;
	for( i = 2; i < size-2; i++)
	{
		CK_A = CK_A + tab[i];
		CK_B = CK_B + CK_A;
	}
	tab[i] = CK_A;
	i++;
	tab[i] = CK_B;
}

void GpsStart(void) {

  // hexadecimal messages to start GPS
uint8_t start_gps1[] = {0xB5, 0x62, 0x06, 0x04, 0x04, 0x00, 0x00, 0x00, 0x09, 0x00, 0x17, 0x76}; //UBX-CFG-RST -> 04 -> hardware reset
uint8_t start_gps2[] = {0xB5, 0x62, 0x0A, 0x04, 0x00, 0x00, 0x0E, 0x34};	// Poll receiver

 
uint8_t RMC_Off[] = { 0XB5, 0X62, 0X06, 0X01, 0X08, 0X00, 0XF0, 0X04, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X03, 0X3F};
uint8_t VTG_Off[] = { 0XB5, 0X62, 0X06, 0X01, 0X08, 0X00, 0XF0, 0X05, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X04, 0X46};
uint8_t GSA_Off[] = { 0XB5, 0X62, 0X06, 0X01, 0X08, 0X00, 0XF0, 0X02, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0X31};
uint8_t GSV_Off[] = { 0XB5, 0X62, 0X06, 0X01, 0X08, 0X00, 0XF0, 0X03, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X02, 0X38};
uint8_t GLL_Off[] = { 0XB5, 0X62, 0X06, 0X01, 0X08, 0X00, 0XF0, 0X01, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X2A};
// char GGA_Off[] = { 0XB5, 0X62, 0X06, 0X01, 0X08, 0X00, 0XF0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0X23};
uint8_t GGA_On[] = { 0XB5, 0X62, 0X06, 0X01, 0X08, 0X00, 0XF0, 0X00, 0X00, 0X01, 0X01, 0X00, 0X00, 0X00, 0X01, 0X2C};
uint8_t ZDA_Off[] = { 0XB5, 0X62, 0X06, 0X01, 0X08, 0X00, 0XF0, 0X08, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X07, 0X5B};

//uint8_t POWER_MODE_CONFIG[] = { 0xB5, 0x62, 0x06, 0x3B, 0x2C, 0x01, 0x00, 0x3C, 0x00,  }; //  UBX-CFG-PM2 - Extended power management configuration

uint8_t POWER_MODE_ECO[] 			= { 0xB5, 0x62, 0x06, 0x86, 0x08, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x5B}; //UBX-CFG-RXM
uint8_t POWER_MODE_ECO_UCENTER[]	= { 0xB5, 0x62, 0x06, 0x86, 0x08, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x6F};

 

//Power Save Mode (PSM) allows a reduction in system power consumption by selectively switchingparts of the receiver on and off. It is selected using the message UBX-CFG-RXM and configured using UBX-CFG-PM2. It is recommended to use UBX-CFG-PMS instead if available (only supported inprotocol versions 18+) as it provides a simplified interface; see section Power mode setup fordetails
//CAM-M8Q-0-10  = >  SPG 3.01  => 18.00  //ROM CORE 3.01 (107888)
uint8_t GNSS_Selection[] = { 0XB5, 0X62, 0X06, 0X3E, 0X3C,
		0X00, 0X00, 0X00, 0X20, 0X07, 						// config header
		0X00, 0X08, 0X10, 0X00, 0X01, 0X00, 0X01, 0X01,		// GPS
		0X01, 0X01, 0X03, 0X00, 0X00, 0X00, 0X01, 0X01, 	// SBAS
		0X02, 0X04, 0X08, 0X00, 0X00, 0X00, 0X01, 0X01, 	// Galileo
		0X03, 0X08, 0X10, 0X00, 0X00, 0X00, 0X01, 0X01, 	// BeiDou
		0X04, 0X00, 0X08, 0X00, 0X00, 0X00, 0X01, 0X01, 	// IMES
		0X05, 0X00, 0X03, 0X00, 0X00, 0X00, 0X01, 0X01, 	// QZSS
		0X06, 0X08, 0X0E, 0X00, 0X00, 0X00, 0X01, 0X01, 	// GLONASS Off
		0X2C, 0X4D};




CheckSum(GNSS_Selection, sizeof(GNSS_Selection));

CheckSum(POWER_MODE_ECO, sizeof(POWER_MODE_ECO));


OutGpsRst(1);
HAL_Delay(1);

HAL_UART_Transmit_IT(&GPS_UART_PORT, start_gps1, sizeof(start_gps1));
HAL_Delay(100);

HAL_UART_Transmit_IT(&GPS_UART_PORT, start_gps2, sizeof(start_gps2));
HAL_Delay(100);

HAL_UART_Transmit_IT(&GPS_UART_PORT, RMC_Off, sizeof(RMC_Off));
HAL_Delay(30);

HAL_UART_Transmit_IT(&GPS_UART_PORT, VTG_Off, sizeof(VTG_Off));
HAL_Delay(30);

HAL_UART_Transmit_IT(&GPS_UART_PORT, GSA_Off, sizeof(GSA_Off));
HAL_Delay(30);

HAL_UART_Transmit_IT(&GPS_UART_PORT, GSV_Off, sizeof(GSV_Off));
HAL_Delay(30);

HAL_UART_Transmit_IT(&GPS_UART_PORT, GLL_Off, sizeof(GLL_Off));
HAL_Delay(30);

HAL_UART_Transmit_IT(&GPS_UART_PORT, ZDA_Off, sizeof(ZDA_Off));
HAL_Delay(30);

HAL_UART_Transmit_IT(&GPS_UART_PORT, GGA_On, sizeof(GGA_On));
HAL_Delay(200);

HAL_UART_Transmit_IT(&GPS_UART_PORT, GNSS_Selection, sizeof(GNSS_Selection));
HAL_Delay(200);

HAL_UART_Transmit_IT(&GPS_UART_PORT, POWER_MODE_ECO_UCENTER, sizeof(POWER_MODE_ECO_UCENTER)); // UBX-CFG-RXM
HAL_Delay(30);


}

int find_word(char *tableau , char *word, int taille_word){
// char word[8] = "hassasin";
//char Buffer[1000]=sdfhksfhkasd/./.fjka(hassasin)hdkjfakjsdfhkksjdfhkjh....etc 
int k=0;
int t=0; 
int len=0; 
int sor=0; 
for (k=0; k<12; k++){ 
		len=0;
    for (t=0; t<taille_word; t++){ 
        if (tableau[k]==word[t]) 
					{len++;} 
        if (len==8) 
					{sor =1;
					 break; }
    } 
		sor= 0;
}

return sor;
 }

//float transformer_char_latitude_todecdeg(char *t){      // fonction qui transforme la latitude string en latitude float en degr�s d�cimal
// float latitude_degdec;
//	latitude_degdec=((t[0]-48)*10+(t[1]-48))+((t[2]-48)*pow(10,6)+(t[3]-48)*pow(10,5)+(t[5]-48)*pow(10,4)+(t[6]-48)*pow(10,3)+(t[7]-48)*pow(10,2)+(t[8]-48)*10+t[9]-48)*0.00001/60;
////  LedOn(0, 50, 50, LEDLOW);
////	 CDC_Transmit_FS("---\n",sizeof("---\n"));
////	 	sprintf(go, "%8f\n",latitude_degdec);
////			CDC_Transmit_FS(go,sizeof(go));
////    	HAL_Delay(20);
//	return latitude_degdec;
//}
// float transformer_char_longitude_todecdeg(char *t){    // fonction qui transforme la longitude string en logitude float en degr�s d�cimal
//	  float longitude_degdec;
//	 	longitude_degdec=((t[0]-48)*pow(10,2)+(t[1]-48)*10+(t[2]-48))+((t[3]-48)*pow(10,6)+(t[4]-48)*pow(10,5)+(t[6]-48)*pow(10,4)+(t[7]-48)*pow(10,3)+(t[8]-48)*pow(10,2)+(t[9]-48)*10+t[10]-48)*0.00001/60;
////	 	 CDC_Transmit_FS("---\n",sizeof("---\n"));
////	 	sprintf(go, "%8f\n",longitude_degdec);
////			CDC_Transmit_FS(go,sizeof(go));
////    	HAL_Delay(20);
//	return longitude_degdec;
// }
