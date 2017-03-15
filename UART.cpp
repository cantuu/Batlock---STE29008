/*
 * UART.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */

#include "UART.h"
#include <avr/io.h>

UART::UART(int bd, int db,
		   int pr, int sb)
	:_baudrate(bd), _databits(db), _parity(pr), _stopbits(sb)
{
	UBRR0 = (F_CPU / (16ul * this->_baudrate))-1;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
}

UART::~UART() {
	// TODO Auto-generated destructor stub
}

void UART::put(unsigned char data) {
	while (!(UCSR0A & (1-UDRE0)));
	UDR0 = data;
}

unsigned char UART::get() {

}

void UART::puts(char * str) {

}
