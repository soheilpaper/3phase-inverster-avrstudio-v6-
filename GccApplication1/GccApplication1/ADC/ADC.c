//------------------------------------------------------------------------------
// Copyright:      Pascal Stang ( 30.09.2002 )
// Author:         Pascal Stang - Copyright (C) 2002
// Remarks:        Modified by Sh. Nourbakhsh Rad  at date: 20.10.2008
// known Problems: none
// Version:        2.5.0
// Description:    Analog-to-Digital converter functions for Atmel AVR series
//------------------------------------------------------------------------------

#include "ADC.h"


//! Software flag used to indicate when
/// the a2d conversion is complete.
#if (FastRead ==0) || (FastRead ==1)
	volatile unsigned char 							a2dCompleteFlag;
#endif

// functions

// initialize a2d converter
void a2dInit(void)
{
	a2dTurnOn();																								// enable ADC (turn on ADC power)
	
	a2dSingleSample();																					// default to single sample convert mode
	a2dSetPrescaler(ADC_PRESCALE);															// set default prescaler
	a2dSetReference(ADC_REFERENCE);															// set default reference
	a2dSet10bit();																							// set to right-adjusted result

	#if (FastRead ==0) || (FastRead ==1)
		a2dCompleteFlag = False;																	// clear conversion complete flag

		sbi(ADCSR, ADIE);																					// enable ADC interrupts
	
		sei();																										// turn on interrupts (if not already on)
	#endif
}

// configure A2D converter to Single Sample mode
void a2dSingleSample(void)
{
	cbi(ADCSR, ADFR);
}

// configure A2D converter to Auto Trigger mode
void a2dAutoTrigger(void)
{
	sbi(ADCSR, ADFR);
}

// configure A2D converter right-adjusted result for 10bit conversion result
void a2dSet10bit(void)
{
	cbi(ADMUX, ADLAR);																					// set to right-adjusted result
}

// configure A2D converter right-adjusted result for 8bit conversion result
void a2dSet8bit(void)
{
	sbi(ADMUX, ADLAR);																					// clear right-adjusted result
}

// turn on a2d converter
void a2dTurnOn(void)
{
	sbi(ADCSR, ADEN);																						// enable ADC (turn on ADC power)
}

// turn off a2d converter
void a2dTurnOff(void)
{
	#if (FastRead ==0) || (FastRead ==1)
		cbi(ADCSR, ADIE);																					// disable ADC interrupts
	#endif
	
	cbi(ADCSR, ADEN);																						// disable ADC (turn off ADC power)
}

// configure A2D converter clock division (prescaling)
void a2dSetPrescaler(unsigned char prescale)
{
	outb(ADCSR, ((inb(ADCSR) & ~ADC_PRESCALE_MASK) | prescale));
}

// configure A2D converter voltage reference
void a2dSetReference(unsigned char ref)
{
	outb(ADMUX, ((inb(ADMUX) & ~ADC_REFERENCE_MASK) | (ref<<6)));
}

// sets the a2d input channel
void a2dSetChannel(unsigned char ch)
{
	outb(ADMUX, (inb(ADMUX) & ~ADC_MUX_MASK) | (ch & ADC_MUX_MASK));			// set channel
}

// start a conversion on the current a2d input channel
void a2dStartConvert(void)
{
	#if (FastRead ==0) || (FastRead ==1)
		sbi(ADCSR, ADIF);																					// clear hardware "conversion complete" flag 
	#endif
	
	sbi(ADCSR, ADSC);																						// start conversion
}

// return True if conversion is complete
unsigned char a2dIsComplete(void)
{
	return bit_is_set(ADCSR, ADSC);
}

// Perform a 10-bit conversion
// starts conversion, waits until conversion is done, and returns result
unsigned short a2dConvert10bit(unsigned char ch)
{
	#if (FastRead ==0)
		a2dCompleteFlag = False;																						// clear conversion complete flag
		outb(ADMUX, (inb(ADMUX) & ~ADC_MUX_MASK) | (ch & ADC_MUX_MASK));		// set channel
		
		sbi(ADCSR, ADIF);																										// clear hardware "conversion complete" flag 
		sbi(ADCSR, ADSC);																										// start conversion
		while(!a2dCompleteFlag);																						// wait until conversion complete

	#elif (FastRead ==1)
		sbi(ADCSR, ADIF);																										// clear hardware "conversion complete" flag 
		sbi(ADCSR, ADSC);																										// start conversion
		while(bit_is_set(ADCSR, ADSC));																			// wait until conversion complete

	#endif
	
	return (ADCW);																												// read ADC (full 10 bits);
}

// Perform a 8-bit conversion.
// starts conversion, waits until conversion is done, and returns result
unsigned char a2dConvert8bit(unsigned char ch)
{
	#if (FastRead ==0) || (FastRead ==1)
		// do 10-bit conversion and return highest 8 bits
		return (a2dConvert10bit(ch)>>2);																		// return ADC MSB byte
	
	#else
		return (ADCH);																											// read ADC (8 bits);
		
	#endif
}

//! Interrupt handler for ADC complete interrupt.
ISR_ADC_COMPLETE()
{
	#if (FastRead ==0) || (FastRead ==1)
		// set the a2d conversion flag to indicate "complete"
		a2dCompleteFlag = True;
	#endif
}
