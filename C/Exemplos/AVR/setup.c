#include "setup.h"

void setup() {
	LED_DDRx |= (1 << LED_PIN);

	LED_PORTx &= ~(1 << LED_PIN);
}
