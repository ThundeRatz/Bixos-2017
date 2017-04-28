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

#define SensorMIN 400
#define SensorMIN2 600

int main() {
	sensors_init();
	motors_init();
	sei();
	wdt_reset();
	wdt_disable();

	int sensorFE = get_sensor(SENSOR_FE);
	int sensorFD = get_sensor(SENSOR_FD);
	int sensorLE = get_sensor(SENSOR_LE);
	int sensorLD = get_sensor(SENSOR_LD);

	for (;;){
		if (sensorFE > SensorMIN || sensorFD > SensorMIN) {
			motors(255,255);
			if (sensorFE > sensorFD && sensorFE > SensorMIN2)
				motors(180,255);
			if (sensorFD > sensorFE && sensorFD > SensorMIN2)
				motors(255,180);				
		}
		else if (sensorLE > SensorMIN)
			motors(0,255);
		else if (sensorLD > SensorMIN)
			motors(255,0);
		else
			motors(255,-255);		
	}


	_delay_ms(10);


	return 0;
}
