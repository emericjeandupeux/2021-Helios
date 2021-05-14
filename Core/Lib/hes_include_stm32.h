#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//#include "hes_filt.h"

#include "stm32L4xx_hal.h"


#define INITIA 0 // !! IF 0 no BLE SCREEN and GPS initialization / for developpement purpose only

#define SUEZ 0 // 1 :


//DEBUG SOUND
#define debug_sound_vibration



/* ---------- SELECT IMU -----------*/

#define DWM1001C // accelero helios v2

#define MPU6050_ADDR 0xD0	// accelero helios v3 temporary fix (blue board on DWM footprint)

#define MC3413 0x98  // accelero helios v3 (green board with RAK) on DWM footprint and v4

/*
Hard_conf[0] = 1 	MPU6050_ADDR 0xD0
Hard_conf[0] = 2 	MC3413 0x98
Hard_conf[0] = 3 	DWM1001C
 */

/* ---------- SELECT IMU -----------*/


/* ---------- SELECT DEVICE TYPE -----------*/

//#define DATI_LIEN
#define DATI

/* ---------- SELECT DEVICE TYPE -----------*/
#define TIME_BETWEEN_PING 10



#ifdef DATI_LIEN

#define BATTERYOK 			1
#define VIBOK 				1
#define BUZOK 				1

#define WIFI				0
#define RAK811 				1
#define DECA1004_OK 		0



// DMA
#define DMA_GPS_ON 			0
#define DMA_RAK_ON 			1
#define DMA_NEMEUS_ON 		0

#endif

#ifdef DATI

#define BATTERYOK 			1

#define VIBOK 				1
#define BUZOK 				1

#define WIFI				0
#define RAK811 				0
#define DECA1004_OK 		0



#define DMA_GPS_ON 			1
#define DMA_RAK_ON 			0
#define DMA_NEMEUS_ON 		1

#endif


#define BOX4GAZ 			0  // 1 : if REGAZ project ,  0 : else
#define DISPLAYCHARGHES 	1 // 1 : display HESTIAM on Init , 0 : display REGAZ on Init


#define BAT_MIN 3300
#define BAT_MAX 4100

#define TIME_BEFORE_SHUTDOWN_LOWBAT 100000

#ifdef debug
#define SEC_ONOFF_SCREEN 3600 // [s] time before power off screen 
#endif

#ifndef debug
#define SEC_ONOFF_SCREEN 	20 // [s] time before power off screen // EJ: was 20
#endif



#define NB_MS_REALERTGAZ 5000

/////////////////////////////
// for TabAlert[]
#define NONE_ALERT    0
#define ALERT_SOS     1
#define ALERT_MALAISE 2
#define ALERT_SONO    3
#define ALERT_COL     4
#define ALERT_DIST    5
#define ALERT_LOWBAT  6
#define ALERT_H2SVME  7
#define ALERT_H2SVLCT 8
#define ALERT_O2      9
#define ALERT_COVME   10
#define ALERT_COVLCT  11
#define ALERT_EX      12
#define ALERT_FALL    13

#define NB_ALERT      14  // reporting size TabAlert[]
#define NB_GAZ_BEG    7
#define NB_GAZ_END    12

/////////////////////////////
// for TabGen[]
#define ALERT_ON       0
#define GPS_ON         1 //1
#define BUZ_ON_FAST    2 
#define LED_ON_FAST    3	
#define VIB_ON_FAST    4	
#define BUZ_ON_SLOW    5 
#define LED_ON_SLOW    6	
#define VIB_ON_SLOW    7
#define SOS_PUSH_LONG  8
#define SIGFOX_SEND    9
#define FALL_DELAY    10
#define FALL_UP_DELAY 11
#define NMAXS_MALAISE 12 // c1.tps_PerteDeVerticalite * 60 * 100; // duration of malaise on sample (100 Hz) x [s] ;
#define NMAXS_IMMO    13 // c1.tps_immo * 60 * 100; // duration of immo on sample (100 Hz) x [s] ;
#define NMAXS_FALL    14 // c1.tps_chute * 100; // duration of fall on sample (100 Hz) x [s] ; 
#define NS_MALAISE    15
#define NS_IMMO       16
#define NS_FALL       17
#define ALERT_ON_PREVIOUS 18
#define I_READ_BUTTON 19
#define RE_ON_SCREEN  20
#define ON_ON         21
#define NS_ON         22
#define SOS_ON        23
#define NS_SOS        24
#define SOS_RELEACH   25
#define FALL_IND_1    26
#define FALL_IND_2    27
#define FALL_COND_1   28
#define FALL_COND_2   29  // 1
#define FALL_COND_3   30
#define FALL_COND_4   31
#define GPS_IND_BUF   32
#define GPS_START_IT  33 // 1
#define GPS_TRF_FULL  34
#define GPS_ON_PREVIOUS  35
#define TYPE_ALERT    36
#define STEP_GIRL     37 
#define STEP_GIRL_ALARM  38
#define SOS_PANIC     39
#define STATUT_GPS      40 
#define STATUT_NETWORK  41 // 1
#define BAT_VALUE       42 
#define CHARGEC         43
#define EOC             44
#define LEDR            45 
#define LEDV            46
#define LEDB            47
#define LEDR0           48
#define LEDV0           49 
#define LEDB0           50
#define STOPDEVICE      51
#define SCREENSTATE     52 // 1
#define SCREENSTATEON   53
#define FORCEOFFSCREEN  54
#define ALERT_ONLED_PREVIOUS 55
#define SIG_ALERT       56
#define GPS_GOOD        57
#define BOXNUMBER       58
#define LOCK_I2C1   	59
#define FORCE_GPS   	60
#define GPS_DATA_READY  61
#define STARTUP_OK      62
#define DECA1004_DIST   63
#define NB_SATT_FOUND   64
#define GPS_DURATION		65
#define LORA_SEND				66
#define ALERT_PENDING				67
#define LAST_LORAWAN_MSG			68
#define ID_ALERT					69
#define GGA_SENTENCE_DETECTED 		70
#define LORA_FRAME_DETECTED 		71
#define NEMEUS_STATE 				72
#define DISTANCE_DETECTED 			73
#define DATA_READABLE 				74
#define COUNT_NOACK 				75
#define SIGFOX_STATE 				76
#define LORAWAN_STATE 				77
#define SIGFOX_RSSI 				78
#define LORAWAN_RSSI 				79
#define RSSI_BEST_WIFI 				80
#define NEMEUS_AVAILABLE 			81
#define LOW_BAT 				82
#define BATT_REP 			83
#define STATUS_REP 		84
#define REP_RSSI 		85
#define GPS_REP 		86
#define RSSI_REP 		87
#define LORAP2P_SEND 	88
#define DUAL_SEND    	89
#define AVG_CURRENT 	90
#define VBAT_mV			91
//#define ALERT_SENT_WAIT_FOR_DOWNLINK 89


#define NB_GEN  			  91 // reporting size TabGen[]


/////////////////////////////
// for Flag[]
#define F_CHARGER 1
#define F_BATTERY 2
#define F_100HZ 3


#define NB_FLAG 4

/////////////////////////////
// for TabFloatValue[]
#define H2S_VALUE  0
#define O2_VALUE   1  // 21.0 
#define CO_VALUE   2
#define EX_VALUE   3
#define DB_VALUE   4
#define LATI       5
#define LONGI      6
#define TH_H2SVME  7
#define TH_H2SVLCT 8
#define TH_O2      9
#define TH_COVME   10
#define TH_COVLCT  11
#define TH_EX      12
#define O2_A  13
#define O2_B  14
#define CO_A  15
#define CO_B  16
#define EX_A  17
#define EX_B  18
#define H2S_A 19
#define H2S_B 20
#define DB_A  21
#define DB_B  22

#define NB_FLOATVALUE    23  // reporting size TabFloatValue[]

/////////////////////////////
// for TabTimer[]
#define GPS_REPEAT_START  0
#define GPS_FIRST_START   1
#define LAST_UPDATE_GPS 	2
#define ACK_TIMER		 	3
#define LAST_UPDATE_WIFI 	4
#define TIMER_LOW_BAT 	5
//#define GPS_C   1

#define NB_TIMER    6  // reporting size TabGpsTimer[]   // EJ : +1 pour LAST_UPDATE_GPS

///////////////////////////////
//// for TabGirlBoardTimer[]
//#define GIRL_TIM_PREVIOUS_READY 0
//#define GIRL_TIM_READY          1
//#define GIRL_TIM_MILLI_T        2
//#define GIRL_TIM_READY_OUT      3
//#define GIRL_TIM_MILLI_T2       4
//	
//#define NB_GIRLTIMER    5  // reporting size TabGirlBoardTimer[]	
	
/////////////////////////////
// for TabAlertAll[]
#define ALL_TIM_1   0
#define ALL_TIM_2   1
#define ALL_TIM_3   2

#define NB_ALLTIMER    3  // reporting size TabAlertAll[]

#define MAX_TAB_DIST 5


// LORAWAN_STATE
#define LW_OFF 			0 //
#define LW_WAIT_JOIN 	1 // Asked to join and waiting for an answer
#define LW_JOIN_OK 		2 // Joined but no RSSI, need to send uplink with ack
#define LW_JOINED 		3 // Joined and received RSSI

//
#define NO_ACK_PENDING		0 //
#define LW_JOIN_PENDING		1 //
#define ACK_LORA_PENDING 	2 // Asked to join and waiting for an answer
#define SF_DELAY_ON 		3 // Joined but no RSSI, need to send uplink with ack
#define ACK_SF_PENDING 		4 // Joined but no RSSI, need to send uplink with ack
#define NO_ACK_SF_RETRY 	5 // Joined but no RSSI, need to send uplink with ack
#define ACK_SF_PENDING_2 	6 // Joined but no RSSI, need to send uplink with ack


	
//#define ALERT_OFF			0 //
//#define WAIT_FOR_DOWNLINK 	1 // Asked to join and waiting for an answer
//#define DOWNLINK_RECEIVED	2 // Joined but no RSSI, need to send uplink with ack
//#define SEND_ALERT_SF		3 // Joined but no RSSI, need to send uplink with ack
//
//
//



