#include "hes_uint82bitint.h"


int uint82bitint(uint8_t hexIn) {
int output = 0 ;
uint8_t hexMulti = 0x01 ; 
int fact = 1 ;

for (int i=0;i<8;i++)
{
output = (int) ((( hexIn & (uint8_t) hexMulti )/( (uint8_t) hexMulti ))* fact) + output ;
hexMulti = hexMulti << 1 ; 
fact = fact * 10 ;
}
return output ; // output ; 
}
