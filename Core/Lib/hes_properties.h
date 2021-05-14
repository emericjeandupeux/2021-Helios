#include "hes_include_stm32.h"

extern unsigned char Hard_conf[1];
extern unsigned char Code_name[64];
extern unsigned char Client[16];

void AskProperties(uint8_t re_Hard_conf, unsigned char *re_Client);
void LoadProperties(void);
