#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>

#include "display.h"
#include "DS1302.h"
#include  "uart.h"

int main(void) {
	initOutput();
	uart_init();
	stdout= &uart_output;
	stdin= &uart_input;
	init();
	while (1) {

		printf("yyyy %u\n", getYear());
		printf("MM %u\n", getMonth());
		printf("dd %u\n", getDay());
		printf("HH %u\n", getHour());
		printf("mm %u\n", getMinutes());
		printf("ss %u\n", getSeconds());
		printf("reg0 %x\n", read_register(0));
		printf("reg1 %x\n", read_register(1));
		printf("reg2 %x\n", read_register(2));
		printf("reg3 %x\n", read_register(3));
		printf("reg4 %x\n", read_register(4));
		printf("reg5 %x\n", read_register(5));
		printf("reg6 %x\n", read_register(6));
		printf("reg7 %x\n", read_register(7));
		setTime(read_register(0),read_register(0),read_register(0));
		_delay_ms(1000);

	}
}

