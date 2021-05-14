#include "hes_include_stm32.h"
#include "hes_screen.h"
#include "lis2dh12_reg.h"

extern I2C_HandleTypeDef hi2c1;

extern I2C_HandleTypeDef IMU_I2C_PORT;
	
#define IMU_I2C_PORT	hi2c1	


int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp,
                              uint16_t len);

int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);

void Init_IMU(void);

void Measure_IMU(uint8_t buffer6[]);

void imuMsr2floatG_y_bit_res16bit(uint8_t buffer6[]) ;

void imuMsr2floatG_HeliosV1(float acc[],uint8_t buffer6[],int nbBit,int scale);

void printScreen(char input[]);

char * itoa (int value, char *result, int base);

typedef union{
  int16_t i16bit[3];
  uint8_t u8bit[6];
} axis3bit16_t;

typedef union{
  int16_t i16bit;
  uint8_t u8bit[2];
} axis1bit16_t;
