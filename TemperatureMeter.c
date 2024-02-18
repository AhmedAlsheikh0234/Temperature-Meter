/*
 * TemperatureMeter.c
 *
 * Created: 12/9/2023 10:21:55 PM
 *  Author: Ahmed Al-Sheikh
 */ 


#include <avr/io.h>
#define  F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ADC_driver.h"
#include "LCD_driver.h"
#include "macros.h"

unsigned char read_val;
unsigned short temp,V;
int main(void)
{
	LCD_clearscr();
	LCD_init();
	ADC_init();
	LCD_sendstring("Temperature=");
    while(1)
    {
        V=ADC_read()*2.5;    //equation of transformation from ADC_READ to Volt(mV)
		if (V>=1000)
		{
			temp=(V-1000)/10;   //if Temp is above 0
			if (temp<10)
			{   
				LCD_movecursor(1,16);
				LCD_sendstring(" ");
				LCD_movecursor(1,13);
				LCD_sendchar(temp+48);
				LCD_sendchar(0xDF);
				LCD_sendchar('C');
				LCD_movecursor(2,1);
				LCD_sendstring("     ");
				
			}
			else if(temp<100)
			{
				LCD_movecursor(1,13);
				LCD_sendstring("   ");
				LCD_movecursor(2,1);
				LCD_sendchar((temp/10)+48);
				LCD_sendchar((temp%10)+48);
				
				LCD_sendchar(0xDF);
				
				LCD_sendchar('C');
			}
			else
			{
				
			}
		}
		else
		{
			temp=(1000-V)/10;       //if Temp is below 0
			if (temp<10)
			 {
				LCD_movecursor(1,13);
				LCD_sendchar('-');	
				LCD_sendchar(temp+48);
						
				LCD_sendchar(0xDF);
					
				LCD_sendstring("C");
				LCD_movecursor(2,1);
				LCD_sendstring("     ");
		   	}
			else if(temp<100)
			{   
				LCD_movecursor(1,13);
				LCD_sendstring("    ");
		    	LCD_movecursor(2,1);
						
				LCD_sendchar('-');
				LCD_sendnumber(temp);
				
				LCD_sendchar(0xDF);
						
				LCD_sendstring("C");
			}
			else
			{
						
			}
					
		}
		    
	}
}