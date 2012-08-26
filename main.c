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
#include "macro.h"
#include "buttons.h"


#define CHECK_DELAY 100

void loop();
void setUp();
void checkAllOutputs();
void displayCurrentTime();

const uint32_t HOUR_STEPS[] = { D_ONE, D_TWO, D_THRE, D_FOUR, D_HFVE, D_SIX, D_SEVN, D_EGHT, D_NINE, D_HTEN, D_ELVN,
		D_TWLV };

const uint32_t MINUTE_STEPS[] = { D_OCLK, (D_MFVE | D_PAST), (D_MTEN | D_PAST), (D_QUAR | D_PAST), (D_TWTY | D_PAST),
		(D_MFVE | D_TO | D_HALF), (D_HALF), (D_MFVE | D_PAST | D_HALF), (D_TWTY | D_TO), (D_QUAR | D_TO),
		(D_MTEN | D_TO), (D_MFVE | D_TO) };

int main(void) {
	setUp();
	halt(false);
	while (1) {
		loop();
	}
}

void setUp() {
	initOutput();
	initClock();
	checkAllOutputs();
	enableButtons();
}

void loop() {
	if (buttonIsPressed(HOUR_BTN)) {
		incHour();
	} else if (buttonIsPressed(MINUTE_BTN)) {
		incMinute();
	}
	displayCurrentTime();
	delayMs(LOCK_INPUT_TIME);
}

void setAndWait(uint32_t word) {
	setRegister(word);
	delayMs(CHECK_DELAY);
}

void checkAllOutputs() {
	setAndWait(D_ITIS);
	setAndWait(D_MFVE);
	setAndWait(D_MTEN);
	setAndWait(D_QUAR);
	setAndWait(D_TWTY);
	setAndWait(D_TO);
	setAndWait(D_PAST);
	setAndWait(D_HALF);
	setAndWait(D_ELVN);
	setAndWait(D_TWO);
	setAndWait(D_HTEN);
	setAndWait(D_ONE);
	setAndWait(D_TWLV);
	setAndWait(D_THRE);
	setAndWait(D_FOUR);
	setAndWait(D_SIX);
	setAndWait(D_EGHT);
	setAndWait(D_SEVN);
	setAndWait(D_NINE);
	setAndWait(D_HFVE);
	setAndWait(D_OCLK);
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
	uint32_t registers = D_ITIS;
	uint8_t min = getMinutes();
	uint8_t hour = correctHour(min, getHour());
	registers |= HOUR_STEPS[hour - 1];
	int minIdx = (int) (min / 5);
	registers |= MINUTE_STEPS[minIdx];
	setRegister(registers);
}

