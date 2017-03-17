/*
 * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: Gabriel e André
 */

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "UART.h"

char pin_led = 3;
const unsigned char led_mask = (1 << pin_led);
char pin_bot = 4;
const unsigned char bot_mask = (1 << pin_bot);
unsigned long tempo = 1000;

UART uart;

void setup () {
	DDRB = (DDRB | led_mask) & ~bot_mask;
}

bool ler_botao() {
	return (PINB & bot_mask);
}

void acende_led() {
	PORTB = PORTB | led_mask;
}

void apaga_led() {
	PORTB = PORTB & ~led_mask;
}

void loop() {
	uart.put(uart.get()+1);
	if(ler_botao())	{
		acende_led();
	}else {
		apaga_led();
	}
}

int main () {
	setup();
	while(true)
		loop();

}



