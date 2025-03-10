
#define BAUD_RATE 115200        // Velocidad de comunicación serial

#include "Caracterizador.h"
#include "Segmentador.h"

Cr_Control c_car;

/* ventana de señales sEMG*/
Sg_canalData data[NUM_CHANNELS];
/* vector de cataceristicas*/
Cr_Caracteristicas veChar[NUM_CHANNELS*NUM_CAR]; 


void setup() {
  Serial.begin(BAUD_RATE);


  for (int i=0;i<NUM_CHANNELS;i++){
    for(int j=0;j<WINDOW_SIZE;j++){
        data[i].canal[j]=(i+1)*(j);
    }
  }

  Cr_Inicie(&c_car, data,veChar);
  Cr_Procese(&c_car);

}

void loop(){

 
  // Array de punteros a funciones

  /*
    for (int i=0;i<NUM_CHANNELS;i++){
      for(int j=0;j<WINDOW_SIZE;j++){
          Serial.print(data[i].canal[j]);
          Serial.print(",");
      }
    Serial.println();
  }
  */

/*
  for(int j=0;j<NUM_CHANNELS*NUM_CAR;j++){
      Serial.print(veChar[j]);
    Serial.print(",");
  }
  Serial.println();
*/

float inicio=millis();
Cr_Procese(&c_car);
float fin=millis();
Serial.println(fin-inicio);
delay(1000);

//Serial.println(NUM_CHANNELS*NUM_CAR);

}