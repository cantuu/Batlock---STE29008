/*
 * buzzer.cpp
 *
 *  Created on: May 12, 2017
 *      Author: root
 */

#include "buzzer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/iom2560.h>

unsigned long long buzzer::_ticks = 0;
unsigned long long buzzer::ciclos = 0;
unsigned long long buzzer::uTmin = 0;
unsigned long long buzzer::ftimer = 0;
unsigned long long buzzer::atual = 0;
int buzzer::_pin=0;

buzzer::buzzer(int pin, unsigned long Hertz){
	_pin = pin;

	TCCR2A = 0x00; //WGM20 e WGM21 para fast pwm
//	TCCR2A = 0x02; //WGM20 e WGM21 para fast pwm
	TCCR2B = 0x03; //division clock to 64
	div = 64;

	ftimer = F_CPU / float(div);
	uTmin = 1 / float(ftimer) * 1000000;

	ciclos = ftimer / float(Hertz);
	TCNT2 = 0xFF - ciclos; //0xFF - 16;
}

void buzzer::play(int ms) {
	unsigned long long inicial = atual;

	TIMSK2 = 0x01; //Liga interrupção overflow
	while ((inicial + ms) > atual);
	TIMSK2 = 0x00; //Desliga interrupção overflow
}

void buzzer::isr_handler() {
	GPIO _buzzer(_pin, GPIO::OUTPUT);
	_buzzer.set(true);
	_buzzer.set(false);

	//TCNT0 = 0xFF - ciclos ; //0xFF - 16;
	_ticks++;

	//Cada tick tem 240 ciclos de duracao de uTmin.
	atual = _ticks * ((255 - ciclos) * (uTmin / 1000.0));

}

ISR(TIMER2_OVF_vect) {
	buzzer::isr_handler();
}
