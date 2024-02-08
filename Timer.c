/*
 * Timer.c
 *
 * Created: 2/6/2024 4:29:47 AM
 *  Author: VTE
 */ 
#include "Timer.h"
void timer0_overflow(void){
	//set prescaler here
	//SET_BIT(TCCR0,CS00)
	//SET_BIT(TCCR0,CS00)
	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,CS00);
	sei();
	SET_BIT(TIMSK,TOIE0);
}
void timer0_ctc(void){
	//set prescaler here
	//SET_BIT(TCCR0,CS00)
	//SET_BIT(TCCR0,CS00)
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,CS00);
	// load value here
	OCR0=0;
	sei();
	SET_BIT(TIMSK,OCF0);
	
}
void timer1_overflow(void){
	
}
void timer1_ctc(void){
	
}
void timer2_overflow(void){
	//set prescaler here
	//SET_BIT(TCCR2,CS20)
	//SET_BIT(TCCR2,CS20)
	CLR_BIT(TCCR2,WGM20);
	CLR_BIT(TCCR2,WGM21);
	SET_BIT(TCCR2,CS20);
	sei();
	SET_BIT(TIMSK,TOIE2);
	
}
void timer2_ctc(void){
	//set prescaler here
	//SET_BIT(TCCR2,CS20)
	//SET_BIT(TCCR2,CS20)
	CLR_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);
	SET_BIT(TCCR2,CS20);
	// load value here
	OCR0=0;
	sei();
	SET_BIT(TIMSK,OCF2);
}
void timer2_overflow_External_clock(void)
{
	// select timer clock 
	SET_BIT(ASSR,AS2);
	// select timer prescalar 
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS22);
	sei();
	SET_BIT(TIMSK,TOIE2);
}
void timer_wave_nonPWM(void)
{

	SET_BIT(DDRB,3);
	// select CTC mode
	SET_BIT(TCCR0,WGM01);
	//load in ocr0
	OCR0=64;
	
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS02);
	// toggle OC0 on compare match
	SET_BIT(TCCR0,COM00);
}

void timer_wave_fastPWM(void)
{
	SET_BIT(DDRB,3);
	// select fast PWM mode
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	// load OCR0 
	OCR0=64;
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS02);
	// Set OC0 on compare match
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
}


void timer_wave_phasecorrectPWM(void)
{
	
	SET_BIT(DDRB,3);
	SET_BIT(TCCR0,WGM00);
	OCR0=64;
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS02);
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
}