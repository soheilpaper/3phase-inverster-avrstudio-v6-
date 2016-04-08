//-----------------------------------------------------------------------------
// Copyright:      RAD Electronic Co. LTD,
// Author:         Sh. Nourbakhsh Rad
// Remarks:        
// known Problems: none
// Version:        3.5.1
// Description:    NOKIA 1100 Display (PCF8814) driver
//-----------------------------------------------------------------------------

#ifndef _N1100_H_
	#define _N1100_H_

	#include "N1100config.h"


	#define N11_SIZE_X           	96
	#define N11_SIZE_Y           	65

	#define N11_Xr           			(unsigned char)(N11_SIZE_X)
	#define N11_Rr           			(unsigned char)(N11_SIZE_Y/8+1)

	#define GetMaxX() 						((unsigned char)N11_SIZE_X-1)
	#define GetMaxY() 						((unsigned char)N11_SIZE_Y-1)

	//------------------------
	#if LCDlight == 0
		extern unsigned char 					N11_Cache[N11_Xr][N11_Rr];
	#endif
	
	//------------------------
	typedef enum {
		cmd   	= 0,
	  data  	= 1
	} N11_RS;

	typedef enum {
		PIXEL_OFF  	= 0,
		PIXEL_ON  	= 1,
		PIXEL_XOR  	= 2
	} N11_Pmode;

	//------------------------
	#define BLACK									PIXEL_ON
	#define WHITE									PIXEL_OFF
	#define INVERS								PIXEL_XOR
	
	//-----------------------------------------------------------------------
	#ifndef _rol(x)
	  #define _rol(x) 						((x & 0x80) ? ((x << 1) | 0x01) : (x << 1));
	  #define _ror(x)							((x & 0x01) ? ((x >> 1) | 0x80) : (x >> 1));
	#endif

	#ifndef True
		#define True								1
		#define False								0
	#endif

	#ifndef ON
		#define ON									1
		#define OFF									0
	#endif
	
	#ifndef HIGH
		#define HIGH								1
		#define LOW									0	
	#endif


	//******************* Function Prototypes
	void N11_Write(N11_RS DC, unsigned char c);
	void N11_GotoXR(unsigned char x, unsigned char r);

	void N11_Init(void);
	void N11_CLS(void);
	
	void N11_Update(void);
	
	void N11_Contrast(unsigned char cont);
	void N11_Backlight(unsigned char x);

	void N11_SetPixel(unsigned char x, unsigned char y, N11_Pmode mode);	
	unsigned char N11_ReadPixel(unsigned char x, unsigned char y);
	void N11_FillRect(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, N11_Pmode mode);
	
	void N11_DrawBitmap(const unsigned char *bitmap, unsigned char x, unsigned char y, N11_Pmode mode);

#endif	//_N1100_H_