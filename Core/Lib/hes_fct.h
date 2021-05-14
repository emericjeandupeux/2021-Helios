#include "hes_include_stm32.h"
#include "hes_charger.h"
#include "hes_led.h"

void LedChargeIndic(int TabGen[]);

void CopyTabChar(uint8_t inTab1[],uint8_t outTab1[],int size);

//void SearchChar(uint8_t inTab1[], uint8_t inSearchTab[],int outTabind[], int sizeS, int size);

void TaskAlertAcc(float angle,float accres,int TabAlert[],int TabGen[], float seuil);

unsigned char bootloader(unsigned char tps_appui);

float config_seuil(void);

void Load_configuration_value(void);
