

#define BAUD_RATE 115200        // Velocidad de comunicación serial

#include "Tiempo.h"
#include "display.h"
#include "model.h"
#include "Caracterizador.h"


Tm_Control c_tiempo;
Dp_Control c_display;
IA_Control c_modelo;


/* vector de cataceristicas*/
Cr_Caracteristicas veChar[NUM_CHANNELS*NUM_CAR]={
0.265038, 0.265049, 0.070282, 0.249603, 0.256334, 0.497321, 0.426966, 0.058930, 0.487868, 0.534802, 0.426966, 0.357895, 0.503627, 0.503627, 0.261026, 0.485213, 0.457620, 0.538670, 0.485714, 0.015957, 0.462494, 0.556349, 0.485714, 0.489130, 0.166907, 0.166907, 0.027859, 0.169718, 0.211580, 0.525187, 0.422222, 0.034286, 0.572080, 0.546422, 0.422222, 0.322222, 0.153360, 0.153407, 0.026306, 0.151844, 0.150257, 0.544615, 0.463415, 0.015729, 0.529367, 0.561324, 0.463415, 0.553191, 0.309484, 0.309513, 0.098605, 0.331152, 0.312818, 0.490639, 0.428571, 0.006103, 0.520791, 0.430686, 0.428571, 0.858586, 0.145204, 0.145159, 0.021080, 0.137913, 0.191056, 0.575357, 0.588889, 0.035326, 0.474200, 0.577046, 0.588889, 0.546392, 0.174909, 0.174908, 0.030628, 0.187945, 0.196803, 0.574814, 0.471910, 0.014369, 0.661101, 0.612911, 0.471910, 0.708333, 0.203287, 0.203295, 0.041342, 0.191285, 0.173571, 0.455416, 0.431818, 0.028958, 0.573810, 0.504145, 0.431818, 0.627660
}; 

Tm_Periodo periodos[2];

void setup() {
  Serial.begin(BAUD_RATE);

  Tm_config_timer();


  //Inicialización de periodos
  Tm_Inicie(&c_tiempo,periodos,2);
  //Inicializar display
  Dp_Inicie(&c_display, 0);
  //inicializar modelo
  IA_Inicie(&c_modelo, NN, veChar);

}

void loop(){

  if (get_atender_flag(&c_tiempo)){
    Tm_Procese(&c_tiempo);
    set_atender_flag(&c_tiempo,NO);
    //Serial.println(millis());
  }

  if (Tm_Hubo_periodo(&c_tiempo,0)){

    Dp_Procese (&c_display);
    Tm_Baje_periodo(&c_tiempo,0);
    //Serial.println(millis());
  }
   
  int a =millis();
  if((a>10000)&&(a<10005)){
       IA_Predict(&c_modelo);
  }
      

}