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
Timer timer(1000);

void setup () {
	//DDRB = (DDRB | led_mask) & ~bot_mask;
	sei(); //enable interruptions
}

bool val_botao=false;
char message[8];

bool umavez=false;

void loop() {
	val_botao = !val_botao;
	//led.set(val_botao);
	//sprintf (message, "TESTE\n");// DA UART. RECEBE ESTE TEXTO TODO E ARMAZENA EM UMA FILA DE TAMANHO 8\n");
	//uart.puts(message);
    char teste = uart.get();
	//if(teste != '0'){
//		sprintf (message, "LEU: %c\n", teste);
//		uart.puts(message);
	//}

	//sprintf (message, "micro: %lu\n", timer.micros());
	//uart.puts(message);

	timer.udelay((1000000)/2);
	//timer.delay(1000);
}

int main () {
	setup();
	while(true)
		loop();

}



