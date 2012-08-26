#include <avr/io.h>
#include "macro.h"
#include "display.h"

void initOutput() {
	SHIFTREG_ENABLE_OUTPUTS;
}

void setRegisters(char word) {
	for (int i = 0; i < 8; i++) {
		SHIFTREG_CLK_0;
		char data = word << i;
		if (data & 0x80) {
			SHIFTREG_DATA_1;
		} else {
			SHIFTREG_DATA_0;
		}
		SHIFTREG_CLK_1;
	}
}

void setR(uint32_t word) {
	for (int i = 0; i < 24; i++) {
		SHIFTREG_CLK_0;
		uint32_t data = word << i;
		if (data & 0x800000) {
			SHIFTREG_DATA_1;
		} else {
			SHIFTREG_DATA_0;
		}
		SHIFTREG_CLK_1;
	}
}

void setTime(char reg1, char reg2, char reg3) {
	SHIFTREG_STRB_0;
	setRegisters(reg3);
	setRegisters(reg2);
	setRegisters(reg1);
	SHIFTREG_STRB_1;
}
