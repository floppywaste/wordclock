#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "buttons.h"

void enableButtons() {
	DDRD &= ~(1 << DDD6);
	DDRD &= ~(1 << DDD7);
	/*
	 * Pull buttons high
	 */
	BUTTON_PORT |= _BV(HOUR_BTN);
	BUTTON_PORT |= _BV(MINUTE_BTN);
}

/*
 * enable hour and minute buttons for external interrupt
 */
void enableButtonInterrupts() {

	PCICR |= (1 << PCIE2);
	PCMSK2 |= (1 << PCINT22);
	PCMSK2 |= (1 << PCINT23);

	sei();
}

/*
 * Returns 1 if the specified button was pressed, 0 otherwise.
 */
int button_is_pressed(uint8_t btn) {
	if (bit_is_clear(BUTTON_PIN, btn)) {
		delay_ms(DEBOUNCE_TIME);
		if (bit_is_clear(BUTTON_PIN, btn))
			return 1;
	}

	return 0;
}

void delay_ms(uint16_t ms) {
	while (ms) {
		_delay_ms(1);
		ms--;
	}
}
