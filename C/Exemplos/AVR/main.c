#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

#include "setup.h"

#define LED_ON()     LED_PORTx |=  (1 << LED_PIN)
#define LED_OFF()    LED_PORTx &= ~(1 << LED_PIN)
#define LED_TOGGLE() LED_PORTx ^=  (1 << LED_PIN)

int main() {
	setup();

	for (;;) {
		LED_TOGGLE();
		_delay_ms(500);
	}
}
