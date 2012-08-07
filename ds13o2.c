#include <avr/io.h>
#include <util/delay.h>
#include "ds1302.h"
#include <stdio.h>
#include  "uart.h"

void ds1302_init(void) {
	DS1302_CLK_DIR_OUT;
	DS1302_RST_DIR_OUT;
	DS1302_IO_DIR_OUT;
}

void ds1302_reset(void) {
	DS1302_CLK_0;
	_delay_us(10);
	DS1302_RST_0;
	_delay_us(10);
	DS1302_RST_1;
	_delay_us(10);
}

void ds1302_write_byte(unsigned char data) {
	unsigned char i;
	for (i = 0; i < 8; i++) {
		DS1302_CLK_0;
		_delay_us(10);
		if (data & 0x01)
			DS1302_IO_1;
		else
			DS1302_IO_0;
		_delay_us(10);
		DS1302_CLK_1;
		_delay_us(10);
		data >>= 1;

	}
}

unsigned char ds1302_read_byte(void) {
	unsigned char i, data;
	data = 0;

	for (i = 0; i < 8; i++) {
		DS1302_CLK_0;
		_delay_us(10);
		data >>= 1;
		if (DS1302_IO_IN)
			data |= 0x80;
		_delay_us(10);
		DS1302_CLK_1;
		_delay_us(10);
	}
	return data;
}

void ds1302_write(unsigned char reg, unsigned char data) {
	DS1302_IO_DIR_OUT;
	ds1302_reset();
	ds1302_write_byte(reg);
	ds1302_write_byte(data);

	DS1302_CLK_0;
	_delay_us(10);
	DS1302_RST_0;
	_delay_us(10);
}

unsigned char ds1302_read(unsigned char reg) {
	unsigned char data;
	DS1302_IO_DIR_OUT;
	ds1302_reset();
	ds1302_write_byte(reg);
	DS1302_IO_DIR_IN;
	data = ds1302_read_byte();
	DS1302_CLK_0;
	_delay_us(10);
	DS1302_RST_0;
	_delay_us(10);

	return data;

}

void gettime(unsigned char *nowtime) {

	unsigned char i;
	DS1302_IO_DIR_OUT;
	ds1302_reset();
	ds1302_write_byte(0xbf);
	DS1302_IO_DIR_IN;
	for (i = 0; i < 7; i++) {
		nowtime[i] = ds1302_read_byte();
		printf("%u %x %u \n", i, nowtime[i], nowtime[i]);
	}
	DS1302_CLK_0;
	_delay_us(10);
	DS1302_RST_0;
	_delay_us(10);

}

void settime(unsigned char *settime) {
	unsigned char i;
	ds1302_write(0x8e, 0);
	ds1302_reset();
	ds1302_write_byte(0xbe);
	for (i = 0; i < 7; i++) {
		ds1302_write_byte(settime[i]);

	}
	ds1302_write_byte(0);
	DS1302_CLK_0;
	_delay_us(10);
	DS1302_RST_0;
	_delay_us(10);
}

