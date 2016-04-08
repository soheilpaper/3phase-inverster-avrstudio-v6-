//-----------------------------------------------------------------------------
// Copyright:      	www.KnowledgePlus.ir
// Author:         	OZHAN KD
// Remarks:        	code ported to GNUC by Sh. Nourbakhsh Rad
// known Problems: 	none
// Version:        	1.5.2
// Description:    	
//									MCU: ATmega64 @8MHz external xtal
//									
//									3 phase SPWM outputs on OCR1A,OCR1B,OCR1C
//									Carrier frequency = 15.6 KHz
//									Sine frequency range = 0.5-100Hz with 0.1Hz step
//									PWM resolution = 8bit
//									
//									Frequency varies by applied voltage to ADC0(PF0)
//									ADC Vref = AVcc
//									ADC result<14 ---> output off
//									ADC result: 14-1009 ---> f: 0.5 Hz - 100 Hz
//									ADC result>1009 ---> f=100 Hz
//									
//-----------------------------------------------------------------------------
// History:					
//									V1.0 Mar 2011
//										Start Project....
//									
//									V1.1 Feb 2011
//										Linear V/F curve added
//									
//									V1.2 Jun 2011
//										Acceleration-Deceleration added
//									
//									V1.3 Jul 2011
//										Adjustable Acceleration-Deceleration
//										by ADC1 and ADC2 analog inputs
//										ADC1 sets acceleration (1s-255s)
//										ADC2 sets decceleration (1s-255s)
//										Adjusted values are times for 100Hz change in frequency
//									
//									V1.4 Jul 2012
//										Fixed some bugs
//									
//									V1.5 Oct 4, 2012
//										Timer3 mode changed to Fast PWM (due to problems in frequency change)
//										modification in amplitude calculation
//
//-----------------------------------------------------------------------------

#include "SPWM.h"

#include "SINE_tbl.h"
#include "TIMER_tbl.h"


//******************* Constants
volatile unsigned int 										FinalSpeed		= 0;
volatile unsigned char 										Acceleration	= 1;
volatile unsigned char 										Deceleration	= 1;

volatile unsigned int 										speed					= 0;
volatile unsigned char 										index					= 0;

volatile unsigned char 										MSflag				= 0;

volatile unsigned int 										TCounter 			= 0;


//*************************************************
//******************* Functions *******************
//*************************************************
unsigned char A_calc(unsigned char sine, unsigned char Ain)
{
	unsigned int 						sine_temp;
	unsigned char 					sine1;
 
	sine1 = (sine<128)? ~sine : sine;
 
	sine_temp   = ((unsigned int)sine1) <<1;
	sine_temp  -= 255;
	sine_temp  *= Ain;
	sine_temp >>= 8;
	sine_temp  += 255;
	sine_temp >>= 1;
	sine_temp  += 1;
 
	sine1 = (unsigned char)sine_temp;
 
	return((sine<128)? ~sine1 : sine1);
}	//A_calc

//-----------------------------------------------------------------------------
ISR_PWM_SET()
{
	unsigned long 				A;

	if 			(speed>795)				index += 16;
	else if	(speed>595)				index += 8;
	else if	(speed>395)				index += 4;
	else if	(speed>195)				index += 2;
	else 											index += 1;

	//-------------------
	if(speed>=f_Base)
	{
		PWMR_SET(pgm_read_byte(&sine[R_Index(index)]));
		PWMS_SET(pgm_read_byte(&sine[S_Index(index)]));
		PWMT_SET(pgm_read_byte(&sine[T_Index(index)]));
	}

	//-----
	else if (speed<=f_Boost)
	{
		PWMR_SET(A_calc(pgm_read_byte(&sine[R_Index(index)]), A_Boost));
		PWMS_SET(A_calc(pgm_read_byte(&sine[S_Index(index)]), A_Boost));
		PWMT_SET(A_calc(pgm_read_byte(&sine[T_Index(index)]), A_Boost));
	}

	//-----
	else
	{
		A = ((N *(unsigned long)(speed -f_Boost)) /M) +A_Boost;
		
		PWMR_SET(A_calc(pgm_read_byte(&sine[R_Index(index)]), (unsigned char)A));
		PWMS_SET(A_calc(pgm_read_byte(&sine[S_Index(index)]), (unsigned char)A));
		PWMT_SET(A_calc(pgm_read_byte(&sine[T_Index(index)]), (unsigned char)A));
	}
}	//ISR_PWM_SET

ISR_SPEED_TUNE()								//Occur every 1ms!
{
	#if (ACC_DEC_USE ==0)
		speed = FinalSpeed;

	#else
		static unsigned char 					ACC_counter = 0;
		static unsigned char 					DEC_counter = 0;
	 
	
		//-----  Acceleration
		if(speed<FinalSpeed)
		{
			DEC_counter = 0;

			#if (ACC_DEC_USE ==1) || (ACC_DEC_USE ==3)
				ACC_counter++;
		 		if(ACC_counter>=Acceleration)
		 		{
		 			ACC_counter = 0;
		  		speed++;
				}

			#else
				speed = FinalSpeed;

			#endif
		}

		//-----  Deceleration
		else if(speed>FinalSpeed)
		{
			ACC_counter = 0;

			#if (ACC_DEC_USE ==2) || (ACC_DEC_USE ==3)
				DEC_counter++;
				if(DEC_counter>=Deceleration)
				{
			  	DEC_counter = 0;
			  	speed--;
				}

			#else
				speed = FinalSpeed;

			#endif
		}

		//-----
		else
		{
	 		ACC_counter = 0;
	  	DEC_counter = 0;
		}

	#endif	

	//-------------------
	if(speed)
	{
		FRQ_SET(pgm_read_word(&Timer_Value[speed])-1);

 		if(MSflag==0)
 		{
			PWMRST_ON();
			MSflag = 1;
		
			PWM_INTV_TMR_ON();
			PWM_INTV_ena();
		}
	}

	//-----
	else
	{
	 	PWMRST_OFF();
		MSflag = 0;

	 	PWM_INTV_TMR_OFF();
	 	PWM_INTV_dis();
	}
	
	TCounter++;
}	//ISR_SPEED_TUNE

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SPWM_init(void)
{
	SPWM_HW_init();
	
	PWMR_SET(R_Index(index));
 	PWMS_SET(S_Index(index));
 	PWMT_SET(T_Index(index));

	PWM_TMR_init();
	PWM_TMR_ON();
	
	PWM_INTV_init();
	SPEED_INTV_SET(SPEED_INTV_time);		//Occur every 1ms!

	SPEED_INTV_init();
	SPEED_INTV_ena();
}	//SPWM_init

unsigned int SetFrequency(unsigned int FRQ)
{
	if			(FRQ<14)					FinalSpeed = 0;
	else if (FRQ<1010)				FinalSpeed = FRQ -13;
	else 											FinalSpeed = 996;
	
	return(FinalSpeed +4);
}	//SetFrequency

unsigned char SetAcceleration(unsigned char ACC)
{
	if(ACC) 									Acceleration = ACC;
	else 											Acceleration = 1;
	
	return(Acceleration);
}	//SetAcceleration

unsigned char SetDeceleration(unsigned char DEC)
{
	if(DEC) 									Deceleration = DEC;
	else 											Deceleration = 1;
	
	return(Deceleration);
}	//SetDeceleration
