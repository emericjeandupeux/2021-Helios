#include "hes_include_stm32.h"
#include "hes_charger.h"
#include "hes_led.h"

void LedChargeIndic(int TabGen[]);

void CopyTabChar(uint8_t inTab1[],uint8_t outTab1[],int size);

//void SearchChar(uint8_t inTab1[], uint8_t inSearchTab[],int outTabind[], int sizeS, int size);

void TaskAlertAcc(uint8_t accy,uint16_t accres,int TabAlert[],int TabGen[]);

unsigned char bootloader(unsigned char tps_appui);
