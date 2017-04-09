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

#define THRESHOLD_FE 50
#define THRESHOLD_FD 50
#define THRESHOLD_LE 400
#define THRESHOLD_LD 400

int main() {
	sensors_init();
	motors_init();
	sei();
	wdt_reset();
	wdt_disable();

	for (;;) {
		if(get_sensor(SENSOR_FE) < THRESHOLD_FE || get_sensor(SENSOR_FD) < THRESHOLD_FD){ //se tiver oponente na frente (Threshold em CM)
			while(get_sensor(SENSOR_LE) > THRESHOLD_LE || get_sensor(SENSOR_LD) > THRESHOLD_LD){   //vai pra frente até a borda do dojo (branco é leitura pequena)
				motors(150, 150);
			}
			motors(-255, -255);   //chegou até a borda do dojo. Dar um pouco de ré e repetir a rotina
			_delay_ms(200);
		}
		else{                           //se não tiver oponente na frente, ficar girando
			motors(255, -255);
		}
		_delay_ms(10);
	}

	return 0;
}
