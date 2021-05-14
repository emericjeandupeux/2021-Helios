#include "hes_include_stm32.h"
#include "hes_gpio_h3.h"

extern UART_HandleTypeDef huart3;

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef NEMEUS_UART_PORT;

#define RAK811_UART_PORT	huart1
	
#define NEMEUS_UART_PORT	huart3	


//##############################################################
// Nemeus module 
//##############################################################

void WakeUpNemeusLS(void);

void RebootNemeusLS(int TabGen[]);

void PowerOffNemeus();

void TurnOffAllLayers(void);


//##############################################################
// LORA P2P (point to point), private Lora network
//##############################################################

void SendTestLora(void);

void SendMessLora(char buffer_Lora[]);

void ContinuousRxLora(void) ;


//RAK811

void SendTestLora811(void);

void EnableLora811(void);

void EnableLoraSend811(void);

void EnableLoraReceive811(void);

void SendMessLora811(char buffer_Lora[]);

void PingHelios_Rak811(void);


//##############################################################
// LoraWan, to Objenious or similar
//##############################################################

void SendOnLora(void);

void LoraWanOn(void);

void SendMessLoraWan(char buffer_lorawan[]);

void LoraWanAskKey(int TabGen[]);


//##############################################################
// Sigfox, to backend.sigfox (no private network possible)
//##############################################################

void SigfoxOn(void);

void SendOnMessSigfox(uint8_t b_downlink);

void SendOffMessSigfox(void);

void SendIdAskSF(void);

void SendMessSigfox(char buffer_sig[], int TabGen[]);


//##############################################################
// Gathering all data in a string
//##############################################################
		
void BuildMessAlert(char buffer_sig[], int TabGen[], float TabFloatValue[], uint32_t TabGpsTimer[]);

void BuildMessGPS(char buffer_sig[], int TabGen[], float TabFloatValue[], uint32_t TabGpsTimer[]);

void BuildMessWifi(char buffer_sig[], int TabGen[], float TabFloatValue[], uint32_t TabTimer[], char macWifi[]);

void FuncLoraMessNoGPS(char buffer_lora[], int TabGen[], float TabFloatValue[], uint32_t TabGpsTimer[]);

//##############################################################
// Misc
//##############################################################

void decimal2hexa(unsigned int decimal, char hexa[], unsigned int size_char);

void SendMess(char char_in[], UART_HandleTypeDef huart);

void SendMessWifi(char char_in[]);
