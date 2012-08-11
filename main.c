#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>

#include "display.h"
#include "DS1302.h"
#include  "uart.h"
#include  "macro.h"

void initDebug() {
	uart_init();
	stdout= &uart_output;
	stdin= &uart_input;
}

int main(void) {
	initOutput();
	initDebug();
	init();
	while (1) {
		printf("yyyy %u\n", getYear());
		printf("MM %u\n", getMonth());
		printf("dd %u\n", getDate());
		printf("dow %u\n", getDay());
		printf("HH %u\n", getHour());
		printf("mm %u\n", getMinutes());
		printf("ss %u\n", getSeconds());

		setTime(getSeconds(), getSeconds(), getSeconds());

		_delay_ms(500);

	}
}

