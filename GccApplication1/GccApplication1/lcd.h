//LCD Functions Developed by electroSome
#define eS_PORTA0 0
#define eS_PORTA1 1
#define eS_PORTA2 2
#define eS_PORTA3 3
#define eS_PORTA4 4
#define eS_PORTA5 5
#define eS_PORTA6 6
#define eS_PORTA7 7
#define eS_PORTB0 10
#define eS_PORTB1 11
#define eS_PORTB2 12
#define eS_PORTB3 13
#define eS_PORTB4 14
#define eS_PORTB5 15
#define eS_PORTB6 16
#define eS_PORTB7 17
#define eS_PORTC0 20
#define eS_PORTC1 21
#define eS_PORTC2 22
#define eS_PORTC3 23
#define eS_PORTC4 24
#define eS_PORTC5 25
#define eS_PORTC6 26
#define eS_PORTC7 27
#define eS_PORTD0 30
#define eS_PORTD1 31
#define eS_PORTD2 32
#define eS_PORTD3 33
#define eS_PORTD4 34
#define eS_PORTD5 35
#define eS_PORTD6 36
#define eS_PORTD7 37

#ifndef D0
#define D0 eS_PORTA0
#define D1 eS_PORTA1
#define D2 eS_PORTA2
#define D3 eS_PORTA3
#endif

#include<util/delay.h>

void pinChange(int a, int b)
{
	if(b == 0)
	{
		if(a == eS_PORTA0)
		  PORTA &= ~(1<<PA0);
		else if(a == eS_PORTA1)
		  PORTA &= ~(1<<PA1); 
		else if(a == eS_PORTA2)
		  PORTA &= ~(1<<PA2);
		else if(a == eS_PORTA3)
		  PORTA &= ~(1<<PA3); 
		else if(a == eS_PORTA4)
		  PORTA &= ~(1<<PA4); 
		else if(a == eS_PORTA5)
		  PORTA &= ~(1<<PA5); 
		else if(a == eS_PORTA6)
		  PORTA &= ~(1<<PA6);  
		else if(a == eS_PORTA7)
		  PORTA &= ~(1<<PA7);
		else if(a == eS_PORTB0)
		  PORTB &= ~(1<<PB0);  
		else if(a == eS_PORTB1)
		  PORTB &= ~(1<<PB1);
		else if(a == eS_PORTB2)
		  PORTB &= ~(1<<PB2);  
		else if(a == eS_PORTB3)
		  PORTB &= ~(1<<PB3);  
		else if(a == eS_PORTB4)
		  PORTB &= ~(1<<PB4);  
		else if(a == eS_PORTB5)
		  PORTB &= ~(1<<PB5);  
		else if(a == eS_PORTB6)
		  PORTB &= ~(1<<PB6);  
		else if(a == eS_PORTB7)
		  PORTB &= ~(1<<PB7);
		else if(a == eS_PORTC0)
		  PORTC &= ~(1<<PC0);   
		else if(a == eS_PORTC1)
		  PORTC &= ~(1<<PC1); 
		else if(a == eS_PORTC2)
		  PORTC &= ~(1<<PC2);
		else if(a == eS_PORTC3)
		  PORTC &= ~(1<<PC3);   
		else if(a == eS_PORTC4)
		  PORTC &= ~(1<<PC4);  
		else if(a == eS_PORTC5)
		  PORTC &= ~(1<<PC5);  
        else if(a == eS_PORTC6)
          PORTC &= ~(1<<PC6);		
		else if(a == eS_PORTC7)
		  PORTC &= ~(1<<PC7);
		else if(a == eS_PORTD0)
		  PORTD &= ~(1<<PD0);
		else if(a == eS_PORTD1)
		  PORTD &= ~(1<<PD1);  
		else if(a == eS_PORTD2)
		  PORTD &= ~(1<<PD2);
		else if(a == eS_PORTD3)
		  PORTD &= ~(1<<PD3);
		else if(a == eS_PORTD4)
		  PORTD &= ~(1<<PD4);
		else if(a == eS_PORTD5)
		  PORTD &= ~(1<<PD5);
		else if(a == eS_PORTD6)
		  PORTD &= ~(1<<PD6);   
		else if(a == eS_PORTD7)
		  PORTD &= ~(1<<PD7);           
	}
	else
	{
		if(a == eS_PORTA0)
		  PORTA |= (1<<PA0);
		else if(a == eS_PORTA1)
		  PORTA |= (1<<PA1);
		else if(a == eS_PORTA2)
		  PORTA |= (1<<PA2);
		else if(a == eS_PORTA3)
		  PORTA |= (1<<PA3);
		else if(a == eS_PORTA4)
		  PORTA |= (1<<PA4);
		else if(a == eS_PORTA5)
		  PORTA |= (1<<PA5);
		else if(a == eS_PORTA6)
		  PORTA |= (1<<PA6);
		else if(a == eS_PORTA7)
		  PORTA |= (1<<PA7);
		else if(a == eS_PORTB0)
	  	  PORTB |= (1<<PB0);
		else if(a == eS_PORTB1)
		  PORTB |= (1<<PB1);
		else if(a == eS_PORTB2)
		  PORTB |= (1<<PB2);
		else if(a == eS_PORTB3)
		  PORTB |= (1<<PB3);
		else if(a == eS_PORTB4)
		  PORTB |= (1<<PB4);
		else if(a == eS_PORTB5)
		  PORTB |= (1<<PB5);
		else if(a == eS_PORTB6)
		  PORTB |= (1<<PB6);
		else if(a == eS_PORTB7)
		  PORTB |= (1<<PB7);
		else if(a == eS_PORTC0)
		  PORTC |= (1<<PC0);
		else if(a == eS_PORTC1)
		  PORTC |= (1<<PC1);
		else if(a == eS_PORTC2)
	  	  PORTC |= (1<<PC2);
		else if(a == eS_PORTC3)
		  PORTC |= (1<<PC3);
		else if(a == eS_PORTC4)
		  PORTC |= (1<<PC4);
		else if(a == eS_PORTC5)
		  PORTC |= (1<<PC5);
		else if(a == eS_PORTC6)
		  PORTC |= (1<<PC6);  
		else if(a == eS_PORTC7)
		  PORTC |= (1<<PC7);
		else if(a == eS_PORTD0)
		  PORTD |= (1<<PD0);
		else if(a == eS_PORTD1)
		  PORTD |= (1<<PD1);
		else if(a == eS_PORTD2)
		  PORTD |= (1<<PD2);
		else if(a == eS_PORTD3)
		  PORTD |= (1<<PD3);
		else if(a == eS_PORTD4)
		  PORTD |= (1<<PD4);
		else if(a == eS_PORTD5)
		  PORTD |= (1<<PD5);
		else if(a == eS_PORTD6)
		  PORTD |= (1<<PD6);
		else if(a == eS_PORTD7)
		  PORTD |= (1<<PD7);
	}
}



//LCD 8 Bit Interfacing Functions
void Lcd8_Port(char a)
{
	if(a & 1)
	pinChange(D0,1);
	else
	pinChange(D0,0);
	
	if(a & 2)
	pinChange(D1,1);
	else
	pinChange(D1,0);
	
	if(a & 4)
	pinChange(D2,1);
	else
	pinChange(D2,0);
	
	if(a & 8)
	pinChange(D3,1);
	else
	pinChange(D3,0);
	
	if(a & 16)
	pinChange(D4,1);
	else
	pinChange(D4,0);

	if(a & 32)
	pinChange(D5,1);
	else
	pinChange(D5,0);
	
	if(a & 64)
	pinChange(D6,1);
	else
	pinChange(D6,0);
	
	if(a & 128)
	pinChange(D7,1);
	else
	pinChange(D7,0);
}
void Lcd8_Cmd(char a)
{
	pinChange(RS,0);             // => RS = 0
	Lcd8_Port(a);             //Data transfer
	pinChange(EN,1);             // => E = 1
	_delay_ms(1);
	pinChange(EN,0);             // => E = 0
	_delay_ms(1);
}

void Lcd8_Clear()
{
	Lcd8_Cmd(1);
}

void Lcd8_Set_Cursor(char a, char b)
{
	if(a == 1)
	Lcd8_Cmd(0x80 + b);
	else if(a == 2)
	Lcd8_Cmd(0xC0 + b);
}

void Lcd8_Init()
{
	pinChange(RS,0);
	pinChange(EN,0);
	_delay_ms(20);
	///////////// Reset process from datasheet /////////
	Lcd8_Cmd(0x30);
	_delay_ms(5);
	Lcd8_Cmd(0x30);
	_delay_ms(1);
	Lcd8_Cmd(0x30);
	_delay_ms(10);
	/////////////////////////////////////////////////////
	Lcd8_Cmd(0x38);    //function set
	Lcd8_Cmd(0x0C);    //display on,cursor off,blink off
	Lcd8_Cmd(0x01);    //clear display
	Lcd8_Cmd(0x06);    //entry mode, set increment
}

void Lcd8_Write_Char(char a)
{
	pinChange(RS,1);             // => RS = 1
	Lcd8_Port(a);             //Data transfer
	pinChange(EN,1);             // => E = 1
	_delay_ms(1);
	pinChange(EN,0);             // => E = 04
	_delay_ms(1);
}

void Lcd8_Write_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	Lcd8_Write_Char(a[i]);
}

void Lcd8_Shift_Right()
{
	Lcd8_Cmd(0x1C);
}

void Lcd8_Shift_Left()
{
	Lcd8_Cmd(0x18);
}
//End LCD 8 Bit Interfacing Functions

//LCD 4 Bit Interfacing Functions

void Lcd4_Port(char a)
{
	if(a & 1)
	pinChange(D4,1);
	else
	pinChange(D4,0);
	
	if(a & 2)
	pinChange(D5,1);
	else
	pinChange(D5,0);
	
	if(a & 4)
	pinChange(D6,1);
	else
	pinChange(D6,0);
	
	if(a & 8)
	pinChange(D7,1);
	else
	pinChange(D7,0);
}
void Lcd4_Cmd(char a)
{
	pinChange(RS,0);             // => RS = 0
	Lcd4_Port(a);
	pinChange(EN,1);            // => E = 1
	_delay_ms(1);
	pinChange(EN,0);             // => E = 0
	_delay_ms(1);
}

void Lcd4_Clear()
{
	Lcd4_Cmd(0);
	Lcd4_Cmd(1);
}

void Lcd4_Set_Cursor(char a, char b)
{
	char temp,z,y;
	if(a == 1)
	{
		temp = 0x80 + b;
		z = temp>>4;
		y = (0x80+b) & 0x0F;
		Lcd4_Cmd(z);
		Lcd4_Cmd(y);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b;
		z = temp>>4;
		y = (0xC0+b) & 0x0F;
		Lcd4_Cmd(z);
		Lcd4_Cmd(y);
	}
}

void Lcd4_Init()
{
	Lcd4_Port(0x00);
	_delay_ms(20);
	///////////// Reset process from datasheet /////////
	Lcd4_Cmd(0x03);
	_delay_ms(5);
	Lcd4_Cmd(0x03);
	_delay_ms(11);
	Lcd4_Cmd(0x03);
	/////////////////////////////////////////////////////
	Lcd4_Cmd(0x02);
	Lcd4_Cmd(0x02);
	Lcd4_Cmd(0x08);
	Lcd4_Cmd(0x00);
	Lcd4_Cmd(0x0C);
	Lcd4_Cmd(0x00);
	Lcd4_Cmd(0x06);
}

void Lcd4_Write_Char(char a)
{
	char temp,y;
	temp = a&0x0F;
	y = a&0xF0;
	pinChange(RS,1);             // => RS = 1
	Lcd4_Port(y>>4);             //Data transfer
	pinChange(EN,1);
	_delay_ms(1);
	pinChange(EN,0);
	_delay_ms(1);
	Lcd4_Port(temp);
	pinChange(EN,1);
	_delay_ms(1);
	pinChange(EN,0);
	_delay_ms(1);
}

void Lcd4_Write_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	Lcd4_Write_Char(a[i]);
}

void Lcd4_Shift_Right()
{
	Lcd4_Cmd(0x01);
	Lcd4_Cmd(0x0C);
}

void Lcd4_Shift_Left()
{
	Lcd4_Cmd(0x01);
	Lcd4_Cmd(0x08);
}
//End LCD 4 Bit Interfacing Functions
