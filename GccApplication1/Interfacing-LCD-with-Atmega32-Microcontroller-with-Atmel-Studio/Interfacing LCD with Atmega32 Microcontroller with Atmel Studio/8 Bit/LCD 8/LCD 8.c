
#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#define D0 eS_PORTD0
#define D1 eS_PORTD1
#define D2 eS_PORTD2
#define D3 eS_PORTD3
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
int main(void)
{
    DDRD = 0xFF;
	DDRC = 0xFF;
	int i;
	Lcd8_Init();
	while(1)
	{
		Lcd8_Set_Cursor(1,1);
		Lcd8_Write_String("electroSome LCD Hello World");
		for(i=0;i<15;i++)
		{
			_delay_ms(500);
			Lcd8_Shift_Left();
		}
		for(i=0;i<15;i++)
		{
			_delay_ms(500);
			Lcd8_Shift_Right();
		}
		Lcd8_Clear();
		Lcd8_Write_Char('e');
		Lcd8_Write_Char('S');
		_delay_ms(2000);
	}

	}
