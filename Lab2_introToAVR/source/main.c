/*	Author: xhe058
 *  Partner(s) Name: zhangcheng liang
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include <avr/interrupt.h>
enum States {Start, Init, On, Off}temp;
#include "../header/io.h"
#include "io.c"
void TimerISR();
void TimerOff();
void TimerOn();
void TimerSet(unsigned long M);
void Tick();
//void ADC_init();
//void set_PWM();
//void PWM_on();
//void PWM_off();


volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

//unsigned char i = 0x00;
//unsigned char c = '0';
//unsigned short AD_convert = 0x00;	



int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
	DDRB = 0xFF;
	//DDRD = 0xFF;
	PORTA = 0xFF;
	PORTB = 0x00;
	//PORTD = 0x00;
	temp = Start;
	
	PWM_on();
	
	//ADC_init();
	//LCD_init();
	
	//temp = start;
	//TimerSet(50);//easy for demo
	//TimerSet(300);
	//TimerOn();
	//unsigned char tmpB = 0x00;
	
 /* Insert your solution below */
 
 	//tmpB = ~tmpB;
	//PORTB = tmpB;
	
	while (1) {
		Tick();
		
			
	}
	return 1;

}
/*
void set_PWM(double frequency){
	static double current_frequency;
	if(frequency != current_frequency){
		if(!frequency){
			TCCR3B &= 0x08;
		}else{
			TCCR3B |=0x03;
		}
		if(frequency < 0.954){
			OCR3A = 0xFFFF;
		}else if (frequency>31250){
			OCR3A = 0x0000;
		}else{
			OCR3A = (short)(8000000 / (128 * frequency))-1;
		}
		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on(){
	TCCR3A = (1<<COM3A0);
	TCCR3B = (1<<WGM32) | (1<<CS31) | (1<<CS30);
	set_PWM(0);
}

void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}
*/

void Tick(){
	
	
}


/*
void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 <<ADSC) | (1 << ADATE);
}
*/

void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;	
}

void TimerOff(){
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet (unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
