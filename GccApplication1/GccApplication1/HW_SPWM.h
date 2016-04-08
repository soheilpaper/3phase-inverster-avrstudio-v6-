//-----------------------------------------------------------------------------
// Copyright:      www.KnowledgePlus.ir
// Author:         OZHAN KD modified by Sh. Nourbakhsh Rad
// Remarks:        
// known Problems: none
// Version:        1.0.0
// Description:    hardware initiation
//-----------------------------------------------------------------------------

#ifndef _SPWMHW_H_
	#define _SPWMHW_H_

  #include "app_config.h"


	//----------- Definitions

	//-----------  Volumes inputs !!!
	#define FRQ_ACH													0
	#define ACC_ACH													1
	#define DEC_ACH													2

	//----------- Buzzer (output)
	#define BUZER_PRT												PORTC
	#define BUZER_DDR												DDRC
	#define BUZER_PIN												PINC
	#define BUZER_BIT												7

	//----------- Green LED (output)
	#define GLED_PRT												PORTC
	#define GLED_DDR												DDRC
	#define GLED_PIN												PINC
	#define GLED_BIT												5

	//----------- Red LED (output)
	#define RLED_PRT												PORTC
	#define RLED_DDR												DDRC
	#define RLED_PIN												PINC
	#define RLED_BIT												6


	//---------------------------------------------------------------
	//---------------------------------------------------------------
	#define BUZER_init()										sbi(BUZER_DDR, BUZER_BIT);	cbi(BUZER_PRT, BUZER_BIT)

	#define GLED_init()											sbi(GLED_DDR, GLED_BIT); 		cbi(GLED_PRT, GLED_BIT)
	#define RLED_init()											sbi(RLED_DDR, RLED_BIT); 		cbi(RLED_PRT, RLED_BIT)

	//---------------------
	#define BUZER(x)				  							(x ? (sbi(BUZER_PRT, BUZER_BIT)) : (cbi(BUZER_PRT, BUZER_BIT)))
	
	#define GLED(x)				  								(x ? (sbi(GLED_PRT, GLED_BIT)) 	 : (cbi(GLED_PRT, GLED_BIT)))
	#define RLED(x)				  								(x ? (sbi(RLED_PRT, RLED_BIT)) 	 : (cbi(RLED_PRT, RLED_BIT)))


	//---------------------------------------------------------------
	//---------------------------------------------------------------
	#define SIGNAL_ON_DUR										2
	#define SIGNAL_OFF_DUR									6

	#define BOOT_sign												2
	#define OK_sign													1
	#define ERROR_sign											3


	//***************************************************************************************
	//***************************************************************************************	
	void HW_init(void)
	{
		//--------- Initial all inputs/outputs & Start values
		BUZER_init();						// output & OFF
		
		GLED_init();						// output & OFF
		RLED_init();						// output & OFF
	}	//HW_init
	
	void BUZZER(unsigned char times)
	{
		unsigned char 				i;

		for(i=0; i<times; i++)
		{
			BUZER(ON);
				_delay_ms(SIGNAL_ON_DUR *30);
			
			BUZER(OFF);
				_delay_ms(SIGNAL_OFF_DUR *30);
		}
	}	//BUZZER
	
#endif //_SPWMHW_H_
