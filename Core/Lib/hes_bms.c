
#include "hes_bms.h"

void ChargerSend(uint8_t *pData, uint16_t Size) {
  //uint16_t DevAddress;
  //DevAddress = 0x47 << 1;
  HAL_I2C_Master_Transmit(&BMS_I2C_PORT, 0x47, pData, Size, 10);
}

void ChargerRec(uint8_t *pData, uint16_t Size) {
  uint16_t DevAddress;
  DevAddress = 0x47 << 1;
  HAL_I2C_Master_Receive(&BMS_I2C_PORT, DevAddress, pData, Size, 10);
}

