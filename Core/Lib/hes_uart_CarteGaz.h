#include "main.h"
#include "usart.h"
/*
CMD_DISPLAY, SIZE, POSX, POSY, MSG
size : 2 4 6 8 10 12 14 16

*/
#define CMD_DISPLAY 	0x01



/*

GET_XX, 0x01, 0x00

return :

SEND_XX, SIZE, DATA
*/
#define GET_O2					0x02
#define GET_EX					0x03
#define GET_H2S					0x04
#define GET_CO					0x05
#define GET_SONOMETRE 	0x06
#define GET_TEM					0x07

#define SEND_O2					0x12
#define SEND_EX					0x13
#define SEND_H2S				0x14
#define SEND_CO					0x15
#define SEND_SONOMETRE 	0x16
#define SEND_TEMP				0x17

/*
SET_XX, 0x01, STATE


STATE 0x00 : OFF
STATE 0x01 : ON
*/
#define SET_LIGHT				0x08
#define SET_DISPLAY			0x09
#define SET_2V85				0x0A
#define BLINK						0x0B
#define SET_LPM					0x0C
#define WARNING					0x0D
#define BATTERY					0x0E
#define TAUX						0x10

#define ERROR						0xF0

#define SET_GPS_STATUS	0x20
#define SET_NET_STATUS	0x21
#define SET_NIV_SON			0x22

#define LOADING 				0x23

#define ALERTE					0x0F

#define ON							0x01
#define OFF							0x00

#define UART_READY 			0xFF

#define CHANNEL_CO 				0
#define CHANNEL_VIDE 			1
#define CHANNEL_TEMP 			2
#define CHANNEL_EX 				3
#define CHANNEL_O2 				4
#define CHANNEL_H2S			  5
#define CHANNEL_SONOMETRE 6


#define VME								0x03
#define VLCT							0x02
#define AUCUN							0x01

void uart_sendCommandExtinction(uint8_t state);
void uart_sendCommandWarning(uint8_t danger,uint8_t state);
void uart_sendCommandGet(uint8_t command);
void uart_sendCommandGPIO(uint8_t command, uint8_t state);
void uart_sendCommandDisplay(uint8_t xpos, uint8_t ypos, uint8_t police, char * msg, uint8_t sizeMsg);
void uart_sendCommandBlink(uint8_t alpha, uint8_t frequency, uint8_t state);
void uart_sendCommandLPM(uint8_t state);
void uart_sendCommandDisplay_value(uint32_t value);
void uart_sendCommandBattery(uint8_t level);
void uart_sendCommandPrint();
uint32_t uart_convData(uint8_t * pdata);
uint32_t uart_getValue(uint8_t * pdata);
void uart_is_ready(void);
void uart_Process_Data(uint8_t command, uint8_t * data);
void uart_commandAlerte(uint8_t alerte);
void uart_sendCommandDisplay_PPM(int h2s, int o2, int ex, int co);
void uart_sendCommandDisplay_PPM2(float h2s, uint8_t seuil_H2S ,float o2,uint8_t seuil_O2 ,float ex,uint8_t seuil_EX ,float co,uint8_t seuil_CO);
void uart_setGPS_Status(uint8_t status);
void uart_setNetwork_Status(uint8_t status);
void uart_setNiv_Sonore(uint8_t nivSonore);
uint8_t uart_isReady(uint8_t * buffer);
void uart_putValue(uint8_t * buffer);
uint8_t uart_searchForCommand(uint8_t command ,uint8_t *data);
void uart_recieveCommand(uint8_t command, uint8_t *pdata,uint8_t sizeData);
void uart_wait();