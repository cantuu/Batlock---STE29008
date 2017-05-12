/*
 * buzzer.cpp
 *
 *  Created on: May 12, 2017
 *      Author: root
 */

#include "buzzer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "GPIO.h"

unsigned long long buzzer::_ticks = 0;
unsigned long long buzzer::ciclos = 0;
unsigned long long buzzer::uTmin=0;
unsigned long long buzzer::ftimer=0;
unsigned long long buzzer::atual=0;

buzzer::buzzer() {
/*	TCCR2A = 0x02; //WGM20 e WGM21 para fast pwm
	TIMSK2 = 0x01; //liga interrupção overflow
//	TCCR0B = 0x03; //division clock to 64
//	div = 64;
	div = 1;

	ftimer = F_CPU / float(div);
	uTmin = 1/float(ftimer)*1000000;

	ciclos = ftimer/float(1000000);
	TCNT2 = 0xFF - ciclos ; //0xFF - 16;*/


		TCCR2A = 0x00; //WGM20 e WGM21 para fast pwm
		TIMSK2 = 0x01; //liga interrupção overflow
		TCCR2B = 0x03; //division clock to 64
		div = 64;
	//	div = 1;

		ftimer = F_CPU / float(div);
		uTmin = 1/float(ftimer)*1000000;

		ciclos = ftimer/float(240000);
		TCNT2 = 0xFF - ciclos ; //0xFF - 16;
}


void buzzer::play(int ms){
	GPIO _buzzer(10, GPIO::OUTPUT);

	unsigned long long inicial = atual;
	while((inicial+ms)>atual){_buzzer.set(true);
	_buzzer.set(false);}
	_buzzer.set(false);
}

void buzzer::isr_handler() {


 	//TCNT0 = 0xFF - ciclos ; //0xFF - 16;
	_ticks++;

	//Cada tick tem 240 ciclos de duracao de uTmin.
	atual=_ticks*((255-ciclos)*(uTmin/1000.0));

}

ISR(TIMER2_OVF_vect) {
	buzzer::isr_handler();
}
