#include "hes_filt.h"

float filt5(float val,float tabVal[])
{
	float val_out = 0 ;
	
	tabVal[1] = tabVal[0] ;
	tabVal[2] = tabVal[1] ;
	tabVal[3] = tabVal[2] ;
	tabVal[4] = tabVal[3] ;
	tabVal[5] = tabVal[4] ;
	tabVal[6] = tabVal[5] ;
	tabVal[7] = tabVal[6] ;
	tabVal[8] = tabVal[7] ;
	tabVal[9] = tabVal[8] ;
	
	tabVal[0] = val ; 
	
	val_out = (tabVal[0]+tabVal[1]+tabVal[2]+tabVal[3]+tabVal[4]+tabVal[5]+tabVal[6]+tabVal[7]+tabVal[8]+tabVal[9])/10 ; 
	
	return val_out ;
	
}


