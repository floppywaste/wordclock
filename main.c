#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>

#include "display.h"
#include "DS1302.h"
#include  "uart.h"
#include  "macro.h"

void __write_out(uint8_t value) {
	SET(DDRB, DDB2);
	for (int i = 0; i < 8; i++) {
//		DS1302_CLK_0;
		CLR(PORTB, PB1);
		_delay_ms(1);
		if (value & 0x01) {
			SET(PORTB, PB2);
//			DS1302_IO_1;
			printf("1");
		} else {
//			DS1302_IO_0;
			CLR(PORTB, PB2);
			printf("0");
		}
		printf("\n");
		_delay_ms(1);
//		DS1302_CLK_1;
		SET(PORTB, PB1);
		_delay_ms(1);
		value >>= 1;

	}
}

uint8_t __read_in() {
	uint8_t input_value = 0;
	CLR(DDRB, DDB2);

	CLR(PORTB, PB1);
	for (int i = 0; i < 8; ++i) {
		printf("%x ", PINB);
		if (PINB & (1 << PB2))
			input_value |= (1 << i);
		printf("\n");
		SET(PORTB, PB1);
		_delay_ms(1);
		CLR(PORTB, PB1);
//		DS1302_CLK_1;
	}

	return input_value;
}

uint8_t _read_register(uint8_t reg) {
	uint8_t cmd_byte = 129; /* 1000 0001 */
	uint8_t reg_value;
	cmd_byte |= (reg << 1);

	printf("cmd_byte %x\n", cmd_byte);

//	DS1302_CLK_0;
	CLR(PORTB, PB1);

	DS1302_RST_1;
	SET(PORTB, PB0);
	__write_out(cmd_byte);
	reg_value = __read_in();

	printf("reg_value %x\n", reg_value);

//	DS1302_RST_0;
	CLR(PORTB, PB0);

	return reg_value;
}

int main(void) {
	initOutput();
	uart_init();
	stdout= &uart_output;
	stdin= &uart_input;
	init();
	SET(DDRB, DDB0);
	SET(DDRB, DDB1);
	while (1) {
		_read_register(0);
		_read_register(1);
		_read_register(2);

//		printf("yyyy %u\n", getYear());
//		printf("MM %u\n", getMonth());
//		printf("dd %u\n", getDay());
//		printf("HH %u\n", getHour());
//		printf("mm %u\n", getMinutes());
//		printf("ss %u\n", getSeconds());
//		printf("reg0 %x\n", read_register(0));
//		printf("reg1 %x\n", read_register(1));
//		printf("reg2 %x\n", read_register(2));
//		printf("reg3 %x\n", read_register(3));
//		printf("reg4 %x\n", read_register(4));
//		printf("reg5 %x\n", read_register(5));
//		printf("reg6 %x\n", read_register(6));
//		printf("reg7 %x\n", read_register(7));
//		setTime(read_register(0),read_register(0),read_register(0));

		_delay_ms(1000);

	}
}

