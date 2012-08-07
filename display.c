#include <avr/io.h>

#define SET(port,b) (port) |= (1<<(b))
#define CLR(port,b) (port) &= ~(1<<(b))


void initOutput() {
	DDRD = (1 << DDD3) | (1 << DDD4) | (1 << DDD5);
}

void setRegisters(char word) {
	SET(PORTD, PD4);
	for (int i = 0; i < 8; i++) {
		CLR(PORTD, PD5);
		char data = word << i;
		if (data & 0x80) {
			SET(PORTD, PD3);
		} else {
			CLR(PORTD, PD3);
		}
		SET(PORTD, PD5);
	}
}

void setTime(char reg1, char reg2, char reg3) {
	setRegisters(reg3);
	setRegisters(reg2);
	setRegisters(reg1);
}
