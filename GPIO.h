/*
 * GPIO.h
 *
 *  Created on: 22 de mar de 2017
 *      Author: gabriel
 */
#include <stdint.h>
#ifndef GPIO_H_
#define GPIO_H_

class GPIO {
public:
	enum PortDirection_t{
		OUTPUT = 1,
		INPUT = 0
	};

	GPIO(int pin, PortDirection_t dir);
	~GPIO();
	bool get();
	void set(bool val);

private:
	unsigned char pin_mask;
	volatile uint8_t *_ddr;
	volatile uint8_t *_pin;
	volatile uint8_t *_port;
};

#endif /* GPIO_H_ */
