/*
 * main.cpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: Gabriel e André
 */

#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "GPIO.h"
#include "Timer.h"

const int pin_led = 11;//03;
//const unsigned char led_mask = (1 << pin_led);

const int pin_bot = 12;//04;
//const unsigned char bot_mask = (1 << pin_bot);

unsigned long tempo = 1000;

UART uart(19200,
		  UART::DATABITS_8,
		  UART::PARITY_NONE,
		  UART::STOPBITS_2);

GPIO led(pin_led, GPIO::OUTPUT);
GPIO botao(pin_bot,GPIO::INPUT);
Timer timer(1000);

void setup () {
	//DDRB = (DDRB | led_mask) & ~bot_mask;
	sei();
}

bool val_botao;
char message[8];

void loop() {
	val_botao = botao.get();
	led.set(val_botao);
	//sprintf (message, "LED: %d\n", val_botao);
	//uart.puts(message);
	sprintf (message, "%d\n", timer.millis());
	uart.puts(message);


}

int main () {
	setup();
	while(true)
		loop();

}



