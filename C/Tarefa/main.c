/**
 * Processo Seletivo 2017 - main.c
 *
 * Equipe ThundeRatz de Robótica
 * 03/2017
 */

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "sensors.h"
#include "motors.h"
int map(int formerValue, int formerMin, int formerMax, int newMin, int newMax){
	long int newValue;
	newValue = (long int) (formerValue - formerMin)*(newMax - newMin);
	newValue /= (formerMax - formerMin);
	newValue += newMin;
	return (int)newValue;
}

int main() {
	sensors_init();
	motors_init();
	sei();
	wdt_reset();
	wdt_disable();
	int le,ld,fe,fd,dif;

	for (;;) {
		le = get_sensor (SENSOR_LE);
		ld = get_sensor (SENSOR_LD);
		fe = get_sensor (SENSOR_LE);
		fd = get_sensor (SENSOR_LE);
		if (fe > 300 && fd > 300){
			motors(255,255);
		}
		else if (le > 300){
			motors(-255,255);
		}
		else if (ld > 300){
			motors(255,-255);
		}
		else {
			dif = map (fe-fd,-300,300,-70,70);
			motors(200-dif,200+dif);

		}
		_delay_ms(10);
	}

	return 0;
}
