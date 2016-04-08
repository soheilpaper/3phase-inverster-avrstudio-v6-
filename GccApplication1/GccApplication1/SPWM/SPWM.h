//-----------------------------------------------------------------------------
// Copyright:      www.KnowledgePlus.ir
// Author:         OZHAN KD modified by Sh. Nourbakhsh Rad
// Remarks:        
// known Problems: none
// Version:        1.2.0
// Description:    SPWM ...
//-----------------------------------------------------------------------------

#ifndef _SPWM_H_
	#define _SPWM_H_

	#include "SPWMconfig.h"

	
	//----------- Definitions
	#define freq_Base 											50U  // 50Hz
	#define freq_Boost 											10U  // 10Hz
	#define A_Boost 												25UL //
	
	#define f_Base 													(freq_Base  *10U -5U)
	#define f_Boost 												(freq_Boost *10U -5U)
	
	#define N															 	(255UL  -A_Boost)
	#define M 															(f_Base -f_Boost)

	//---------------------
	#define R_offset												0
	#define S_offset												84U
	#define T_offset												170U

	#define R_Index(indx)										(unsigned char)(indx +R_offset)
	#define S_Index(indx)										(unsigned char)(indx +S_offset)
	#define T_Index(indx)										(unsigned char)(indx +T_offset)
	
	//---------------------------------------------------------------
	extern volatile unsigned int 						TCounter;

	//---------------------------------------------------------------
	#define TMR_PRS_MASK										0x07
	#define TMR_PRESCL_set(reg, prs)				reg = ((reg & ~TMR_PRS_MASK) | (prs & TMR_PRS_MASK))

	// Timer prescaler factors
	#ifndef TMR_Prescale
		typedef enum {
				PRS_CLK0				=	0x00,						//prescaler: clk/off
				PRS_CLK1				=	0x01,						//prescaler: clk/1
				PRS_CLK8				=	0x02,						//prescaler: clk/8
				PRS_CLK64				=	0x03,						//prescaler: clk/64
				PRS_CLK256			=	0x04,						//prescaler: clk/256
				PRS_CLK1024			=	0x05						//prescaler: clk/1024
			} TMR_Prescale;
	#endif
		
	//---------------------
	#define TMR_CLK_OFF(reg)								TMR_PRESCL_set(reg, PRS_CLK0)
	#define TMR_CLK_ON(reg, prs)						TMR_PRESCL_set(reg, prs)

	//---------------------------------------------------------------
	//---------------------------------------------------------------
	//Carrier Frequency ,  Timer1 : "Phase Correct PWM Mode" , Fcarrier = F_CPU /(prescaler *Top)
	#define PWM_TMR_ON()										TMR_PRESCL_set(PWM_TMR_Reg, PRS_CLK1)
	#define PWM_TMR_OFF()										TMR_PRESCL_set(PWM_TMR_Reg, PRS_CLK0)
	
	//Main Frequency ,  Timer3 : "Fast PWM Mode" , Fmain = F_CPU /(prescaler *Top) *SIN_points /FRQ
	#define	PWM_INTV_TMR_ON()								TMR_PRESCL_set(PWM_INTV_Reg, PRS_CLK1)
	#define	PWM_INTV_TMR_OFF()							TMR_PRESCL_set(PWM_INTV_Reg, PRS_CLK0)
	
	//---------------------
	#define PWMR_ON()												sbi(R_Timer_Reg, R_Out_Mode)
	#define PWMR_OFF()											cbi(R_Timer_Reg, R_Out_Mode)

	#define PWMS_ON()												sbi(S_Timer_Reg, S_Out_Mode)
	#define PWMS_OFF()											cbi(S_Timer_Reg, S_Out_Mode)

	#define PWMT_ON()												sbi(T_Timer_Reg, T_Out_Mode)
	#define PWMT_OFF()											cbi(T_Timer_Reg, T_Out_Mode)

	//-----------------------
	#define PWMRST_ON()											PWMR_ON();  PWMS_ON();  PWMT_ON()
	#define PWMRST_OFF()										PWMR_OFF(); PWMS_OFF(); PWMT_OFF()

	//---------------------------------------------------------------
	#define PWMR_init()											sbi(PWMR_DDR, PWMR_BIT); PWMR_OFF()
	#define PWMS_init()											sbi(PWMS_DDR, PWMS_BIT); PWMS_OFF()
	#define PWMT_init()											sbi(PWMT_DDR, PWMT_BIT); PWMT_OFF()

	//-----------------------
	#define SPWM_HW_init()									PWMR_init(); PWMS_init(); PWMT_init()

	//---------------------------------------------------------------
	#define PWMR_SET(x)											R_PWM_Reg = x
	#define PWMS_SET(x)											S_PWM_Reg = x
	#define PWMT_SET(x)											T_PWM_Reg = x

	//-----------------------
	#define FRQ_SET(x)											SPEED_Reg = x
	#define SPEED_INTV_SET(x)								SPEED_Intv_Reg = x



	//******************* Function Prototypes
	void SPWM_init(void);
	
	unsigned int SetFrequency(unsigned int FRQ);
	unsigned char SetAcceleration(unsigned char ACC);
	unsigned char SetDeceleration(unsigned char DEC);
	
#endif	//_SPWM_H_
