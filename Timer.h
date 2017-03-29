/*
 * Timer.h
 *
 *  Created on: 24 de mar de 2017
 *      Author: gabriel
 */

#ifndef TIMER_H_
#define TIMER_H_

typedef unsigned long Hertz;
typedef unsigned long long Microseconds;
typedef unsigned long long Milliseconds;

class Timer {
public:
	Timer(Hertz freq);
	Milliseconds millis();
	Microseconds micros();
	void delay (Milliseconds ms);
	void udelay (Microseconds us);
	static void isr_handler();

private:
	static unsigned long long _ticks;
	static unsigned long long timer_Count;
	static Milliseconds millisegundos;

};

#endif /* TIMER_H_ */
