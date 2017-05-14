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
#include "UART1.h"
#include "GPIO.h"
#include "Timer.h"
#include "Management.h"
#include "buzzer.h"
#include "RDM6300.h"
//#include <avr/iom2560.h>

const int pin_led_vermelho = 11;
const int pin_led_verde = 9;

const int pin_botao_1 = 12;
const int pin_botao_2 = 13;
const int pin_botao_3 = 7;

const int pin_buzzer = 8;

const int pin_rele = 10;

unsigned long freq_timer = 1000;
unsigned long freq_buzzer = 240000;

UART uart(19200, UART::DATABITS_8, UART::PARITY_NONE, UART::STOPBITS_2);

//NAO SEI SE TA CERTO ISSO!
UART1 serial(19200, UART1::DATABITS_8, UART1::PARITY_NONE, UART1::STOPBITS_2);
RDM6300<UART1> RFID(&serial);

GPIO led_vermelho(pin_led_vermelho, GPIO::OUTPUT);
GPIO led_verde(pin_led_verde, GPIO::OUTPUT);

GPIO botao_1(pin_botao_1, GPIO::INPUT); //ADM
GPIO botao_2(pin_botao_2, GPIO::INPUT); //Abrir porta
GPIO botao_3(pin_botao_3, GPIO::INPUT); //Apagar memoria

buzzer buzz(pin_buzzer, freq_buzzer);

GPIO rele(pin_rele, GPIO::OUTPUT);

Timer timer(freq_timer);

Management<unsigned long> admin(12345);

void setup() {
	sei();
	//enable interruptions
}

bool val_botao_1 = false;
bool val_botao_2 = false;
bool val_botao_3 = false;

char message[16];
bool umavez = false;
unsigned long long tempo_decorrido = 0;

void loop() {
	val_botao_1 = botao_1.get();
	val_botao_2 = botao_2.get();
	val_botao_3 = botao_3.get();

	if (val_botao_1) { // ADM!
		led_verde.set(true);
		led_vermelho.set(true);
		buzz.play(1000);
		timer.udelay((1000000) / 2);
		buzz.play(500);
		timer.udelay((1000000) / 10);
		buzz.play(1000);

//		if(admin.admin_login(RFID.read()) == 0){
		admin.admin_login(12345); //ISSO TA AQUI SO PRA TESTE!!!!!!!!!!!
		tempo_decorrido = timer.millis(); //Para sair do estado de ADM depois de 10s sem uso

		//Liga os dois LEDs para indicar que esta em estado de ADM

		val_botao_1 = false;
		while (!val_botao_1 && ((10000+tempo_decorrido) > timer.millis())) {
			if (val_botao_3) {
				//Apaga toda a memoria
				tempo_decorrido = timer.millis();
			} else {
				//Le se tem algo no RFID
				int ret_add = admin.add(13579);

			}
			val_botao_1 = botao_1.get();
		}
//		}

		//Desloga
		admin.admin_logoff();
		tempo_decorrido = 0;
		led_verde.set(false);
		led_vermelho.set(false);
	}
	else if(val_botao_2){//Abre a porta
		rele.set(true);
		led_verde.set(true);
		buzz.play(1000);
		rele.set(false);
		led_verde.set(false);
	}

	else if(val_botao_3){//Apaga a memoria
		admin.del(0);
	}

//	RFID.read();



}

int main() {
	setup();

	while (true)
		loop();

}

