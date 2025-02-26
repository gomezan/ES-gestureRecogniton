


#define BAUD_RATE 115200        // Velocidad de comunicación serial

#define INPUT_PIN0 A0
#define INPUT_PIN1 A1
#define INPUT_PIN2 A2
#define INPUT_PIN3 A3
#define INPUT_PIN4 A4
#define INPUT_PIN5 A5
#define INPUT_PIN6 A8
#define INPUT_PIN7 A9 

#include "Tiempo.h"

short sensor_value0 = 0;
short sensor_value1 = 0;
short sensor_value2 = 0;
short sensor_value3 = 0;
short sensor_value4 = 0;
short sensor_value5 = 0;
short sensor_value6 = 0;
short sensor_value7 = 0;



Tm_Control c_tiempo;

void setup() {
  Serial.begin(BAUD_RATE);

  Tm_config_timer();

  Tm_Periodo periodos[1];

}

void loop(){

}