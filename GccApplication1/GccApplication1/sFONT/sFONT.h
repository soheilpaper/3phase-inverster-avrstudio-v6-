//-----------------------------------------------------------------------------
// Copyright:      RAD Electronic Co. LTD,
// Author:         Sh. Nourbakhsh Rad
// Remarks:        
// known Problems: none
// Version:        01.10.2011
// Description:    NOKIA 1100 Display (PCF8814) simple FONT
//-----------------------------------------------------------------------------
#ifndef EFONT_H_
	#define EFONT_H_
	
	#include "..\N11\N1100.h"	
	//#include "ef5x7.h"

	
	//******************* Function Prototypes
	void N11_PrintChar(char ch);								//write character to LCD
	void N11_PrintString(char *str);						//write string to LCD (C string type)
	
	#define StringAt(l, c, s)			{N11_GotoXR(c, l);	N11_PrintString(s);}			//l: 0...7  &  c: 0...95

#endif	//EFONT_H_
