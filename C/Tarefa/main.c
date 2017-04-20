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

int main() {
    sensors_init();
    motors_init();
    sei();
    wdt_reset();
    wdt_disable();

    for (;;) {
        int sensorlatd = get_sensor(SENSOR_LD);
        int sensorlate = get_sensor(SENSOR_LE);
        int sensorfrd = get_sensor(SENSOR_FD);
        int sensorfre = get_sensor(SENSOR_LD);
        if (sensorlatd < sensorfrd) && (sensorlate < sensorfre) {
			//quando o objeto está quase alinhado a frente
            if (sensorfrd<650) && (sensorfre<650){
				if (sensorfre==sensorfrd)
                    motors(255, 255);
                else if(sensorfre<sensorfrd)
					motors(255, 100);
			    else
					motors(100, 255);
			}
			else if (sensorfrd<850) && (sensorfre<850){
                if (sensorfre==sensorfrd)
                    motors(255, 255);
                else if(sensorfre<sensorfrd)
					motors(255, 200);
				else
					motors(200, 255);
            }

			else
                motors(255, 255);
        }
        else if (sensorlate>sensorlatd) // mais esquerda
			motors(-255, 255);
        else //mais direita
			motors(255, -255);

    }

    return 0;
}
