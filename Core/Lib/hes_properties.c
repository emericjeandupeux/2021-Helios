#include "hes_properties.h"
#include "hes_task.h"

//unsigned char Hard_conf[64] = "MPU6050_ADDR ET AUTRES";
unsigned char Code_name[64] = "HeliosModifLora + SF";
//unsigned char Client[64] = "AES";

unsigned char Hard_conf[1] = "";
unsigned char Client[16] = "";

void AskProperties(uint8_t re_Hard_conf, unsigned char *re_Client)
{
	uint8_t commit = 0;
	uint8_t new_Client = 0;
	unsigned char buffer_prop;

	//L'ecture du choix de l'imu et du nom client dans l'eeprom
	ee_read(256, sizeof(Hard_conf), Hard_conf);
	ee_read(272, sizeof(Client), Client);

	//Test si le choix de l'IMU a changer
	if (re_Hard_conf != Hard_conf)
	{
		Hard_conf[0] = re_Hard_conf;
		ee_writeToRam(256, sizeof(Hard_conf), Hard_conf);
		commit = 1;
	}

	//Test si le nom du client a changer
	for (int l = 0; l <= 16; l++)
	{
		if (re_Client[l] != Client[l])
		{
			new_Client = 1;
			l = 16;
		}
	}
	if (new_Client == 1)
	{
		for (int j = 0; j <= 16; j++)
		{
			Client[j] = re_Client[j];
		}
		ee_writeToRam(272, sizeof(Client), Client);
		commit = 1;
	}

	//Ecriture dans l'eeprom si il y a des changements
	if (commit == 1)
	{
		ee_commit();
		vibration_LBL(2, 200, 200);
	}
	sprintf(buffer_prop, "INFO,%s,%d,%d,%s,%s,%s", ID_Sigfox, TabGen[VBAT_mV],
			TabGen[BAT_VALUE], Hard_conf, Code_name, Client);
	CDC_Transmit_FS(buffer_prop, strlen(buffer_prop));
}

void LoadProperties(void)
{
	uint8_t default_name;
	uint8_t commit2 = 0;
	ee_read(256, sizeof(Hard_conf), Hard_conf);
	ee_read(272, sizeof(Client), Client);
	if ((Hard_conf[0] != '1') && (Hard_conf[0] != '2') && (Hard_conf[0] != '3'))
	{
		Hard_conf[0] = '2'; // MC3413 par défaut
		ee_writeToRam(256, sizeof(Hard_conf), Hard_conf);
		commit2 = 1;
	}
	for (int i = 0; i <= strlen(Client); i++)
	{
		if (Client[i] == 255)
		{
			default_name++;
		}
	}
	if(default_name > 0){
		sprintf(Client,"Hestiam");
		ee_writeToRam(272, sizeof(Client), Client);
		commit2 = 1;
	}
	if(commit2 != 0){
		ee_commit();
		vibration_LBL(1, 0, 500);
	}
}
