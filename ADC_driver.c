/*
 * ADC_driver.c
 *
 * Created: 12/7/2023 3:37:11 PM
 *  Author: Ahmed Al-Sheikh
 */ 


#include <avr/io.h>
#include "macros.h"
#include "ADC_driver.h"
#include <avr/interrupt.h>

void ADC_init(void)
{	/*sei();    // if you want ADC source of interrrupt active
	set_bit(ADCSRA,ADIE); */
	set_bit(ADMUX,MUX4);             //	activate ADC substraction mode (PA0-PA1) if want else set bit on mux bits (see slides for table)
	set_bit(ADMUX,REFS0);
	set_bit(ADMUX,REFS1);    // internal Vref  ( Vref connected to capacitor to GND ) */
	set_bit(ADCSRA,ADEN);    // ADC ENABLE
	set_bit(ADCSRA,ADPS1);   // Prescaler (/64)  [Freq.=125k]
	set_bit(ADCSRA,ADPS2);    
}
unsigned short ADC_read(void)
{
	unsigned short read_val;
	set_bit(ADCSRA,ADSC);       //start conversion
	while(read_bit(ADCSRA,ADSC)==1); //when conversion finish (start conversion clears and become 0) exit while 
	
	/*OR    while(read_bit(ADCSRA,ADIF)==0);  //when conversion finish exit while
	set_bit(ADCSRA,ADIF);   //clear interrupt flag */
	
	read_val=(ADCL);        // adc 10 bit value stored in return_val (8 bits from ADClow and 2 bits from ADChigh)
	read_val |= (ADCH<<8); 
	return read_val;     /* IMPORTANT READ LOW FIRST THEN HIGH NOT HIGH THEN LOW OR ELSE THE REGISTER WILL BE LOCKED ON FIRST READ */
}