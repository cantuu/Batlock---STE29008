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

UART1 serial(9600, UART1::DATABITS_8, UART1::PARITY_NONE, UART1::STOPBITS_1);
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
bool umavez = true;
unsigned long long tempo_decorrido = 0;

unsigned long lido;

void loop() {

	if(umavez){
		lido = '0';
		while (serial.has_data()) {
			RFID.parse(serial.get());
		}
		if(RFID.get_valid_id()){
			RFID.set_valid_id(false);

			lido = RFID.get_current_id();
			RFID.reset_current();
			umavez=false;
			admin.set_admin(lido);
			buzz.play(1000);
			timer.udelay((1000000) / 5);
			buzz.play(1000);
			timer.udelay((1000000) / 5);
			buzz.play(400);
			timer.udelay((1000000) / 5);
			buzz.play(400);
			timer.udelay((1000000) / 5);
			buzz.play(400);
			timer.udelay((1000000) / 5);

		}

	} else{
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
			 tempo_decorrido = timer.millis(); //Para sair do estado de ADM depois de 10s sem uso

			 while ((10000+tempo_decorrido) > timer.millis()) {//10s para logar como adm
				 while (serial.has_data()) {
								RFID.parse(serial.get());
				}
				if(RFID.get_valid_id()){
					lido=RFID.get_current_id();
					RFID.set_valid_id(false);
					RFID.reset_current();
					if(admin.admin_login(lido)==0){
						 buzz.play(2000);//logou
						 	 	 	 //renovar o tempo e dar 10s pro jogaADM excluir tudo ou add um novo joga
						 	 	 	 tempo_decorrido = timer.millis(); //Para sair do estado de ADM depois de 10s sem uso
									 while ((10000+tempo_decorrido) > timer.millis()) {//10s para logar como adm
										 val_botao_3 = botao_3.get();
										 if(val_botao_3){//Apaga a memoria
											 admin.del(0);
											 buzz.play(5000);
										 } else {
											 while (serial.has_data()) {
														RFID.parse(serial.get());
											}
											if(RFID.get_valid_id()){
												 buzz.play(500);
												 led_verde.set(false);
												 timer.delay(250);
												 buzz.play(500);
												 led_verde.set(true);
												 timer.delay(250);


												 int ret_add = admin.add(RFID.get_current_id());
												 RFID.reset_current();
													RFID.set_valid_id(false);


											}

										 }
									 }
									 break;
					}
				}
				 if(botao_1.get())break;
			 }
			 //		}

			 //Desloga
			 admin.admin_logoff();
			 tempo_decorrido = 0;
			 led_verde.set(false);
			 led_vermelho.set(false);
		 }
		 else	if (val_botao_2==1) { //Abre a porta
			rele.set(false);
			led_verde.set(true);
			buzz.play(1000);
			rele.set(true);
			led_verde.set(false);
		}

		 while (serial.has_data()) {
			        RFID.parse(serial.get());
		}
		if(RFID.get_valid_id()){
			RFID.set_valid_id(false);
			lido = RFID.get_current_id();
			RFID.reset_current();
			RFID.set_valid_id(false);

			if (admin.search(lido) >= 0 || lido==admin.get_admin()) {
				rele.set(false);
				led_verde.set(true);
				buzz.play(1000);
				led_verde.set(false);
				rele.set(true);
			}else{
				led_vermelho.set(true);
				buzz.play(2000);
				timer.delay(500);
				buzz.play(500);
				led_vermelho.set(false);
			}
		}

	}
}

int main() {
	setup();
	rele.set(true);

	while (true)
		loop();

}

