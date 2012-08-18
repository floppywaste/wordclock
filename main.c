#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#include "display.h"
#include "DS1302.h"
#include  "uart.h"
#include  "macro.h"

void initDebug() {
	uart_init();
	stdout= &uart_output;
	stdin= &uart_input;
}

void initTimeInput() {
	DDRD &= ~(1 << DDD6);
	DDRD &= ~(1 << DDD7);

	PORTD |= (1 << PORTD6);
	PORTD |= (1 << PORTD7);

	PCICR |= (1 << PCIE2);     // set PCIE0 to enable PCMSK0 scan
	PCMSK2 |= (1 << PCINT22);   // set PCINT0 to trigger an interrupt on state change
	PCMSK2 |= (1 << PCINT23);   // set PCINT0 to trigger an interrupt on state change

	sei();
}

uint8_t debounce(volatile uint8_t *port, uint8_t pin) {
	if (!(*port & (1 << pin))) {
		/* Pin wurde auf Masse gezogen, 100ms warten   */
		_delay_ms(10);   // Maximalwert des Parameters an _delay_ms
		_delay_ms(10);   // beachten, vgl. Dokumentation der avr-libc
		if (*port & (1 << pin)) {
			/* Anwender Zeit zum Loslassen des Tasters geben */
			_delay_ms(10);
			_delay_ms(10);
			return 1;
		}
	}
	return 0;
}

char taster(void) {
	static unsigned char zustand;
	char rw = 0;

	if (zustand == 0 && !(PIND & (1 << PD6)))   //Taster wird gedrueckt (steigende Flanke)
			{
		zustand = 1;
		rw = 1;
	} else if (zustand == 1 && !(PIND & (1 << PD6)))   //Taster wird gehalten
			{
		zustand = 2;
		rw = 0;
	} else if (zustand == 2 && (PIND & (1 << PD6)))   //Taster wird losgelassen (fallende Flanke)
			{
		zustand = 3;
		rw = 0;
	} else if (zustand == 3 && (PIND & (1 << PD6)))   //Taster losgelassen
			{
		zustand = 0;
		rw = 0;
	}

	return rw;
}

ISR (PCINT2_vect) {
	if (taster()) {
		addMinutes(1);
		SET(PORTC, PC5);
	} else {
		CLR(PORTC, PC5);
	}
//	if (debounce(&PIND, PD7)) {
//		addHours(1);
//	}
	// printf("int: %x", PORTD);
}

void setUp() {
	SET(DDRC, DDC5);
	SET(PORTC, PC5);

	initOutput();
//	initDebug();
	initClock();
//	initTimeInput();
}

uint8_t correctHour(uint8_t min, uint8_t hour) {
	uint8_t correctedHour = hour;
	bool nextHour = (min >= 25);
	if (nextHour) {
		correctedHour = (hour + 1) % 24;
	}
	if (correctedHour == 0) {
		hour = 12;
	} else if (correctedHour > 12) {
		correctedHour -= 12;
	}

	return correctedHour;
}

int between(uint8_t min, uint8_t loBound, uint8_t hiBound) {
	return min >= loBound && min < hiBound;
}

void displayCurrentTime() {
	uint8_t reg1 = 0;
	uint8_t reg2 = 0;
	uint8_t reg3 = D3_ITIS;

	uint8_t min = getMinutes();
	uint8_t hour = correctHour(min, getHour());
	switch (hour) {
	case 1:
		reg2 |= D2_ONE;
		break;
	case 2:
		reg2 |= D2_TWO;
		break;
	case 3:
		reg2 |= D2_THRE;
		break;
	case 4:
		reg2 |= D2_FOUR;
		break;
	case 5:
		reg1 |= D1_HFVE;
		break;
	case 6:
		reg1 |= D1_SIX;
		break;
	case 7:
		reg1 |= D1_SEVN;
		break;
	case 8:
		reg1 |= D1_EGHT;
		break;
	case 9:
		reg1 |= D1_NINE;
		break;
	case 10:
		reg1 |= D1_HTEN;
		break;
	case 11:
		reg1 |= D1_ELVN;
		break;
	case 12:
		reg2 |= D2_TWLV;
		break;
	}

	if (between(min, 0, 5)) {
		reg1 |= D1_OCLK;
	} else if (between(min, 5, 10)) {
		reg3 |= D3_MFVE;
		reg2 |= D2_PAST;
	} else if (between(min, 10, 15)) {
		reg3 |= D3_MTEN;
		reg2 |= D2_PAST;
	} else if (between(min, 15, 20)) {
		reg2 |= D2_QUAR | D2_PAST;
	} else if (between(min, 20, 25)) {
		reg3 |= D3_TWTY;
		reg2 |= D2_PAST;
	} else if (between(min, 25, 30)) {
		reg3 |= D3_MFVE | D3_HALF;
		reg2 |= D2_TO;
	} else if (between(min, 30, 35)) {
		reg3 |= D3_HALF;
	} else if (between(min, 35, 40)) {
		reg3 |= D3_MFVE | D3_HALF;
		reg2 |= D2_PAST;
	} else if (between(min, 40, 45)) {
		reg3 |= D3_TWTY;
		reg2 |= D2_TO;
	} else if (between(min, 45, 50)) {
		reg2 |= D2_QUAR | D2_TO;
	} else if (between(min, 50, 55)) {
		reg3 |= D3_MTEN;
		reg2 |= D2_TO;
	} else if (between(min, 55, 60)) {
		reg3 |= D3_MFVE;
		reg2 |= D2_TO;
	}

	setTime(reg1, reg2, reg3);
}

void checkAllOutputs() {
	setTime(0, 0, D3_ITIS);
	_delay_ms(30);
	setTime(0, 0, D3_MFVE);
	_delay_ms(30);
	setTime(0, 0, D3_MTEN);
	_delay_ms(30);
	setTime(0, D2_QUAR, 0);
	_delay_ms(30);
	setTime(0, 0, D3_TWTY);
	_delay_ms(30);
	setTime(0, D2_TO, 0);
	_delay_ms(30);
	setTime(0, D2_PAST, 0);
	_delay_ms(30);
	setTime(0, 0, D3_HALF);
	_delay_ms(30);
	setTime(D1_ELVN, 0, 0);
	_delay_ms(30);
	setTime(0, D2_TWO, 0);
	_delay_ms(30);
	setTime(D1_HTEN, 0, 0);
	_delay_ms(30);
	setTime(0, D2_ONE, 0);
	_delay_ms(30);
	setTime(0, D2_TWLV, 0);
	_delay_ms(30);
	setTime(0, D2_THRE, 0);
	_delay_ms(30);
	setTime(0, D2_FOUR, 0);
	_delay_ms(30);
	setTime(D1_SIX, 0, 0);
	_delay_ms(30);
	setTime(D1_EGHT, 0, 0);
	_delay_ms(30);
	setTime(D1_SEVN, 0, 0);
	_delay_ms(30);
	setTime(D1_NINE, 0, 0);
	_delay_ms(30);
	setTime(D1_HFVE, 0, 0);
	_delay_ms(30);
	setTime(D1_OCLK, 0, 0);
	_delay_ms(30);
}

void loop() {
	checkAllOutputs();
	hour(15);
	minutes(43);
	seconds(30);
	while (1) {
		displayCurrentTime();
		_delay_ms(500);
	}
}

int main(void) {
	setUp();
	halt(false);
	loop();
}

