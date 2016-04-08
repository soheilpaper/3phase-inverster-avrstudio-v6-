
#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif


#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"


#include <avr/io.h>

int main(void)
{
   DDRD = 0xFF;
   DDRC = 0xFF;
   int i;
   Lcd4_Init();
   while(1)
   {
	   Lcd4_Set_Cursor(1,1);
	   Lcd4_Write_String("electroSome LCD Hello World");
	   for(i=0;i<15;i++)
	   {
		   _delay_ms(500);
		   Lcd4_Shift_Left();
	   }
	   for(i=0;i<15;i++)
	   {
		   _delay_ms(500);
		   Lcd4_Shift_Right();
	   }
	   Lcd4_Clear();
	   Lcd4_Set_Cursor(2,1);
	   Lcd4_Write_Char('e');
	   Lcd4_Write_Char('S');
	   _delay_ms(2000);
   }
}