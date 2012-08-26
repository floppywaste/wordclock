#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#include "display.h"
#include "DS1302.h"
#include "uart.h"
#include "macro.h"
#include "buttons.h"

#define CHECK_DELAY 100

void loop();
void setUp();
void initDebug();
void checkAllOutputs();
void displayCurrentTime();

ISR (PCINT2_vect) {
	cli();
	if (button_is_pressed(HOUR_BTN)) {
		incHour();
//		addHours(1);
//		displayCurrentTime();
		delay_ms(LOCK_INPUT_TIME);
	} else if (button_is_pressed(MINUTE_BTN)) {
		incMinute();
//		addMinutes(1);
//		displayCurrentTime();
		delay_ms(LOCK_INPUT_TIME);
	}
	sei();
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

void setUp() {
	initOutput();
//	initDebug();
	initClock();
	checkAllOutputs();
	enableButtons();
//	initTimeInput();
}

void loop() {
	if (button_is_pressed(HOUR_BTN)) {
		incHour();
	} else if (button_is_pressed(MINUTE_BTN)) {
		incMinute();
	}
	displayCurrentTime();
	delay_ms(LOCK_INPUT_TIME);
}

int main(void) {
	setUp();
	halt(false);
	hour(17);
	minutes(58);
	seconds(20);
	while (1) {
		loop();
	}
}

void checkAllOutputs() {
	setTime(0, 0, D3_ITIS);
	_delay_ms(CHECK_DELAY);
	setTime(0, 0, D3_MFVE);
	_delay_ms(CHECK_DELAY);
	setTime(0, 0, D3_MTEN);
	_delay_ms(CHECK_DELAY);
	setTime(0, D2_QUAR, 0);
	_delay_ms(CHECK_DELAY);
	setTime(0, 0, D3_TWTY);
	_delay_ms(CHECK_DELAY);
	setTime(0, D2_TO, 0);
	_delay_ms(CHECK_DELAY);
	setTime(0, D2_PAST, 0);
	_delay_ms(CHECK_DELAY);
	setTime(0, 0, D3_HALF);
	_delay_ms(CHECK_DELAY);
	setTime(D1_ELVN, 0, 0);
	_delay_ms(CHECK_DELAY);
	setTime(0, D2_TWO, 0);
	_delay_ms(CHECK_DELAY);
	setTime(D1_HTEN, 0, 0);
	_delay_ms(CHECK_DELAY);
	setTime(0, D2_ONE, 0);
	_delay_ms(CHECK_DELAY);
	setTime(0, D2_TWLV, 0);
	_delay_ms(CHECK_DELAY);
	setTime(0, D2_THRE, 0);
	_delay_ms(CHECK_DELAY);
	setTime(0, D2_FOUR, 0);
	_delay_ms(CHECK_DELAY);
	setTime(D1_SIX, 0, 0);
	_delay_ms(CHECK_DELAY);
	setTime(D1_EGHT, 0, 0);
	_delay_ms(CHECK_DELAY);
	setTime(D1_SEVN, 0, 0);
	_delay_ms(CHECK_DELAY);
	setTime(D1_NINE, 0, 0);
	_delay_ms(CHECK_DELAY);
	setTime(D1_HFVE, 0, 0);
	_delay_ms(CHECK_DELAY);
	setTime(D1_OCLK, 0, 0);
	_delay_ms(CHECK_DELAY);
}

void initDebug() {
	uart_init();
	stdout= &uart_output;
	stdin= &uart_input;
}

