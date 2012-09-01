

#define BUTTON_PORT PORTD       /* PORTx - register for button output */
#define BUTTON_PIN PIND         /* PINx - register for button input */
#define HOUR_BTN PD6          /* bit for button input/output */
#define MINUTE_BTN PD7          /* bit for button input/output */

#define DEBOUNCE_TIME 20        /* time to wait while "de-bouncing" button */
#define LOCK_INPUT_TIME 150    /* time to wait after a button press */

int buttonIsPressed(uint8_t btn);

void enableButtons();
void enableButtonInterrupts();

void delayMs(uint16_t ms);

