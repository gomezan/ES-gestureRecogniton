


#define BAUD_RATE 115200        // Velocidad de comunicación serial

#include "Tiempo.h"
#include "display.h"
#include "model.h"
#include "EMG.h"

Tm_Control c_tiempo;
Dp_Control c_display;
IA_Control c_modelo;
EMG_Control c_emg;

Tm_Periodo periodos[2];

EMG_PassBandFilterState estados_pb[NUM_CHANNELS];
EMG_TopNotchFilterState estados_tn[NUM_CHANNELS];

float x0[84] = {0.07179141265f, 0.07176098202f, 0.00516047294f, 0.06232322494f, 0.04402086568f, 0.42696629213f, 0.38042323159f, 0.42696629213f, 0.00000000000f, 0.00427576832f, 0.04985663299f, 0.06700493265f, 0.02486227392f, 0.02486144577f, 0.00061832756f, 0.02646058037f, 0.03258088467f, 0.47777777778f, 0.49242699870f, 0.47777777778f, 0.00000000000f, 0.00052471143f, 0.02978401219f, 0.02716190072f, 0.01344048764f, 0.01343785970f, 0.00046357471f, 0.01234224124f, 0.01425627637f, 0.56097560976f, 0.47228669853f, 0.56097560976f, 0.00000000000f, 0.00036780950f, 0.01315303985f, 0.01328867443f, 0.03445092215f, 0.03445433878f, 0.00162397225f, 0.03073017386f, 0.02441391626f, 0.48051948052f, 0.59347318558f, 0.48051948052f, 0.04040404040f, 0.00109169254f, 0.04558184639f, 0.04286537589f, 0.06553221947f, 0.06554323019f, 0.00430033339f, 0.06707897294f, 0.06231049667f, 0.36666666667f, 0.39861676643f, 0.36666666667f, 0.09278350515f, 0.00381235068f, 0.06941407321f, 0.07039783598f, 0.08860976921f, 0.08858866200f, 0.00786745927f, 0.09320228240f, 0.04673397277f, 0.19101123596f, 0.63618926605f, 0.19101123596f, 0.05208333333f, 0.00386484171f, 0.05188357938f, 0.07823272481f, 0.01487018180f, 0.01486634398f, 0.00022219171f, 0.01375236424f, 0.01211770190f, 0.50000000000f, 0.52488123874f, 0.50000000000f, 0.00000000000f, 0.00020060256f, 0.01514436134f, 0.01561168225f};

void setup() {
  Serial.begin(BAUD_RATE);

  Tm_config_timer();


  //Inicialización de periodos
  Tm_Inicie(&c_tiempo,periodos,2);
  //Inicializar display
  Dp_Inicie(&c_display, 0);
  //inicializar modelo
  IA_Inicie(&c_modelo, NN);
  //  Inicializar modulo de lectura de señales sEMG
  EMG_Inicie(&c_emg, 1, estados_tn, estados_pb);
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

 /*  
  int a =millis();
  if((a>10000)&&(a<10005)){
       IA_Predict(&c_modelo,x0);
  }
   */   

}