//-----------------------------------------------------------------------------
// Copyright:      www.KnowledgePlus.ir
// Author:         OZHAN KD modified by Sh. Nourbakhsh Rad
// Remarks:        
// known Problems: none
// Version:        1.1.0
// Description:    SPWM configuration ...
//-----------------------------------------------------------------------------

#ifndef _SPWMC_H_
	#define _SPWMC_H_

  #include "..\app_config.h"


	//----------- Definitions
	#define ACC_DEC_USE											3										//0: Acceleration: disable - Deceleration: disable
																															//1: Acceleration: enable  - Deceleration: disable
																															//2: Acceleration: disable - Deceleration: enable
																															//3: Acceleration: enable  - Deceleration: enable
	// Pins.....
	//------------  PHASE1 (R)
	#define PWMR_PRT												PORTB
	#define PWMR_DDR												DDRB
	#define PWMR_BIT												5

	#define	R_Timer_Reg											TCCR1A
	#define	R_Out_Mode											COM1A1
	#define	R_PWM_Reg												OCR1A
	
	//------------  PHASE2 (S)
	#define PWMS_PRT												PORTB
	#define PWMS_DDR												DDRB
	#define PWMS_BIT												6

	#define	S_Timer_Reg											TCCR1A
	#define	S_Out_Mode											COM1B1
	#define	S_PWM_Reg												OCR1B

	//------------  PHASE3 (T)
	#define PWMT_PRT												PORTB
	#define PWMT_DDR												DDRB
	#define PWMT_BIT												7

	#define	T_Timer_Reg											TCCR1A
	#define	T_Out_Mode											COM1C1
	#define	T_PWM_Reg												OCR1C

	//------------  Speed!
	#define	SPEED_Reg												OCR3A
	#define	SPEED_Intv_Reg									OCR2
	
	//------------  PWM!
	#define PWM_TMR_Reg											TCCR1B
	#define PWM_INTV_Reg										TCCR3B


	//---------------------------------------------------------------
	//---------------------------------------------------------------
	#define	ISR_PWM_SET()										ISR(TIMER3_COMPA_vect)				//PWM   tune interval ISR (every ???      , by FRQ_SET)
	#define	ISR_SPEED_TUNE()								ISR(TIMER2_COMP_vect)					//Speed tune interval ISR (every 1mS now! , by SPEED_INTV_SET)

	//---------------------------------------------------------------
	//Initialize R & S & T, PWM pulse (Timer1: PWM, phase correct, 8bit - mode1, clk/1)
	//
	//See SPWM.h for Prescaler setting, Carrier Frequency ,  Timer1 : "Phase Correct PWM Mode" , Fcarrier = F_CPU /(prescaler *Top)
	#define PWM_TMR_init()									TCCR1A = 0b00000001

	//-----------------------
	//Initialize PWM tune interval (Timer3: Fast PWM - mode15, clk/1)
	//
	//See SPWM.h for Prescaler setting, Main Frequency ,  Timer3 : "Fast PWM Mode" , Fmain = F_CPU /(prescaler *Top) *SIN_points /FRQ
	#define PWM_INTV_init()									TCCR3A = 0b00000011;	\
																					TCCR3B = 0b00011000

 	#define PWM_INTV_ena()									sbi(ETIFR,  OCF3A);		\
 																					sbi(ETIMSK, OCIE3A)
 																					
	#define PWM_INTV_dis()									cbi(ETIMSK, OCIE3A)

	//-----------------------
	//Initialize speed tune interval (Timer2: CTC - mode2, clk/64)
	//
	//Speed tune interval will occur every 1mS , INTVtime = (1000 *F_CPU /prescaler) -1
	#define SPEED_INTV_init()								TCCR2 = 0b00001011

 	#define SPEED_INTV_time									124//229			//About 1mS
 	
 	#define SPEED_INTV_ena()								sbi(TIFR,  OCF2);		\
 																					sbi(TIMSK, OCIE2)
 																					
	#define SPEED_INTV_dis()								cbi(TIMSK, OCIE2)

#endif	//_SPWMC_H_
