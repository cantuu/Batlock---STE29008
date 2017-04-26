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
unsigned long long tempo_decorrido = 0;

void loop() {
	val_botao = botao.get();

	if(val_botao){
		admin.admin_login(12345);
		led.set(true);
		tempo_decorrido = timer.millis();
	}
	if(tempo_decorrido>0 && ((timer.millis()-tempo_decorrido) > 5000)){
		admin.admin_logoff();
		tempo_decorrido=0;
		led.set(false);
	}


	int teste_Add=3;
	teste_Add = admin.add(13579);
	teste_Add = admin.add(04354);
	teste_Add = admin.add(112233);
	teste_Add = admin.add(112833);

	int size = admin.get_size_db();
	sprintf (message, "size: %d\n", size);
	uart.puts(message);
	timer.udelay((1000000)/2);

	teste_Add = admin.add(152833);

	//timer.delay(1000);
}

int main () {
	setup();
	while(true)
		loop();

}



