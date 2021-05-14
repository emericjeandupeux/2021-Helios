/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../Lib/u8g2/u8g2.h"
extern uint32_t tab_ADC_value [7];
extern uint8_t ready ;
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern uint32_t tab_ADC_value [7];

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */


/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OLED_RST_Pin GPIO_PIN_13
#define OLED_RST_GPIO_Port GPIOC
#define GAZ1_CH5_Pin GPIO_PIN_0
#define GAZ1_CH5_GPIO_Port GPIOA
#define TX2_GPS_Pin GPIO_PIN_2
#define TX2_GPS_GPIO_Port GPIOA
#define MOTOR_WU_Pin GPIO_PIN_3
#define MOTOR_WU_GPIO_Port GPIOA
#define GAZ3_CH9_Pin GPIO_PIN_4
#define GAZ3_CH9_GPIO_Port GPIOA
#define GAZ_WU_Pin GPIO_PIN_7
#define GAZ_WU_GPIO_Port GPIOA
#define LED_WU_Pin GPIO_PIN_0
#define LED_WU_GPIO_Port GPIOB
#define GPS_RST_Pin GPIO_PIN_1
#define GPS_RST_GPIO_Port GPIOB
#define LORA_WU_Pin GPIO_PIN_2
#define LORA_WU_GPIO_Port GPIOB
#define TX3_LORA_Pin GPIO_PIN_10
#define TX3_LORA_GPIO_Port GPIOB
#define RX3_LORA_Pin GPIO_PIN_11
#define RX3_LORA_GPIO_Port GPIOB
#define OLED_WU_Pin GPIO_PIN_12
#define OLED_WU_GPIO_Port GPIOB
#define SCL2_OLED_Pin GPIO_PIN_13
#define SCL2_OLED_GPIO_Port GPIOB
#define SDA2_OLED_Pin GPIO_PIN_14
#define SDA2_OLED_GPIO_Port GPIOB
#define DWM_WU_Pin GPIO_PIN_15
#define DWM_WU_GPIO_Port GPIOB
#define DWM_RST_Pin GPIO_PIN_8
#define DWM_RST_GPIO_Port GPIOA
#define TX1_CARTEGAZ_Pin GPIO_PIN_9
#define TX1_CARTEGAZ_GPIO_Port GPIOA
#define RX1_CARTEGAZ_Pin GPIO_PIN_10
#define RX1_CARTEGAZ_GPIO_Port GPIOA
#define RX2_GPS_Pin GPIO_PIN_15
#define RX2_GPS_GPIO_Port GPIOA
#define DONE_2_Pin GPIO_PIN_3
#define DONE_2_GPIO_Port GPIOB
#define DONE_1_Pin GPIO_PIN_4
#define DONE_1_GPIO_Port GPIOB
#define CHA_ISEL_Pin GPIO_PIN_5
#define CHA_ISEL_GPIO_Port GPIOB
#define SCL1_Pin GPIO_PIN_6
#define SCL1_GPIO_Port GPIOB
#define SDA1_Pin GPIO_PIN_7
#define SDA1_GPIO_Port GPIOB
#define BP_ON_Pin GPIO_PIN_8
#define BP_ON_GPIO_Port GPIOB
#define BP_SOS_Pin GPIO_PIN_9
#define BP_SOS_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */




extern u8g2_t u8g2;
extern float buffer_ADC[7];


extern uint8_t batteryLevel;

// tableau pour l'envoie des informations en UART
extern uint16_t values_ADC[7];
extern uint8_t status_GPS;
//extern uint8_t LORAWAN_STATE;
extern uint8_t alerte;
extern uint8_t son;

extern uint8_t warrning;
extern uint8_t danger;

extern char taux_H2S[7];
extern char taux_O2[7];
extern char taux_CO[7];
extern char taux_EX[7];

extern uint8_t start_Process_UART;


extern uint8_t seuil_H2S;
extern uint8_t seuil_O2;
extern uint8_t seuil_CO;
extern uint8_t seuil_EX;

extern uint8_t extinction;
struct config_data
{
	unsigned char tps_immo;
	unsigned char tps_PerteDeVerticalite;
	unsigned char tps_GPS_ON;
	unsigned char tps_GPS_OFF;
	unsigned char tps_Alarme;
	unsigned char chute_Actif;
	unsigned char malaise_Actif;
	unsigned char com_sigfox;
	unsigned char com_LoRa;
	unsigned char GPS_Actif;
	unsigned char Immo_Actif;
	unsigned char Verti_Actif;
	unsigned char Sensibilite_chute;
	unsigned char tps_chute;
	unsigned char Angle;
}c1,c_default;

#define SON				8
#define SEND			7
#define SEND30S		6
#define SEND60S		5
#define GAZ				4
#define CHUTE 		3
#define SOS 			2
#define MALAISE		1
#define NONE			0

//#define ON 								1
//#define OFF 							0

#define VME								0x03
#define VLCT							0x02
#define AUCUN							0x01

#define GAZ_H2S						1
#define GAZ_O2						2
#define GAZ_CO						3
#define GAZ_EX						4



void jumpToBootloader(void);
void vibration_LBL(uint8_t nb_de_vibration, unsigned short pause_vib, unsigned short duree_vib);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
