#include <avr/io.h>
#include "LCD.h"
#define  F_CPU 1000000UL
#include <util/delay.h>
#include "std_macros.h"

int main(void)
{
	LCD_vInit();
	
	unsigned short a,b,ON,distance;
	
	// Set pin D7 as output for ultrasonic sensor trigger
	DIO_vsetPINDir('D',7,1);
	
	while(1)
	{

		TCCR1A = 0;
		// Clear Input Capture flag
		SET_BIT(TIFR,ICF1);
		
		// Generate pulse to enable ultrasonic sensor
		DIO_write('D',7,1);
		_delay_us(50);
		DIO_write('D',7,0);
		
		// Configure Timer1 for rising edge detection, no prescaler
		TCCR1B = 0xc1;
		while (READ_BIT(TIFR,ICF1) == 0);
		a = ICR1;
		SET_BIT(TIFR,ICF1);
		
		// Configure Timer1 for falling edge detection, no prescaler
		TCCR1B = 0x81;
		while ((TIFR&(1<<ICF1)) == 0);
		b = ICR1;
		SET_BIT(TIFR,ICF1);
		TCNT1=0;
		TCCR1B = 0;
		ON=b-a;
		
		// Calculate distance
		distance=((ON*34600)/(F_CPU*2)) ;
		
		// Display distance on LCD
		if (distance >= 80)
		{
			LCD_clearscreen();
			LCD_vSend_string("   No object");
			_delay_ms(1000);
		}
		else
		{
			LCD_clearscreen();
			LCD_vSend_string("Distance=");
			LCD_vSend_char((distance/10)+48);
			LCD_vSend_char((distance%10)+48);
			LCD_vSend_string("cm");
			_delay_ms(1000);
		}
	}
}
