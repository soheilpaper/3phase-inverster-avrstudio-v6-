//-----------------------------------------------------------------------------
// Copyright:      www.KnowledgePlus.ir
// Author:         OZHAN KD ported by Sh. Nourbakhsh Rad
// Remarks:        
// known Problems: none
// Version:        1.1.0
// Description:    SPWM test...
//-----------------------------------------------------------------------------
//#ifndef F_CPU
//#define F_CPU 8000000UL // 16 MHz clock speed
//#endif
//	Include Headers
//*****************************************************************************
#include "app_config.h"
#include "HW_SPWM.h"

//--------------------------------------------------
#include "N11\N1100.h"
#include "sFONT\sFONT.h"

//--------------------------------------------------
#include "ADC\ADC.h"

//--------------------------------------------------
#include "SPWM\SPWM.h"

#define D4 eS_PORTC4
#define D5 eS_PORTC5
#define D6 eS_PORTC6
#define D7 eS_PORTC7
#define RS eS_PORTC2
#define EN eS_PORTC3
#include "lcd.h" //Can be download from the bottom of this article
//	Constants and Varables
//*****************************************************************************

//Temp Const.
char 														Ctemp[24];
int  														Itemp = 0;


//	Functions Prototype
//*****************************************************************************
void Initial(void);
void Splash(void);

void test01(void);
void LCD_0(void);

//	<<< main function >>>
//*****************************************************************************
void main(void)
{
	LCD_0();
	Initial();
	test01();
	
	while(1);
} //main


//---------------------------------------------------------//
//---------------------------------------------------------//
void Initial(void)
{
	cli();												//Interrupts disable

	HW_init();
	a2dInit();										//AVCC & DIV64
	
	_delay_ms(500);

	//----------------------
	N11_Init();
	N11_Contrast(10);
	N11_Backlight(ON);
	
	//----------------------
	BUZZER(BOOT_sign);
	_delay_ms(500);

	//----------------------
	//static FILE mystdout = FDEV_SETUP_STREAM(N11_PrintChar, NULL, _FDEV_SETUP_WRITE);
  //stdout = &mystdout;
	
	N11_CLS();
	
	//----------------------
	Splash();
	BUZZER(OK_sign);

	//------------
	sei();												//Interrupts enabel	
}	//Initial

void Splash(void)
{
	static char *SPchar[5] = {
			"  SPWM test!!!",
			"by :",
			"Nourbakhsh & elasa.ir",
			"Copyright:",
			"    OZHAN KD"
			};

	//-------------
	StringAt(0, 2, SPchar[0]);
	StringAt(2, 2, SPchar[1]);
	StringAt(3, 2, SPchar[2]);
	StringAt(5, 2, SPchar[3]);
	StringAt(6, 2, SPchar[4]);

	//-------------
	_delay_ms(3000);
	N11_CLS();
}	//Splash


//---------------------------------------------------------//
//---------------------------------------------------------//
void test01(void)
{
	unsigned char				LVflag 	= 0;
	unsigned int				TCRtemp = 0;
	unsigned char				i 			= 0;

	unsigned int				FRQtemp;
	unsigned char				ACCtemp;
	unsigned char				DECtemp;

	SPWM_init();
	
	ADC_CH_init(FRQ_ACH);
	ADC_CH_init(ACC_ACH);
	ADC_CH_init(DEC_ACH);
	
	//----- main loop!
	while(1)
	{		
		if(TCounter>=TCRtemp)									//100mS
		{
			TCRtemp = TCounter +100;						//1mS x100
			
			FRQtemp = a2dConvert10bit(FRQ_ACH);
			ACCtemp = a2dConvert8bit(ACC_ACH);
			DECtemp = a2dConvert8bit(DEC_ACH);
			
			//-------------------------------
			FRQtemp = SetFrequency(FRQtemp);
			ACCtemp = SetAcceleration(ACCtemp);
			DECtemp = SetDeceleration(DECtemp);
	
			//-------------------------------
			
			int a;
			char str[16];
			
			
			Lcd4_Init();
						
			sprintf(Ctemp, "FRQ: %03d.%01d Hz ", (FRQtemp/10), (FRQtemp%10));
			Lcd4_Set_Cursor(1,1);
			Lcd4_Write_String(Ctemp) ;
			
			 
			//_delay_ms(1000);
			//}
			//#endif
			float b;
			//char str[16];

			sprintf(Ctemp, "AC:%03dSc ", ACCtemp);
			Lcd4_Set_Cursor(2,1);
			Lcd4_Write_String(Ctemp) ; 
			
			
			float b2;
			//char str[16];

			
			sprintf(Ctemp, "DE:%03dSc ", DECtemp);
			Lcd4_Set_Cursor(2,10);
			Lcd4_Write_String(Ctemp) ;
			
			//_delay_ms(1000);
			
			sprintf(Ctemp, "FRQ: %03d.%01d Hz ", (FRQtemp/10), (FRQtemp%10));
			StringAt(1, 2, Ctemp);
			
			sprintf(Ctemp, "ACC: %03d sec ", ACCtemp);
			StringAt(3, 2, Ctemp);
	
			sprintf(Ctemp, "DEC: %03d sec ", DECtemp);
			StringAt(5, 2, Ctemp);
			
			i++;
			if(i==5)					{						LVflag = 1;		}
			else if(i==10)		{	i = 0;		LVflag = 0;	}
		}
		
		GLED(LVflag);
		//_delay_ms(200);
	}//while
} //test01


//---------------------------------------------------------//
//---------------------------------------------------------//
void LCD_0(void)
{
	

DDRD = 0xFF;
DDRC = 0xFF;
int i;
Lcd4_Init();
Lcd4_Set_Cursor(1,1);
Lcd4_Write_String("Elasa.ir Test");  
	
}	