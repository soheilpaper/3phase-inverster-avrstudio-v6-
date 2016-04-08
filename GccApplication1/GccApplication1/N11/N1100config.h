//-----------------------------------------------------------------------------
// Copyright:      RAD Electronic Co. LTD,
// Author:         Sh. Nourbakhsh Rad
// Remarks:        
// known Problems: none
// Version:        3.5.1
// Description:    NOKIA 1100 Display (PCF8814) driver
//-----------------------------------------------------------------------------
//
//
//		display: rear site, pin 1 on left site
//		.														.
//		.														.
//		|			  	rear side  				|
//		|___________________________|
//		|   _  | | | | | | | |  _   |
//		|  |   8             1   |  |
//		|__|                     |__| 
//
//		1 XRES Reset
//		2 XCS Chip Select
//		3 VSS (GND) Ground
//		4 SDA Serial Data
//		5 SCLK Serial Clock
//		6 VDDI Power supply 1.8v - max. 3.3v
//		7 VDD Power supply  2.8v - max. 3.3v
//		8 LED+ Power Led
//-----------------------------------------------------------------------------

#ifndef _N1100C_H_
	#define _N1100C_H_

  #include "..\app_config.h"

	
	//----------- Definitions
	#define LCDlight												1					// 0: normal LCD
																										// 1: light LCD ( simple, read from LCD impossible! )
																										// 2: light LCD ( very simple, only upper case letters text!!)
	
	#define MirrorY													1					//	mirror Y axis (about X axis)
	#define InvertScreen										1					//	invert screen in horizontal axis

	
	// Pins.....
	#define N11_CS_DDR											DDRD
	#define N11_CS_PRT											PORTD
	#define N11_CS_BIT											3
	//------
	#define N11_SDA_DDR											DDRD
	#define N11_SDA_PRT											PORTD
	#define N11_SDA_BIT											1

	#define N11_SCL_DDR											DDRD
	#define N11_SCL_PRT											PORTD
	#define N11_SCL_BIT											0
	//------
	#define N11_RST_DDR											DDRD
	#define N11_RST_PRT											PORTD
	#define N11_RST_BIT											2

	#define N11_BKL_DDR											DDRD
	#define N11_BKL_PRT											PORTD
	//#define N11_BKL_BIT											4

	//---------------------------------------------------------------
	#define N11_CS_init()										sbi(N11_CS_DDR,N11_CS_BIT);		sbi(N11_CS_PRT,N11_CS_BIT)

	#define N11_SDA_init()									sbi(N11_SDA_DDR,N11_SDA_BIT); cbi(N11_SDA_PRT,N11_SDA_BIT)
	#define N11_SCL_init()									sbi(N11_SCL_DDR,N11_SCL_BIT); cbi(N11_SCL_PRT,N11_SCL_BIT)

	//---------------------
	#define N11_CS(x)												(x ? (sbi(N11_CS_PRT,N11_CS_BIT))   : (cbi(N11_CS_PRT,N11_CS_BIT)))

	#define N11_SDA(x)											(x ? (sbi(N11_SDA_PRT,N11_SDA_BIT)) : (cbi(N11_SDA_PRT,N11_SDA_BIT)))
	#define N11_SCL(x)											(x ? (sbi(N11_SCL_PRT,N11_SCL_BIT)) : (cbi(N11_SCL_PRT,N11_SCL_BIT)))

	//---------------------------------------------------------------
	#ifdef N11_RST_BIT
		#define N11_RST_init()								sbi(N11_RST_DDR,N11_RST_BIT); cbi(N11_RST_PRT,N11_RST_BIT)
		#define N11_RST(x)										(x ? (sbi(N11_RST_PRT,N11_RST_BIT)) : (cbi(N11_RST_PRT,N11_RST_BIT)))
	#else
		#define N11_RST_init()
		#define N11_RST(x)
	#endif

	#ifdef N11_BKL_BIT
		#define N11_BKL_init()								sbi(N11_BKL_DDR,N11_BKL_BIT); cbi(N11_BKL_PRT,N11_BKL_BIT)
		#define N11_BKL(x)										(x ? (sbi(N11_BKL_PRT,N11_BKL_BIT)) : (cbi(N11_BKL_PRT,N11_BKL_BIT)))
	#else
		#define N11_BKL_init()
		#define N11_BKL(x)
	#endif

#endif	//_N1100C_H_