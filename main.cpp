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
#include "GPIO.h"

const int pin_led = 11;
//const unsigned char led_mask = (1 << pin_led);

const int pin_bot = 12;
//const unsigned char bot_mask = (1 << pin_bot);

unsigned long tempo = 1000;

UART uart(19200,
		  UART::DATABITS_8,
		  UART::PARITY_NONE,
		  UART::STOPBITS_2);

GPIO led(pin_led, GPIO::OUTPUT);
GPIO botao(pin_bot,GPIO::INPUT);

void setup () {
	//DDRB = (DDRB | led_mask) & ~bot_mask;
}

bool val_botao;

void loop() {
	val_botao = botao.get();
	led.set(val_botao);
}

int main () {
	setup();
	while(true)
		loop();

}



