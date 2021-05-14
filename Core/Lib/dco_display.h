//#include "stm32f0xx_hal.h"
//#include "/u8g2/u8g2.h"
#include "main.h"
#include "dco_hestiam.h"
#include "dco_images.h"
#include "dco_REGAZ.h"
#include <stdio.h>


extern I2C_HandleTypeDef hi2c2;

extern I2C_HandleTypeDef BIGOLED_I2C_PORT;
	
#define BIGOLED_I2C_PORT	hi2c2	


uint8_t u8x8_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8,U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,U8X8_UNUSED void *arg_ptr);
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
void display_dco(float TabFloatValue[],int TabAlert[],int TabGen[],uint32_t TabTimer[], char name[], char * msg1, char * msg2, char *msg3, char *msg4);
void ClearScreen(void);
void display_Print_PPM(char *title, float value,float tension);
void display_Print(char *msg);
void display_Init(uint8_t b_diplay_msg);
void display_InitBis();
void display_Chargement(void);
void display_Chargement_perso(void);
void display_Print_Sound_Level(uint8_t choice);
void display_warning(uint8_t nb);
void display_Print_UART(char *msg, uint8_t xpos, uint8_t ypos, uint8_t sizePolice);
void display_BatteryLvl(uint8_t level, uint8_t posXmes, uint8_t posYmes);
void display_GPS_status(uint8_t status, uint32_t TabGpsTimer[], int TabGen[]);
void display_network_status(uint8_t status, uint8_t posXmes, uint8_t posYmes);
void display_Wifi (int TabGen[], char name[]);
void RepeaterLinkStatus(int TabGen[]);
void NetworkStatus(int TabGen[]);
void display_Alerte(int TabGen[], uint8_t type_Alerte);
void display_wait(uint8_t step);
void display_son(uint8_t db);
void display_AlerteGaz(uint8_t gaz,int type_warning);
void display_AlerteDanger(int TabGen[], uint32_t TabAlertAll[], int type_warning);
void display_SendMess(void);
#define STAGE1	1
#define STAGE2	2
#define STAGE3	3
#define STAGE4	4
