#include "hes_uart_CarteGaz.h"
#include <stdio.h>
#include "string.h"
#include <math.h>
uint32_t uart_convData(uint8_t * pdata){
	uint32_t value = 0;
	value = (pdata[0]<<8) + (pdata[1]<<4) + pdata[2];
	return value;
}
uint32_t uart_getValue(uint8_t * pdata){
	uint32_t value = 0;
	value = (pdata[2]<<8) + (pdata[3]<<4) + pdata[4];
	return value;
}

void uart_sendCommandWarning(uint8_t danger,uint8_t state){
	uint8_t data  [] = {WARNING, 0x02,danger,state};
	HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}
void uart_sendCommandGet(uint8_t command){
		uint8_t data  [] = {command, 0x01,0x00};
		HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}

void uart_sendCommandPrint(){
uint8_t data[10] = {TAUX,0x08,0x31,AUCUN,0x31,VLCT,0x31,VLCT,0x31,VME};
	
	HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}
void uart_sendCommandDisplay_PPM2(float h2s, uint8_t seuil_H2S ,float o2,uint8_t seuil_O2 ,float ex,uint8_t seuil_EX ,float co,uint8_t seuil_CO){
	char str_part_float[4][2];
	char tab_H2S[7] = {};
	char tab_O2[7] = {};
	char tab_EX[7] = {};
	char tab_CO[7] = {};
		
	// permet d'obtenir la valeur absolue 
	h2s = fabs(h2s);
	o2 = fabs(o2);
	ex = fabs(ex);
	co =fabs(co);
	
	uint8_t data[34];
	int i = 0;
	int y = 2;
	sprintf(tab_H2S,"%i",(int)h2s);
	strcat(tab_H2S,".");
	sprintf(str_part_float[0],"%i",((int)(h2s*10))%10);
	strcat(tab_H2S,str_part_float[0]);
		
	sprintf(tab_O2,"%i",(int)o2);
	strcat(tab_O2,".");
	sprintf(str_part_float[1],"%i",((int)(o2*10))%10);
	strcat(tab_O2,str_part_float[1]);
		
	sprintf(tab_EX,"%i",(int)ex);
	strcat(tab_EX,".");
	sprintf(str_part_float[2],"%i",((int)(ex*10))%10);
	strcat(tab_EX,str_part_float[2]);
		
	sprintf(tab_CO,"%i",(int)co);
	strcat(tab_CO,".");
	sprintf(str_part_float[3],"%i",((int)(co*10))%10);
	strcat(tab_CO,str_part_float[3]);
	data[0] = TAUX;
	data[1] = 32;
	//EXPLOSIF
	for(i=0;i<7;i++){
		data[y]=tab_EX[i];
		y++;
	}
	data[y] = seuil_EX;
	y++;
	
	//H2S
	for(i=0;i<7;i++){
		data[y]=tab_H2S[i];
		y++;
	}
	data[y] = seuil_H2S;
	y++;
	
	//O2
	for(i=0;i<7;i++){
		data[y]=tab_O2[i];
		y++;
	}
	data[y] = seuil_O2; 
	y++;
	
	//CO
	for(i=0;i<7;i++){
		data[y]=tab_CO[i];
		y++;
	}
	data[33] = seuil_CO;
	HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}
void uart_sendCommandDisplay_PPM(int h2s, int o2, int ex, int co){
	char tab_H2S[7] = {};
	char tab_O2[7] = {};
	char tab_EX[7] = {};
	char tab_CO[7] = {};

	sprintf(tab_H2S,"%i",h2s);
	sprintf(tab_O2,"%i",o2);
	sprintf(tab_EX,"%i",ex);
	sprintf(tab_CO,"%i",co);

	uint8_t data[34];
	data[0] = TAUX;
	data[1] = sizeof(data)-2;
	data[2] =tab_EX[0];
	data[3] =tab_EX[1];
	data[4] =tab_EX[2];
	data[5] =tab_EX[3];
	data[6] =tab_EX[4];
	data[7] =tab_EX[5];
	data[8] =tab_EX[6];
	data[9] =0x01;
	data[10] =tab_H2S[0];
	data[11] =tab_H2S[1];
	data[12] =tab_H2S[2];
	data[13] =tab_H2S[3];
	data[14] =tab_H2S[4];
	data[15] =tab_H2S[5];
	data[16] =tab_H2S[6];
	data[17] =0x01;
	data[18] =tab_O2[0];
	data[19] =tab_O2[1];
	data[20] =tab_O2[2];
	data[21] =tab_O2[3];
	data[22] =tab_O2[4];
	data[23] =tab_O2[5];
	data[24] =tab_O2[6];
	data[25] =0x01;
	data[26] =tab_CO[0];
	data[27] =tab_CO[1];
	data[28] =tab_CO[2];
	data[29] =tab_CO[3];
	data[30] =tab_CO[4];
	data[31] =tab_CO[5];
	data[32] =tab_CO[6];
	data[33] =0x01;

	HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}

void uart_commandAlerte(uint8_t alerte){
			uint8_t data [] = {ALERTE,0x01,alerte};
		HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}
void uart_setGPS_Status(uint8_t status){
		uint8_t data [] = {SET_GPS_STATUS,0x01,status};
		HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}
void uart_setNetwork_Status(uint8_t status){
		uint8_t data [] = {SET_NET_STATUS,0x01,status};
		HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}
void uart_setNiv_Sonore(uint8_t nivSonore){
		uint8_t data [] = {SET_NIV_SON,0x01,nivSonore};
		HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}
void uart_sendCommandGPIO(uint8_t command, uint8_t state){
		uint8_t data [] = {command,0x01,state};
		HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}

void uart_sendCommandDisplay(uint8_t xpos, uint8_t ypos, uint8_t police, char * msg, uint8_t sizeMsg){
		uint8_t data [sizeMsg+5];
		data [0] =  0x01;
		data [1] =	sizeMsg + 3;
		data [2] =	xpos;
		data [3] =	ypos;
		data [4] = police;
		for(int i = 0; i < sizeMsg; i++){
			data[i +5] = msg[i];
		}
		HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}


void uart_sendCommandBlink(uint8_t alpha, uint8_t frequency, uint8_t state){
	uint8_t data []  = {BLINK,0x03,alpha,frequency,state};
	HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}

void uart_sendCommandBattery(uint8_t level){
	uint8_t data []  = {BATTERY,0x01,level};
	HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}

void uart_sendCommandLPM(uint8_t state){
		uint8_t data [] = {SET_LPM,0x01,state};
		HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}

//utiliser pour le debug uniquement
void uart_sendCommandDisplay_value(uint32_t value){
	char str_value[6];
	sprintf(str_value,"%u",value);
	uart_sendCommandDisplay(15,15,14,str_value,sizeof(str_value));
}

uint8_t uart_searchForCommand(uint8_t command ,uint8_t *data){
	int i = 0;
	uint8_t size = 0;
	uint8_t found = 0;
//	do{
//		if(uart_bufferCplt[i] == command){
//			size = uart_bufferCplt[i++];
//			for(int y =0;y<size;y++){
//				data[y] = uart_bufferCplt[i];
//				i++;
//			}
//			found = 1;
//		}
//		i++;
//	}while(i<sizeof(uart_bufferCplt) || !found);
//	if(found){
//		for(i=0;i<sizeof(uart_bufferCplt);i++){
//		uart_bufferCplt[i] = 0;
//		}
//	}
	return found;
}

void uart_wait(){
	uint8_t time = 0;
	uint8_t timeout = 0;
	do{
		HAL_Delay(1000);
		time = time +1;
		if (time > 5) {
			timeout = 1;
		}
	}while((ready==0) && (timeout==0));
	HAL_Delay(500);
	ready = 0;
	
}
void uart_recieveCommand(uint8_t command, uint8_t *pdata,uint8_t sizeData){
	uint8_t data[sizeData];
	for (int i = 0;i<sizeData;i++){
		data[i] = pdata[i];
	}
	switch(command){
		case SEND_H2S :
			tab_ADC_value[CHANNEL_H2S] 		= uart_convData(data);
			break;
		case SEND_O2 :
			tab_ADC_value[CHANNEL_O2]   	= uart_convData(data);
			break;
		case SEND_TEMP :
			tab_ADC_value[CHANNEL_TEMP] 	= uart_convData(data);
			break;
		case SEND_CO :
			tab_ADC_value[CHANNEL_CO] 		= uart_convData(data);
			break;
		case SEND_EX :
			tab_ADC_value[CHANNEL_EX] 		= uart_convData(data);
			break;
		case SEND_SONOMETRE :
			tab_ADC_value[CHANNEL_SONOMETRE] = uart_convData(data);
			break;
		case UART_READY :
			ready = 1;
			break;
	}
}

void uart_Process_Data(uint8_t command, uint8_t * data){
	switch(command){
		case SEND_O2:
			tab_ADC_value[0] = uart_convData(data);
			break;
		case SEND_EX:
			tab_ADC_value[1] = uart_convData(data);
			break;
		case SEND_H2S:
			tab_ADC_value[2] = uart_convData(data);
			break;
		case SEND_CO:
			tab_ADC_value[3] = uart_convData(data);
			break;
		case SEND_SONOMETRE:
			tab_ADC_value[4] = uart_convData(data);
			break;
		case SEND_TEMP:
			tab_ADC_value[5] = uart_convData(data);
			break;
		case ERROR:
			break;
		case UART_READY:
			break;
		default :
			break;
	}
}


uint8_t uart_isReady(uint8_t * buffer){
uint8_t ready = 0;
uint8_t data [] = {buffer[0],buffer[1],buffer[2]};
	if (data[0] == UART_READY){
		ready = 1;
	}
	return ready;
}

void uart_putValue(uint8_t * buffer){
	uint8_t data[3];
	for (int i = 0; i<3;i++){
		data[i] = buffer[i+2];
	}
	switch(buffer[0]){
		case SEND_O2:
			tab_ADC_value[CHANNEL_O2] = uart_convData(data);
			break;
		case SEND_EX:
			tab_ADC_value[CHANNEL_EX] = uart_convData(data);
			break;
		case SEND_H2S:
			tab_ADC_value[CHANNEL_H2S] = uart_convData(data);
			break;
		case SEND_CO:
			tab_ADC_value[CHANNEL_CO] = uart_convData(data);
			break;
		case SEND_SONOMETRE:
			tab_ADC_value[CHANNEL_SONOMETRE] = uart_convData(data);
			break;
		case SEND_TEMP:
			tab_ADC_value[CHANNEL_TEMP] = uart_convData(data);
			break;
		default :
			break;
	}

}
void uart_sendCommandExtinction(uint8_t state){
		uint8_t data [] = {LOADING,0x01,state};
		HAL_UART_Transmit(&huart1,data,sizeof(data),1000);
}
