/*
 * UART.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */

#include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "GPIO.h"

FIFO<8> UART::_tx_fifo;
FIFO<8> UART::_rx_fifo;

UART::UART(unsigned long bd,
		   DataBits_t db,
		   ParityBits_t pr,
		   StopBits_t sb)
	:_baudrate(bd),
	 _databits(db),
	 _parity(pr),
	 _stopbits(sb)
{
	//set baudrate
	UBRR0 = (F_CPU / (16ul * this->_baudrate))-1;
	// liga RX e Tx
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	//set databits
	if (_databits == DATABITS_9) {
		UCSR0B = (1<<RXB80)|(1<<TXB80);
		UCSR0B = (UCSR0B & ~(1 << UCSZ02)) | (_databits << UCSZ00);
		//UCSR0C = (UCSR0C & ~(3 << UCSZ00)) | (_databits << UCSZ00);
	}//else
	UCSR0C = (UCSR0C & ~(3 << UCSZ00)) | (_databits << UCSZ00);
	//set parity
	UCSR0C = (UCSR0C & ~(3 << UPM00)) | (_parity << UPM00);
	//set stopbits
	UCSR0C = (UCSR0C & ~(1 << USBS0)) | (_stopbits < USBS0);

	// set frame: 8N1
	//UCSR0C = (3<<UCSZ00);

	//Ativando a interrupçao
	//UCSR0B = (UCSR0B | (1 << TXCIE0));
	UCSR0B |= (1 << RXCIE0);
	UCSR0B &= ~(1 << UDRIE0);


}

UART::~UART() {
	// TODO Auto-generated destructor stub
}

void UART::put(unsigned char data) {
	// wait until UDR is empty
	//while (!(UCSR0A & (1<<UDRE0)));

	// send data
	//UDR0 = data;
	_tx_fifo.push(data);
	UCSR0B |= (1 << UDRIE0);

}


unsigned char UART::get() {
	// wait data until received
	//while (!(UCSR0A & (1<<RXC0)));

	//return received data
	//return UDR0;


	if(_rx_fifo.size()>0){
		return _rx_fifo.pop();
	}
	return '0';

}

void UART::puts(const char * str) {

	while (* str !='\0') {
		put(*str);
		str++;
	}

}

void UART::isr_handler_RX(){
	//Quando recebe algo, empurra na fila
	_rx_fifo.push(UDR0);
}

void UART::isr_handler_TX(){
	//Quando é para enviar algo, dá um pop na fila

	//Devo desativar aqui o UDRE para evitar que ele fique esperando a interrupçao?
	//E daí o ativo somente no puts?
	//http://www.avrfreaks.net/forum/interrupt-driven-usart-1
	if(_tx_fifo.size()>0){
		UDR0 = _tx_fifo.pop();
	}else{
		UCSR0B &= ~(1 << UDRIE0);
	}
}

ISR(USART_RX_vect) {
	UART::isr_handler_RX();
}

ISR(USART_UDRE_vect) {
	UART::isr_handler_TX();

}
