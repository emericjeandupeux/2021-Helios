/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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

 Universal Helios Code for Helios V2 (H3)   v21p3
 */

#define	BOX4GAZSN  3 

#define WHILEON 1 // !! IF 0 no while(1)  / for developpement purpose only

//#define ping_lorawan

#define LTAB 5
#define LTABD 4

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "../Lib/USB_CDC/usbd_cdc_if.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

// for GPS
uint8_t y_full[400];
uint16_t ar_full[400];
uint16_t arr[400];
uint8_t yy[400];
uint8_t REBOOT_FROM_WATCHDOG = 0;

uint32_t timeBeforeDMA_SF = 10 * 1000;
uint8_t dma_sf_once = 0;

//permet d'afficher un message d'alerte
uint8_t seuil_H2S = AUCUN;
uint8_t seuil_O2 = AUCUN;
uint8_t seuil_CO = AUCUN;
uint8_t seuil_EX = AUCUN;

uint32_t millis = 0;
uint32_t time_network_rep = 0;
uint8_t nb_parametre = 17;
unsigned char ID_Sigfox[8] = "NO ID";
extern struct config_data c1;
uint8_t DMA_Done = 0;

uint8_t batt_20 = 0;
uint8_t batt_15 = 0;
uint8_t batt_10 = 0;
uint8_t batt_5 = 0;
uint32_t low_bat_shutdown = 0;

uint16_t accres;
float accres2;
uint16_t accy;
float accy2;
float angle;
uint8_t once_rak = 1;
uint8_t once_gps = 1;
uint8_t once_nem = 1;

HAL_StatusTypeDef I2C1_OK = HAL_OK;

uint8_t network_state = 0;

float H2SAdc = 0;

uint8_t ping_rep_ok = 0;

#include "../Lib/hes_gpio_h3.h"
#include "../Lib/hes_bms.h"
#include "../Lib/hes_charger.h"
#include "../Lib/hes_fall.h"
#include "../Lib/hes_fonts.h"
#include "../Lib/hes_gps.h"
#include "../Lib/hes_imu.h"
#include "../Lib/hes_fct_screen.h"
#include "../Lib/hes_led.h"
#include "../Lib/hes_powersave.h"
#include "../Lib/hes_screen.h"
#include "../Lib/hes_sequencer.h"
#include "../Lib/hes_task.h"
#include "../Lib/hes_uint82bitint.h"
#include "../Lib/hes_buzvib.h"
#include "../Lib/hes_sigfoxlora.h"
#include "../Lib/dwm_api.h"
#include "../Lib/dwm1001_tlv.h"
#include "../Lib/lis2dh12_reg.h"
#include "../Lib/hes_fct.h"
#include "../Lib/hes_uart_CarteGaz.h"
//#include "../Lib/dco_display.h"
//#include "../Lib/dco_fonts.h"
//#include "../Lib/eeprom_emul.h"
//#include "../Lib/eeprom_flash.h"
#include "../Lib/hes_ee.h"
#include "../Lib/hes_properties.h"

uint8_t DUAL_STATE_LS = NO_ACK_PENDING;

unsigned char pChar1;
unsigned char pChar2;
unsigned char pChar3;

char msg_Lora[20];

uint8_t Rx_RAK811[MAXITRAK];
uint8_t Rx_bufferRAK811[MAXITRAK];

uint8_t Rx_datagps[MAXITGPS];
uint8_t Rx_Buffergps[MAXITGPS];

uint8_t Rx_Nemeus[MAXITNEMEUS];
uint8_t Rx_bufferNemeus[MAXITNEMEUS];

uint8_t Rx_data1004[MAX_1004];

uint8_t Rx_WIFI[MAXITWIFI];

char WifiName[30];

float acc[4];

__IO uint32_t ErasingOnGoing = 0;

uint8_t batteryLevel = 0;
uint8_t status_GPS = 0;
uint8_t status_Network = 0;
uint8_t alerte = 0;
uint8_t son = 0;
uint8_t extinction = 0;
uint8_t warrning = 0;
uint8_t danger = 0;
uint8_t cnt_uart1_buffer = 0;
uint8_t cnt_uart2_buffer = 0;
uint8_t cnt_uart3_buffer = 0;
uint8_t USB_In_Event = 0;

uint16_t every_100ms = 0;

uint32_t time_cnt = 2000;  // 2000 = 20 seconds

u8g2_t u8g2;

uint8_t GA_Nem = 0;

int type_buz_alert = 3;
int i_buz = 0; //del
int i_buz2 = 0; //del
int i_led = 0;

int i_read_button = 0;

uint8_t buffer6[6];
uint16_t ar[400];
uint8_t y[400];

uint16_t i = 0;

uint32_t tab_ADC_value[7];

uint32_t count_tim7 = 0;
uint8_t IT100HZ = 1;

uint8_t count_nb_join = 0;
uint8_t vib_only_once_cnt = 0;
uint8_t IMU_nodata = 0;

/*!--------DCO AJOUT----------------!*/
uint8_t ready = 0;

/*!------ END DCO AJOUT-----------!*/

volatile uint8_t Flag[NB_FLAG];
int TabGen[NB_GEN];
int TabDist[MAX_TAB_DIST];
int distCnt = 0;
int TabAlert[NB_ALERT];
uint32_t TabTimer[NB_TIMER];
float TabFloatValue[NB_FLOATVALUE];
uint32_t TabAlertAll[NB_ALLTIMER];

uint32_t AskJoinTimeLoraWan = 0;
uint32_t CheckLoraWanStatus = 0;
uint32_t CheckWifi = 0;
uint32_t alertBat = 0;
uint32_t TimeBeforeSFSent = 0;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */
	//EE_Status ee_status = EE_OK;
	int powersave = 0;

	uint32_t upperLedTab[LTAB + 2]; // Tab[0]  <= 1 for ON or 0 for OFF
	upperLedTab[LTABD + 1] = 20;		// dt1 before task 1
	upperLedTab[LTABD + 2] = 9980;	// dt2 after	task 1
	InitTaskState(upperLedTab, 2);

	uint32_t sosTab[LTAB + 1]; // Tab[0] <= 1 for ON or 0 for OFF
	sosTab[LTABD + 1] = 10;		// dt1 before task 1
	InitTaskState(sosTab, 1);

	// for REGAZ
	uint32_t ScreenTab[LTAB + 3]; // Tab[0] <= 1 for ON or 0 for OFF
	ScreenTab[LTABD + 1] = 50;	 // dt1 before task 1
	ScreenTab[LTABD + 2] = 300;	 // dt1 before task 2
	ScreenTab[LTABD + 3] = 50;	 // dt1 before task 3
	InitTaskState(ScreenTab, 3);

	uint32_t BatTab[LTAB + 1]; // Tab[0] <= 1 for ON or 0 for OFF
	BatTab[LTABD + 1] = 5000;		 // dt1 before task 1
	InitTaskState(BatTab, 1);

	uint32_t chargerTab[LTAB + 1]; // Tab[0] <= 1 for ON or 0 for OFF
	chargerTab[LTABD + 1] = 500;		// dt1 before task 1     // EJ : was 500
	InitTaskState(chargerTab, 1);

	uint32_t updateLedTab[LTAB + 1]; // Tab[0] <= 1 for ON or 0 for OFF
	updateLedTab[LTABD + 1] = 100;	 // dt1 before task 1
	InitTaskState(updateLedTab, 1);

	uint32_t Timer_screen;
	uint32_t TimerLastLoraMessage = 0;
	uint32_t TimerLastSigfoxMessage = 0;

	/*!-----DCO AJOUT----!*/
	// Pour la communication UART avec la carte Fille *
	/*!--------DCO AJOUT----------------!*/

	/*!------ END DCO AJOUT-----------!*/

	/*!-----DCO AJOUT----!*/

	/*!-----END DCO AJOUT----!*/

	/*!--------DCO AJOUT----------------!*/

	for (int i_fct = 0; i_fct < NB_ALERT; i_fct++)
	{
		TabAlert[i_fct] = 0;
	}
	for (int i_fct = 0; i_fct < NB_GEN; i_fct++)
	{
		TabGen[i_fct] = 0;
	}
	for (int i_fct = 0; i_fct < NB_TIMER; i_fct++)
	{
		TabTimer[i_fct] = 0;
	}
	for (int i_fct = 0; i_fct < NB_FLOATVALUE; i_fct++)
	{
		TabFloatValue[i_fct] = 0;
	}
	for (int i_fct = 0; i_fct < MAX_TAB_DIST; i_fct++)
	{
		TabDist[i_fct] = 0;
	}
	for (int i_fct = 0; i_fct < MAX_TAB_DIST; i_fct++)
	{
		Rx_bufferNemeus[i_fct] = 0;
	}

	//TabGirlBoardTimer[GIRL_TIM_READY_OUT] = 1 ;

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */
	/* Enable and set FLASH Interrupt priority */
	/* FLASH interrupt is used for the purpose of pages clean up under interrupt */

	/* Unlock the Flash Program Erase controller */

	/* Enable Power Control clock */

	/*!--------DCO AJOUT----------------!*/

	/*!------ END DCO AJOUT-----------!*/

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */

	MX_GPIO_Init();

	if (InOn() == 1 && bootloader(3) == 1)
	{
		GPIO_InitTypeDef GPIO_InitStruct =
		{ 0 };
		USB_DFU();
		OutDone1(0); //Stop Powersave part 1
		OutDone2(1); //Stop Powersave part 2

		/*Configure GPIO pins : PAPin PAPin */

		LedOn(0, 0, 100, TabGen);
		HAL_GPIO_DeInit(GPIOA, MOTOR_WU_Pin);
		__HAL_RCC_GPIOA_CLK_ENABLE();
		HAL_GPIO_WritePin(GPIOA, MOTOR_WU_Pin, GPIO_PIN_SET);

		GPIO_InitStruct.Pin = MOTOR_WU_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_PULLDOWN;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		jumpToBootloader();
	}
	else
	{
		HAL_MspInit();
		MX_DMA_Init();
		MX_I2C1_Init();
		MX_I2C2_Init();
		MX_USART1_UART_Init();
		MX_USART2_UART_Init();
		MX_USART3_UART_Init();
		MX_TIM7_Init();
		MX_TIM16_Init();
		MX_IWDG_Init();
		Hes_USB_Config_Mode();
	}

	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	HAL_GPIO_WritePin(GAZ_WU_GPIO_Port, GAZ_WU_Pin, GPIO_PIN_SET);
	OuChaIsel(0);

	OutDone1(0); //Stop Powersave part 1
	OutDone2(1); //Stop Powersave part 2
	HAL_Delay(1);
	OutLedWu(1);

	TabGen[GPS_DURATION] = 10;

	LedChargeIndic(TabGen);

	if (RCC->CSR & 1 << RCC_CSR_IWDGRSTF_Pos)
	{

		__HAL_RCC_CLEAR_RESET_FLAGS();
		OutDone1(0); //Stop Powersave part 1
		OutDone2(1); //Stop Powersave part 2

		REBOOT_FROM_WATCHDOG = 1;
	}
	else
		powersave = PowerSave();
	//RCC_GetFlagStatus(RCC_FLAG_IWDGRST);

	//Chargement config
	default_value();
	Load_configuration_value();
	LoadProperties();
	//Démarrage Nemeus et enregistrement/chargement de l'Id_sigfox
	Load_ID_Sigfox(AskSigFox_ID());

	TabGen[NMAXS_MALAISE] = c1.tps_PerteDeVerticalite * 60 * 100; // duration of malaise on sample (100 Hz) x [s] ;
	TabGen[NMAXS_IMMO] = c1.tps_immo * 60 * 100; // duration of immo on sample (100 Hz) x [s] ;
	TabGen[NMAXS_FALL] = c1.tps_chute * 100; // duration of fall on sample (100 Hz) x [s] ;
	TabGen[FALL_COND_2] = 1;
	TabGen[GPS_START_IT] = 1;
	TabGen[TYPE_ALERT] = NONE_ALERT;

	TabGen[BAT_VALUE] = 100;
	TabGen[SCREENSTATE] = 1;

	if (powersave == 0)
	{
		HAL_Delay(2);
		LedOn(0, 0, 50, TabGen);

#ifndef debug_sound_vibration
		if (REBOOT_FROM_WATCHDOG == 0)
			PowerBuzVib(100);
#endif

	}

	HAL_TIM_Base_Start_IT(&htim7);

	ScreenOn();
	display_Init(!REBOOT_FROM_WATCHDOG);
	if (BOX4GAZ == 1)
	{
		HAL_GPIO_WritePin(GAZ_WU_GPIO_Port, GAZ_WU_Pin, GPIO_PIN_RESET);
	}

	if (c1.GPS_Actif == 0)
	{
		GpsStop();
	}
	else
	{
		TabGen[GPS_ON] = 1;
	}

	// IMU INITIALISATION

	Init_IMU();

	/*!--------DCO AJOUT----------------!*/

	OutDwmRst(0);
	OutDwmWu(0);

	/*!--------DCO AJOUT----------------!*/

	if (SUEZ == 0)
	{
		if (DMA_Done == 0)
		{
			WakeUpNemeusLS();
			RebootNemeusLS(TabGen);
		}

		if (c1.com_sigfox == 1 && TabGen[SIGFOX_STATE] == 0 && c1.com_LoRa == 0)
		{
			SigfoxOn();
			TimerLastSigfoxMessage = HAL_GetTick();
			TabGen[SIGFOX_STATE] = 1;
			SendOnMessSigfox(!REBOOT_FROM_WATCHDOG);
			DUAL_STATE_LS = ACK_SF_PENDING;
		}
		else if (c1.com_LoRa == 1)
		{
			if (c1.com_sigfox == 1)
				SigfoxOn();
			HAL_Delay(1000);

			LoraWanOn();

			AskJoinTimeLoraWan = HAL_GetTick();
			TabGen[LORAWAN_STATE] = LW_WAIT_JOIN;
			DUAL_STATE_LS = LW_JOIN_PENDING;
		}
		TimerLastSigfoxMessage = HAL_GetTick();
	}

	if (c1.loraP2P == 1)
	{
		if (RAK811 == 1)
		{
			HAL_UART_Receive_DMA(&huart1, Rx_RAK811, MAXITRAK);
			OutDwmRst(1);
			HAL_Delay(500);

			if (REBOOT_FROM_WATCHDOG == 0)
			{
				EnableLoraSend811();
				SendTestLora811();
			}
			EnableLoraReceive811();
		}
		else
		{
			if (REBOOT_FROM_WATCHDOG == 0)
			{
				SendTestLora();
				ContinuousRxLora();
			}
		}
	}

	HAL_TIM_Base_Start_IT(&htim7);
	HAL_Delay(1);
	if (c1.GPS_Actif == 1)
	{
		TabGen[GPS_ON] = 1;
	}
	Timer_screen = HAL_GetTick();

#ifndef debug_sound_vibration
	if (REBOOT_FROM_WATCHDOG == 0)
		PowerBuzVib(100);
	//PowerBuz(100);
#endif

	timeBeforeDMA_SF = HAL_GetTick();

	if (WIFI == 1)
	{
		//SendMessWifi("ATE0\r\n");
		SendMessWifi("AT+CWLAP\r\n"); // CHANGE SPEED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		TabGen[RSSI_BEST_WIFI] = -200;
		sprintf(WifiName, "%s", "NoName");
		CheckWifi = HAL_GetTick();
		alertBat = HAL_GetTick();
		//WifiName "NoName";
	}

	if (DMA_GPS_ON == 1)
	{
		HAL_UART_Receive_DMA(&huart2, Rx_datagps, MAXITGPS);
	}
	else if (SUEZ == 0)
		HAL_UART_Receive_IT(&huart2, &pChar2, 1); // gps

	if (DMA_RAK_ON == 1)
	{
		HAL_UART_Receive_DMA(&huart1, Rx_RAK811, MAXITRAK);
	}

	if ((DMA_NEMEUS_ON) == 1 && (DMA_Done == 0))
	{
		HAL_UART_Receive_DMA(&huart3, Rx_Nemeus, MAXITNEMEUS);
	}

	/* ----------------------------------WHILE BEGIN---------------------------------------------*/

	while (1)
	{

		uint32_t Time_Now = HAL_GetTick();
		millis = HAL_GetTick();

		HAL_IWDG_Refresh(&hiwdg);

		if (SUEZ == 1 || WIFI == 1)
			HAL_UART_Receive_IT(&huart1, &pChar1, 1);  // 1004

		if (SUEZ == 1)
		{
			ComputeAdcH2S(TabFloatValue, H2SAdc, TabAlertAll, TabGen);
			//ComputeAdc(TabFloatValue,O2Adc,COadc,ExAdc,H2SAdc,DBAdc,TabAlertAll,TabGen);
			ComputeAlerteGaz(TabAlert, TabFloatValue);
		}

// ##########################GPS################################################

		if (TabGen[GPS_GOOD] == 1)
		{
			if (millis - TabTimer[LAST_UPDATE_GPS] < 15 * 60 * 1000)
				TabGen[GPS_DURATION] = c1.tps_GPS_ON;
		}

		if (c1.GPS_Actif == 1) // GPS IS ENABLED
		{
			GPS_Management();
		}

// ########################## GPS END ################################################

// ########################## MESSAGE MANAGEMENT #####################################

		if (SUEZ == 1 && TabGen[DISTANCE_DETECTED] == 1)
			TabGen[DISTANCE_DETECTED] = 0;

		if (WIFI == 1)
		{
			if ((millis - CheckWifi) > 10 * 1000)
			{
				SendMessWifi("AT+CWLAP\r\n");
				TabGen[RSSI_BEST_WIFI] = -200;
				//BuildMessWifi(bufferWifi, TabGen, TabFloatValue,  TabTimer, WifiName);
				CheckWifi = HAL_GetTick();
			}
		}

		if (c1.loraP2P == 1)
		{
			TaskSendLoraNoGPS(TabGen, TabFloatValue, TabTimer);
		}

		if (c1.com_LoRa == 1)
		{ 	// RSSI MANAGEMENT
			if ((DUAL_STATE_LS == NO_ACK_SF_RETRY) || // Downlink failed for sigfox, try again
					(((HAL_GetTick() - AskJoinTimeLoraWan) > 1 * 15 * 1000)
							&& (DUAL_STATE_LS == SF_DELAY_ON)) || // If Lora with ACK ok -> Sigfox msg in 10 seconds
					(((HAL_GetTick() - AskJoinTimeLoraWan) > 1 * 30 * 1000)
							&& ((DUAL_STATE_LS == ACK_LORA_PENDING)
									|| (DUAL_STATE_LS == LW_JOIN_PENDING)))) // If Lora with ACK not ok 30 seconds after start, Sigfox msg
			{
				//TIME TO SEND SIGFOX ON MESSQGE TO GET RSSI
				if (DUAL_STATE_LS == NO_ACK_SF_RETRY
						|| DUAL_STATE_LS == LW_JOIN_PENDING)
				{
					RebootNemeusLS(TabGen);
					DUAL_STATE_LS = ACK_SF_PENDING_2;
					PowerVib(100);

					SigfoxOn();
				}
				else
					DUAL_STATE_LS = ACK_SF_PENDING;
				SendOnMessSigfox(1);

				AskJoinTimeLoraWan = HAL_GetTick();

			}

			if (((HAL_GetTick() - AskJoinTimeLoraWan) > 1 * 30 * 1000)
					&& (DUAL_STATE_LS == ACK_SF_PENDING_2))
			{ // WAITING FOR DL SIGFOX 2 BUT NEVER RECEIVED
				LoraWanOn();
				DUAL_STATE_LS = NO_ACK_PENDING;
			}

			if (TabGen[ALERT_PENDING] == 1 && TabGen[LORA_SEND] == 1)
			{
				TaskSendLoraWan(TabGen, TabFloatValue, TabTimer);
				//TimerLastLoraMessage = HAL_GetTick();
			}
		}

		if (TabGen[DUAL_SEND] == 1)
			TaskSendDUAL(TabGen, TabFloatValue, TabTimer, WifiName);

		if (c1.com_sigfox == 1)
		{
			if (TabGen[ALERT_PENDING] == 1 && TabGen[SIGFOX_SEND] == 1)
				TaskSendSigfox(TabGen, TabFloatValue, TabTimer, WifiName);
		}

#ifdef ping_lorawan
		if (c1.com_LoRa == 1)
		{
			if ( (HAL_GetTick() - TimerLastLoraMessage) > 5 * 60 * 1000)
			{
				TabGen[LORA_SEND] = 1;
				TimerLastLoraMessage = HAL_GetTick();
			}
		}			
		#endif			

		// ########################## MESSAGE MANAGEMENT END ##############################
		Task_USB_Configuration();

		TaskExtButton(TabGen);

		TaskFallTest(TabAlert, TabGen);

		TaskUpdateUpperLed(updateLedTab, TabGen); // bug +

		TaskLedBlinking(upperLedTab, TabGen);

		TaskOnScreen(TabGen, &Timer_screen);

		TaskBigScreen(ScreenTab, TabAlert, TabGen, TabFloatValue, TabTimer,
				TabAlertAll, WifiName);

		if (TabGen[CHARGEC] == 0)
			TaskAlertAll(TabAlert, TabGen, TabAlertAll, TabFloatValue);

		Battery_Charger_Management();

//		if(Time_Now % 1000 == 0)
//		{
//			Flag[F_CHARGER] = 1;
//			Battery_Charger_Management();
//		}

		// EVERY 100 HZ
		if (Flag[F_100HZ] == 1)
		{

			Flag[F_100HZ] = 0;

			if (TabGen[ALERT_ON] == 0)
			{
				if (TabGen[LOCK_I2C1] == 0)  // check I2C1 is available
				{
					Measure_IMU(buffer6); // read 6x register of IMU

					TaskAlertAcc(angle, accres, TabAlert, TabGen, config_seuil()); // check Alert for Malaise and Immo

					TaskFallManager(ar, y, accres, accy, TabGen);
				}
			}
		}

		if (c1.loraP2P == 1)
		{
			if (DMA_RAK_ON == 1)
			{
				if (Time_Now % 1000 == 0 && once_rak == 1)
				{
					once_rak = 0;
					uint8_t i = 0;
					uint8_t buffer[MAXITRAK] =
					{ 0 };

					for (int cnt = 0; cnt < MAXITRAK; cnt++)
						buffer[cnt] = Rx_RAK811[cnt];

					//strcpy(buffer, Rx_RAK811);
					while (i < MAXITRAK)
					{
						if (buffer[i] == 'a')
						{
							uint8_t y = 0;
							Rx_bufferRAK811[y++] = buffer[i++];

							for (y; y < MAXITRAK; y++)
							{
								if (buffer[i] != '\r')
								{
									if (i == MAXITRAK && y < MAXITRAK)
										i = 0; // wrapping the circular buffer

									Rx_bufferRAK811[y] = buffer[i++];
								}
								else
								{
									for (y; y < MAXITRAK; y++)
									{
										Rx_bufferRAK811[y] = 0;
									}
									i = MAXITRAK;
									y = MAXITRAK;
								}
							}
						}
						i++;
					}
					Task_Read_Incoming_Rak();
				}
				else
					once_rak = 1;
			}
			Repeater_Link_Management();
		}

		if (DMA_GPS_ON == 1 && c1.GPS_Actif == 1)
		{
			uint8_t buffer[MAXITGPS] =
			{ 0 };
			if (Time_Now % 1000 == 0 && once_gps == 1)
			{
				once_gps = 0;
				uint8_t i = 0;
				for (uint8_t y = 0; y < MAXITGPS; y++)
				{
					buffer[y] = Rx_datagps[y];
				}

				while (i < MAXITGPS)
				{
					if (buffer[i] == '$')
					{
						uint8_t y = 0;
						Rx_Buffergps[y++] = buffer[i++];

						for (y; y < MAXITGPS; y++)
						{
							if (buffer[i] != '\r')
							{
								if (i == MAXITGPS && y < MAXITGPS)
									i = 0; // wrapping the circular buffer

								Rx_Buffergps[y] = buffer[i++];
							}
							else
							{
								for (y; y < MAXITGPS; y++)
								{
									Rx_Buffergps[y] = 0;
									i = MAXITGPS;
								}
							}
						}
					}
					i++;
				}
				TaskGPS(Rx_Buffergps, TabGen, TabTimer, TabFloatValue);

				for (uint8_t y = 0; y < MAXITGPS; y++)
				{
					Rx_datagps[y] = 0;
					Rx_Buffergps[y] = 0;
				}
			}
			else
				once_gps = 1;
		}

		if (DMA_NEMEUS_ON == 1)
		{
			uint8_t save_pos_start = MAXITNEMEUS;
			uint8_t save_pos_end = MAXITNEMEUS;
			uint8_t copy = 0;

			if (Time_Now % 1000 == 0 && once_nem == 1)
			{
				once_nem = 0;
				uint8_t i = 0;
				uint8_t buffer[MAXITNEMEUS] =
				{ 0 };
				for (uint8_t y = 0; y < MAXITNEMEUS; y++)
				{
					buffer[y] = Rx_Nemeus[y];
				}

				while (i < MAXITNEMEUS)
				{
					if (buffer[i] == '+')
					{
						if (((i < MAXITNEMEUS - 1) && (buffer[i + 1] == 'M'))
								|| ((i == MAXITNEMEUS - 1) && (buffer[0] == 'M')))
						{
							if (buffer[i + 6] == 'R' || buffer[i + 14] == ','
									|| GA_Nem == 1)
							{
								copy = 1;
								if (GA_Nem != 0)
									save_pos_start = i;
							}
						}

						if (((i < MAXITNEMEUS - 1) && (buffer[i + 1] == 'G'))
								|| ((i == MAXITNEMEUS - 1) && (buffer[0] == 'G')))
						{
							GA_Nem = 1;
							save_pos_start = i;
							if (i + 16 < 100 && buffer[i + 16] == '\r')
							{
								save_pos_end = i + 16;
							}
						}
					}
					if (buffer[i] == 'R')
					{
						if (buffer[i + 1] == 'R' || buffer[i - 1] == 'E')
						{
							if (buffer[i - 11] == 'S' && buffer[i - 10] == 'F')
							{
								//ERROR: End of SF Reception windows
								copy = 2;
								save_pos_start = i;
								if (DUAL_STATE_LS == ACK_SF_PENDING)
									DUAL_STATE_LS = NO_ACK_SF_RETRY;

							}
						}

						if (((i < MAXITNEMEUS - 1) && (buffer[i + 1] == 'C'))
								|| ((i == MAXITNEMEUS - 1) && (buffer[0] == 'C')))
						{
							copy = 1;
							i = i - 5;
							save_pos_start = i;
						}
					}

					if (copy == 1)
					{
						uint8_t y = 0;
						Rx_bufferNemeus[y++] = buffer[i++];

						for (y; y < MAXITNEMEUS; y++)
						{
							if (buffer[i] != '\r')
							{
								if (i == MAXITNEMEUS && y < MAXITNEMEUS)
									i = 0; // wrapping the circular buffer

								Rx_bufferNemeus[y] = buffer[i++];
							}
							else
							{
								save_pos_end = i;
								for (y; y < MAXITNEMEUS; y++)
								{
									Rx_bufferNemeus[y] = 0;
								}
								i = MAXITNEMEUS;
								y = MAXITNEMEUS;
							}
						}
					}
					i++;
				}
				if (copy == 1)
					Task_Read_Nemeus();

				if (copy == 1 || copy == 2)
				{
					for (uint8_t y = save_pos_start; y < save_pos_end; y++)
					{
						Rx_Nemeus[y] = 0;
					}
				}
			}
			else
				once_nem = 1;
		}
	}
	//}
	/* USER CODE END WHILE */
	/* USER CODE BEGIN 3 */

	/* USER CODE END 3 */
}

/* ----------------------------------WHILE END---------------------------------------------*/

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct =
	{ 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct =
	{ 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit =
	{ 0 };

	/** Configure LSE Drive Capability
	 */
	HAL_PWR_EnableBkUpAccess();
	__HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48
			| RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE
			| RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSICalibrationValue = 0;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
	RCC_OscInitStruct.PLL.PLLM = 1;
	RCC_OscInitStruct.PLL.PLLN = 16;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1
			| RCC_PERIPHCLK_USART2 | RCC_PERIPHCLK_USART3 | RCC_PERIPHCLK_I2C1
			| RCC_PERIPHCLK_I2C2 | RCC_PERIPHCLK_USB;
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
	PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
	PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
	PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
	PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
		Error_Handler();
	}
	/** Configure the main internal regulator output voltage
	 */
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
	{
		Error_Handler();
	}
	/** Enable MSI Auto calibration
	 */
	HAL_RCCEx_EnableMSIPLLMode();
}

/* USER CODE BEGIN 4 */
// ISR function for Timer 7, every 10 ms
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if (htim->Instance == htim7.Instance)
	{

// loop control			
		if (count_tim7 < time_cnt)    // 1000 = 10 seconds,  100 = 1 second
			count_tim7++;
		else
			count_tim7 = 0;

		if (count_tim7 % 10 == 2)
			every_100ms = 1; // not used

		if (count_tim7 == 400)      // every 20 seconds, 0 second after startup
		{
			if (BATTERYOK == 1)
				Flag[F_BATTERY] = 1;
		}
		else if (count_tim7 % 250 == +1) // every 20 seconds, 10 seconds after startup // 2
		{
			if (BATTERYOK == 1)
				Flag[F_CHARGER] = 1;
		}
//		else if (count_tim7 % 1000 == 2) // every 1 s
//		{
//			//SendMess("AT+MAC=?\n");
//			//SendMessLora();
//
//		}
		else
		{
			TaskButtonManager(TabGen, TabAlert);
			TaskAlertManager(TabGen, &i_led);

			Flag[F_100HZ] = 1;
		}
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{ // fonction d'interruption qui s'execute chaque 50 caract�re qui se mettent dans Rx_datagps[]
//TaskUARTMessage(TabGen, WifiName, TabDist, TabTimer, huart);
}

/**
 * @brief  FLASH end of operation interrupt callback.
 * @param  ReturnValue: The value saved in this parameter depends on the ongoing procedure
 *                  Mass Erase: Bank number which has been requested to erase
 *                  Page Erase: Page which has been erased
 *                    (if 0xFFFFFFFF, it means that all the selected pages have been erased)
 *                  Program: Address which was selected for data program
 * @retval None
 */
void HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue)
{
	/* Call CleanUp callback when all requested pages have been erased */
	if (ReturnValue == 0xFFFFFFFF)
	{
		EE_EndOfCleanup_UserCallback();
	}
}

/**
 * @brief  Clean Up end of operation interrupt callback.
 * @param  None
 * @retval None
 */
void EE_EndOfCleanup_UserCallback(void)
{
	ErasingOnGoing = 0;

}

void WakeUpNemeus_forID(void)
{
	WakeUpNemeusLS();
	RebootNemeusLS(TabGen);
	HAL_UART_Receive_DMA(&huart3, Rx_Nemeus, MAXITNEMEUS);
	DMA_Done = 1;
	HAL_Delay(200);
}

void vibration_LBL(uint8_t nb_de_vibration, unsigned short pause_vib,
		unsigned short duree_vib)
{
	while (nb_de_vibration > 0)
	{
		PowerVib(duree_vib);
		HAL_Delay(pause_vib);
		nb_de_vibration--;
	}
}

#define DFU_BOOTLOADER_ADD 0x1FFF0000U

extern PCD_HandleTypeDef hpcd;
typedef void (*pFunction)(void);
pFunction JumpToApplication;
uint32_t JumpAddress;

void jumpToBootloader(void)
{

	/* Test if user code is programmed starting from address 0x0800C000 */
	/*if(((*(__IO uint32_t*)DFU_BOOTLOADER_ADD) & 0x2FFE0000 ) == 0x20000000)*/
	/* Jump to user application */

	HAL_RCC_DeInit();

	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;

	__disable_irq();

	__HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();

	JumpAddress = *(__IO uint32_t*) (DFU_BOOTLOADER_ADD + 4);
	JumpToApplication = (pFunction) JumpAddress;

	/* Initialize user application's Stack Pointer */
	__set_MSP(*(__IO uint32_t*) 0x08000000);
	JumpToApplication();
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	   tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
