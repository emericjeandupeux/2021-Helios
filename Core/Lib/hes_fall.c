#include "hes_fall.h"



uint16_t mean(uint8_t *t, uint16_t val_initiale) {
	uint16_t a;
	a = 0;
	for (i = val_initiale; i <= val_initiale + 10; i++) {
		a = a + t[i];
	}
	a = a / 11;

	return a;
}



uint8_t test_chute(uint16_t *accl, uint8_t *v) {

	uint32_t millis_begin;

	millis_begin = HAL_GetTick();



	/*double total_time;
	clock_t start, end;
	 start = clock();
	 srand(time(NULL));*/
	uint16_t i = 0;

	uint8_t  a = 0;


	while (i <= 400 - 2 - 56 - 50 - 10 && a == 0 ) {
		//CDC_Transmit_FS("Debut test chute\n",sizeof("Debut test chute\n"));
//    Serial.print("Debut test chute\n");
		if (accl[i] < 153) {                        // on detecte la chute et le nombre 153 ~ 0.80 en d�cimale
			a = 1;
			// CDC_Transmit_FS("a <0.8063",sizeof("a <0.8063idr"));
//          Serial.print("1er if");
			for (uint16_t j = i; j <= 2 + i; j++) {
				if (accl[j] > 153) {               // on test si la chute dure 30ms   le nombre 153 ~ 0.80 en d�cimale
					a = 0;
					break;
				}
			}
//
//         Serial.print("a==true");
			if (a == 1) {
				// CDC_Transmit_FS("a==true",sizeof("a==true"));
				for (uint16_t j = i ; j <= i + 2 + 56; j++) { // on cherche � detecter la chute !!!!!

					if (accl[j] >= 207 ) { // /*2.5025*/){      207 ~ 2.50 en d�cimal
						a = 1;
						//		 CDC_Transmit_FS("acc supe � 8",sizeof("acc supe � 8"));
						break;
					}
					else {
						a = 0;
					}

				}

			}
			if (a == 1 ) {
				uint16_t b;
				//   float angle;
				b = mean(v, i + 3 + 56 + 50);

//
//
//
////          angle =acos(b)*180/(3.14);                         // on calcul l'angle que fais le vecteur de la pesenteur avec l'axe y

//             //if (60<=angle){
				if (b <= 140 && b >= 114)
				{ // 140 ~ 0.4   -0.4 ~ 114
					a = 1;
					break;
				}
				else
				{
					a = 0;
					//i=i+15+298+100;
				}

			}

		}

		i = i + 1;

	}
	//	char lcd_buf1[8];

//	sprintf(lcd_buf1, "%+-5.4f\n",e);
//		CDC_Transmit_FS(lcd_buf1,sizeof(lcd_buf1));

	//HAL_Delay(3);
	//  millis_tot = HAL_GetTick() - millis_begin;


	//char  lcd_buf1[5]={'\0','\0','\0','\0','\0'};
//	total_time = ((double) (end - start)) / CLOCKS_PER_SEC;

	//sprintf(lcd_buf1, "%d\n",( (int) millis_tot));
	//CDC_Transmit_FS(lcd_buf1,sizeof(lcd_buf1));


	return a;
}



/*

void func_sig_mess2(char buffer_sig[], int sos,int fall,int h2sAlerte,int bat, int batlevel)
{
int signe_value = -1 ;
int val1byte = 0 ;
int val2byte = 0 ;
int val3to7byte = 0 ;
int val8to12byte = 0 ;
uint8_t buffer = 0x00 ;
char buffer_lat[5] ;
char buffer_long[5] ;


//sos + 0
//sos - 1
//fall + 2
//fall - 3
//batt + 4
//batt - 5
//gaz + 6
//gaz - 7
//other + 8
//other - 9

if (sos == 1)
{
	if (signe_value == 1)
	{ val1byte = 0 ;}
	else
		{ val1byte = 1 ;}
	}
else if(fall == 1)
	{
	if (signe_value == 1)
	{ val1byte = 2 ;}
	else
		{ val1byte = 3 ;}
	}
else if(bat == 1)
	{
	if (signe_value == 1)
	{ val1byte =  4;}
	else
		{ val1byte = 5 ;}
	}
	else if(h2sAlerte == 1)
	{
	if (signe_value == 1)
	{ val1byte =  6;}
	else
		{ val1byte = 7 ;}
	}
else
	{
	if (signe_value == 1)
	{ val1byte = 8 ;}
	else
		{ val1byte = 9 ;}
	}

val2byte = batlevel/10 ;
if (val2byte>9)
{val2byte = 9 ;}
	if (val2byte<0)
{val2byte = 0 ;}


buffer = (uint8_t) ( val1byte*16 + val2byte );



//buffer_lat = (uint32_t) val3to7byte ;
//buffer_long = (uint32_t) val8to12byte ;

sprintf(buffer_sig, "%2X", buffer);

for (int i_bb=0;i_bb<12;i_bb++)
{
	if(buffer_sig[i_bb]<33)
	{
		buffer_sig[i_bb] = 48 ;
	}
}



}
*/
