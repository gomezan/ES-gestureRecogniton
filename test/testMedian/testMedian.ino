

#include "Tiempo.h"
#include "display.h"
#include "model.h"
#include "Buffer.h"
#include "Segmentador.h"
#include "Caracterizador.h"
#include <Filtrador.h>

Tm_Control c_tiempo;
Dp_Control c_display;
IA_Control c_modelo;
Buffer_Control c_buff;
Sg_Control c_seg;
Cr_Control c_car;
Fc_Control c_filter;

/*Tabla de periodos */
Tm_Periodo periodos[2];

/*Estados de los filtros digitales */
Fc_PassBandFilterState estados_pb[NUM_CHANNELS];
Fc_TopNotchFilterState estados_tn[NUM_CHANNELS];

/* ventana de señales sEMG*/
Sg_canalData data[NUM_CHANNELS];

/* vector de cataceristicas*/
Cr_Caracteristicas veChar[NUM_CHANNELS*(NUM_CAR_T+NUM_CAR_F)]; 


void setup() {
  Serial.begin(BAUD_RATE);

  Tm_config_timer();

  //Inicializar buffer de datos
  Bf_Inicie(&c_buff,SIZE_BUFFER);
  //Inicialización de periodos
  Tm_Inicie(&c_tiempo,periodos,2);
  //Inicializar display
  Dp_Inicie(&c_display, 0);
  //inicializar modelo
  IA_Inicie(&c_modelo, NN, veChar);
  //  Inicializar modulo de lectura de señales sEMG
  Fc_Inicie(&c_filter,estados_tn, estados_pb);
  //Inicializar segmentador
  Sg_Inicie(&c_seg, 1,data);
  //Inicializar caracterizador
  Cr_Inicie(&c_car, data,veChar);

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

  if (Tm_Hubo_periodo(&c_tiempo,1)){
    Sg_Procese (&c_seg);
    Tm_Baje_periodo(&c_tiempo,2);
    //Serial.println(millis());
  }



/*Revisar si el buffer se llena*/
  if(Bf_Lleno(&c_buff,0)){
      Serial.println("esta lleno");
  }

 

 /*Revisar inferencia*/
 /*
  int a =millis();
  if((a>10000)&&(a<10005)){
       IA_Predict(&c_modelo);
  }
  */   

}