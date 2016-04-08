//-----------------------------------------------------------------------------
// Copyright:      RAD Electronic Co. LTD,
// Author:         Sh. Nourbakhsh Rad
// Remarks:        
// known Problems: none
// Version:        01.10.2011
// Description:    NOKIA 1100 Display (PCF8814) simple FONT
//-----------------------------------------------------------------------------

#include "sFONT.h"
#include "ef5x7.h"


//******************* Functions *******************
void N11_PrintChar(char ch)
{	
	unsigned char i;
	
	for(i=0; i<5; i++)
  	N11_Write(data,	pgm_read_byte(&ef5x7[ch-32][i])<<1);
	
	N11_Write(data, 0x00);
}	//N11_PrintChar

void N11_PrintString(char *str)
{   
	N11_Write(cmd, 0xAE); 				// disable display;
	
	while(*str)										//look for end of string
  	N11_PrintChar(*str++);

	N11_Write(cmd, 0xAF); 				//enable display;
}	//N11_PrintString
