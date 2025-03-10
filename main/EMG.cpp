/* EMG.c    implementaci�n del módulo de adqusición de señales */

#include <Tiempo.h>
#include "EMG.h"
#include "Varios.h"

//
extern Tm_Control c_tiempo;


/* Rutina para iniciar el módulo (su estructura de datos) */   
char EMG_Inicie (EMG_Control *emg, 
                Tm_Num n_periodo,
                EMG_TopNotchFilterState *tn, 
                EMG_PassBandFilterState *pb)
   {

   //inicializar estados de filtros   
   emg->tn = tn;
   emg->pb = pb;   
   
   //Inicializar periodo
   emg->n_periodo = n_periodo;
   if ( !Tm_Inicie_periodo(&c_tiempo, n_periodo, PERIODO_EMG) )
      return NO;

   return SI;
   };


                  
/* Rutina para procesar el módulo (dentro del loop de polling) */				
void EMG_Procese (EMG_Control *emg){

   float inputSignals[NUM_CHANNELS];
   float outputSignals[NUM_CHANNELS];

   // Leer valores de los pines analógicos
   for (int i = 0; i < NUM_CHANNELS; i++) {
       inputSignals[i] = analogRead(analogPins[i]);
   }
   // Aplicar el filtro top notch a los 8 canales
   for (int i = 0; i < NUM_CHANNELS; i++) {

      EMG_TopNotchFilterState *tn = emg->tn + i;
       outputSignals[i] = topNotch(inputSignals[i], tn);
   }
   // Aplicar el filtro pasa bandas a los 8 canales
   for (int i = 0; i < NUM_CHANNELS; i++) {
      EMG_PassBandFilterState *pb = emg->pb + i;
      outputSignals[i] = pasabandas(outputSignals[i], pb->states);
   }

   // Imprimir los valores de las salidas de los 8 canales
   /*
    for (int i = 0; i < NUM_CHANNELS; i++) {
        Serial.print(outputSignals[i], 4);
        if(i!=NUM_CHANNELS-1){
           Serial.print(","); 
        } else{
            Serial.println();
        }
        
    }

    */
    
   
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
