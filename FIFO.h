/*
 * FIFO.h
 *
 *  Created on: Mar 31, 2017
 *      Author: root
 */

#ifndef FIFO_H_
#define FIFO_H_
#include "UART.h"
#include <avr/io.h>
#include <stdio.h>
template <typename T, int Q_SIZE>
class FIFO {
public:
	static const unsigned int FIFO_ERROR_EMPTY = -1;
	static const unsigned int FIFO_ERROR_FULL = -2;

	FIFO() {
		_head = 0;
		_tail = 0;
		_counter_size = 0;
	}

	~FIFO(){};
	void clear () {
		_head = 0;
		_tail = 0;
		_counter_size = 0;
	}

	int push(T value) {
		//if (((this->_tail+1)%Q_SIZE) == _head)
		if (Q_SIZE <= this->_counter_size)
			return (int)FIFO_ERROR_FULL;//ta cheio

		_buffer[_tail] = value;
		this->_counter_size++;
		//_tail = (_tail+1) % Q_SIZE;

		if(_tail == Q_SIZE-1){
			_tail=0;
			//this->clear();
		}else
			_tail++;

		return 0;
	}
	T pop(){
		T returnval;
		//if(_head==_tail)
		if(this->_counter_size==0)
			return (int)FIFO_ERROR_EMPTY;
		returnval=_buffer[_head];
		this->_counter_size--;
		/*_head++;
		if (_head == Q_SIZE) {
			_head = 0;
		}*/
		if(_head == Q_SIZE-1)
			_head=0;
		else
			_head++;

		return returnval;
	}

	int size(){
		return _counter_size;
	}
private:
	int _head, _tail, _counter_size;
	T _buffer[Q_SIZE];
};

#endif /* FIFO_H_ */
