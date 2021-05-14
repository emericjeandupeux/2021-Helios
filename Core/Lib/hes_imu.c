#include "hes_imu.h"
#include "hes_properties.h"
#include <math.h>

/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive register to write
 *
 */
int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
	if (handle == &hi2c1)
	{
		/* Write multiple command */
		reg |= 0x80;
		HAL_I2C_Mem_Write(handle, LIS2DH12_I2C_ADD_L, reg,
		I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
	}
	return 0;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that store the data read
 * @param  len       number of consecutive register to read
 *
 */
int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len)
{
	if (handle == &hi2c1)
	{
		/* Read multiple command */
		reg |= 0x80;
		HAL_I2C_Mem_Read(handle, LIS2DH12_I2C_ADD_L, reg,
		I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
	}
	return 0;
}

// MPU6050_ADDR
#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75

// MC3413
#define MC_PWR_MGMT_1_REG 0x07
#define MC_SMPLRT_DIV_REG 0x08
#define MC_OUTCFG_REG 0x20
#define MC_ACCEL_XOUT_REG 0x0D

extern uint16_t accres;
extern float accres2;
extern uint16_t accy;
extern float accy2;
extern HAL_StatusTypeDef I2C1_OK;

extern uint8_t IMU_nodata;

void Init_IMU(void)
{

	IMU_nodata = 0;

	// MC3413
	if (Hard_conf[0] == '2')
	{
		uint8_t check = 0;
		uint8_t Data;

		Data = 0x00; // switch to standby mode be able to write in the registers
		HAL_I2C_Mem_Write(&hi2c1, MC3413, MC_PWR_MGMT_1_REG, 1, &Data, 1, 1000);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register // gyro
		Data = 0x09;
		HAL_I2C_Mem_Write(&hi2c1, MC3413, MC_SMPLRT_DIV_REG, 1, &Data, 1, 1000);

		Data = 0x23; // 0xX3 : 10 bits , 0x12 : 8 bits, 0x00 : 6 bits
		HAL_I2C_Mem_Write(&hi2c1, MC3413, MC_OUTCFG_REG, 1, &Data, 1, 1000);

		//HAL_I2C_Mem_Read (&hi2c1, MPU3413_ADDR, PWR_MGMT_1_REG, 1, &check, 1, 1000);
		Data = 0x01; // goes in wake state, normal behaviour, config is already done
		HAL_I2C_Mem_Write(&hi2c1, MC3413, MC_PWR_MGMT_1_REG, 1, &Data, 1, 1000);
	}

	//MPU6050_ADDR
	if (Hard_conf[0] == '1')
	{
		uint8_t check;
		uint8_t Data;

		// check device ID WHO_AM_I

		HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1,
				1000);

		//if (check == 104)  // 0x68 will be returned by the sensor if everything goes well
		//{
		// power management register 0X6B we should write all 0's to wake the sensor up
		Data = 0;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1,
				1000);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register // gyro
		Data = 0x07;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1,
				1000);

		// Set accelerometer configuration in ACCEL_CONFIG Register
		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> � 4g
		Data = 0x01;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1,
				1000);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 250 �/s
		//Data = 0x00;
		//HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, 1000);
		//}
	}

	//DWM1001C
	if (Hard_conf[0] == '3')
	{

		// HAL_I2C_Mem_Read(&hi2c1,0x33,0x0F, 1, &buffer_acc, 1, 10);

		uint8_t buffer2[2];
		buffer2[0] = 0x20;
		buffer2[1] = 0x7F;
		HAL_I2C_Master_Transmit(&hi2c1, 0x32, buffer2, 2, 20); // 0x32

		buffer2[0] = 0x23;
		buffer2[1] = 0x18;
		HAL_I2C_Master_Transmit(&hi2c1, 0x32, buffer2, 2, 20); // x032
	}
}

extern uint8_t IMU_Count = 0;

void Measure_IMU(uint8_t buffer6[])
{
	if (I2C1_OK == HAL_OK)
	{

		// MC3413
		if (Hard_conf[0] == '2')
		{
			I2C1_OK = HAL_I2C_Mem_Read(&hi2c1, MC3413, 0x0D, 1, &buffer6[0], 1,
					10); // xMSB
			//HAL_I2C_Mem_Read(&hi2c1,0x33,0x2A, 1, &buffer6[2], 1, 10);   // yLSB
			I2C1_OK = HAL_I2C_Mem_Read(&hi2c1, MC3413, 0x0F, 1, &buffer6[2], 1,
					10); // yMSB
			//HAL_I2C_Mem_Read(&hi2c1, MPU3413_ADDR, 0x12, 1, &buffer6[4], 1, 10);   // zLSB
			I2C1_OK = HAL_I2C_Mem_Read(&hi2c1, MC3413, 0x11, 1, &buffer6[4], 1,
					10); // zMSB
		}

		//MPU6050_ADDR
		if (Hard_conf[0] == '1')
		{
			uint8_t Rec_Data[6];

			int16_t Accel_X_RAW = 0;
			int16_t Accel_Y_RAW = 0;
			int16_t Accel_Z_RAW = 0;

			I2C1_OK = HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, ACCEL_XOUT_H_REG,
					1, buffer6, 6, 1);

			Accel_X_RAW = (int16_t) (Rec_Data[0]);   //<< 8 | Rec_Data [1]);
			Accel_Y_RAW = (int16_t) (Rec_Data[2]);   //<< 8 | Rec_Data [3]);
			Accel_Z_RAW = (int16_t) (Rec_Data[4]);   //<< 8 | Rec_Data [5]);
		}

		//buffer6

		/*** convert the RAW values into acceleration in 'g'
		 we have to divide according to the Full scale value set in FS_SEL
		 I have configured FS_SEL = 0. So I am dividing by 16384.0
		 for more details check ACCEL_CONFIG Register              ****/

		//DWM1001C
		if (Hard_conf[0] == '3')
		{
			//HAL_I2C_Mem_Read(&hi2c1,0x33,0x28, 1, &buffer6[0], 1, 10);   // xLSB
			I2C1_OK = HAL_I2C_Mem_Read(&hi2c1, 0x33, 0x29, 1, &buffer6[1], 1,
					10); // xMSB//  HAL_I2C_Mem_Read(&hi2c1,0x33,0x29, 1, &buffer6[1], 1, 10);   // xMSB
			//HAL_I2C_Mem_Read(&hi2c1,0x33,0x2A, 1, &buffer6[2], 1, 10);   // yLSB
			I2C1_OK = HAL_I2C_Mem_Read(&hi2c1, 0x33, 0x2B, 1, &buffer6[3], 1,
					10);   // yMSB
			//HAL_I2C_Mem_Read(&hi2c1,0x33,0x2C, 1, &buffer6[4], 1, 10);   // zLSB
			I2C1_OK = HAL_I2C_Mem_Read(&hi2c1, 0x33, 0x2D, 1, &buffer6[5], 1,
					10);   // zMSB
		}
	}
	else
	{
		HAL_Delay(10);
		I2C1_OK = HAL_OK;
	}

//acceleration_mg[0]  = ((float)	(((int8_t) buffer6[1]))) / 32; 	
//acceleration_mg[1]  = ((float)	(	((int8_t) buffer6[3])) )/ 32; 		
//acceleration_mg[2]  = ((float)	(	((int8_t) buffer6[5]))) / 32; 	

	if (IMU_Count < 200 && IMU_nodata < 100)
	{
		IMU_Count++;
		if (buffer6[0] == 0 && buffer6[1] == 0 && buffer6[2] == 0
				&& buffer6[3] == 0 && buffer6[4] == 0 && buffer6[5] == 0)
			IMU_nodata++;
	}
	imuMsr2floatG_y_bit_res16bit(buffer6); // compute norm of acceleration and Y axis acceleation

}

extern float acc[4];
extern float angle;
float absLBL(float a)
{
	a = a >= 0 ? a : -a;
	return a;
}

float Degrees(double Radian)
{
	return (Radian * 180) / 3.1415;
}

void imuMsr2floatG_y_bit_res16bit(uint8_t buffer6[])
{
	//MPU6050_ADDR
	if (Hard_conf[0] == '1')
	{
		acc[0] = ((float) (((int8_t) buffer6[0]))) / 64;
		acc[1] = ((float) (((int8_t) buffer6[2]))) / 64;
		acc[2] = ((float) (((int8_t) buffer6[4]))) / 64;

		accy2 = absLBL(acc[0]);
		accy = (uint16_t) (((acc[0]) + 4) * 255) / 8;  // y to top

		double ang = absLBL(acc[0]) / absLBL(acc[2]);
		angle = Degrees(atan(ang));
	}

	// MC3413
	if (Hard_conf[0] == '2')
	{
		acc[0] = ((float) (((int8_t) buffer6[0]))) / 64;
		acc[1] = ((float) (((int8_t) buffer6[2]))) / 64;
		acc[2] = ((float) (((int8_t) buffer6[4]))) / 64;

		accy2 = absLBL(acc[0]);
		accy = (uint16_t) (((-acc[0]) + 4) * 255) / 8;  // y to top

		double ang = absLBL(acc[0]) / absLBL(acc[2]);
		angle = Degrees(atan(ang));
	}

	//DWM1001C
	if (Hard_conf[0] == '3')
	{
		acc[0] = ((float) (((int8_t) buffer6[1]))) / 32;
		acc[1] = ((float) (((int8_t) buffer6[3]))) / 32;
		acc[2] = ((float) (((int8_t) buffer6[5]))) / 32;

		accy2 = absLBL(acc[1]);
		accy = (uint16_t) (((-acc[1]) + 4) * 255) / 8;  // y to top
	}

	acc[3] = sqrt(acc[0] * acc[0] + acc[1] * acc[1] + acc[2] * acc[2]); //computation of result acceleration

	accres2 = acc[3];
	accres = (uint16_t) (((acc[3] + 4) * 255) / 8);
}

void imuMsr2floatG_HeliosV1(float acc[], uint8_t buffer6[], int nbBit,
		int scale)
{

	unsigned dec;
	double powV1;
	double value1;

	dec = 16 - ((unsigned) nbBit);
	powV1 = pow(2, (16 - nbBit));
	value1 = pow(2, (nbBit - 1)) / scale;

	for (int i = 0; i < 3; i++)
	{
		acc[i] = (float) (((((int16_t) (((buffer6[2 * i + 1] << 8)
				+ buffer6[2 * i]) << (16 - nbBit))) / powV1)) / value1);
	}
	acc[3] = sqrt(acc[0] * acc[0] + acc[1] * acc[1] + acc[2] * acc[2]); //computation of result acceleration

	acc[2] = -acc[2]; // convert to orthogonal reper

// rotation around Z axis for Helios acceleration definition (X to right, Y to top)
	acc[0] = -acc[0];
	acc[1] = -acc[1];

}

void printScreen(char input[])
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 7);
	ssd1306_WriteString(input, Font_7x10, White);
	ssd1306_UpdateScreen();
}

char* itoa(int value, char *result, int base)
{
	// check that the base if valid
	if (base < 2 || base > 36)
	{
		*result = '\0';
		return result;
	}

	char *ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do
	{
		tmp_value = value;
		value /= base;
		*ptr++ =
				"zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35
						+ (tmp_value - value * base)];
	} while (value);

	// Apply negative sign
	if (tmp_value < 0)
		*ptr++ = '-';
	*ptr-- = '\0';
	while (ptr1 < ptr)
	{
		tmp_char = *ptr;
		*ptr-- = *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}
