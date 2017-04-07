/*
 * Timer.cpp
 *
 *  Created on: 24 de mar de 2017
 *      Author: gabriel
 */

#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned long long Timer::_ticks = 0;
unsigned long long Timer::ciclos = 0;
Milliseconds Timer::millisegundos=0;
Microseconds Timer::microsegundos;

unsigned long long Timer::uTmin=0;
unsigned long long Timer::uTmax=0;
unsigned long long Timer::ftimer=0;

Timer::Timer(Hertz freq) {
	TCCR0A = 0x00; //Normal operation
//	TCCR0B = 0x05; //division clock to 1024
	TIMSK0 = 0x01; //liga interrupção overflow

	if(freq <= 15000 && freq > 62){
		TCCR0B = 0x05; //division clock to 1024
		div=1024;
	}
	else if(freq < 62000){
		TCCR0B = 0x04; //division clock to 256
		div=256;
	}
	else if(freq < 250000){
		TCCR0B = 0x03; //division clock to 64
		div = 64;
	}
	//else
		//error

	ftimer = F_CPU / float(div);
	uTmin = 1/float(ftimer)*1000000;
	uTmax = 256/float(ftimer)*1000000;

	ciclos = ftimer/float(freq);
	TCNT0 = 0xFF - ciclos ; //0xFF - 16;
}

Milliseconds Timer::millis() {
	return millisegundos;
}
Microseconds Timer::micros() {
	return microsegundos;
}

void Timer::delay(Milliseconds ms) {
	Milliseconds inicial = millisegundos;
	while((inicial+ms)>millisegundos);
}
void Timer::udelay(Microseconds us) {
	Microseconds inicial = microsegundos;
	while((inicial+us)>microsegundos);
}
void Timer::isr_handler() {
 	//TCNT0 = 0xFF - ciclos ; //0xFF - 16;
	_ticks++;

	//Cada tick tem 240 ciclos de duracao de uTmin.
	millisegundos=_ticks*((255-ciclos)*(uTmin/1000.0));
	microsegundos=_ticks*((255-ciclos)*(uTmin));

}

ISR(TIMER0_OVF_vect) {
	Timer::isr_handler();
}
