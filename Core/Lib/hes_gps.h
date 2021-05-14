#include "hes_include_stm32.h"
#include "hes_gpio_h3.h"

extern UART_HandleTypeDef huart2;

extern UART_HandleTypeDef GPS_UART_PORT;
	
#define GPS_UART_PORT	huart2	

void GpsStop(void);

void GpsStart(void);

int find_word(char *tableau , char *word, int taille_word);

//float transformer_char_latitude_todecdeg(char *t);

//float transformer_char_longitude_todecdeg(char *t);