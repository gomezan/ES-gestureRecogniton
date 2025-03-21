


#define BAUD_RATE 115200        // Velocidad de comunicación serial

#include "Tiempo.h"
#include "display.h"
#include "model.h"
#include "EMG.h"
#include "Buffer.h"
#include "Segmentador.h"
#include "Caracterizador.h"

Tm_Control c_tiempo;
Dp_Control c_display;
IA_Control c_modelo;
EMG_Control c_emg;
Buffer_Control c_buff;
Sg_Control c_seg;
Cr_Control c_car;

/*Tabla de periodos */
Tm_Periodo periodos[3];

/*Estados de los filtros digitales */
EMG_PassBandFilterState estados_pb[NUM_CHANNELS];
EMG_TopNotchFilterState estados_tn[NUM_CHANNELS];

/* ventana de señales sEMG*/
Sg_canalData data[NUM_CHANNELS];

/* vector de cataceristicas*/
Cr_Caracteristicas veChar[NUM_CHANNELS*NUM_CAR]; 


void setup() {
  Serial.begin(BAUD_RATE);

  Tm_config_timer();

  //Inicialización de periodos
  Tm_Inicie(&c_tiempo,periodos,3);
  //Inicializar display
  Dp_Inicie(&c_display, 0);
  //inicializar modelo
  IA_Inicie(&c_modelo, NN, veChar);
  //  Inicializar modulo de lectura de señales sEMG
  EMG_Inicie(&c_emg, 1, estados_tn, estados_pb);
  //Inicializar buffer de datos
  Bf_Inicie(&c_buff,SIZE_BUFFER);
  //Inicializar segmentador
  Sg_Inicie(&c_seg, 2,data);
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
    EMG_Procese (&c_emg);
    Tm_Baje_periodo(&c_tiempo,1);
  }

  if (Tm_Hubo_periodo(&c_tiempo,2)){
    Sg_Procese (&c_seg);
    Tm_Baje_periodo(&c_tiempo,2);
    //Serial.println(millis());
  }



/*Revisar si el buffer se llena*/
/*
  if(Bf_Lleno(&c_buff,0)){
      Serial.println("esta lleno");
  }
*/
 

 /*Revisar inferencia*/
 /*
  int a =millis();
  if((a>10000)&&(a<10005)){
       IA_Predict(&c_modelo);
  }
  */   

}