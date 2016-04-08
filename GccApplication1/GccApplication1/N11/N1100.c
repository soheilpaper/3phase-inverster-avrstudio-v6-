//-----------------------------------------------------------------------------
// Copyright:      RAD Electronic Co. LTD,
// Author:         Sh. Nourbakhsh Rad
// Remarks:        
// known Problems: none
// Version:        3.5.1
// Description:    NOKIA 1100 Display (PCF8814) driver
//-----------------------------------------------------------------------------

#include "N1100.h"


//******************* Constants
#if LCDlight == 0
	unsigned char 						N11_Cache[N11_Xr][N11_Rr];
#endif


//*************************************************
//******************* Functions *******************
//*************************************************
void N11_Write(N11_RS DC, unsigned char c)		//write command or data to LCD
{
	int i;

	N11_CS(LOW);
	
	N11_SCL(LOW);
		N11_SDA(DC);
	N11_SCL(HIGH);

	for(i=7; i>=0; i--)
	{
		N11_SCL(LOW);
			N11_SDA(bit_is_set(c, i));
		N11_SCL(HIGH);
	}

	N11_CS(HIGH);
}	//*N11_Write

void N11_GotoXR(unsigned char x, unsigned char r)		//goto X(0..95) and R(0..8)
{
	N11_Write(cmd, (0xB0| (r&0x0F)));        		//Y axis initialisation: 0100 rrrr           
	N11_Write(cmd, (0x00| (x&0x0F)));        		//X axis initialisation: 0000 xxxx  (x3 x2 x1 x0)
	N11_Write(cmd, (0x10|((x>>4)&0x07)));     	//X axis initialisation: 0010 0xxx  (x6 x5 x4)
}	//*N11_GotoXR

//------------------------
void N11_Init(void)														//initial LCD
{
	N11_CS_init();
              
	N11_SDA_init();
	N11_SCL_init();
             
	N11_RST_init();
	N11_BKL_init();
		
	//----------------
	N11_CS(LOW);
		_delay_ms(50);							//min. 5ms

	N11_RST(HIGH);
	
	N11_Write(cmd, 0x23);     		//write VOP register - contrast MSB value(00100ccc - 	  c7 c6 c5)
	N11_Write(cmd, 0x90);					//write VOP register - contrast LSB value(1001cccc - c3 c2 c1 c0)

	N11_Write(cmd, 0xA4);     		//all on/normal display
	N11_Write(cmd, 0x2F);     		//Power control set(charge pump on/off)
	N11_Write(cmd, 0x40);     		//set start row address = 0
	N11_Write(cmd, 0xB0);     		//set R-address = 0
	N11_Write(cmd, 0x10);     		//set X-address, upper 3 bits
	N11_Write(cmd, 0x00);      		//set X-address, lower 4 bits
	//----
	#if MirrorY ==1
		N11_Write(cmd, 0xC8); 			//mirror Y axis (about X axis)
	#endif
	
	#if InvertScreen ==1
		N11_Write(cmd, 0xA1);				//invert screen in horizontal axis
	#endif
	//----
	N11_Write(cmd, 0xAC);     		//set initial row (R0) of the display
	N11_Write(cmd, 0x07);

	N11_Write(cmd, 0xAF);    			//display ON/OFF

	N11_CLS();     	    					//clear LCD
	N11_Write(cmd,0xA7);     			//invert display

		_delay_ms(500);
	N11_Write(cmd,0xA6);     			//normal display (non inverted)
		_delay_ms(500);
}	//*N11_Init

void N11_CLS(void)														//clear LCD
{
	unsigned char 			x, r;
	
	N11_GotoXR(0, 0);
	N11_Write(cmd, 0xAE); 					// disable display;
	
	//fill LCD and the video buffer with zero!
	for(r=0; r<N11_Rr; r++)
	{
		for(x=0; x<N11_Xr; x++)
		{
			#if LCDlight == 0
				N11_Cache[x][r]= 0x00;
			#endif
			N11_Write(data, 0x00);
		}
	}

	N11_Write(cmd, 0xAF); 					// enable display;
}	//*N11_CLS

void N11_Update(void) 												//write data of cache to display RAM
{
	#if LCDlight == 0
		unsigned char 			x, r;
	
		N11_GotoXR(0, 0);
		//N11_Write(cmd, 0xAE); 					// disable display;
	
		//serialize the video buffer to LCD
		for(r=0; r<N11_Rr; r++)
			for(x=0; x<N11_Xr; x++)
				N11_Write(data, N11_Cache[x][r]);
		
		//N11_Write(cmd, 0xAF); 					// enable display;
	#endif//LCDlight
}	//*N11_Update

//------------------------
void N11_Contrast(unsigned char cont)					//set LCD contrast value from 0x00 to 0x7F
{
	N11_Write(cmd, 0x21);					//LCD extended commands.
	N11_Write(cmd, 0x80|cont);		//set LCD Vop (Contrast)
	N11_Write(cmd, 0x20)	;				//LCD standard commands, horizontal addressing mode.
}	//*N11_Contrast

void N11_Backlight(unsigned char x)						//LCD backlight ON/OFF
{
	#ifdef N11_BKL_BIT
		N11_BKL(x);
	#endif//N11_BKL_BIT
}	//*N11_Backlight

//------------------------
void N11_SetPixel(unsigned char x, unsigned char y, N11_Pmode mode)
{
	#if LCDlight == 0
		unsigned char			r, pd;
		
	 	if((x > GetMaxX()) || (y > GetMaxY()))			return;				//exit if coordinates are not legal
	  
		r  = y/8;
		pd = 1 << (y%8);
		
		if		 (mode == PIXEL_ON)			N11_Cache[x][r] |=  pd;
		else if(mode == PIXEL_OFF)		N11_Cache[x][r] &= ~pd;
		else if(mode == PIXEL_XOR)		N11_Cache[x][r] ^=  pd;
	
		N11_GotoXR(x, r);
		N11_Write(data, N11_Cache[x][r]);
	#endif//LCDlight
}	//*N11_PutPixel
	
unsigned char N11_ReadPixel(unsigned char x, unsigned char y)
{	
	#if LCDlight == 0
	 	if((x > GetMaxX()) || (y > GetMaxY()))			return(0x00);				//exit if coordinates are not legal
			
		return(bit_is_set(N11_Cache[x][y/8], (1 << (y%8))) ? 0x01 : 0x00);
	#endif//LCDlight
}	//*N11_ReadPixel
	
void N11_FillRect(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, N11_Pmode mode)
{
	#if LCDlight == 0
		unsigned char			x, y;
		unsigned char 		h, w;
	
	 	w = x2 + 1;
	 	h = y2 + 1;
	 	
	 	N11_Write(cmd, 0xAE); 					// disable display;
	
		for(y=y1; y<h; y++)
			for(x=x1; x<w; x++)
				N11_SetPixel(x, y, mode);
	
		N11_Write(cmd, 0xAF); 					// enable display;
	#endif//LCDlight
}	//*N11_FillRect
	
	//------------------------
void N11_DrawBitmap(const unsigned char *bitmap, unsigned char x, unsigned char y, N11_Pmode mode)
{
	#if LCDlight == 0
		unsigned char 		header, width, height;
		unsigned char			xx, yy, rr;
		unsigned int			xy;
		unsigned char			pd, pc, ps;
		unsigned char 		Cdata;
		
	  
		header = pgm_read_byte(&bitmap[0]);  	//header size & width & height
	  width  = pgm_read_byte(&bitmap[1]);
	  height = pgm_read_byte(&bitmap[2]);
	
		ps = _ror(1 << (y%8));
	
		for(xx=0; xx<width; xx++)
		{
			pd = ps;
	 		Cdata = pgm_read_byte(&bitmap[xx+header]);
	
			for(yy=0, pc=0; yy<height; yy++,pc++)
			{
				if(pc==8)
				{
					xy = (unsigned char)(yy/8)*width + xx+header;
				 	Cdata = pgm_read_byte(&bitmap[xy]);
	
				 	pc = 0;
				}//if pc
	
				rr = (unsigned char)((y+yy)/8);
				pd = _rol(pd);
					
				
				//Draw BMP!
				if(mode == PIXEL_XOR)
				{
					if(bit_is_set(Cdata, pc))			N11_Cache[x+xx][rr] &= ~pd;
					else													N11_Cache[x+xx][rr] |=  pd;
				}
				else
				{
					if(bit_is_set(Cdata, pc))			N11_Cache[x+xx][rr] |=  pd;
					else													N11_Cache[x+xx][rr] &= ~pd;
				}
			}//for yy
		}//for xx
	
		N11_Update();
	#endif//LCDlight
} //*N11_DrawBitmap
