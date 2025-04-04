


#define BAUD_RATE 115200        // Velocidad de comunicación serial


#include "Tiempo.h"
#include "EMG.h"
#include "Filtrador.h"
#include "Buffer.h"
#include "Segmentador.h"


Tm_Control c_tiempo;
EMG_Control c_emg;
Buffer_Control c_buff;
Fc_Control c_filter;
Sg_Control c_seg;

/*Tabla de periodos */
Tm_Periodo periodos[2];

/*Estados de los filtros digitales */
Fc_PassBandFilterState estados_pb[NUM_CHANNELS];
Fc_TopNotchFilterState estados_tn[NUM_CHANNELS];

/* ventana de señales sEMG*/
Sg_canalData data[NUM_CHANNELS];

void setup() {
  Serial.begin(BAUD_RATE);

  //Configuración del timer
  Tm_config_timer();

  //Inicialización de periodos
  Tm_Inicie(&c_tiempo,periodos,2);
  //Inicializar EMG
  EMG_Inicie(&c_emg, 0);
  //Inicializar buffer de datos
  Bf_Inicie(&c_buff,SIZE_BUFFER);
  //Incializar filtrador
  Fc_Inicie(&c_filter,estados_tn, estados_pb);
  //Inicializar segmentador
  Sg_Inicie(&c_seg, 1,data);

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

  if (Tm_Hubo_periodo(&c_tiempo,1)){
    Sg_Procese (&c_seg);
    Tm_Baje_periodo(&c_tiempo,1);
  }

  if(Bf_Lleno(&c_buff,0)){
      Serial.println("esta lleno");
  }

    
}