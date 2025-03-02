/* EMG.c    implementaci�n del módulo de adqusición de señales */

#include <Tiempo.h>
#include "EMG.h"
#include "Varios.h"

extern Tm_Control c_tiempo;

// Definimos 8 vectores globales de tipo float
float vector1[100], vector2[100], vector3[100], vector4[100],
      vector5[100], vector6[100], vector7[100], vector8[100];

// Función para inicializar los vectores
void inicializar_vectores() {
    for (int i = 0; i < 100; i++) {
        vector1[i] = (i + 1) * 1.0f;
        vector2[i] = (i + 1) * 2.0f;
        vector3[i] = (i + 1) * 3.0f;
        vector4[i] = (i + 1) * 4.0f;
        vector5[i] = (i + 1) * 5.0f;
        vector6[i] = (i + 1) * 6.0f;
        vector7[i] = (i + 1) * 7.0f;
        vector8[i] = (i + 1) * 8.0f;
    }
}

/* Rutina para iniciar el módulo (su estructura de datos) */   
char EMG_Inicie (EMG_Control *emg, 
                Tm_Num n_periodo,
                EMG_TopNotchFilterState *tn, 
                EMG_PassBandFilterState *pb)
   {

   //inicializar estados de filtros   
   emg->tn = tn;
   emg->pb = pb;

   inicializar_vectores();   
   
   //Inicializar periodo
   emg->n_periodo = n_periodo;
   if ( !Tm_Inicie_periodo(&c_tiempo, n_periodo, PERIODO_BASE) )
      return NO;

   return SI;
   };


                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void EMG_Procese (EMG_Control *emg){

   float inputSignals[NUM_CHANNELS];
   float outputSignals[NUM_CHANNELS];

   // Leer valores de los pines 
    inputSignals[0] = vector1[emg->cont];
    inputSignals[1] = vector2[emg->cont];
    inputSignals[2] = vector3[emg->cont];
    inputSignals[3] = vector4[emg->cont];
    inputSignals[4] = vector5[emg->cont];
    inputSignals[5] = vector6[emg->cont];
    inputSignals[6] = vector7[emg->cont];
    inputSignals[7] = vector8[emg->cont];

    emg->cont=emg->cont+1;
    if(emg->cont>100){
      emg->cont=0;
    }

   // Imprimir los valores de las salidas de los 8 canales
    for (int i = 0; i < NUM_CHANNELS; i++) {
        Serial.print(inputSignals[i], 4);
        if(i!=NUM_CHANNELS-1){
           Serial.print(","); 
        } else{
            Serial.println();
        }
        
    }
   
};


   
float topNotch(float input, EMG_TopNotchFilterState* state) {
   float x = input - -1.35553798 * state->z1 - 0.85952856 * state->z2;
   float output = 0.92976428 * x + -1.35553798 * state->z1 + 0.92976428 * state->z2;

   // Actualizar los estados
   state->z2 = state->z1;
   state->z1 = x;

   return output;
}


float pasabandas(float input, EMG_FilterState* states){
 float output = input;

   EMG_FilterState* state = &states[0];
   float x = output - -1.55168605*state->z1 - 0.60217825*state->z2;
   output = 0.18484459*x + -0.36968919*state->z1 + 0.18484459*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[1];
   x = output - -1.55937726*state->z1 - 0.61011176*state->z2;
   output = 1.00000000*x + -2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[2];
   x = output - -1.57478541*state->z1 - 0.62600594*state->z2;
   output = 1.00000000*x + -2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[3];
   x = output - -1.59795635*state->z1 - 0.64990921*state->z2;
   output = 1.00000000*x + -2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[4];
   x = output - -1.62894391*state->z1 - 0.68187875*state->z2;
   output = 1.00000000*x + -2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[5];
   x = output - -1.66779008*state->z1 - 0.72195989*state->z2;
   output = 1.00000000*x + -2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[6];
   x = output - -1.71449515*state->z1 - 0.77015521*state->z2;
   output = 1.00000000*x + -2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[7];
   x = output - -1.76897548*state->z1 - 0.82638079*state->z2;
   output = 1.00000000*x + -2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[8];
   x = output - -1.83100627*state->z1 - 0.89040697*state->z2;
   output = 1.00000000*x + -2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[9];
   x = output - -1.90014757*state->z1 - 0.96178173*state->z2;
   output = 1.00000000*x + -2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[10];
   x = output - 1.97506052*state->z1 - 0.97521697*state->z2;
   output = 1.00000000*x + 2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[11];
   x = output - 1.97566705*state->z1 - 0.97582352*state->z2;
   output = 1.00000000*x + 2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[12];
   x = output - 1.97686545*state->z1 - 0.97702197*state->z2;
   output = 1.00000000*x + 2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[13];
   x = output - 1.97862684*state->z1 - 0.97878344*state->z2;
   output = 1.00000000*x + 2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[14];
   x = output - 1.98090898*state->z1 - 0.98106568*state->z2;
   output = 1.00000000*x + 2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[15];
   x = output - 1.98365733*state->z1 - 0.98381418*state->z2;
   output = 1.00000000*x + 2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[16];
   x = output - 1.98680653*state->z1 - 0.98696355*state->z2;
   output = 1.00000000*x + 2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[17];
   x = output - 1.99028187*state->z1 - 0.99043910*state->z2;
   output = 1.00000000*x + 2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;
 

   state = &states[18];
   x = output - 1.99400096*state->z1 - 0.99415844*state->z2;
   output = 1.00000000*x + 2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

   state = &states[19];
   x = output - 1.99787543*state->z1 - 0.99803319*state->z2;
   output = 1.00000000*x + 2.00000000*state->z1 + 1.00000000*state->z2;
   state->z2 = state->z1;
   state->z1 = x;

 return output;

}


/* ===== RUTINAS DE INTERFAZ ====== */



/* == FIN DE RUTINAS DE INTERFAZ == */
