


#define BAUD_RATE 115200        // Velocidad de comunicación serial


#include "Tiempo.h"
#include "EMG.h"


Tm_Control c_tiempo;
EMG_Control c_emg;

Tm_Periodo periodos[1];
EMG_PassBandFilterState estados_pb[NUM_CHANNELS];
EMG_TopNotchFilterState estados_tn[NUM_CHANNELS];

void setup() {
  Serial.begin(BAUD_RATE);

  Tm_config_timer();


  //Inicialización de periodos
  Tm_Inicie(&c_tiempo,periodos,1);
  //Inicializar EMG
  EMG_Inicie(&c_emg, 0, estados_tn, estados_pb);

}

void loop(){

  if (get_atender_flag(&c_tiempo)){
    Tm_Procese(&c_tiempo);
    set_atender_flag(&c_tiempo,NO);
    //Serial.println(millis());
  }

  if (Tm_Hubo_periodo(&c_tiempo,0)){
    EMG_Procese (&c_emg);
    Tm_Baje_periodo(&c_tiempo,0);
  }
    
}