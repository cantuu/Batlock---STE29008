/*
 * GPIO.cpp
 *
 *  Created on: 22 de mar de 2017
 *      Author: gabriel
 */

#include "GPIO.h"
#include <avr/io.h>
#include <errno.h>
//#include <avr/iom2560.h>

GPIO::GPIO(int pin, PortDirection_t dir) {
	//configurar DDR
	if (pin >= 0 && pin <= 7) {
		//portd
		pin += 16;
		this->pin_mask = (1<< pin);

		_ddr = & DDRD;
		_pin = & PIND;
		_port = & PORTD;
	}
	if (pin >= 8 && pin <= 13) {
		pin -= 8;
		this->pin_mask = (1<< 4);

		_ddr = & DDRB;
		_pin = & PINB;
		_port = & PORTB;
	}
	if(dir == INPUT)
		*_ddr = (*_ddr & ~pin_mask);
	else
		*_ddr = (*_ddr | pin_mask);

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

