#include "hes_include_stm32.h"
#include "hes_sequencer.h"
#include "hes_led.h"
#include "hes_screen.h"
#include "hes_charger.h"
#include "hes_fall.h"
#include "hes_bms.h"
#include "hes_buzvib.h"
#include "hes_uart_CarteGaz.h"
#include "dco_display.h"
#include "hes_gps.h"
#include "hes_sigfoxlora.h"

#define MAXITNEMEUS 200
#define MAXITWIFI 70
#define MAXITGPS 100
#define MAX_1004 7
#define MAXITRAK 100

#define SOS_TOUCH 1
#define ON_TOUCH 2

#define NBECHBRUTALFALL 1000 // entre 300 et 500


#define XZERO 10 //X offset for battery indicator
#define YZERO 3 //Y offset for battery indicator
#define BATTHEIGHT 6 // hauteur for battery indicator
#define BATTWIDTH 12  // largeur for battery indicator

extern uint8_t y_full[400];
extern uint16_t ar_full[400];
extern uint16_t arr[400];
extern uint8_t yy[400];
extern int ReadyGirl  ;
extern uint8_t Rx_Buffergps[MAXITGPS];


void TaskClearScreen(void);

void TaskBigScreen(uint32_t Tab[], int TabAlert[], int TabGen[], float TabFloatValue[], uint32_t TabGpsTimer[], uint32_t TabAlertAll[], char name[]);

void TaskLedBlinking(uint32_t Tab[], int TabGen[]);

void TaskUpdateUpperLed(uint32_t Tab[], int TabGen[]);

//void TaskCharger(uint32_t Tab[], int TabGen[]);
void TaskCharger(int TabGen[]);

//void TaskReadBat(uint32_t Tab[], int TabGen[]);
void TaskReadBat(int TabGen[]);

void TaskExtButton(int TabGen[]);

void TaskFallTest(int TabAlert[], int TabGen[]);

void TaskAlertAll(int TabAlert[], int TabGen[], uint32_t TabAlertAll[], float TabFloatValue[]);

void TaskOnScreen(int TabGen[], uint32_t * Timer_screen);

void TaskGPS(uint8_t RxI[], int TabGen[], uint32_t TabGpsTimer[], float TabFloatValue[]);

void TaskSendMessage(int TabGen[], float TabFloatValue[], uint32_t TabTimer[], char WifiName[]);

void TaskSendSigfox(int TabGen[], float TabFloatValue[], uint32_t TabTimer[], char WifiName[]);

void TaskSendDUAL(int TabGen[], float TabFloatValue[], uint32_t TabTimer[],	char WifiName[]);

void TaskSendLora(int TabGen[], float TabFloatValue[], uint32_t TabGpsTimer[]);

void TaskSendLoraWan(int TabGen[], float TabFloatValue[], uint32_t TabGpsTimer[]);

void TaskButtonManager(int TabGen[], int TabAlert[]);

void TaskAlertManager(int TabGen[], int * i_led);

void TaskFallManager(uint16_t ar[], uint8_t y[], uint16_t accres, uint8_t accy, int TabGen[]);

void TaskUARTMessage(int TabGen[], char WifiName[], int TabDist[], uint32_t TabTimer[], UART_HandleTypeDef *huart);

void TaskSendLoraNoGPS(int TabGen[], float TabFloatValue[], uint32_t TabGpsTimer[]);

void Task_Read_Nemeus(void);

void Task_Read_Incoming_Rak(void);

void Repeater_Link_Management(void);

void Battery_Charger_Management(void);

void GPS_Management(void);

void Task_USB_Configuration(void);

void TaskReadGaz(uint32_t Tab[], float *gazFloatLevel, float *COFloatLevel, float h2sOffset, float h2sfactor,ADC_HandleTypeDef *hadc1);
