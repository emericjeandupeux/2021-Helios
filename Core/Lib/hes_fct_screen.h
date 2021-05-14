#include "hes_include_stm32.h"
#include "hes_screen.h"
#include "hes_uart_CarteGaz.h"

extern int ReadyGirl ;

void initScreen(void);
void ScreenMessExt3s(void);
void ScreenMessExt2s(void);
void ScreenMessExt1s(void);
void ScreenMessExtOnly(void);
void ScreenMessEmpty(void);


void AdcCompute(float tab_ADC []);
void	ComputeAlerteGaz(int TabAlert[],float TabFloatValue[]);
void ComputeAdc(float TabFloatValue[],float O2Adc,float COadc,float ExAdc,float H2SAdc,float DBAdc,uint32_t TabAlertAll[],int TabGen[]);
void ComputeAdcH2S(float TabFloatValue[],float H2SAdc,uint32_t TabAlertAll[],int TabGen[]);