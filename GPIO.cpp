/*
 * GPIO.cpp
 *
 *  Created on: 22 de mar de 2017
 *      Author: gabriel
 */

#include "GPIO.h"
#include <avr/io.h>
#include <errno.h>

GPIO::GPIO(int pin, PortDirection_t dir) {
	//calcular a mascara
	this->pin_mask = (1<< pin);

	//configurar DDR
	if (pin >= 0 && pin <= 7) {
		//portd
		if(dir == INPUT)
			DDRD = (DDRD & ~pin_mask);
		else
			DDRD = (DDRD | pin_mask);

		_ddr = & DDRD;
		_pin = & PIND;
		_port = & PORTD;
	}
	if (pin >= 8 && pin <= 13) {
		if(dir == INPUT)
			DDRB = (DDRB & ~pin_mask);
		else
			DDRB = (DDRB | pin_mask);
		_ddr = & DDRB;
		_pin = & PINB;
		_port = & PORTB;
	}
}

GPIO::~GPIO() {}

bool GPIO::get() {
	//ler do pin
	return(*_pin & pin_mask);
}

void GPIO::set(bool val) {
	//escrever no PORT
	if(val == true)
		(*_port) = (*_port) | pin_mask;
	else
		(*_port) = (*_port) & ~ pin_mask;

}

