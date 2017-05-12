/*
 * buzzer.h
 *
 *  Created on: May 12, 2017
 *      Author: root
 */

#ifndef BUZZER_H_
#define BUZZER_H_

class buzzer {
public:
	buzzer();
	void play(int ms);
	static void isr_handler();


	private:
		//static const int pin_buzzer=13;
		//GPIO _buzzer(pin_buzzer, GPIO::OUTPUT);

    	static unsigned long long uTmin;
		static unsigned long long _ticks;
		static unsigned long long ciclos;
		static unsigned long long ftimer;
		static unsigned long long atual;

		int div;

};

#endif /* BUZZER_H_ */
