#include "DS1302.h"
#include <avr/io.h>
#include <util/delay.h>
#include "macro.h"

void initClock() {
	DS1302_CLK_DIR_OUT;
	DS1302_RST_DIR_OUT;
}

void _write_out(uint8_t value) {
	SET(DDRB, DDB2);
	for (int i = 0; i < 8; i++) {
		DS1302_CLK_0
		_delay_ms(1);
		if (value & 0x01) {
			DS1302_IO_1
		} else {
			DS1302_IO_0
		}
		_delay_ms(1);
		DS1302_CLK_1
		_delay_ms(1);
		value >>= 1;
	}
}

uint8_t _register_bcd_to_dec_(uint8_t reg, uint8_t high_bit) {
	uint8_t val = read_register(reg);
	uint8_t mask = (1 << (high_bit + 1)) - 1;
	val &= mask;
	val = (val & 15) + 10 * ((val & (15 << 4)) >> 4);
	return val;
}

uint8_t _register_bcd_to_dec(uint8_t reg) {
	return _register_bcd_to_dec_(reg, 7);
}

void _register_dec_to_bcd_(uint8_t reg, uint8_t value, uint8_t high_bit) {
	uint8_t regv = read_register(reg);
	uint8_t mask = (1 << (high_bit + 1)) - 1;

	/* convert value to bcd in place */
	uint8_t tvalue = value / 10;
	value = value % 10;
	value |= (tvalue << 4);

	/* replace high bits of value if needed */
	value &= mask;
	value |= (regv &= ~mask);

	write_register(reg, value);
}

void _register_dec_to_bcd(uint8_t reg, uint8_t value) {
	_register_dec_to_bcd_(reg, value, 7);
}

uint8_t _read_in() {
	uint8_t input_value = 0;
	DS1302_IO_DIR_IN
	DS1302_CLK_0
	for (int i = 0; i < 8; ++i) {
		if (DS1302_IO_IN_1)
			input_value |= (1 << i);
		DS1302_CLK_1
		_delay_ms(1);
		DS1302_CLK_0
	}

	return input_value;
}

uint8_t read_register(uint8_t reg) {
	uint8_t cmd_byte = 129; /* 1000 0001 */
	uint8_t reg_value;
	cmd_byte |= (reg << 1);

	DS1302_CLK_0
	DS1302_RST_1
	_write_out(cmd_byte);
	reg_value = _read_in();

	DS1302_RST_0

	return reg_value;
}

void write_register(uint8_t reg, uint8_t value) {
	uint8_t cmd_byte = (128 | (reg << 1));

	DS1302_CLK_0
	DS1302_RST_1

	_write_out(cmd_byte);
	_write_out(value);

	DS1302_RST_0
}

void halt(bool enable)
{
  uint8_t sec = read_register(SEC_REG);
  sec &= ~(1 << 7);
  sec |= (enable << 7);
  write_register(SEC_REG, sec);
}

/*** Get time ***/

uint8_t getSeconds() {
	return _register_bcd_to_dec_(SEC_REG, 6);
}

uint8_t getMinutes() {
	return _register_bcd_to_dec(MIN_REG);
}

uint8_t getHour() {
	uint8_t hr = read_register(HR_REG);
	uint8_t adj;
	if (hr & 128) /* 12-hour mode */
		adj = 12 * ((hr & 32) >> 5);
	else
		/* 24-hour mode */
		adj = 10 * ((hr & (32 + 16)) >> 4);
	hr = (hr & 15) + adj;
	return hr;
}

uint8_t getDate() {
	return _register_bcd_to_dec_(DATE_REG, 5);
}

uint8_t getMonth() {
	return _register_bcd_to_dec_(MON_REG, 4);
}

uint8_t getDay() {
	return _register_bcd_to_dec_(DAY_REG, 2);
}

uint16_t getYear() {
	return 2000 + _register_bcd_to_dec(YR_REG);
}

/*** Set time ***/

void seconds(uint8_t sec) {
	_register_dec_to_bcd_(SEC_REG, sec, 6);
}

void minutes(uint8_t min) {
	_register_dec_to_bcd_(MIN_REG, min, 6);
}

void hour(uint8_t hr) {
	write_register(HR_REG, 0); /* set 24-hour mode */
	_register_dec_to_bcd_(HR_REG, hr, 5);
}

void date(uint8_t date) {
	_register_dec_to_bcd_(DATE_REG, date, 5);
}

void month(uint8_t mon) {
	_register_dec_to_bcd_(MON_REG, mon, 4);
}

void day(uint8_t day) {
	_register_dec_to_bcd_(DAY_REG, day, 2);
}

void year(uint16_t yr) {
	yr -= 2000;
	_register_dec_to_bcd(YR_REG, yr);
}

void addMinutes(uint8_t mins) {
	uint8_t newMinutes = getMinutes() + mins;
	if (newMinutes > 59)
		newMinutes -= 60;
	minutes(newMinutes);
}

void addHours(uint8_t hours) {
	uint8_t newHours = getHour() + hours;
	if (newHours > 23)
		newHours -= 24;
	hour(newHours);
}
