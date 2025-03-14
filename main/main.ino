


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

//float x2[96] = {0.18181163200f, 0.18180530073f, 0.03307736204f, 0.17601142157f, 0.14676175464f, 0.52432184010f, 0.31460674157f, 0.03479513362f, 0.45754606848f, 0.55198577905f, 0.31460674157f, 0.20000000000f, 0.01731488898f, 0.01730909617f, 0.00080212086f, 0.01719017435f, 0.01824061938f, 0.56252658602f, 0.64285714286f, 0.01584523573f, 0.39311186105f, 0.55896004845f, 0.64285714286f, 0.00000000000f, 0.06326084889f, 0.06325683437f, 0.00400200410f, 0.06435212482f, 0.07142328575f, 0.52226322525f, 0.38888888889f, 0.03042219672f, 0.50374501446f, 0.53005128713f, 0.38888888889f, 0.02222222222f, 0.05495117660f, 0.05496216128f, 0.00412961256f, 0.05282909969f, 0.05245186347f, 0.55089874608f, 0.47560975610f, 0.02024463583f, 0.49591158318f, 0.56095447109f, 0.47560975610f, 0.10638297872f, 0.01466523307f, 0.01466611625f, 0.00040486814f, 0.01648795517f, 0.01619854419f, 0.49286222023f, 0.51948051948f, 0.00972142865f, 0.51181865436f, 0.47037909974f, 0.51948051948f, 0.00000000000f, 0.00946008864f, 0.00944657482f, 0.00008991281f, 0.00765338982f, 0.00810879392f, 0.53771041172f, 0.51111111111f, 0.10155391196f, 0.36779725652f, 0.52818608640f, 0.51111111111f, 0.00000000000f, 0.10929857712f, 0.10929459594f, 0.01196882983f, 0.11419571766f, 0.10233392319f, 0.55809205662f, 0.39325842697f, 0.01787314016f, 0.63526040099f, 0.58490564115f, 0.39325842697f, 0.45833333333f, 0.32721901422f, 0.32722379725f, 0.10709320421f, 0.33108534521f, 0.24608520539f, 0.42430975687f, 0.31818181818f, 0.01847540449f, 0.53703093234f, 0.45853850002f, 0.31818181818f, 0.79787234043f};

void setup() {
  Serial.begin(BAUD_RATE);

  Tm_config_timer();

  //Inicialización de periodos
  Tm_Inicie(&c_tiempo,periodos,3);
  //Inicializar display
  Dp_Inicie(&c_display, 0);
  //inicializar modelo
  IA_Inicie(&c_modelo, NN);
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
       IA_Predict(&c_modelo,x2);
  }
  */   

}