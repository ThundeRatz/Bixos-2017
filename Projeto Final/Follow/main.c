#include "math.h"
#include "sensors.h"
#include "motors.h"
#include "timer.h"

void calculateCm(){
  for(int i = 0; i < 5; i++){ /*armazenando distancia lida pelos sensores*/
      if(distance[i]*5.0/1023 > 0.9){
        distCm[i] = 48.75*pow(distance[i], -1.26);
      }
      else{
        distCm[i] = 48.10*pow(distance[i], -2.63);
      }
    }
}

int main() {
  timer_init();  /*"iniciando" as bibliotecas*/
  motors_init();
  sensors_init();

  long int timeAVR = get_tick(); /*Armazenando o tempo inicial*/
  float distCm[5] = {0};   
  float error;
  float kp = 1;
  float power = 100;
  
  for (;;){
    update_distance(); /*Atualizando sensores*/
    
    calculateCm(); /*conversao de leitura analogica para distancia em cm*/

    if(distCm[1] > 100 && distCm[2] > 100 && distCm[3] > 100){
      motors(110, -110);
    }
    else{
      while(line[0] > 200 && line[1] > 200){
        update_line();
        calculateCm();
        error = distCm[1] - distCm[3];
        motors(power + kp*error, power - kp*error);
        _delay_ms(10);
      }
      motors(-200, -200);
      _delay_ms(500);
      motors(0, 0);
    }
    _delay_ms(10);
  }
  return 0;

}