//------------------------------------------------------------------------------
// Copyright:      Pascal Stang ( 30.09.2002 )
// Author:         Pascal Stang - Copyright (C) 2002
// Remarks:        Modified by Sh. Nourbakhsh Rad  at date: 20.10.2008
// known Problems: none
// Version:        2.5.0
// Description:    Analog-to-Digital converter functions for Atmel AVR series
//------------------------------------------------------------------------------

#ifndef _ADC_H_
	#define _ADC_H_
	
  #include "..\app_config.h"

	#define FastRead												0										//0: Normal reading ADC
																															//1: Fast reading ADC (befor a2dConvert, a2dSetChannel should be set!)
																															//2: Very fast reading ADC without INT (a2dSetChannel, a2dStartConvert and a2dIsComplete should be set and check!)
	
	//************************************************************************** SHN
	#define ADC_PORT												PORTF
	#define ADC_DDR													DDRF
	
	#define	ISR_ADC_COMPLETE()							ISR(ADC_vect)				//Interrupt handler for ADC complete ISR
	
	
	// configure a2d port (PORTA) as input, so we can receive analog signals
	// make sure pull-up resistors are turned off
	#define ADC_CH_init(Achn)								cbi(ADC_DDR,  Achn); cbi(ADC_PORT, Achn)
	
	typedef enum {
			ACH0		= 0x00,
			ACH1		= 0x01,
			ACH2		= 0x02,
			ACH3		= 0x03,
			ACH4		= 0x04,
			ACH5		= 0x05,
			ACH6		= 0x06,
			ACH7		= 0x07,
			ACH8		= 0x08
		} ADC_CHANEL;
	
	//**************************************************************************
	
	// A2D clock prescaler select
	//		*selects how much the CPU clock frequency is divided
	//		to create the A2D clock frequency
	//		*lower division ratios make conversion go faster
	//		*higher division ratios make conversions more accurate
	#define ADC_PRESCALE_DIV2								0x00								///< 0x01,0x00 -> CPU clk/2
	#define ADC_PRESCALE_DIV4								0x02								///< 0x02 -> CPU clk/4
	#define ADC_PRESCALE_DIV8								0x03								///< 0x03 -> CPU clk/8
	#define ADC_PRESCALE_DIV16							0x04								///< 0x04 -> CPU clk/16
	#define ADC_PRESCALE_DIV32							0x05								///< 0x05 -> CPU clk/32
	#define ADC_PRESCALE_DIV64							0x06								///< 0x06 -> CPU clk/64
	#define ADC_PRESCALE_DIV128							0x07								///< 0x07 -> CPU clk/128
	
	// default value
	#define ADC_PRESCALE										ADC_PRESCALE_DIV64
	
	// do not change the mask value
	#define ADC_PRESCALE_MASK								0x07
	
	// A2D voltage reference select
	//		*this determines what is used as the
	//		full-scale voltage point for A2D conversions
	#define ADC_REFERENCE_AREF							0x00								///< 0x00 -> AREF pin, internal VREF turned off
	#define ADC_REFERENCE_AVCC							0x01								///< 0x01 -> AVCC pin, internal VREF turned off
	#define ADC_REFERENCE_RSVD							0x02								///< 0x02 -> Reserved
	#define ADC_REFERENCE_256V							0x03								///< 0x03 -> Internal 2.56V VREF
	
	// default value
	#define ADC_REFERENCE										ADC_REFERENCE_AVCC
	
	// do not change the mask value
	#define ADC_REFERENCE_MASK							0xC0
	
	// bit mask for A2D channel multiplexer
	#define ADC_MUX_MASK										0x1F
	
	// channel defines (for reference and use in code)
	// these channels supported by all AVRs with A2D
	#define ADC_CH_ADC0											0x00
	#define ADC_CH_ADC1											0x01
	#define ADC_CH_ADC2											0x02
	#define ADC_CH_ADC3											0x03
	#define ADC_CH_ADC4											0x04
	#define ADC_CH_ADC5											0x05
	#define ADC_CH_ADC6											0x06
	#define ADC_CH_ADC7											0x07
	#define ADC_CH_122V											0x1E								///< 1.22V voltage reference
	#define ADC_CH_AGND											0x1F								///< AGND
	
	// these channels supported only in ATmega128
	// differential with gain
	#define ADC_CH_0_0_DIFF10X							0x08
	#define ADC_CH_1_0_DIFF10X							0x09
	#define ADC_CH_0_0_DIFF200X							0x0A
	#define ADC_CH_1_0_DIFF200X							0x0B
	#define ADC_CH_2_2_DIFF10X							0x0C
	#define ADC_CH_3_2_DIFF10X							0x0D
	#define ADC_CH_2_2_DIFF200X							0x0E
	#define ADC_CH_3_2_DIFF200X							0x0F
	// differential
	#define ADC_CH_0_1_DIFF1X								0x10
	#define ADC_CH_1_1_DIFF1X								0x11
	#define ADC_CH_2_1_DIFF1X								0x12
	#define ADC_CH_3_1_DIFF1X								0x13
	#define ADC_CH_4_1_DIFF1X								0x14
	#define ADC_CH_5_1_DIFF1X								0x15
	#define ADC_CH_6_1_DIFF1X								0x16
	#define ADC_CH_7_1_DIFF1X								0x17
	                            	
	#define ADC_CH_0_2_DIFF1X								0x18
	#define ADC_CH_1_2_DIFF1X								0x19
	#define ADC_CH_2_2_DIFF1X								0x1A
	#define ADC_CH_3_2_DIFF1X								0x1B
	#define ADC_CH_4_2_DIFF1X								0x1C
	#define ADC_CH_5_2_DIFF1X								0x1D
	
	// compatibility for new Mega processors
	// ADCSR hack apparently no longer necessary in new AVR-GCC
	#ifdef ADCSRA
		#ifndef ADCSR
			#define ADCSR												ADCSRA
		#endif
	#endif
	
	#ifdef ADATE
		#define ADFR													ADATE
	#endif
	
	
	//************************************************************************
	//************************************************ function prototypes
	//************************************************************************
	
	//! Initializes the A/D converter.
	/// Turns ADC on and prepares it for use.
	void a2dInit(void);
	
	//! configure A2D converter to
	/// Single Sample mode
	void a2dSingleSample(void);
	
	//! configure A2D converter to
	/// Auto Trigger mode
	void a2dAutoTrigger(void);
	
	//! configure A2D converter right-adjusted result
	/// for 10bit conversion result
	void a2dSet10bit(void);

	//! configure A2D converter right-adjusted result
	/// for 8bit conversion result
	void a2dSet8bit(void);

	//! Turn on A/D converter
	void a2dTurnOn(void);

	//! Turn off A/D converter
	void a2dTurnOff(void);
	
	//! Sets the division ratio of the A/D converter clock.
	/// This function is automatically called from a2dInit()
	/// with a default value.
	void a2dSetPrescaler(unsigned char prescale);
	
	//! Configures which voltage reference the A/D converter uses.
	/// This function is automatically called from a2dInit()
	/// with a default value.
	void a2dSetReference(unsigned char ref);
	
	//! sets the a2d input channel
	void a2dSetChannel(unsigned char ch);
	
	//! start a conversion on the current a2d input channel
	void a2dStartConvert(void);
	
	//! return TRUE if conversion is complete
	unsigned char a2dIsComplete(void);
	
	//! Starts a conversion on A/D channel# ch,
	/// returns the 10-bit value of the conversion when it is finished.
	unsigned short a2dConvert10bit(unsigned char ch);
	
	//! Starts a conversion on A/D channel# ch,
	/// returns the 8-bit value of the conversion when it is finished.
	unsigned char a2dConvert8bit(unsigned char ch);
	
#endif	//_ADC_H_
