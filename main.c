#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "UART/UART.h"

void _init_() {
	
	// Configuración de pines como entrada
	DDRC &= ~((1 << DDC0) | (1 << DDC1)); // PC0, PC1 como entrada
	DDRB &= ~((1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3)); // PB0, PB1, PB2, PB3 como entrada

	// Habilitar resistencias pull-up internas
	PORTC |= (1 << DDC0) | (1 << DDC1); // Habilitar pull-ups en PC0 y PC1
	PORTB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3); // Habilitar pull-ups en PB0, PB1, PB2 y PB3
	
	// Configuración de los pines PC0, PC1 (PCINT8, PCINT9)
	PCICR |= (1 << PCIE1); // Habilitar interrupciones por cambio de pin para PCINT[14:8] (Port C)
	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9); // Habilitar PCINT8 (PC0) y PCINT9 (PC1)
	
	// Configuración de los pines PB0, PB1, PB2, PB3 (PCINT0, PCINT1, PCINT2, PCINT3)
	PCICR |= (1 << PCIE0); // Habilitar interrupciones por cambio de pin para PCINT[7:0] (Port B)
	PCMSK0 |= (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2) | (1 << PCINT3); // Habilitar PB0, PB1, PB2, PB3
	
	// Habilitar interrupciones globales
	sei();
}

// ISR para los pines PB0, PB1, PB2, PB3 (PCINT0, PCINT1, PCINT2, PCINT3)
ISR(PCINT0_vect) {
	_delay_ms(20);
	if (!(PINB & (1 << PINB0))) {
		writeUART('3');
	}
	if (!(PINB & (1 << PINB1))) {
		writeUART('4');
	}
	if (!(PINB & (1 << PINB2))) {
		writeUART('5');
	}
	if (!(PINB & (1 << PINB3))) {
		writeUART('6');
	}
}

// ISR para los pines PC0 y PC1 (PCINT8, PCINT9)
ISR(PCINT1_vect) {
	_delay_ms(20);
	if (!(PINC & (1 << PINC0))) {
		writeUART('1');
	}
	if (!(PINC & (1 << PINC1))) {
		writeUART('2');
	}
}

int main(void) {
	_init_();
	initUART9600();	
	while (1) {
	}
}
