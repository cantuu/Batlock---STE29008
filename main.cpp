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
#include "Management.h"

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
Management<unsigned long> admin(12345);

void setup () {
	sei(); //enable interruptions
}

bool val_botao=false;
char message[16];

bool umavez=false;

void loop() {
	//val_botao = !val_botao;
	//led.set(val_botao);
	//sprintf (message, "TESTE\n");// DA UART. RECEBE ESTE TEXTO TODO E ARMAZENA EM UMA FILA DE TAMANHO 8\n");
	//uart.puts(message);
    //char teste = uart.get();
	//if(teste != '0'){
		//sprintf (message, "LEU: %c\n", teste);
		//uart.puts(message);
	//}

	//sprintf (message, "micro: %lu\n", timer.micros());
	//uart.puts(message);

	admin.admin_login(12345);

	int teste_Add=3;

	teste_Add = admin.add(13579);
	sprintf (message, "ADD 1: %d\n", teste_Add);
	uart.puts(message);
	timer.udelay((1000000)/2);

	teste_Add = admin.add(04354);
	sprintf (message, "ADD 2: %d\n", teste_Add);
	uart.puts(message);
	timer.udelay((1000000)/2);


	teste_Add = admin.add(112233);
	sprintf (message, "ADD 3: %d\n", teste_Add);
	uart.puts(message);
	timer.udelay((1000000)/2);


	teste_Add = admin.add(112833);
	sprintf (message, "ADD 4: %d\n", teste_Add);
	uart.puts(message);
	timer.udelay((1000000)/2);


	int teste_search = 3;

	teste_search = admin.search(112233);
	sprintf (message, "search 1: %d\n", teste_search);
	uart.puts(message);
	timer.udelay((1000000)/2);

	teste_search = admin.search(86523);
	sprintf (message, "search 2: %d\n", teste_search);
	uart.puts(message);
	timer.udelay((1000000)/2);

	int size = admin.get_size_db();
	sprintf (message, "size: %d\n", size);
	uart.puts(message);
	timer.udelay((1000000)/2);

	int teste_del = admin.del(112233);
	sprintf (message, "del: %d\n", teste_del);
	uart.puts(message);
	timer.udelay((1000000)/2);

	//timer.delay(1000);
}

int main () {
	setup();
	while(true)
		loop();

}



