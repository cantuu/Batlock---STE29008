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
unsigned long long Timer::timer_Count = 0;
Milliseconds Timer::millisegundos=0;

Timer::Timer(Hertz freq) {
	TCCR0A = 0x00; //Normal operation
	TCCR0B = 0x05; //division clock to 1024
	TIMSK0 = 0x01; //liga interrupção overflow
	TCNT0 = 0xF0; //0xFF - 16;

	if(freq>0)timer_Count = (1/(float)freq)/(1/15625.0);
}

Milliseconds Timer::millis() {
	return millisegundos;
}
Microseconds Timer::micros() {

}
void Timer::delay(Milliseconds ms) {
	Milliseconds inicial = millisegundos;
	while((inicial+ms)>millisegundos);
}
void Timer::udelay(Microseconds us) {

}
void Timer::isr_handler() {
	TCNT0 = 0xF0;
	_ticks++;

	if((_ticks/timer_Count)>0) millisegundos=(_ticks/timer_Count);
}

ISR(TIMER0_OVF_vect) {
	Timer::isr_handler();
}
