#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>

#include "display.h"
#include "ds1302.h"
#include  "uart.h"

uint8_t _register_bcd_to_dec(uint8_t val, uint8_t high_bit) {
	uint8_t mask = (1 << (high_bit + 1)) - 1;
	val &= mask;
	val = (val & 15) + 10 * ((val & (15 << 4)) >> 4);
	return val;
}

int main(void) {
	initOutput();
	uart_init();
	stdout= &uart_output;
	stdin= &uart_input;
	while (1) {
		ds1302_init();
////		unsigned char now[8];
////		gettime(now);
//
////		char str1[8];
//		DS1302_ReadDateTime();
//
//		printf("time c: %u-%u-%u-%u-%u-%u\n", DateTime.Hour, DateTime.Min,


		unsigned char now[8];
		gettime(now);

		printf("0 %x\n", now[0]);
		printf("1 %x\n", now[1]);
		printf("2 %x\n", now[2]);
		printf("3 %x\n", now[3]);
		printf("4 %x\n", now[4]);
		printf("5 %x\n", now[5]);
		printf("6 %x\n", now[6]);
		printf("7 %x\n", now[7]);
		_delay_ms(1000);
		setTime(now[0], now[0], now[0]);
//		_delay_ms(2000);
//		setTime(now[1], 0, 0);
//		_delay_ms(2000);
//
//		setTime(now[2], 0, 0);
//		_delay_ms(2000);
//		setTime(now[3], 0, 0);
//		_delay_ms(2000);
//		setTime(now[4], 0, 0);
//		_delay_ms(2000);
//		setTime(now[5], 0, 0);
//		_delay_ms(2000);
//		setTime(now[6], 0, 0);
//		_delay_ms(2000);
//		setTime(now[7], 0, 0);
//		_delay_ms(2000);
//		setTime(0, 0, 0);
//		setTime(D1_OCLK, D2_ONE, D3_ITIS);
	}
}

