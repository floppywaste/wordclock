#include <avr/io.h>
#include "macro.h"
#include "display.h"

void initOutput() {
	SHIFTREG_ENABLE_OUTPUTS;
}

void setRegister(uint32_t word) {
	SHIFTREG_STRB_0;
	for (int i = 0; i < 24; i++) {
		SHIFTREG_CLK_0;
		uint32_t data = word << i;
		if (data & 0x80000000) {
			SHIFTREG_DATA_1;
		} else {
			SHIFTREG_DATA_0;
		}
		SHIFTREG_CLK_1;
	}
	SHIFTREG_STRB_1;
}
