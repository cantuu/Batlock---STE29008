/*
 * UART.h
 *
 *  Created on: 15 de mar de 2017
 *      Author: aluno
 */

#ifndef UART_H_
#define UART_H_

class UART {
public:
	UART(int bd = 19200,
		 int db = 8,
		 int pr = 0,
		 int sb = 1);
	~UART();

	void put(unsigned char data);
	unsigned char get();
	void puts(char * str);

private:
	int _baudrate;
	int _databits;
	int _parity;
	int _stopbits;
};

#endif /* UART_H_ */
